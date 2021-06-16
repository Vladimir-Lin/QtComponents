#include <qtcomponents.h>

N::VcfGrid:: VcfGrid   (QObject * parent,QGraphicsItem * item,Plan * p)
           : VcfCanvas (          parent,                item,       p)
           , Gap       ( QSizeF ( 1.00 , 1.00 )                       )
           , Dot       ( QSizeF ( 0.02 , 0.02 )                       )
{
  Painter . addMap   ( "Default" , 0                  ) ;
  Painter . addPen   ( 0 , QColor ( 192 , 192 , 192 ) ) ;
  Painter . addBrush ( 0 , QColor ( 224 , 224 , 224 ) ) ;
}

N::VcfGrid::~VcfGrid(void)
{
}

void N::VcfGrid::Paint(QPainter * p,QRectF Region,bool clip,bool color)
{
  pushPainters ( p )                     ;
  Painter . setPainter ( p , "Default" ) ;
  if (Painter.pathes.contains(0))        {
    p->drawPath(Painter.pathes[0])       ;
  }                                      ;
  popPainters  ( p )                     ;
}

void N::VcfGrid::CreatePath(void)
{
  Painter.pathes[0] = QPainterPath() ;
  CreateShape ( &Painter.pathes[0] ) ;
}

void N::VcfGrid::CreateShape(QPainterPath * p)
{
  QPointF G ( Gap . width () , Gap . height () ) ;
  QPointF D ( Dot . width () , Dot . height () ) ;
  QPointF GS = toPaper ( G )                     ;
  QPointF DT = toPaper ( D )                     ;
  QSizeF  DS (DT.x(),DT.y())                     ;
  QPointF DH = DT / 2                            ;
  QPointF BP(ScreenRect.left(),ScreenRect.top()) ;
  QPointF GP                                     ;
  do                                             {
    GP = BP - DH                                 ;
    p -> addEllipse ( QRectF ( GP , DS ) )       ;
    BP . setX ( BP . x ( ) + GS . x ( )  )       ;
    if ( BP . x () > ScreenRect . right () )     {
      BP . setX ( ScreenRect . left () )         ;
      BP . setY ( BP . y () + GS . y() )         ;
    }                                            ;
  } while (BP.x()<=ScreenRect.right ()          &&
           BP.y()<=ScreenRect.bottom()         ) ;
}
