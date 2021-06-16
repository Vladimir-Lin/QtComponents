#include <qtcomponents.h>
#include "nPictureFlowPrivate.hpp"

#define d ((PictureFlowPrivate *)D)

N::PictureFlow:: PictureFlow (QWidget * parent,Plan * p)
               : Widget      (          parent,       p)
{
  D = (void *)new PictureFlowPrivate ;

  d->state = new PictureFlowState;
  d->state->reset();
  d->state->reposition();

  d->renderer = new PictureFlowSoftwareRenderer;
  d->renderer->state = d->state;
  d->renderer->widget = this;
  d->renderer->init();

  d->animator = new PictureFlowAnimator;
  d->animator->state = d->state;
  QObject::connect(&d->animator->animateTimer, SIGNAL(timeout()), this, SLOT(updateAnimation()));

  QObject::connect(&d->triggerTimer, SIGNAL(timeout()), this, SLOT(render()));

  setAttribute ( Qt::WA_StaticContents     , true ) ;
  setAttribute ( Qt::WA_OpaquePaintEvent   , true ) ;
  setAttribute ( Qt::WA_NoSystemBackground , true ) ;
}

N::PictureFlow::~PictureFlow(void)
{
  delete d->renderer ;
  delete d->animator ;
  delete d->state    ;
  delete d           ;
}

QSize N::PictureFlow::sizeHint(void) const
{
  return QSize ( 160 , 128 ) ;
}

int N::PictureFlow::slideCount(void) const
{
  return d->state->slideImages.count();
}

QColor N::PictureFlow::backgroundColor(void) const
{
  return QColor(d->state->backgroundColor);
}

void N::PictureFlow::setBackgroundColor(const QColor& c)
{
  d->state->backgroundColor = c.rgb();
  triggerRender();
}

QSize N::PictureFlow::slideSize(void) const
{
  return QSize(d->state->slideWidth, d->state->slideHeight);
}

void N::PictureFlow::setSlideSize(QSize size)
{
  d->state->slideWidth = size.width();
  d->state->slideHeight = size.height();
  d->state->reposition();
  triggerRender();
}

N::PictureFlow::ReflectionEffect N::PictureFlow::reflectionEffect(void) const
{
  return (ReflectionEffect)d->state->reflectionEffect ;
}

void N::PictureFlow::setReflectionEffect(ReflectionEffect effect)
{
  d->state->reflectionEffect = (int)effect;
  triggerRender();
}

QImage N::PictureFlow::slide(int index) const
{
  QImage* i = 0;
  if((index >= 0) && (index < slideCount()))
    i = d->state->slideImages[index];
  return i ? QImage(*i) : QImage();
}

void N::PictureFlow::addSlide(const QImage& image)
{
  int c = d->state->slideImages.count();
  d->state->slideImages.resize(c+1);
  d->state->slideImages[c] = new QImage(image);
  triggerRender();
}

void N::PictureFlow::addSlide(const QPixmap& pixmap)
{
  addSlide(pixmap.toImage());
}

void N::PictureFlow::setSlide(int index, const QImage& image)
{
  if((index >= 0) && (index < slideCount()))
  {
    QImage* i = image.isNull() ? 0 : new QImage(image);
    delete d->state->slideImages[index];
    d->state->slideImages[index] = i;
    triggerRender();
  }
}

void N::PictureFlow::setSlide(int index, const QPixmap& pixmap)
{
  setSlide(index, pixmap.toImage());
}

int N::PictureFlow::centerIndex(void) const
{
  return d->state->centerIndex;
}

void N::PictureFlow::setCenterIndex(int index)
{
  index = qMin(index, slideCount()-1);
  index = qMax(index, 0);
  d->state->centerIndex = index;
  d->state->reset();
  d->animator->stop(index);
  triggerRender();
}

void N::PictureFlow::clear(void)
{
  int c = d->state->slideImages.count();
  for(int i = 0; i < c; i++)
    delete d->state->slideImages[i];
  d->state->slideImages.resize(0);

  d->state->reset();
  triggerRender();
}

void N::PictureFlow::render(void)
{
  d->renderer->dirty = true;
  update();
}

void N::PictureFlow::triggerRender(void)
{
  d->triggerTimer.setSingleShot(true);
  d->triggerTimer.start(0);
}

void N::PictureFlow::showPrevious(void)
{
  int step = d->animator->step;
  int center = d->state->centerIndex;

  if(step > 0)
    d->animator->start(center);

  if(step == 0)
    if(center > 0)
      d->animator->start(center - 1);

  if(step < 0)
    d->animator->target = qMax(0, center - 2);
}

void N::PictureFlow::showNext(void)
{
  int step = d->animator->step;
  int center = d->state->centerIndex;

  if(step < 0)
    d->animator->start(center);

  if(step == 0)
    if(center < slideCount()-1)
      d->animator->start(center + 1);

  if(step > 0)
    d->animator->target = qMin(center + 2, slideCount()-1);
}

void N::PictureFlow::showSlide(int index)
{
  index = qMax(index, 0);
  index = qMin(slideCount()-1, index);
  if(index == d->state->centerSlide.slideIndex)
    return;

  d->animator->start(index);
}

void N::PictureFlow::keyPressEvent(QKeyEvent * event)
{
  if(event->key() == Qt::Key_Left)
  {
    if(event->modifiers() == Qt::ControlModifier)
      showSlide(centerIndex()-10);
    else
      showPrevious();
    event->accept();
    return;
  }

  if(event->key() == Qt::Key_Right)
  {
    if(event->modifiers() == Qt::ControlModifier)
      showSlide(centerIndex()+10);
    else
      showNext();
    event->accept();
    return;
  }

  event->ignore();
}

void N::PictureFlow::mousePressEvent(QMouseEvent * event)
{
  if(event->x() > width()/2)
    showNext();
  else
    showPrevious();
}

void N::PictureFlow::paintEvent(QPaintEvent * event)
{
  Q_UNUSED(event);
  d->renderer->paint();
}

void N::PictureFlow::resizeEvent(QResizeEvent * event)
{
  triggerRender();
  QWidget::resizeEvent(event);
}

void N::PictureFlow::updateAnimation(void)
{
  int old_center = d->state->centerIndex;
  d->animator->update();
  triggerRender();
  if(d->state->centerIndex != old_center)
    emit centerIndexChanged(d->state->centerIndex);
}
