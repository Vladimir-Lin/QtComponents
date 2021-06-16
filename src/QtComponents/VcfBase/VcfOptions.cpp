#include <qtcomponents.h>

N::VcfOptions:: VcfOptions ( void        )
              : Private    ( false       )
              , ColorMode  ( true        )
              , DPI        ( 300         )
              , Insert     ( true        )
              , LineSpace  ( 0.025       )
              , PictureDPI ( 96.00       )
              , ScaleRatio ( 1.00 , 1.00 )
{
}

N::VcfOptions::~VcfOptions (void)
{
}

// Centimeter to Paper resolution
// cm * DPI * 100 / 254
QPointF N::VcfOptions::position(QPointF cm)
{
  qreal x = cm.x() ; x *= DPI ; x *= 100 ; x /= 254 ; x /= ScaleRatio.width () ;
  qreal y = cm.y() ; y *= DPI ; y *= 100 ; y /= 254 ; y /= ScaleRatio.height() ;
  return QPointF(x,y)                                                          ;
}

QRectF N::VcfOptions::Region(QRectF cm)
{
  QPointF S(cm.left(),cm.top())          ;
  QPointF W(cm.width(),cm.height())      ;
  S = position(S)                        ;
  W = position(W)                        ;
  return QRectF(S.x(),S.y(),W.x(),W.y()) ;
}

QPointF N::VcfOptions::Standard(QPointF paper)
{
  qreal x = paper.x() ; x *= 254 ; x /= 100 ; x /= DPI ; x *= ScaleRatio.width () ;
  qreal y = paper.y() ; y *= 254 ; y /= 100 ; y /= DPI ; y *= ScaleRatio.height() ;
  return QPointF(x,y)                                                             ;
}

QRectF N::VcfOptions::Standard(QRectF paper)
{
  QPointF S(paper.left(),paper.top())     ;
  QPointF W(paper.width(),paper.height()) ;
  S = Standard(S)                         ;
  W = Standard(W)                         ;
  return QRectF(S.x(),S.y(),W.x(),W.y())  ;
}

QSizeF N::VcfOptions::PictureOnPaper(QSize size)
{
  return PictureOnPaper(size,PictureDPI) ;
}

QSizeF N::VcfOptions::PictureOnPaper(QSize size,int DPI)
{
  // Convert to CM first
  QPointF C(size.width(),size.height())                          ;
  C.setX(C.x() * 254) ; C.setX(C.x() / 100); C.setX(C.x() / DPI) ;
  C.setY(C.y() * 254) ; C.setY(C.y() / 100); C.setX(C.y() / DPI) ;
  // Convert to Paper
  QPointF S = position(C)                                        ;
  return QSizeF(S.x(),S.y())                                     ;
}

N::VcfOptions & N::VcfOptions::operator = (VcfOptions & options)
{
  Private    = options.Private    ;
  ColorMode  = options.ColorMode  ;
  DPI        = options.DPI        ;
  PictureDPI = options.PictureDPI ;
  Insert     = options.Insert     ;
  LineSpace  = options.LineSpace  ;
  ScaleRatio = options.ScaleRatio ;
  fonts      = options.fonts      ;
  return (*this)                  ;
}
