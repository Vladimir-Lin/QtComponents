#include <qtcomponents.h>

#ifdef QT_OPENGL_LIB

N::IconObject:: IconObject    ( QObject * parent , Plan * p )
              : PictureObject (           parent ,        p )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::IconObject:: IconObject    ( QObject * parent , Plan * p , SceneDestructor * des )
              : PictureObject (           parent ,        p ,                   des )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::IconObject::~IconObject (void)
{
}

void N::IconObject::Configure (void)
{
  ControlPoint color                                    ;
  color  = QColor       ( 192 ,  192 , 192 , 192      ) ;
  addColor              (   0 , color                 ) ;
  color  = ControlPoint (   0 ,    0 ,   1 , 0.02     ) ;
  addColor              (   1 , color                 ) ;
  color  = ControlPoint (   1 ,    0 ,   0 , 0.02     ) ;
  addColor              (   2 , color                 ) ;
  color  = ControlPoint (   0 ,  0.6 ,   0 , 0.01     ) ;
  addColor              (   3 , color                 ) ;
  color  = ControlPoint (   0 ,    0 ,   0 , 0.25     ) ;
  addColor              (   4 , color                 ) ;
  color  = ControlPoint ( 0.1 , 0.70 ,   1 , 0.03     ) ;
  addColor              (   5 , color                 ) ;
  color  = ControlPoint ( 0.2 , 0.75 , 0.2 , 0.10     ) ;
  addColor              (   6 , color                 ) ;
  ///////////////////////////////////////////////////////
  QObject::setProperty  ( "Type"       , "IconObject" ) ;
  setVariable           ( "Type"       , "Icon"       ) ;
  setVariable           ( "Focus"      , false        ) ;
  setVariable           ( "Hold"       , false        ) ;
  setVariable           ( "Menu"       , false        ) ;
  setVariable           ( "Mouse"      , true         ) ;
  setVariable           ( "Emit"       , true         ) ;
  ///////////////////////////////////////////////////////
  setVariable           ( "Front"      , true         ) ;
  setVariable           ( "Back"       , true         ) ;
  setVariable           ( "Side"       , true         ) ;
  setVariable           ( "FrontIcon"  , true         ) ;
  setVariable           ( "BackIcon"   , false        ) ;
  setVariable           ( "Runner"     , true         ) ;
  ///////////////////////////////////////////////////////
  setVariable           ( "ToolTip"    , ""           ) ;
  setVariable           ( "Toggle"     , "Release"    ) ;
  setVariable           ( "Selectable" , true         ) ;
  setVariable           ( "Clickable"  , true         ) ;
  setVariable           ( "Checkable"  , false        ) ;
  setVariable           ( "Checked"    , false        ) ;
  setVariable           ( "Shell"      , true         ) ;
  ///////////////////////////////////////////////////////
  setVariable           ( "GridColor"      , 0        ) ;
  setVariable           ( "BackColor"      , 1        ) ;
  setVariable           ( "FrontColor"     , 2        ) ;
  setVariable           ( "SideColor"      , 3        ) ;
  setVariable           ( "BorderColor"    , 4        ) ;
  setVariable           ( "SeparatorColor" , 5        ) ;
  setVariable           ( "MetricColor"    , 6        ) ;
}

void N::IconObject::renderBox(void)
{
  bool clickable = Value ( "Clickable" ) . toBool ( )        ;
  bool checkable = Value ( "Checkable" ) . toBool ( )        ;
  bool checked   = Value ( "Checked"   ) . toBool ( )        ;
  ////////////////////////////////////////////////////////////
  if ( clickable && checkable && ! checked ) return          ;
  ////////////////////////////////////////////////////////////
  QtGL::PushMatrix         (                               ) ;
  ////////////////////////////////////////////////////////////
  QtGL::Disable            ( GL_CULL_FACE                  ) ;
  QtGL::Disable            ( GL_DEPTH_TEST                 ) ;
  QtGL::Disable            ( GL_LINE_SMOOTH                ) ;
  QtGL::Disable            ( GL_POLYGON_SMOOTH             ) ;
  ////////////////////////////////////////////////////////////
  if                       ( Value ( "Hold" ) . toBool ( ) ) {
    setVariable            ( "BackColor"      , 5          ) ;
    setVariable            ( "FrontColor"     , 1          ) ;
  } else                                                     {
    if ( clickable && checkable && checked )                 {
      setVariable            ( "BackColor"      , 5        ) ;
      setVariable            ( "FrontColor"     , 3        ) ;
    } else                                                   {
      setVariable            ( "BackColor"      , 1        ) ;
      setVariable            ( "FrontColor"     , 2        ) ;
    }                                                        ;
  }                                                          ;
  FeatureCube              ( minimum , maximum             ) ;
  ////////////////////////////////////////////////////////////
  QtGL::Enable             ( GL_CULL_FACE                  ) ;
  QtGL::Enable             ( GL_DEPTH_TEST                 ) ;
  ////////////////////////////////////////////////////////////
  QtGL::PopMatrix          (                               ) ;
  SceneObject::assignColor (                               ) ;
  SceneObject::renderBox   (                               ) ;
}

void N::IconObject::renderUser(void)
{
  QtGL::PushMatrix (                   )              ;
  QtGL::Disable    ( GL_LINE_SMOOTH    )              ;
  QtGL::Disable    ( GL_POLYGON_SMOOTH )              ;
  /////////////////////////////////////////////////////
  if ( Value ( "FrontIcon" ) . toBool ( ) )           {
    renderFront ( )                                   ;
  }                                                   ;
  if ( Value ( "BackIcon"  ) . toBool ( ) )           {
    renderBack  ( )                                   ;
  }                                                   ;
  QtGL::PopMatrix  (                   )              ;
  /////////////////////////////////////////////////////
  if ( ! Value ( "Shell" ) . toBool ( ) ) return      ;
  /////////////////////////////////////////////////////
  bool hit       = Value ( "Hit"       ) . toBool ( ) ;
  bool clickable = Value ( "Clickable" ) . toBool ( ) ;
  bool checkable = Value ( "Checkable" ) . toBool ( ) ;
  if ( checkable || ( clickable && hit ) )            {
    renderBox               ( )                       ;
  }                                                   ;
}

bool N::IconObject::MouseVector (
       ControlPoint & From      ,
       ControlPoint & To        ,
       BMAPs        & buttons   )
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
          Pressed      ( At    , true    )                     ;
          setVariable  ( "X"   , At . x  )                     ;
          setVariable  ( "Y"   , At . y  )                     ;
          setVariable  ( "Hit" , true    )                     ;
          ToolTip      (                 )                     ;
        break                                                  ;
      }                                                        ;
    }                                                          ;
  } else                                                       {
    if ( Value ( "Hit" ) . toBool ( ) )                        {
      Pressed          ( At    , false   )                     ;
      setVariable      ( "Hit" , false   )                     ;
      return true                                              ;
    }                                                          ;
  }                                                            ;
  return true                                                  ;
}

bool N::IconObject::MouseHover (
       ControlPoint & From     ,
       ControlPoint & To       ,
       BMAPs        & buttons  )
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

QString N::IconObject::ToolTip(void)
{
  QString AS = Value ( "ToolTip" ) . toString ( )                 ;
  QRect   RX                                                      ;
  /////////////////////////////////////////////////////////////////
  if ( AS . length ( ) > 0 )                                      {
    QToolTip::showText ( QCursor::pos() , AS , NULL , RX , 3000 ) ;
//    if ( NULL != gui ) gui -> setToolTip ( AS )                   ;
  }                                                               ;
  return AS                                                       ;
}

void N::IconObject::setToolTip(QString tooltip)
{
  setVariable ( "ToolTip" , tooltip ) ;
}

void N::IconObject::setIconSize(QSize s)
{
  maximum . x = minimum . x + s . width  ( ) ;
  maximum . y = minimum . y + s . height ( ) ;
}

void N::IconObject::setIcon (SUID uuid,QImage * image)
{
  if ( IsNull ( image ) ) return         ;
  assignTexture ( uuid , image , false ) ;
  assignUuid    ( uuid                 ) ;
  setIconSize   ( image -> size ( )    ) ;
}

void N::IconObject::setCheckable(bool enabled)
{
  setVariable ( "Checkable" , enabled ) ;
}

bool N::IconObject::setChecked(bool enabled)
{
  setVariable ( "Checked" , enabled )     ;
  return Value ( "Checked" ) . toBool ( ) ;
}

bool N::IconObject::isChecked(void)
{
  return Value ( "Checked" ) . toBool ( ) ;
}

void N::IconObject::Pressed(ControlPoint & At,bool pressed)
{ Q_UNUSED ( At ) ;
  QString when      = Value ( "Toggle"    ) . toString ( ) . toLower ( ) ;
  bool    hit       = Value ( "Hit"       ) . toBool   ( )               ;
  bool    before    = ( "release" != when )                              ;
  bool    checkable = Value ( "Checkable" ) . toBool   ( )               ;
  bool    emits     = Value ( "Emit"      ) . toBool   ( )               ;
  ////////////////////////////////////////////////////////////////////////
  if ( hit && ( ! pressed ) )                                            {
    if ( emits ) emit released ( )                                       ;
    if ( checkable && ( ! before ) )                                     {
      bool checked = isChecked ( )                                       ;
      checked = checked ? false : true                                   ;
      setChecked ( checked )                                             ;
      if ( emits ) emit toggled ( checked )                              ;
    }                                                                    ;
  }                                                                      ;
  ////////////////////////////////////////////////////////////////////////
  if ( ( ! hit ) && pressed )                                            {
    if ( emits ) emit clicked ( )                                        ;
    if ( checkable && before )                                           {
      bool checked = isChecked ( )                                       ;
      checked = checked ? false : true                                   ;
      setChecked ( checked )                                             ;
      if ( emits ) emit toggled ( checked )                              ;
    }                                                                    ;
  }                                                                      ;
  ////////////////////////////////////////////////////////////////////////
  if ( userobjs . contains ( "Selection" ) )                             {
    void    * Handler = userobjs [ "Selection" ]                         ;
    QVariants V                                                          ;
    V << pressed                                                         ;
    V << hit                                                             ;
    V << At . x                                                          ;
    V << At . y                                                          ;
    V << At . z                                                          ;
    CallDynamic ( "Selection" , this , Handler , V )                     ;
  }                                                                      ;
}

#endif
