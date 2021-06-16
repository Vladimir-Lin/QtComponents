#include <qtcomponents.h>

#ifdef QT_OPENGL_LIB

N::TextObject:: TextObject ( QObject * parent , Plan * p )
              : IconObject (           parent ,        p )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::TextObject:: TextObject ( QObject * parent , Plan * p , SceneDestructor * des )
              : IconObject (           parent ,        p ,                   des )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::TextObject::~TextObject (void)
{
}

void N::TextObject::Configure(void)
{
  int    flag = Qt::AlignVCenter                       |
                Qt::AlignLeft                          |
                Qt::TextWordWrap                       ;
  QColor black          (   0 ,    0 ,   0 , 192     ) ;
  //////////////////////////////////////////////////////
  QObject::setProperty  ( "Type"      , "TextObject" ) ;
  setVariable           ( "Type"           , "Text"  ) ;
  //////////////////////////////////////////////////////
  setVariable           ( "Length"         , 40      ) ;
  setVariable           ( "TextColor"      , black   ) ;
  setVariable           ( "TextFlags"      , flag    ) ;
  setVariable           ( "PixelSize"      , 14      ) ;
  //////////////////////////////////////////////////////
  font = plan -> fonts [ Fonts::Editor ] . toQFont ( ) ;
}

void N::TextObject::renderFront(void)
{
  if ( Variables . contains ( "TextureFactor" ) )      {
    QSizeF s = Value ( "TextureFactor" ) . toSizeF ( ) ;
    QRectF r                                           ;
    r . setLeft   ( minimum . x         )              ;
    r . setTop    ( minimum . y         )              ;
    r . setRight  ( maximum . x         )              ;
    r . setBottom ( maximum . y         )              ;
    renderXY      ( r , maximum . z , s )              ;
  } else                                               {
    renderXY ( maximum . z )                           ;
  }                                                    ;
}

void N::TextObject::renderBack(void)
{
  if ( Variables . contains ( "TextureFactor" ) )      {
    QSizeF s = Value ( "TextureFactor" ) . toSizeF ( ) ;
    QRectF r                                           ;
    r . setLeft   ( minimum . x         )              ;
    r . setTop    ( minimum . y         )              ;
    r . setRight  ( maximum . x         )              ;
    r . setBottom ( maximum . y         )              ;
    renderXY      ( r , minimum . z , s )              ;
  } else                                               {
    renderXY ( minimum . z )                           ;
  }                                                    ;
}

void N::TextObject::setTextFlags(int flags)
{
  setVariable ( "TextFlags" , flags ) ;
}

void N::TextObject::setFont(QFont f)
{
  font = f ;
}

void N::TextObject::setPixelSize(float pixels)
{
  setVariable ( "PixelSize" , pixels ) ;
}

void N::TextObject::setTextRange(SUID uuid,QSize s)
{
  QSize ms ( MipSize ( s . width ( ) ) , MipSize ( s . height ( ) ) ) ;
  setIcon ( uuid , new QImage ( ms , QImage::Format_ARGB32 ) )        ;
  textures [ uuid ] -> original -> fill ( 0 )                         ;
  /////////////////////////////////////////////////////////////////////
  double w = s  . width  ( )                                          ;
  double h = s  . height ( )                                          ;
  w       /= ms . width  ( )                                          ;
  h       /= ms . height ( )                                          ;
  /////////////////////////////////////////////////////////////////////
  QSizeF r ( w , h )                                                  ;
  /////////////////////////////////////////////////////////////////////
  setVariable ( "TextureSize"   , s )                                 ;
  setVariable ( "TextureFactor" , r )                                 ;
}

void N::TextObject::setTextColor(QColor c)
{
  setVariable ( "TextColor" , c ) ;
}

void N::TextObject::setText(QString text)
{
  if ( ! Variables . contains ( "PictureUUID" ) ) return      ;
  SUID u = Value ( "PictureUUID" ) . toULongLong ( )          ;
  if ( ! textures . contains ( u ) ) return                   ;
  /////////////////////////////////////////////////////////////
  LockAt   ( "Operate" )                                      ;
  /////////////////////////////////////////////////////////////
  QString n = text                                            ;
  QSize   s = Value ( "TextureSize" ) . toSize ( )            ;
  QColor  c (   0 ,   0 ,             0 ,            255 )    ;
  QRectF  z (   0 ,   0 , s . width ( ) , s . height ( ) )    ;
  QFont   F    = font                                         ;
  int     flag = Qt::AlignCenter                              ;
  int     ps   = Value ( "PixelSize" ) . toInt ( )            ;
  int     len  = Value ( "Length"    ) . toInt ( )            ;
  /////////////////////////////////////////////////////////////
  if ( n . length ( ) > len )                                 {
    n = n . left ( len ) + "..."                              ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  F . setPixelSize ( ps )                                     ;
  if ( Variables . contains ( "TextColor" ) )                 {
    c = Variables [ "TextColor" ] . value <QColor> ( )        ;
  }                                                           ;
  if ( Variables . contains ( "TextFlags" ) )                 {
    flag = Variables [ "TextFlags" ] . toInt ( )              ;
  }                                                           ;
  textures [ u ] -> original -> fill ( 0 )                    ;
  textures [ u ] -> drawText ( c , F , z , flag , n )         ;
  /////////////////////////////////////////////////////////////
  UnlockAt ( "Operate" )                                      ;
}

#endif
