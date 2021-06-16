#include <qtcomponents.h>

N::VcfCursor:: VcfCursor    ( QObject * parent , QGraphicsItem * item , Plan * p )
             : VcfRectangle (           parent ,                 item ,        p )
             , Timer        ( new QTimer ( this )                                )
             , Showing      ( false                                              )
{
  Printable = false                              ;
  Painter . addMap   ( "Default" , 0 )           ;
  Painter . addPen   ( 0 , QColor(  0,  0,255) ) ;
  Painter . addBrush ( 0 , QColor(224,224,224) ) ;
  setFlag (ItemIsSelectable,false)               ;
  setFlag (ItemIsFocusable ,false)               ;
  nConnect ( Timer , SIGNAL ( timeout   ( ) )    ,
             this  , SLOT   ( Twinkling ( ) ) )  ;
  Timer -> setInterval ( 1000 )                  ;
}

N::VcfCursor::~VcfCursor(void)
{
  Timer -> stop ( ) ;
}

void N::VcfCursor::setInterval(int milliseconds)
{
  Timer -> setInterval ( milliseconds ) ;
}

void N::VcfCursor::Start(void)
{
  Timer -> start ( ) ;
}

void N::VcfCursor::Twinkling(void)
{
  update();
}

void N::VcfCursor::paint(QPainter * painter,const QStyleOptionGraphicsItem * option,QWidget * widget)
{
  Paint(painter,ScreenRect,false,true) ;
}

void N::VcfCursor::Paint(QPainter * p,QRectF Region,bool clip,bool color)
{
  pushPainters (p)                  ;
  if (Showing)                      {
    Painter.setPainter(p,"Default") ;
    p -> drawRect (ScreenRect     ) ;
    Showing = false                 ;
  } else                            {
    Showing = true                  ;
  }                                 ;
  popPainters  (p)                  ;
}
