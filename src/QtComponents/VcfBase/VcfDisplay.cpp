#include <qtcomponents.h>

N::VcfDisplay:: VcfDisplay    (void        )
              : Margins       (0,0,3,3     )
              , DPI           (300         )
              , ZoomFactor    (1.00        )
              , MonitorFactor (1.00        )
              , Origin        (QPointF(0,0))
{
  Scene     = new QGraphicsScene ( ) ;
  Transform . reset              ( ) ;
}

N::VcfDisplay::~VcfDisplay (void)
{
}

QString N::VcfDisplay::Percentage(void)
{
  char P[1024]                        ;
  sprintf(P,"%4.2f",(ZoomFactor*100)) ;
  return QString("%1%").arg(P)        ;
}

QSize N::VcfDisplay::available(QSize size)
{
  return QSize                                                        (
           size . width  () - Margins . left () - Margins . right  () ,
           size . height () - Margins . top  () - Margins . bottom ()
         )                                                            ;
}

QSizeF N::VcfDisplay::centimeter(QSize size)
{
  double w = size.width () ;
  double h = size.height() ;
  w *= screen.WidthLength  ;
  w /= screen.WidthPixels  ;
  w /= 10                  ;
  h *= screen.HeightLength ;
  h /= screen.HeightPixels ;
  h /= 10                  ;
  return QSizeF(w,h)       ;
}

QSizeF N::VcfDisplay::toPaper(QSizeF cm)
{
  double x = cm.width () ; x *= DPI ; x *= 100 ; x /= 254 ;
  double y = cm.height() ; y *= DPI ; y *= 100 ; y /= 254 ;
  return QSizeF(x,y)                                      ;
}

QRectF N::VcfDisplay::asPaper(QSize size)
{
  QSizeF S = size                      ;
  QSizeF P = toPaper(centimeter(size)) ;
  Transform.reset ()                   ;
  double sx = S.width  () / P.width () ;
  double sy = S.height () / P.height() ;
  sx *= ZoomFactor                     ;
  sy *= ZoomFactor                     ;
  Transform.scale (sx,sy)              ;
  QTransform I = Transform.inverted()  ;
  QPointF Z(S.width(),S.height())      ;
  Z = I.map(Z)                         ;
  return QRectF(0,0,Z.x(),Z.y())       ;
}

qreal N::VcfDisplay::FactorLevel(qreal factor,bool enlarge)
{
  qreal f = factor;
  int   F = (int)(f * 100);
  bool  B = false;
  for (int i=1;!B && i<Zooms.count();i++) {
    if (Zooms[i-1]==F) {
      if (enlarge) {
        F = Zooms[i];
        B = true;
      } else {
        if (i>1) F = Zooms[i-2]; else F = Zooms[0];
        B = true;
      };
    } else
    if (Zooms[i]==F) {
      if (enlarge) {
        F = Zooms[i+1];
        B = true;
      } else {
        if (i>0) F = Zooms[i-1]; else F = Zooms[0];
        B = true;
      };
    } else
    if (Zooms[i-1]<F && F<Zooms[i]) {
      if (enlarge) {
        F = Zooms[i+1];
        B = true;
      } else {
        if (i>0) F = Zooms[i-1]; else F = Zooms[0];
        B = true;
      };
    };
  };
  f = F; f /= 100;
  return f;
}

void N::VcfDisplay::Enlarge(void)
{
  ZoomFactor = FactorLevel(ZoomFactor,true ) ;
}

void N::VcfDisplay::Shrink(void)
{
  ZoomFactor = FactorLevel(ZoomFactor,false) ;
}

QDoubleSpinBox * N::VcfDisplay::ZoomSpin(QWidget * parent,QWidget * widget,const char * method)
{
  QDoubleSpinBox * ds = new QDoubleSpinBox(parent) ;
  ds->setMinimum    (0.01000       )               ;
  ds->setMaximum    (1000000       )               ;
  ds->setValue      (ZoomFactor*100)               ;
  ds->setSingleStep (1.00          )               ;
  ds->setSuffix     ("%")                          ;
  ds->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  QObject::connect(ds,SIGNAL(valueChanged(double)) ,
                   widget,method                )  ;
  return ds                                        ;
}

void N::VcfDisplay::ZoomSpinChanged(double value)
{
  ZoomFactor = value / 100;
}

void N::VcfDisplay::setDefaultZoom(void)
{
  Zooms.clear() ;
  Zooms <<    1 ;
  Zooms <<    2 ;
  Zooms <<    3 ;
  Zooms <<    4 ;
  Zooms <<    5 ;
  Zooms <<    6 ;
  Zooms <<    7 ;
  Zooms <<    8 ;
  Zooms <<    9 ;
  Zooms <<   10 ;
  Zooms <<   15 ;
  Zooms <<   20 ;
  Zooms <<   25 ;
  Zooms <<   30 ;
  Zooms <<   35 ;
  Zooms <<   40 ;
  Zooms <<   45 ;
  Zooms <<   50 ;
  Zooms <<   55 ;
  Zooms <<   60 ;
  Zooms <<   65 ;
  Zooms <<   70 ;
  Zooms <<   75 ;
  Zooms <<   80 ;
  Zooms <<   85 ;
  Zooms <<   90 ;
  Zooms <<   95 ;
  Zooms <<  100 ;
  Zooms <<  110 ;
  Zooms <<  120 ;
  Zooms <<  130 ;
  Zooms <<  140 ;
  Zooms <<  150 ;
  Zooms <<  160 ;
  Zooms <<  170 ;
  Zooms <<  180 ;
  Zooms <<  190 ;
  Zooms <<  200 ;
  Zooms <<  300 ;
  Zooms <<  400 ;
  Zooms <<  500 ;
  Zooms <<  600 ;
  Zooms <<  700 ;
  Zooms <<  800 ;
  Zooms <<  900 ;
  Zooms << 1000 ;
  Zooms << 1100 ;
  Zooms << 1200 ;
  Zooms << 1300 ;
  Zooms << 1400 ;
  Zooms << 1500 ;
  Zooms << 1600 ;
  Zooms << 1700 ;
  Zooms << 1800 ;
  Zooms << 1900 ;
  Zooms << 2000 ;
  Zooms << 2100 ;
  Zooms << 2200 ;
  Zooms << 2300 ;
  Zooms << 2400 ;
  Zooms << 2500 ;
  Zooms << 2600 ;
  Zooms << 2700 ;
  Zooms << 2800 ;
  Zooms << 2900 ;
  Zooms << 3000 ;
  Zooms << 3100 ;
  Zooms << 3200 ;
  Zooms << 3300 ;
  Zooms << 3400 ;
  Zooms << 3500 ;
  Zooms << 3600 ;
  Zooms << 3700 ;
  Zooms << 3800 ;
  Zooms << 3900 ;
  Zooms << 4000 ;
  Zooms << 4100 ;
  Zooms << 4200 ;
  Zooms << 4300 ;
  Zooms << 4400 ;
  Zooms << 4500 ;
  Zooms << 4600 ;
  Zooms << 4700 ;
  Zooms << 4800 ;
  Zooms << 4900 ;
  Zooms << 5000 ;
}
