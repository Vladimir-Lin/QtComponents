#include <qtcomponents.h>

N::VcfRuler:: VcfRuler     (QObject * parent,QGraphicsItem * item,Plan * p)
            : VcfRectangle (          parent,                item,       p)
            , direction    (North                                         )
{
  Painter . addMap   ( "Default" , 0                  ) ;
  Painter . addPen   ( 0 , QColor ( 192 , 192 , 192 ) ) ;
  Painter . addBrush ( 0 , QColor ( 252 , 252 , 252 ) ) ;
}

N::VcfRuler::~VcfRuler(void)
{
}

void N::VcfRuler::paint(QPainter * p,const QStyleOptionGraphicsItem *,QWidget *)
{
  Paint(p,ScreenRect,true,true);
}

void N::VcfRuler::Paint(QPainter * p,QRectF Region,bool clip,bool color)
{
  pushPainters ( p )         ;
  Painter . drawRect ( p , "Default" , ScreenRect ) ;
  if (Painter.pathes.contains(0)) p->drawPath(Painter.pathes[0]);
  popPainters  ( p )         ;
}

void N::VcfRuler::CreatePath(void)
{
  Painter.pathes[0] = QPainterPath() ;
  switch (direction)                 {
    case North                       :
      PaintNorth(&Painter.pathes[0]) ;
    break                            ;
    case South                       :
      PaintSouth(&Painter.pathes[0]) ;
    break                            ;
    case East                        :
      PaintEast (&Painter.pathes[0]) ;
    break                            ;
    case West                        :
      PaintWest (&Painter.pathes[0]) ;
    break                            ;
  }                                  ;
}

void N::VcfRuler::PaintNorth(QPainterPath * p)
{
  QRectF  dr = ScreenRect ;
  qreal   ep = dr.width ();
  qreal   dh = dr.height();
  qreal   mh = dh / 2     ;
  qreal   mm = dh / 4     ;
  qreal   dl = 0          ;
  int     di = 0          ;
  QPointF xy              ;
  do {
    dl  = di ;
    dl /= 10 ;
    xy.setX(dl);
    xy.setY(dl);
    xy  = toPaper(xy);
    dl  = xy.x();
    if (dl<ep) {
      p->moveTo(dr.left()+dl,dr.bottom());
      if ((di%10)==0) p->lineTo(dr.left()+dl,dr.top   ()   ); else
      if ((di% 5)==0) p->lineTo(dr.left()+dl,dr.bottom()-mh); else
                      p->lineTo(dr.left()+dl,dr.bottom()-mm);
    };
    di ++    ;
  } while (dl<ep);
}

void N::VcfRuler::PaintSouth(QPainterPath * p)
{
  QRectF  dr = ScreenRect  ;
  qreal   ep = dr.width () ;
  qreal   dh = dr.height() ;
  qreal   mh = dh / 2      ;
  qreal   mm = dh / 4      ;
  qreal   dl = 0           ;
  int     di = 0           ;
  QPointF xy               ;
  do {
    dl  = di ;
    dl /= 10 ;
    xy.setX(dl);
    xy.setY(dl);
    xy  = toPaper(xy);
    dl  = xy.x();
    if (dl<ep) {
      p->moveTo(dr.left()+dl,dr.top());
      if ((di%10)==0) p->lineTo(dr.left()+dl,dr.bottom()   ); else
      if ((di% 5)==0) p->lineTo(dr.left()+dl,dr.top   ()+mh); else
                      p->lineTo(dr.left()+dl,dr.top   ()+mm);
    };
    di ++ ;
  } while (dl<ep);
}

void N::VcfRuler::PaintEast(QPainterPath * p)
{
  QRectF  dr = ScreenRect  ;
  qreal   ep = dr.height() ;
  qreal   dw = dr.width () ;
  qreal   mw = dw / 2      ;
  qreal   mm = dw / 4      ;
  qreal   dl = 0           ;
  int     di = 0           ;
  QPointF xy               ;
  do {
    dl  = di ;
    dl /= 10 ;
    xy.setX(dl);
    xy.setY(dl);
    xy  = toPaper(xy);
    dl  = xy.x();
    if (dl<ep) {
      p->moveTo(dr.left(),dr.top()+dl);
      if ((di%10)==0) p->lineTo(dr.right()   ,dr.top()+dl); else
      if ((di% 5)==0) p->lineTo(dr.left ()+mw,dr.top()+dl); else
                      p->lineTo(dr.left ()+mm,dr.top()+dl);
    };
    di ++ ;
  } while (dl<ep);
}

void N::VcfRuler::PaintWest(QPainterPath * p)
{
  QRectF  dr = ScreenRect  ;
  qreal   ep = dr.height() ;
  qreal   dw = dr.width () ;
  qreal   mw = dw / 2      ;
  qreal   mm = dw / 4      ;
  qreal   dl = 0           ;
  int     di = 0           ;
  QPointF xy               ;
  do {
    dl  = di ;
    dl /= 10 ;
    xy.setX(dl);
    xy.setY(dl);
    xy  = toPaper(xy);
    dl  = xy.x();
    if (dl<ep) {
      p->moveTo(dr.right(),dr.top()+dl);
      if ((di%10)==0) p->lineTo(dr.left ()   ,dr.top()+dl); else
      if ((di% 5)==0) p->lineTo(dr.right()-mw,dr.top()+dl); else
                      p->lineTo(dr.right()-mm,dr.top()+dl);
    };
    di ++ ;
  } while (dl<ep);
}
