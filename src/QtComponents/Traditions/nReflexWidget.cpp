#include <qtcomponents.h>

N::ReflexWidget:: ReflexWidget (QWidget * parent,Plan * p)
                : Widget       (          parent,       p)
{
  WidgetClass                                      ;
  text          = ""                               ;
  font          = QFont("Arial", 8, QFont::Normal) ;
  shear         = 0.1                              ;
  colorBg       = Qt::black                        ;
  colorTx       = Qt::white                        ;
  reflexColorBg = Qt::black                        ;
  reflexColorTx = Qt::white                        ;
  alphaFst      = 20                               ;
  alphaSnd      = 120                              ;
  alphaTxt      = 100                              ;
  reflexLgh     = 0                                ;
}

N::ReflexWidget::~ReflexWidget (void)
{
}

QColor N::ReflexWidget::colorBack(void) const
{
  return colorBg ;
}

QColor N::ReflexWidget::colorTxt(void) const
{
  return colorTx ;
}

QString N::ReflexWidget::txt(void) const
{
  return text ;
}

QFont N::ReflexWidget::fnt(void) const
{
  return font ;
}

int N::ReflexWidget::alphaFirst(void) const
{
  return alphaFst ;
}

int N::ReflexWidget::alphaSecond(void) const
{
  return alphaSnd ;
}

int N::ReflexWidget::alphaText(void) const
{
  return alphaTxt ;
}

int N::ReflexWidget::reflex(void) const
{
  return reflexLgh ;
}

double N::ReflexWidget::shearDim(void) const
{
  return shear ;
}

void N::ReflexWidget::setColorBg(QColor color)
{
  colorBg = color ;
  update ( )      ;
}

void N::ReflexWidget::setColorTx(QColor color)
{
  colorTx = color ;
  update ( )      ;
}

void N::ReflexWidget::setAlphaFst(int dim)
{
  alphaFst = dim ;
  update ( )     ;
}

void N::ReflexWidget::setAlphaSnd(int dim)
{
  alphaSnd = dim ;
  update ( )     ;
}

void N::ReflexWidget::setAlphaTxt(int dim)
{
  alphaTxt = dim ;
  update ( )     ;
}

void N::ReflexWidget::setShear(double dim)
{
  shear = dim ;
  update ( )  ;
}

void N::ReflexWidget::setReflexLgh(int lgh)
{
  reflexLgh = lgh ;
  update ( )      ;
}

void N::ReflexWidget::setText(QString tx)
{
  text = tx  ;
  update ( ) ;
}

void N::ReflexWidget::setFont(QFont fnt)
{
  font = fnt ;
  update ( ) ;
}

QSize N::ReflexWidget::minimumSizeHint() const
{
  return QSize( 9,  4) ;
}

QSize N::ReflexWidget::sizeHint() const
{
  return QSize(90, 40) ;
}

void N::ReflexWidget::paintEvent(QPaintEvent * ep)
{ Q_UNUSED    ( ep ) ;
  paintWidget (    ) ;
}

void N::ReflexWidget::paintWidget(void)
{
  QPainter painter(this);

  painter.setWindow(-60, -20, 120, 60);
  painter.setRenderHint(QPainter::Antialiasing);

  QLinearGradient linGrad(0, -15, 0, -13);
  linGrad.setColorAt(0, Qt::white);
  linGrad.setColorAt(1, colorBg);
  linGrad.setSpread(QGradient::PadSpread);
  painter.setBrush(linGrad);
  painter.setPen(QPen(colorBg));
  painter.drawRect(-40, -15, 80, 15);

  painter.setPen(QPen(colorTx));
  painter.setFont(font);
  QRectF R1 (-40, -15, 80, 15);
  painter.drawText(R1, Qt::AlignCenter, text);

  double pi = 3.14159;
  double a    = (pi/180.0) * 180.0;
  double sina = sin(2.0*a);
  double cosa = cos(2.0*a);

  QTransform reflex(cosa, sina, sina, -cosa, 0, 0);
  painter.setTransform(reflex);
  painter.shear(0, shear);

  QLinearGradient linGrad2(0, -15-reflexLgh, 0, -5-(reflexLgh/2));
  reflexColorFst = colorBg;
  reflexColorSnd = colorBg;
  reflexColorBord = colorBg;
  reflexColorFst.setAlpha(alphaFst);
  reflexColorSnd.setAlpha(alphaSnd);
  reflexColorBord.setAlpha(10);
  reflexColorTx = colorTx;
  reflexColorTx.setAlpha(alphaTxt);

  linGrad2.setColorAt(0, reflexColorFst);
  linGrad2.setColorAt(1, reflexColorSnd);
  linGrad2.setSpread(QGradient::PadSpread);
  painter.setBrush(linGrad2);
  painter.setPen(QPen(reflexColorBord));
  painter.drawRect(-40, -15-reflexLgh, 80, 15+reflexLgh);

  QRectF R2 (-40, -15-reflexLgh, 80, 15+reflexLgh);
  painter.setPen(QPen(reflexColorTx));
  painter.drawText(R2, Qt::AlignCenter, text);

}
