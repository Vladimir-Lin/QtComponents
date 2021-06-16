#include <qtcomponents.h>
#include "nPictureFlowPrivate.hpp"

PictureFlowSoftwareRenderer:: PictureFlowSoftwareRenderer (void             )
                            : PictureFlowAbstractRenderer (                 )
                            , size                        (0,0              )
                            , bgcolor                     (qRgb(255,255,255))
                            , effect                      (-1               )
                            , blankSurface                (0                )
{
}

PictureFlowSoftwareRenderer::~PictureFlowSoftwareRenderer(void)
{
  surfaceCache.clear() ;
  buffer = QImage()    ;
  delete blankSurface  ;
}

void PictureFlowSoftwareRenderer::paint(void)
{
  if (!widget) return;
  if (widget->size() != size) init() ;

  if(state->backgroundColor != bgcolor)
  {
    bgcolor = state->backgroundColor;
    surfaceCache.clear();
  }

  if((int)(state->reflectionEffect) != effect)
  {
    effect = (int)state->reflectionEffect;
    surfaceCache.clear();
  }

  if(dirty)
    render();

  QPainter painter(widget);
  painter.drawImage(QPoint(0,0), buffer);
}

void PictureFlowSoftwareRenderer::init()
{
  if(!widget)
    return;

  surfaceCache.clear();
  blankSurface = 0;

  size = widget->size();
  int ww = size.width();
  int wh = size.height();
  int w = (ww+1)/2;
  int h = (wh+1)/2;

  buffer = QImage(ww, wh, iFormat);
  buffer.fill(bgcolor);

  rays.resize(w*2);
  for(int i = 0; i < w; i++)
  {
    PFreal gg = ((PFREAL_ONE >> 1) + i * PFREAL_ONE) / (2*h);
    rays[w-i-1] = -gg;
    rays[w+i] = gg;
  }

  dirty = true;
}

static QRgb blendColor(QRgb c1, QRgb c2, int blend)
{
  int r = qRed(c1) * blend/256 + qRed(c2)*(256-blend)/256;
  int g = qGreen(c1) * blend/256 + qGreen(c2)*(256-blend)/256;
  int b = qBlue(c1) * blend/256 + qBlue(c2)*(256-blend)/256;
  return qRgb(r, g, b);
}

static QImage * prepareSurface                         (
                  const QImage *      slideImage       ,
                  int                 w                ,
                  int                 h                ,
                  QRgb                bgcolor          ,
                  int                 reflectionEffect ,
                  enum QImage::Format iFormat          )
{
  Qt::TransformationMode mode = Qt::SmoothTransformation;
  QImage img = slideImage->scaled(w, h, Qt::IgnoreAspectRatio, mode);

  // slightly larger, to accomodate for the reflection
  int hs = h * 2;
  int hofs = h / 3;

  // offscreen buffer: black is sweet
  QImage* result = new QImage(hs, w, iFormat) ;
  result->fill(bgcolor);

  // transpose the image, this is to speed-up the rendering
  // because we process one column at a time
  // (and much better and faster to work row-wise, i.e in one scanline)
  for(int x = 0; x < w; x++)
    for(int y = 0; y < h; y++)
      result->setPixel(hofs + y, x, img.pixel(x, y));

  if (reflectionEffect != 0) {
    // create the reflection
    int ht = hs - h - hofs;
    int hte = ht;
    for(int x = 0; x < w; x++)
      for(int y = 0; y < ht; y++)
      {
        QRgb color = img.pixel(x, img.height()-y-1);
        result->setPixel(h+hofs+y, x, blendColor(color,bgcolor,128*(hte-y)/hte));
      }

    if (reflectionEffect == 2) {
      // blur the reflection everything first
      // Based on exponential blur algorithm by Jani Huhtanen
      QRect rect(hs/2, 0, hs/2, w);
      rect &= result->rect();

      int r1 = rect.top();
      int r2 = rect.bottom();
      int c1 = rect.left();
      int c2 = rect.right();

      int bpl = result->bytesPerLine();
      int rgba[4];
      unsigned char* p;

      // how many times blur is applied?
      // for low-end system, limit this to only 1 loop
      for(int loop = 0; loop < 2; loop++)
      {
        for(int col = c1; col <= c2; col++)
        {
          p = result->scanLine(r1) + col*4;
          for(int i = 0; i < 3; i++)
            rgba[i] = p[i] << 4;

          p += bpl;
          for(int j = r1; j < r2; j++, p += bpl)
            for(int i = 0; i < 3; i++)
              p[i] = (rgba[i] += (((p[i]<<4)-rgba[i])) >> 1) >> 4;
        }

        for(int row = r1; row <= r2; row++)
        {
          p = result->scanLine(row) + c1*4;
          for(int i = 0; i < 3; i++)
            rgba[i] = p[i] << 4;

          p += 4;
          for(int j = c1; j < c2; j++, p+=4)
            for(int i = 0; i < 3; i++)
              p[i] = (rgba[i] += (((p[i]<<4)-rgba[i])) >> 1) >> 4;
        }

        for(int col = c1; col <= c2; col++)
        {
          p = result->scanLine(r2) + col*4;
          for(int i = 0; i < 3; i++)
            rgba[i] = p[i] << 4;

          p -= bpl;
          for(int j = r1; j < r2; j++, p -= bpl)
            for(int i = 0; i < 3; i++)
              p[i] = (rgba[i] += (((p[i]<<4)-rgba[i])) >> 1) >> 4;
        }

        for(int row = r1; row <= r2; row++)
        {
          p = result->scanLine(row) + c2*4;
          for(int i = 0; i < 3; i++)
            rgba[i] = p[i] << 4;

          p -= 4;
          for(int j = c1; j < c2; j++, p-=4)
            for(int i = 0; i < 3; i++)
              p[i] = (rgba[i] += (((p[i]<<4)-rgba[i])) >> 1) >> 4;
        }
      }

      // overdraw to leave only the reflection blurred (but not the actual image)
      for(int x = 0; x < w; x++)
        for(int y = 0; y < h; y++)
          result->setPixel(hofs + y, x, img.pixel(x, y));
    }
  }

  return result;
}

QImage* PictureFlowSoftwareRenderer::surface(int slideIndex)
{
  if(!state)
    return 0;
  if(slideIndex < 0)
    return 0;
  if(slideIndex >= (int)state->slideImages.count())
    return 0;

  int key = slideIndex;

  QImage* img = state->slideImages.at(slideIndex);
  bool empty = img ? img->isNull() : true;
  if(empty)
  {
    surfaceCache.remove(key);
    imageHash.remove(slideIndex);
    if(!blankSurface)
    {
      int sw = state->slideWidth;
      int sh = state->slideHeight;

      QImage img = QImage(sw, sh, iFormat);

      QPainter painter(&img);
      QPoint p1(sw*4/10, 0);
      QPoint p2(sw*6/10, sh);
      QLinearGradient linearGrad(p1, p2);
      linearGrad.setColorAt(0, Qt::black);
      linearGrad.setColorAt(1, Qt::white);
      painter.setBrush(linearGrad);
      painter.fillRect(0, 0, sw, sh, QBrush(linearGrad));

      painter.setPen(QPen(QColor(64,64,64), 4));
      painter.setBrush(QBrush());
      painter.drawRect(2, 2, sw-3, sh-3);
      painter.end();

      blankSurface = prepareSurface(&img, sw, sh, bgcolor, state->reflectionEffect,iFormat);
    }
    return blankSurface;
  }

  bool exist = imageHash.contains(slideIndex);
  if(exist)
  if(img == imageHash.find(slideIndex).value())
    if(surfaceCache.contains(key))
        return surfaceCache[key];

  QImage* sr = prepareSurface(img, state->slideWidth, state->slideHeight, bgcolor, state->reflectionEffect,iFormat);
  surfaceCache.insert(key, sr);
  imageHash.insert(slideIndex, img);

  return sr;
}

// Renders a slide to offscreen buffer. Returns a rect of the rendered area.
// col1 and col2 limit the column for rendering.
QRect PictureFlowSoftwareRenderer::renderSlide(const SlideInfo &slide, int col1, int col2)
{
  int blend = slide.blend;
  if(!blend)
    return QRect();

  QImage* src = surface(slide.slideIndex);
  if(!src)
    return QRect();

  QRect rect(0, 0, 0, 0);

  int sw = src->height();
  int sh = src->width();
  int h = buffer.height();
  int w = buffer.width();

  if(col1 > col2)
  {
    int c = col2;
    col2 = col1;
    col1 = c;
  }

  col1 = (col1 >= 0) ? col1 : 0;
  col2 = (col2 >= 0) ? col2 : w-1;
  col1 = qMin(col1, w-1);
  col2 = qMin(col2, w-1);

  int zoom = 100;
  int distance = h * 100 / zoom;
  PFreal sdx = fcos(slide.angle);
  PFreal sdy = fsin(slide.angle);
  PFreal xs = slide.cx - state->slideWidth * sdx/2;
  PFreal ys = slide.cy - state->slideWidth * sdy/2;
  PFreal dist = distance * PFREAL_ONE;

  int xi = qMax((PFreal)0, (w*PFREAL_ONE/2) + fdiv(xs*h, dist+ys) >> PFREAL_SHIFT);
  if(xi >= w)
    return rect;

  bool flag = false;
  rect.setLeft(xi);
  for(int x = qMax(xi, col1); x <= col2; x++)
  {
    PFreal hity = 0;
    PFreal fk = rays[x];
    if(sdy)
    {
      fk = fk - fdiv(sdx,sdy);
      hity = -fdiv((rays[x]*distance - slide.cx + slide.cy*sdx/sdy), fk);
    }

    dist = distance*PFREAL_ONE + hity;
    if(dist < 0)
      continue;

    PFreal hitx = fmul(dist, rays[x]);
    PFreal hitdist = fdiv(hitx - slide.cx, sdx);

    int column = sw/2 + (hitdist >> PFREAL_SHIFT);
    if(column >= sw)
      break;
    if(column < 0)
      continue;

    rect.setRight(x);
    if(!flag)
      rect.setLeft(x);
    flag = true;

    int y1 = h/2;
    int y2 = y1+ 1;
    QRgb* pixel1 = (QRgb*)(buffer.scanLine(y1)) + x;
    QRgb* pixel2 = (QRgb*)(buffer.scanLine(y2)) + x;
    QRgb pixelstep = pixel2 - pixel1;

    int center = (sh/2);
    int dy = dist / h;
    int p1 = center*PFREAL_ONE - dy/2;
    int p2 = center*PFREAL_ONE + dy/2;

    const QRgb *ptr = (const QRgb*)(src->scanLine(column));
    if(blend == 256)
      while((y1 >= 0) && (y2 < h) && (p1 >= 0))
      {
        *pixel1 = ptr[p1 >> PFREAL_SHIFT];
        *pixel2 = ptr[p2 >> PFREAL_SHIFT];
        p1 -= dy;
        p2 += dy;
        y1--;
        y2++;
        pixel1 -= pixelstep;
        pixel2 += pixelstep;
      }
    else
      while((y1 >= 0) && (y2 < h) && (p1 >= 0))
      {
        QRgb c1 = ptr[p1 >> PFREAL_SHIFT];
        QRgb c2 = ptr[p2 >> PFREAL_SHIFT];
        *pixel1 = blendColor(c1, bgcolor, blend);
        *pixel2 = blendColor(c2, bgcolor, blend);
        p1 -= dy;
        p2 += dy;
        y1--;
        y2++;
        pixel1 -= pixelstep;
        pixel2 += pixelstep;
     }
   }

   rect.setTop(0);
   rect.setBottom(h-1);
   return rect;
}

void PictureFlowSoftwareRenderer::renderSlides()
{
  int nleft = state->leftSlides.count();
  int nright = state->rightSlides.count();

  QRect r = renderSlide(state->centerSlide);
  int c1 = r.left();
  int c2 = r.right();

  for(int index = 0; index < nleft; index++)
  {
    QRect rs = renderSlide(state->leftSlides[index], 0, c1-1);
    if(!rs.isEmpty())
      c1 = rs.left();
  }
  for(int index = 0; index < nright; index++)
  {
    QRect rs = renderSlide(state->rightSlides[index], c2+1, buffer.width());
    if(!rs.isEmpty())
      c2 = rs.right();
  }
}

// Render the slides. Updates only the offscreen buffer.
void PictureFlowSoftwareRenderer::render()
{
  buffer.fill(state->backgroundColor);
  renderSlides();
  dirty = false;
}
