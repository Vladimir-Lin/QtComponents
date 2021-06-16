#include <qtcomponents.h>

#ifdef QT_OPENGL_LIB

N::PictureObject:: PictureObject ( QObject * parent , Plan * p )
                 : SceneWidget   (           parent ,        p )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::PictureObject:: PictureObject ( QObject * parent , Plan * p , SceneDestructor * des )
                 : SceneWidget   (           parent ,        p ,                   des )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::PictureObject::~PictureObject (void)
{
}

void N::PictureObject::Configure(void)
{
  QObject::setProperty  ( "Type"   , "PictureObject" ) ;
  setVariable           ( "Type"   , "Picture"       ) ;
  setVariable           ( "Focus"  , false           ) ;
  setVariable           ( "Hold"   , false           ) ;
  setVariable           ( "Menu"   , false           ) ;
  setVariable           ( "Mouse"  , true            ) ;
  setVariable           ( "Emit"   , true            ) ;
  //////////////////////////////////////////////////////
  setVariable           ( "Front"  , true            ) ;
  setVariable           ( "Back"   , false           ) ;
  setVariable           ( "Runner" , true            ) ;
  //////////////////////////////////////////////////////
  QString TTT = tr("%1 x %2")                          ;
  setVariable           ( "ToolTipTemplate" , TTT    ) ;
}

bool N::PictureObject::FocusIn(void)
{
  return false ;
}

bool N::PictureObject::FocusOut(void)
{
  return false ;
}

bool N::PictureObject::Spot (
       ControlPoint & From  ,
       ControlPoint & To    ,
       ControlPoint & At    )
{
  if ( ! Value ( "Mouse" ) . toBool ( )  ) return false ;
  return xymSpot ( From , To , At )                     ;
}

bool N::PictureObject::MouseVector (
       ControlPoint & From          ,
       ControlPoint & To            ,
       BMAPs        & buttons       )
{
  if ( ! Value ( "Mouse" ) . toBool ( )  ) return false        ;
  if ( ! matrices . contains ( 2 )       ) return false        ;
  if ( buttons [ Universe::MouseMiddle ] ) return false        ;
  if ( buttons [ Universe::MouseRight  ] ) return false        ;
  //////////////////////////////////////////////////////////////
  ControlPoint At                                              ;
  if ( ! Collide ( From , To , At )      ) return false        ;
  //////////////////////////////////////////////////////////////
  if ( buttons [ Universe::MouseLeft   ] )                     {
    if ( ! isFocus ( ) )                                       {
      Alert ( Click )                                          ;
    }                                                          ;
    setFocus ( true )                                          ;
    if ( Value ( "Hit" ) . toBool ( ) )                        {
      setVariable      ( "X" , At . x  )                       ;
      setVariable      ( "Y" , At . y  )                       ;
      ToolTip          (               )                       ;
      return true                                              ;
    } else                                                     {
      int region = AtRegion ( At )                             ;
      switch ( region )                                        {
        case 0                                                 :
          setVariable  ( "Hit" , false )                       ;
        break                                                  ;
        case 1                                                 :
          setVariable  ( "X" , At . x  )                       ;
          setVariable  ( "Y" , At . y  )                       ;
          setVariable  ( "Hit" , true  )                       ;
          ToolTip      (               )                       ;
        break                                                  ;
      }                                                        ;
    }                                                          ;
  } else                                                       {
    if ( Value ( "Hit" ) . toBool ( ) )                        {
      setVariable  ( "Hit" , false   )                         ;
      return true                                              ;
    }                                                          ;
  }                                                            ;
  return true                                                  ;
}

bool N::PictureObject::MouseHover (
       ControlPoint & From         ,
       ControlPoint & To           ,
       BMAPs        & buttons      )
{
  if ( ! Value ( "Mouse" ) . toBool ( )  ) return false             ;
  if ( ! isFocus             (  )        ) return false             ;
  if ( ! matrices . contains ( 2 )       ) return false             ;
  ///////////////////////////////////////////////////////////////////
  ControlPoint At                                                   ;
  if ( ! Collide ( From , To , At )      ) return false             ;
  ///////////////////////////////////////////////////////////////////
  if ( Value ( "Hit" ) . toBool ( ) )                               {
    setVariable ( "X" , At . x  )                                   ;
    setVariable ( "Y" , At . y  )                                   ;
    ToolTip     (               )                                   ;
    return true                                                     ;
  }                                                                 ;
  ///////////////////////////////////////////////////////////////////
  int region = AtRegion ( At )                                      ;
  if ( region <= 0 )                                                {
    setCursor ( Qt::ArrowCursor )                                   ;
    return false                                                    ;
  }                                                                 ;
  ///////////////////////////////////////////////////////////////////
  bool onlyMoving = true                                            ;
  if ( buttons [ Universe::MouseLeft   ] ) onlyMoving = false       ;
  if ( buttons [ Universe::MouseMiddle ] ) onlyMoving = false       ;
  if ( buttons [ Universe::MouseRight  ] ) onlyMoving = false       ;
  if ( ! onlyMoving ) return true                                   ;
  ///////////////////////////////////////////////////////////////////
  switch ( region )                                                 {
    case 0                                                          :
    break                                                           ;
    case 1                                                          :
      ToolTip   (                    )                              ;
    break                                                           ;
    default                                                         :
    break                                                           ;
  }                                                                 ;
  ///////////////////////////////////////////////////////////////////
  return true                                                       ;
}

bool N::PictureObject::MouseMove (
       ControlPoint & From1      ,
       ControlPoint & To1        ,
       ControlPoint & From2      ,
       ControlPoint & To2        ,
       BMAPs        & buttons    )
{
  return false ;
}

// 0 - Outside
// 1 - inside
int N::PictureObject::AtRegion(ControlPoint & At)
{
  if ( At . x < minimum . x ) return 0 ;
  if ( At . x > maximum . x ) return 0 ;
  if ( At . y < minimum . y ) return 0 ;
  if ( At . y > maximum . y ) return 0 ;
  return 1                             ;
}

QString N::PictureObject::ToolTip(void)
{
  if ( ! Variables . contains ( "PictureUUID" ) ) return ""       ;
  SUID  u = Value ( "PictureUUID" ) . toULongLong ( )             ;
  /////////////////////////////////////////////////////////////////
  if ( ! textures . contains ( u ) ) return ""                    ;
  SceneTexture * t = textures [ u ]                               ;
  if ( IsNull ( t )  ) return ""                                  ;
  /////////////////////////////////////////////////////////////////
  QImage * image = t -> original                                  ;
  if ( IsNull(image) ) return ""                                  ;
  /////////////////////////////////////////////////////////////////
  QSize   s  = image -> size (   )                                ;
  QString AS = ToolTip       ( s )                                ;
  QRect   RX                                                      ;
  /////////////////////////////////////////////////////////////////
  if ( AS . length ( ) > 0 )                                      {
    QToolTip::showText ( QCursor::pos() , AS , NULL , RX , 3000 ) ;
    if ( NULL != gui ) gui -> setToolTip ( AS )                   ;
  }                                                               ;
  return AS                                                       ;
}

QString N::PictureObject::ToolTip(QSize s)
{
  QString TRX = Value ( "ToolTipTemplate" ) . toString ( )                ;
  return QString ( TRX ) . arg ( s . width ( ) ) . arg ( s . height ( ) ) ;
}

QImage * N::PictureObject::CurrentImage(void)
{
  return SceneObject::CurrentImage ( "PictureUUID" ) ;
}

void N::PictureObject::setTexture (SUID uuid,QImage * image,bool Lod)
{
  assignTexture ( uuid , image , Lod ) ;
  assignUuid    ( uuid               ) ;
}

void N::PictureObject::assignUuid(SUID uuid)
{
  setVariable ( "PictureUUID" , uuid ) ;
}

void N::PictureObject::assignTexture (SUID uuid,QImage * image,bool Lod)
{
  SceneTexture * t                              ;
  ///////////////////////////////////////////////
  if ( textures . contains ( uuid ) )           {
    LockAt   ( "Operate" )                      ;
    t = textures [ uuid ]                       ;
    textures . remove ( uuid )                  ;
    UnlockAt ( "Operate" )                      ;
    if ( destructor -> nodes . contains ( t ) ) {
      (*destructor) -= t                        ;
      delete t                                  ;
    }                                           ;
  }                                             ;
  ///////////////////////////////////////////////
  t  = new SceneTexture  ( destructor         ) ;
  t -> node      = uuid                         ;
  t -> create            ( image , true , Lod ) ;
  textures [ uuid ]  = t                        ;
}

void N::PictureObject::renderXY(QRectF & r,double z,QSizeF s)
{
  if ( ! Variables . contains ( "PictureUUID" ) ) return ;
  SUID u = Value ( "PictureUUID" ) . toULongLong ( )     ;
  if ( ! textures . contains ( u ) ) return              ;
  ////////////////////////////////////////////////////////
  QtGL::Disable ( GL_CULL_FACE )                         ;
  bool texture = ( bindTexture  ( u ) >= 0  )            ;
  if ( texture ) TextureRect    ( r , z , s )            ;
  if ( texture ) releaseTexture ( u         )            ;
  QtGL::Enable  ( GL_CULL_FACE )                         ;
}

void N::PictureObject::renderXY(QRectF & r,double z)
{
  if ( ! Variables . contains ( "PictureUUID" ) ) return ;
  SUID u = Value ( "PictureUUID" ) . toULongLong ( )     ;
  if ( ! textures . contains ( u ) ) return              ;
  ////////////////////////////////////////////////////////
  QtGL::Disable ( GL_CULL_FACE )                         ;
  bool texture = ( bindTexture  ( u ) >= 0 )             ;
  if ( texture ) TextureRect    ( r , z    )             ;
  if ( texture ) releaseTexture ( u        )             ;
  QtGL::Enable  ( GL_CULL_FACE )                         ;
}

void N::PictureObject::renderXY(double z)
{
  QRectF r                      ;
  ///////////////////////////////
  r . setLeft   ( minimum . x ) ;
  r . setTop    ( minimum . y ) ;
  r . setRight  ( maximum . x ) ;
  r . setBottom ( maximum . y ) ;
  renderXY      ( r , z       ) ;
}

void N::PictureObject::renderFront(void)
{
  renderXY ( maximum . z ) ;
}

void N::PictureObject::renderBack(void)
{
  renderXY ( minimum . z ) ;
}

void N::PictureObject::renderUser(void)
{
  QtGL::PushMatrix (                   ) ;
  QtGL::Disable    ( GL_LINE_SMOOTH    ) ;
  QtGL::Disable    ( GL_POLYGON_SMOOTH ) ;
  if ( Value ( "Front" ) . toBool ( ) )  {
    renderFront ( )                      ;
  }                                      ;
  if ( Value ( "Back"  ) . toBool ( ) )  {
    renderBack  ( )                      ;
  }                                      ;
  QtGL::PopMatrix  (                   ) ;
}

bool N::PictureObject::Menu (
       QWidget      * widget ,
       QPointF        pos    ,
       ControlPoint & From   ,
       ControlPoint & To     )
{
  return false ;
}

#endif
