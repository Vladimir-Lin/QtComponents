#include <qtcomponents.h>

#ifdef QT_OPENGL_LIB

N::ProgressButton:: ProgressButton ( QObject * parent , Plan * p )
                  : SceneWidget    (           parent ,        p )
                  , reporter       ( NULL                        )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::ProgressButton:: ProgressButton ( QObject * parent , Plan * p , SceneDestructor * des )
                  : SceneWidget    (           parent ,        p ,                   des )
                  , reporter       ( NULL                                                )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::ProgressButton::~ProgressButton (void)
{
  if ( NotNull(reporter) )  {
    reporter -> Leaving ( ) ;
    reporter  = NULL        ;
  }                         ;
}

void N::ProgressButton::Configure(void)
{
  ControlPoint color                                          ;
  /////////////////////////////////////////////////////////////
  color  = QColor       ( 192 ,  192 , 192 , 192            ) ;
  addColor              (    0 , color                      ) ;
  color  = ControlPoint ( 0.00 , 0.00 , 1.00 , 0.15         ) ;
  addColor              (    1 , color                      ) ;
  color  = ControlPoint ( 0.50 , 0.50 , 1.00 , 0.15         ) ;
  addColor              (    2 , color                      ) ;
  color  = ControlPoint ( 0.20 , 0.20 , 1.00 , 0.25         ) ;
  addColor              (    3 , color                      ) ;
  color  = ControlPoint ( 0.50 , 1.00 , 0.50 , 0.25         ) ;
  addColor              (    4 , color                      ) ;
  color  = ControlPoint ( 0.25 , 0.50 , 1.00 , 0.20         ) ;
  addColor              (    5 , color                      ) ;
  color  = ControlPoint ( 1.00 , 0.20 , 0.20 , 0.20         ) ;
  addColor              (    6 , color                      ) ;
  color  = ControlPoint ( 1.00 , 0.20 , 0.20 , 0.40         ) ;
  addColor              (    7 , color                      ) ;
  color  = ControlPoint ( 0.25 , 1.00 , 0.25 , 0.35         ) ;
  addColor              (    8 , color                      ) ;
  color  = ControlPoint ( 0.00 , 0.00 , 0.00 , 0.30         ) ;
  addColor              (    9 , color                      ) ;
  /////////////////////////////////////////////////////////////
  QObject::setProperty  ( "Type"         , "ProgressButton" ) ;
  setVariable           ( "Type"         , "ProgressButton" ) ;
  setVariable           ( "Focus"        , false            ) ;
  setVariable           ( "Hold"         , false            ) ;
  setVariable           ( "Menu"         , false            ) ;
  setVariable           ( "Mouse"        , true             ) ;
  setVariable           ( "Hover"        , true             ) ;
  setVariable           ( "Emit"         , true             ) ;
  /////////////////////////////////////////////////////////////
  setVariable           ( "R1"           , 1.00             ) ;
  setVariable           ( "R2"           , 0.97             ) ;
  setVariable           ( "R3"           , 0.78             ) ;
  setVariable           ( "R4"           , 0.75             ) ;
  setVariable           ( "R5"           , 0.70             ) ;
  setVariable           ( "R6"           , 0.30             ) ;
  /////////////////////////////////////////////////////////////
  setVariable           ( "Z1"           , 0.10             ) ;
  setVariable           ( "Z2"           , 0.50             ) ;
  /////////////////////////////////////////////////////////////
  setVariable           ( "Region"       , 0                ) ;
  setVariable           ( "Location"     , 0                ) ;
  /////////////////////////////////////////////////////////////
  setVariable           ( "StartedColor" , 3                ) ;
  setVariable           ( "StoppedColor" , 4                ) ;
  setVariable           ( "OuterRing"    , 5                ) ;
  setVariable           ( "InnerRing"    , 6                ) ;
  setVariable           ( "PausedColor"  , 7                ) ;
  setVariable           ( "ResumeColor"  , 8                ) ;
}

bool N::ProgressButton::isAttached(void)
{
  return NotNull ( reporter ) ;
}

void N::ProgressButton::setReporter(ProgressReporter * r)
{
  LockAt   ( "Operate" )    ;
  if ( NotNull(reporter) )  {
    reporter -> Leaving ( ) ;
    reporter  = NULL        ;
  }                         ;
  reporter  = r             ;
  reporter -> Using ( )     ;
  UnlockAt ( "Operate" )    ;
}

bool N::ProgressButton::FocusIn(void)
{
  return false ;
}

bool N::ProgressButton::FocusOut(void)
{
  return false ;
}

bool N::ProgressButton::Spot (
       ControlPoint & From   ,
       ControlPoint & To     ,
       ControlPoint & At     )
{
  if ( ! Value ( "Mouse" ) . toBool ( )  ) return false ;
  if ( ! xymSpot ( From , To , At ) ) return false      ;
  ///////////////////////////////////////////////////////
  int region = AtRegion ( At )                          ;
  switch ( region )                                     {
    case 2                                              :
    case 3                                              :
    return true                                         ;
  }                                                     ;
  ///////////////////////////////////////////////////////
  return false                                          ;
}

bool N::ProgressButton::MouseVector (
       ControlPoint & From          ,
       ControlPoint & To            ,
       BMAPs        & buttons       )
{
  if ( ! Value ( "Mouse" ) . toBool ( )  ) return false ;
  if ( ! matrices . contains ( 2 )       ) return false ;
  if ( buttons [ Universe::MouseMiddle ] ) return false ;
  if ( buttons [ Universe::MouseRight  ] ) return false ;
  ///////////////////////////////////////////////////////
  ControlPoint At                                       ;
  if ( ! Collide ( From , To , At )      ) return false ;
  ///////////////////////////////////////////////////////
  if ( buttons [ Universe::MouseLeft   ] )              {
    if ( ! isFocus ( ) )                                {
      Alert    ( Click )                                ;
    }                                                   ;
    setFocus ( true   )                                 ;
    if ( Value ( "Hit" ) . toBool ( ) )                 {
      ToolTip     (                )                    ;
      return true                                       ;
    } else                                              {
      int region = AtRegion ( At )                      ;
      setVariable      ( "Region"   , region    )       ;
      setVariable      ( "Location" , region    )       ;
      switch ( region )                                 {
        case 0                                          : // Outside
          setVariable  ( "Hit"    , false       )       ;
        break                                           ;
        case 1                                          : // Outside inner circle
          setVariable  ( "Hit"    , false       )       ;
        break                                           ;
        case 2                                          : // Big button
          setCursor    ( Qt::PointingHandCursor )       ;
          setVariable  ( "Hit"    , true        )       ;
          ToolTip      (                        )       ;
        break                                           ;
        case 3                                          : // Pause button
          setCursor    ( Qt::OpenHandCursor     )       ;
          setVariable  ( "Hit"    , true        )       ;
          ToolTip      (                        )       ;
        break                                           ;
      }                                                 ;
    }                                                   ;
  } else                                                {
    if ( Value ( "Hit" ) . toBool ( ) )                 {
      setCursor        ( Qt::ArrowCursor        )       ;
      ButtonReleased   (                        )       ;
      setVariable      ( "Region"   , 0         )       ;
      setVariable      ( "Location" , 0         )       ;
      setVariable      ( "Hit"      , false     )       ;
      return true                                       ;
    } else                                              {
      setCursor        ( Qt::ArrowCursor        )       ;
      setVariable      ( "Region"   , 0         )       ;
      setVariable      ( "Location" , 0         )       ;
      setVariable      ( "Hit"      , false     )       ;
    }                                                   ;
  }                                                     ;
  ///////////////////////////////////////////////////////
  return true                                           ;
}

bool N::ProgressButton::MouseHover (
       ControlPoint & From         ,
       ControlPoint & To           ,
       BMAPs        & buttons      )
{
  if ( ! Value ( "Mouse" ) . toBool ( )  ) return false       ;
  if ( ! isFocus             (  )        ) return false       ;
  if ( ! matrices . contains ( 2 )       ) return false       ;
  /////////////////////////////////////////////////////////////
  ControlPoint At                                             ;
  if ( ! Collide ( From , To , At )      ) return false       ;
  /////////////////////////////////////////////////////////////
  if ( Value ( "Hit" ) . toBool ( ) )                         {
    ToolTip ( )                                               ;
    return true                                               ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  int region = AtRegion ( At )                                ;
  setVariable ( "Location" , region )                         ;
  if ( region <= 1 )                                          {
    setCursor ( Qt::ArrowCursor )                             ;
    return false                                              ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  bool onlyMoving = true                                      ;
  if ( buttons [ Universe::MouseLeft   ] ) onlyMoving = false ;
  if ( buttons [ Universe::MouseMiddle ] ) onlyMoving = false ;
  if ( buttons [ Universe::MouseRight  ] ) onlyMoving = false ;
  if ( ! onlyMoving ) return true                             ;
  /////////////////////////////////////////////////////////////
  switch ( region )                                           {
    case 0                                                    :
    case 1                                                    :
      setCursor ( Qt::ArrowCursor        )                    ;
      ToolTip   (                        )                    ;
    break                                                     ;
    case 2                                                    :
      setCursor ( Qt::PointingHandCursor )                    ;
      ToolTip   (                        )                    ;
    break                                                     ;
    case 3                                                    :
      setCursor ( Qt::OpenHandCursor     )                    ;
      ToolTip   (                        )                    ;
    break                                                     ;
    default                                                   :
    break                                                     ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  return true                                                 ;
}

// 0 - Outside
// 1 - Outside inner circle
// 2 - Big button
// 3 - Pause button

int N::ProgressButton::AtRegion(ControlPoint & At)
{
  if ( At . x < minimum . x ) return 0         ;
  if ( At . x > maximum . x ) return 0         ;
  if ( At . y < minimum . y ) return 0         ;
  if ( At . y > maximum . y ) return 0         ;
  //////////////////////////////////////////////
  ControlPoint C                               ;
  double       r                               ;
  C  = minimum                                 ;
  C += maximum                                 ;
  C /= 2                                       ;
  r  = length . x                              ;
  if ( r > length . y ) r = length . y         ;
  r /= 2                                       ;
  //////////////////////////////////////////////
  double dx = At . x - C . x                   ;
  double dy = At . y - C . y                   ;
  double dr = ( dx * dx ) + ( dy * dy )        ;
  double R5 = Value ( "R5" ) . toDouble ( )    ;
  double R6 = Value ( "R6" ) . toDouble ( )    ;
  double r5                                    ;
  double r6                                    ;
  R5 *= r                                      ;
  R6 *= r                                      ;
  r5  = R5 * R5                                ;
  r6  = R6 * R6                                ;
  if ( dr > r5 ) return 1                      ;
  //////////////////////////////////////////////
  if ( dr <  r6 ) return 2                     ;
  //////////////////////////////////////////////
  double s30  = Math::fastSine   ( 30.0 )      ;
  double c30  = Math::fastCosine ( 30.0 )      ;
  double rx   = s30 * R5                       ;
  double ry   = c30 * R6                       ;
  if ( dy > - ry ) return 2                    ;
  if ( dx < - rx ) return 2                    ;
  if ( dx >   rx ) return 2                    ;
  //////////////////////////////////////////////
  double tanc = s30 / c30                      ;
  double tanp = dx  / dy                       ;
  if ( tanp < 0      ) tanp = -tanp            ;
  if ( tanp > tanc   ) return 2                ;
  //////////////////////////////////////////////
  return 3                                     ;
}

double N::ProgressButton::Radius(void)
{
  double r = length . x                ;
  if ( r > length . y ) r = length . y ;
  return ( r / 2 )                     ;
}

QString N::ProgressButton::ToolTip(void)
{
  int     region = Value ( "Location" ) . toInt ( )             ;
  QString AS     = ""                                           ;
  QRect   RX                                                    ;
  ///////////////////////////////////////////////////////////////
  switch ( region )                                             {
    case 2                                                      :
      if ( NotNull ( reporter ) )                               {
        switch ( reporter -> state )                            {
          case 0                                                :
            AS = tr("Start")                                    ;
          break                                                 ;
          case 1                                                :
            AS = tr("Stop")                                     ;
          break                                                 ;
          case 2                                                :
            AS = tr("Paused")                                   ;
          break                                                 ;
          case 3                                                :
            AS = tr("Resuming")                                 ;
          break                                                 ;
          case 4                                                :
            AS = tr("Stopping")                                 ;
          break                                                 ;
        }                                                       ;
      } else                                                    {
        AS = tr("Not attached")                                 ;
      }                                                         ;
    break                                                       ;
    case 3                                                      :
      if ( NotNull ( reporter ) )                               {
        switch ( reporter -> state )                            {
          case 0                                                :
            AS = ""                                             ;
          break                                                 ;
          case 1                                                :
            AS = tr("Pause")                                    ;
          break                                                 ;
          case 2                                                :
            AS = tr("Resume")                                   ;
          break                                                 ;
          case 3                                                :
            AS = tr("Resuming")                                 ;
          break                                                 ;
          case 4                                                :
            AS = tr("Stopping")                                 ;
          break                                                 ;
        }                                                       ;
      } else                                                    {
        AS = tr("Not attached")                                 ;
      }                                                         ;
    break                                                       ;
  }                                                             ;
  ///////////////////////////////////////////////////////////////
  QToolTip::showText ( QCursor::pos() , AS , NULL , RX , 3000 ) ;
  if ( NULL != gui ) gui -> setToolTip ( AS )                   ;
  ///////////////////////////////////////////////////////////////
  return ""                                                     ;
}

void N::ProgressButton::ButtonReleased(void)
{
  int region = Value ( "Region" ) . toInt ( ) ;
  /////////////////////////////////////////////
  switch ( region )                           {
    case 2                                    :
      Toggle        ( )                       ;
    break                                     ;
    case 3                                    :
      PauseOrResume ( )                       ;
    break                                     ;
  }                                           ;
}

void N::ProgressButton::renderDonut (
       ControlPoint & center        ,
       double         R1            ,
       double         R2            ,
       double         Z1            ,
       double         Z2            ,
       double         completed     ,
       int            op            )
{
  ControlPoint C                         ;
  ControlPoint P1                        ;
  ControlPoint P2                        ;
  ControlPoint P3                        ;
  ControlPoint P4                        ;
  double       c [ 1440 ]                ;
  double       s [ 1440 ]                ;
  int          total = completed * 1440  ;
  ////////////////////////////////////////
  if ( total < 0    ) return             ;
  if ( total > 1440 ) total = 1440       ;
  ////////////////////////////////////////
  for (int i = 0 ; i < 1440 ; i++ )      {
    double a = i                         ;
    a /= 4                               ;
    c [ i ] = Math::fastCosine ( a )     ;
    s [ i ] = Math::fastSine   ( a )     ;
  }                                      ;
  ////////////////////////////////////////
  C     = center                         ;
  C . z = 0                              ;
  ////////////////////////////////////////
  for (int i = 0 ; i < total ; i++ )     {
    int j = ( i + 1 ) % 1440             ;
    double x [ 4 ]                       ;
    double y [ 4 ]                       ;
    //////////////////////////////////////
    y [ 0 ] = R1 * c [ i ]               ;
    y [ 1 ] = R2 * c [ i ]               ;
    y [ 2 ] = R1 * c [ j ]               ;
    y [ 3 ] = R2 * c [ j ]               ;
    //////////////////////////////////////
    x [ 0 ] = R1 * s [ i ]               ;
    x [ 1 ] = R2 * s [ i ]               ;
    x [ 2 ] = R1 * s [ j ]               ;
    x [ 3 ] = R2 * s [ j ]               ;
    //////////////////////////////////////
    P1 . x =   x [ 3 ]                   ;
    P1 . y = - y [ 3 ]                   ;
    P1 . z = Z2                          ;
    P2 . x =   x [ 2 ]                   ;
    P2 . y = - y [ 2 ]                   ;
    P2 . z = Z2                          ;
    P3 . x =   x [ 0 ]                   ;
    P3 . y = - y [ 0 ]                   ;
    P3 . z = Z2                          ;
    P4 . x =   x [ 1 ]                   ;
    P4 . y = - y [ 1 ]                   ;
    P4 . z = Z2                          ;
    //////////////////////////////////////
    P1    += C                           ;
    P2    += C                           ;
    P3    += C                           ;
    P4    += C                           ;
    //////////////////////////////////////
    QtGL::Begin   ( op )                 ;
    P1 . Vertex3d (    )                 ;
    P2 . Vertex3d (    )                 ;
    P3 . Vertex3d (    )                 ;
    P4 . Vertex3d (    )                 ;
    QtGL::End     (    )                 ;
    //////////////////////////////////////
    P1 . x =   x [ 1 ]                   ;
    P1 . y = - y [ 1 ]                   ;
    P1 . z = Z1                          ;
    P2 . x =   x [ 0 ]                   ;
    P2 . y = - y [ 0 ]                   ;
    P2 . z = Z1                          ;
    P3 . x =   x [ 2 ]                   ;
    P3 . y = - y [ 2 ]                   ;
    P3 . z = Z1                          ;
    P4 . x =   x [ 3 ]                   ;
    P4 . y = - y [ 3 ]                   ;
    P4 . z = Z1                          ;
    //////////////////////////////////////
    P1    += C                           ;
    P2    += C                           ;
    P3    += C                           ;
    P4    += C                           ;
    //////////////////////////////////////
    QtGL::Begin   ( op )                 ;
    P1 . Vertex3d (    )                 ;
    P2 . Vertex3d (    )                 ;
    P3 . Vertex3d (    )                 ;
    P4 . Vertex3d (    )                 ;
    QtGL::End     (    )                 ;
    //////////////////////////////////////
    P1 . x =   x [ 1 ]                   ;
    P1 . y = - y [ 1 ]                   ;
    P1 . z = Z1                          ;
    P2 . x =   x [ 3 ]                   ;
    P2 . y = - y [ 3 ]                   ;
    P2 . z = Z1                          ;
    P3 . x =   x [ 3 ]                   ;
    P3 . y = - y [ 3 ]                   ;
    P3 . z = Z2                          ;
    P4 . x =   x [ 1 ]                   ;
    P4 . y = - y [ 1 ]                   ;
    P4 . z = Z2                          ;
    //////////////////////////////////////
    P1    += C                           ;
    P2    += C                           ;
    P3    += C                           ;
    P4    += C                           ;
    //////////////////////////////////////
    QtGL::Begin   ( op )                 ;
    P1 . Vertex3d (    )                 ;
    P2 . Vertex3d (    )                 ;
    P3 . Vertex3d (    )                 ;
    P4 . Vertex3d (    )                 ;
    QtGL::End     (    )                 ;
    //////////////////////////////////////
    P1 . x =   x [ 2 ]                   ;
    P1 . y = - y [ 2 ]                   ;
    P1 . z = Z1                          ;
    P2 . x =   x [ 0 ]                   ;
    P2 . y = - y [ 0 ]                   ;
    P2 . z = Z1                          ;
    P3 . x =   x [ 0 ]                   ;
    P3 . y = - y [ 0 ]                   ;
    P3 . z = Z2                          ;
    P4 . x =   x [ 2 ]                   ;
    P4 . y = - y [ 2 ]                   ;
    P4 . z = Z2                          ;
    //////////////////////////////////////
    P1    += C                           ;
    P2    += C                           ;
    P3    += C                           ;
    P4    += C                           ;
    //////////////////////////////////////
    QtGL::Begin   ( op )                 ;
    P1 . Vertex3d (    )                 ;
    P2 . Vertex3d (    )                 ;
    P3 . Vertex3d (    )                 ;
    P4 . Vertex3d (    )                 ;
    QtGL::End     (    )                 ;
  }                                      ;
}

void N::ProgressButton::renderDonut(void)
{
  ControlPoint C                                                 ;
  double       R1                                                ;
  double       R2                                                ;
  double       Z1                                                ;
  double       Z2                                                ;
  double       factor = 0.0                                      ;
  ////////////////////////////////////////////////////////////////
  if ( NotNull ( reporter ) )                                    {
    if ( reporter -> total > 0 )                                 {
      factor  = reporter -> value                                ;
      factor /= reporter -> total                                ;
    }                                                            ;
  }                                                              ;
  ////////////////////////////////////////////////////////////////
  C   = minimum                                                  ;
  C  += maximum                                                  ;
  C  /= 2                                                        ;
  ////////////////////////////////////////////////////////////////
  // Render outside donut
  R1  = Radius     (                                           ) ;
  R2  = R1 * Value ( "R4" ) . toDouble ( )                       ;
  R1  = R1 * Value ( "R1" ) . toDouble ( )                       ;
  Z1  = minimum . z + Value ( "Z1" ) . toDouble ( )              ;
  Z2  = maximum . z - Value ( "Z1" ) . toDouble ( )              ;
  assumeColor      ( "OuterRing"                               ) ;
  renderDonut      ( C , R1 , R2 , Z1 , Z2 , 1.0    , GL_QUADS ) ;
  ////////////////////////////////////////////////////////////////
  // Render inside progress donut
  R1  = Radius     (                                           ) ;
  R2  = R1 * Value ( "R3" ) . toDouble ( )                       ;
  R1  = R1 * Value ( "R2" ) . toDouble ( )                       ;
  Z1  = minimum . z + Value ( "Z2" ) . toDouble ( )              ;
  Z2  = maximum . z - Value ( "Z2" ) . toDouble ( )              ;
  assumeColor      ( "InnerRing"                               ) ;
  renderDonut      ( C , R1 , R2 , Z1 , Z2 , factor , GL_QUADS ) ;
}

void N::ProgressButton::renderPause(void)
{
  ControlPoint C                                              ;
  ControlPoint P1                                             ;
  ControlPoint P2                                             ;
  ControlPoint P3                                             ;
  ControlPoint P4                                             ;
  double       R5                                             ;
  double       R6                                             ;
  double       Z1                                             ;
  double       Z2                                             ;
  double       c [ 1440 ]                                     ;
  double       s [ 1440 ]                                     ;
  /////////////////////////////////////////////////////////////
  if ( NotNull ( reporter ) )                                 {
    switch ( reporter -> state )                              {
      case 0                                                  :
        assumeColor ( "StartedColor" )                        ;
      break                                                   ;
      case 1                                                  :
        assumeColor ( "StoppedColor" )                        ;
      break                                                   ;
      case 2                                                  :
        assumeColor ( "PausedColor" )                         ;
      break                                                   ;
      case 3                                                  :
        assumeColor ( "ResumeColor" )                         ;
      break                                                   ;
      case 4                                                  :
        assumeColor ( "StoppedColor" )                        ;
      break                                                   ;
    }                                                         ;
  } else                                                      {
    assumeColor     ( "ResumeColor" )                         ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  C      = minimum                                            ;
  C     += maximum                                            ;
  C     /= 2                                                  ;
  C . z  = 0                                                  ;
  /////////////////////////////////////////////////////////////
  for (int i = 0 ; i < 1440 ; i++ )                           {
    double a = i                                              ;
    a /= 4                                                    ;
    c [ i ] = Math::fastCosine ( a )                          ;
    s [ i ] = Math::fastSine   ( a )                          ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  Z1  = minimum . z + Value ( "Z1" ) . toDouble ( )           ;
  Z2  = maximum . z - Value ( "Z2" ) . toDouble ( )           ;
  /////////////////////////////////////////////////////////////
  R5  = Radius     (                                        ) ;
  R6  = R5 * Value ( "R6" ) . toDouble ( )                    ;
  R5  = R5 * Value ( "R5" ) . toDouble ( )                    ;
  /////////////////////////////////////////////////////////////
  // render maximum . z surface
  QtGL::Polygon    (                                        ) ;
  /////////////////////////////////////////////////////////////
  // put bottom curve
  for (int i = 150 * 4 ; i <= 210 * 4 ; i++ )                 {
    double x = - s [ i ] * R5                                 ;
    double y =   c [ i ] * R5                                 ;
    P1 . x = x                                                ;
    P1 . y = y                                                ;
    P1 . z = Z2                                               ;
    P1    += C                                                ;
    P1 . Vertex3d ( )                                         ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  // put top two points
  P2 . x = - s [ 210 * 4 ] * R6                               ;
  P2 . y =   c [ 210 * 4 ] * R6                               ;
  P2 . z = Z2                                                 ;
  P2    += C                                                  ;
  P2 . Vertex3d ( )                                           ;
  /////////////////////////////////////////////////////////////
  P3 . x = - s [ 150 * 4 ] * R6                               ;
  P3 . y =   c [ 150 * 4 ] * R6                               ;
  P3 . z = Z2                                                 ;
  P3    += C                                                  ;
  P3 . Vertex3d ( )                                           ;
  /////////////////////////////////////////////////////////////
  QtGL::End        (                                        ) ;
  /////////////////////////////////////////////////////////////
  // render minimum . z surface
  QtGL::Polygon    (                                        ) ;
  /////////////////////////////////////////////////////////////
  // put bottom curve
  for (int i = 150 * 4 ; i <= 210 * 4 ; i++ )                 {
    double x = - s [ 1440 - i ] * R5                          ;
    double y =   c [ 1440 - i ] * R5                          ;
    P1 . x = x                                                ;
    P1 . y = y                                                ;
    P1 . z = Z1                                               ;
    P1    += C                                                ;
    P1 . Vertex3d ( )                                         ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  // put top two points
  P2 . x = - s [ 150 * 4 ] * R6                               ;
  P2 . y =   c [ 150 * 4 ] * R6                               ;
  P2 . z = Z1                                                 ;
  P2    += C                                                  ;
  P2 . Vertex3d ( )                                           ;
  /////////////////////////////////////////////////////////////
  P3 . x = - s [ 210 * 4 ] * R6                               ;
  P3 . y =   c [ 210 * 4 ] * R6                               ;
  P3 . z = Z1                                                 ;
  P3    += C                                                  ;
  P3 . Vertex3d ( )                                           ;
  /////////////////////////////////////////////////////////////
  QtGL::End        (                                        ) ;
  /////////////////////////////////////////////////////////////
  // render curve side surface
  /////////////////////////////////////////////////////////////
  for (int i = 150 * 4 ; i < 210 * 4 ; i++ )                  {
    int    j = i + 1                                          ;
    double x1 = - s [ i ] * R5                                ;
    double y1 =   c [ i ] * R5                                ;
    double x2 = - s [ j ] * R5                                ;
    double y2 =   c [ j ] * R5                                ;
    P1 . x = x1                                               ;
    P1 . y = y1                                               ;
    P1 . z = Z1                                               ;
    P1    += C                                                ;
    P2 . x = x2                                               ;
    P2 . y = y2                                               ;
    P2 . z = Z1                                               ;
    P2    += C                                                ;
    P3 . x = x2                                               ;
    P3 . y = y2                                               ;
    P3 . z = Z2                                               ;
    P3    += C                                                ;
    P4 . x = x1                                               ;
    P4 . y = y1                                               ;
    P4 . z = Z2                                               ;
    P4    += C                                                ;
    QtGL::Quadrilateral (                                   ) ;
    P1 . Vertex3d       (                                   ) ;
    P2 . Vertex3d       (                                   ) ;
    P3 . Vertex3d       (                                   ) ;
    P4 . Vertex3d       (                                   ) ;
    QtGL::End           (                                   ) ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  // render left side surface
  P1 . x = - s [ 150 * 4 ] * R5                               ;
  P1 . y =   c [ 150 * 4 ] * R5                               ;
  P1 . z = Z1                                                 ;
  P1    += C                                                  ;
  P2 . x = - s [ 150 * 4 ] * R6                               ;
  P2 . y =   c [ 150 * 4 ] * R6                               ;
  P2 . z = Z1                                                 ;
  P2    += C                                                  ;
  P3 . x = - s [ 150 * 4 ] * R5                               ;
  P3 . y =   c [ 150 * 4 ] * R5                               ;
  P3 . z = Z2                                                 ;
  P3    += C                                                  ;
  P4 . x = - s [ 150 * 4 ] * R6                               ;
  P4 . y =   c [ 150 * 4 ] * R6                               ;
  P4 . z = Z2                                                 ;
  P4    += C                                                  ;
  QtGL::Quadrilateral   (                                   ) ;
  P1 . Vertex3d         (                                   ) ;
  P3 . Vertex3d         (                                   ) ;
  P4 . Vertex3d         (                                   ) ;
  P2 . Vertex3d         (                                   ) ;
  QtGL::End             (                                   ) ;
  /////////////////////////////////////////////////////////////
  // render right side surface
  P1 . x = - s [ 210 * 4 ] * R5                               ;
  P1 . y =   c [ 210 * 4 ] * R5                               ;
  P1 . z = Z1                                                 ;
  P1    += C                                                  ;
  P2 . x = - s [ 210 * 4 ] * R6                               ;
  P2 . y =   c [ 210 * 4 ] * R6                               ;
  P2 . z = Z1                                                 ;
  P2    += C                                                  ;
  P3 . x = - s [ 210 * 4 ] * R5                               ;
  P3 . y =   c [ 210 * 4 ] * R5                               ;
  P3 . z = Z2                                                 ;
  P3    += C                                                  ;
  P4 . x = - s [ 210 * 4 ] * R6                               ;
  P4 . y =   c [ 210 * 4 ] * R6                               ;
  P4 . z = Z2                                                 ;
  P4    += C                                                  ;
  QtGL::Quadrilateral   (                                   ) ;
  P1 . Vertex3d         (                                   ) ;
  P2 . Vertex3d         (                                   ) ;
  P4 . Vertex3d         (                                   ) ;
  P3 . Vertex3d         (                                   ) ;
  QtGL::End             (                                   ) ;
  /////////////////////////////////////////////////////////////
  // render inner side surface
  P1 . x = - s [ 150 * 4 ] * R5                               ;
  P1 . y =   c [ 150 * 4 ] * R5                               ;
  P1 . z = Z1                                                 ;
  P1    += C                                                  ;
  P2 . x = - s [ 150 * 4 ] * R5                               ;
  P2 . y =   c [ 150 * 4 ] * R5                               ;
  P2 . z = Z2                                                 ;
  P2    += C                                                  ;
  P3 . x = - s [ 210 * 4 ] * R5                               ;
  P3 . y =   c [ 210 * 4 ] * R5                               ;
  P3 . z = Z1                                                 ;
  P3    += C                                                  ;
  P4 . x = - s [ 210 * 4 ] * R5                               ;
  P4 . y =   c [ 210 * 4 ] * R5                               ;
  P4 . z = Z2                                                 ;
  P4    += C                                                  ;
  QtGL::Quadrilateral   (                                   ) ;
  P1 . Vertex3d         (                                   ) ;
  P2 . Vertex3d         (                                   ) ;
  P4 . Vertex3d         (                                   ) ;
  P3 . Vertex3d         (                                   ) ;
  QtGL::End             (                                   ) ;
}

void N::ProgressButton::renderButton(void)
{
  ControlPoint C                                              ;
  ControlPoint P1                                             ;
  ControlPoint P2                                             ;
  ControlPoint P3                                             ;
  ControlPoint P4                                             ;
  double       R5                                             ;
  double       R6                                             ;
  double       Z1                                             ;
  double       Z2                                             ;
  double       c [ 1440 ]                                     ;
  double       s [ 1440 ]                                     ;
  /////////////////////////////////////////////////////////////
  if ( NotNull ( reporter ) )                                 {
    switch ( reporter -> state )                              {
      case 0                                                  :
        assumeColor ( "StoppedColor" )                        ;
      break                                                   ;
      case 1                                                  :
        assumeColor ( "StartedColor" )                        ;
      break                                                   ;
      case 2                                                  :
        assumeColor ( "StartedColor" )                        ;
      break                                                   ;
      case 3                                                  :
        assumeColor ( "StartedColor" )                        ;
      break                                                   ;
      case 4                                                  :
        assumeColor ( "StartedColor" )                        ;
      break                                                   ;
    }                                                         ;
  } else                                                      {
    assumeColor     ( "StoppedColor" )                        ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  C      = minimum                                            ;
  C     += maximum                                            ;
  C     /= 2                                                  ;
  C . z  = 0                                                  ;
  /////////////////////////////////////////////////////////////
  for (int i = 0 ; i < 1440 ; i++ )                           {
    double a = i                                              ;
    a /= 4                                                    ;
    c [ i ] = Math::fastCosine ( a )                          ;
    s [ i ] = Math::fastSine   ( a )                          ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  Z1  = minimum . z + Value ( "Z1" ) . toDouble ( )           ;
  Z2  = maximum . z - Value ( "Z1" ) . toDouble ( )           ;
  /////////////////////////////////////////////////////////////
  R5  = Radius     (                                        ) ;
  R6  = R5 * Value ( "R6" ) . toDouble ( )                    ;
  R5  = R5 * Value ( "R5" ) . toDouble ( )                    ;
  /////////////////////////////////////////////////////////////
  // render maximum half circle
  QtGL::Polygon    (                                        ) ;
  /////////////////////////////////////////////////////////////
  C . z = 0                                                   ;
  for (int i = 0 ; i <= 180 * 4 ; i++ )                       {
    double x = c [ i ] * R5                                   ;
    double y = s [ i ] * R5                                   ;
    P1 . x = x                                                ;
    P1 . y = y                                                ;
    P1 . z = Z2                                               ;
    P1    += C                                                ;
    P1 . Vertex3d ( )                                         ;
  }                                                           ;
  QtGL::End        (                                        ) ;
  /////////////////////////////////////////////////////////////
  // render minimum half circle
  QtGL::Polygon    (                                        ) ;
  /////////////////////////////////////////////////////////////
  C . z = 0                                                   ;
  for (int i = 0 ; i <= 180 * 4 ; i++ )                       {
    double x = - c [ i ] * R5                                 ;
    double y =   s [ i ] * R5                                 ;
    P1 . x = x                                                ;
    P1 . y = y                                                ;
    P1 . z = Z1                                               ;
    P1    += C                                                ;
    P1 . Vertex3d ( )                                         ;
  }                                                           ;
  QtGL::End        (                                        ) ;
  /////////////////////////////////////////////////////////////
  // render half circle side surface
  /////////////////////////////////////////////////////////////
  C . z = 0                                                   ;
  for (int i = 0 ; i < 720 ; i++ )                            {
    int    j  = i + 1                                         ;
    double x1 = - c [ i ] * R5                                ;
    double y1 =   s [ i ] * R5                                ;
    double x2 = - c [ j ] * R5                                ;
    double y2 =   s [ j ] * R5                                ;
    P1 . x = x1                                               ;
    P1 . y = y1                                               ;
    P1 . z = Z1                                               ;
    P1    += C                                                ;
    P2 . x = x2                                               ;
    P2 . y = y2                                               ;
    P2 . z = Z1                                               ;
    P2    += C                                                ;
    P3 . x = x2                                               ;
    P3 . y = y2                                               ;
    P3 . z = Z2                                               ;
    P3    += C                                                ;
    P4 . x = x1                                               ;
    P4 . y = y1                                               ;
    P4 . z = Z1                                               ;
    P4    += C                                                ;
    QtGL::Quadrilateral (                                   ) ;
    P1 . Vertex3d       (                                   ) ;
    P2 . Vertex3d       (                                   ) ;
    P3 . Vertex3d       (                                   ) ;
    P4 . Vertex3d       (                                   ) ;
    QtGL::End           (                                   ) ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  // render maximum . z left side pie
  QtGL::Polygon    (                                        ) ;
  C . z  = Z2                                                 ;
  C . Vertex3d ( )                                            ;
  C . z  = 0                                                  ;
  for (int i = 0 ; i <= 58 * 4 ; i++ )                        {
    double x = - c [ i ] * R5                                 ;
    double y = - s [ i ] * R5                                 ;
    P1 . x = x                                                ;
    P1 . y = y                                                ;
    P1 . z = Z2                                               ;
    P1    += C                                                ;
    P1 . Vertex3d ( )                                         ;
  }                                                           ;
  QtGL::End        (                                        ) ;
  /////////////////////////////////////////////////////////////
  // render minimum . z left side pie
  QtGL::Polygon    (                                        ) ;
  C . z  = Z1                                                 ;
  C . Vertex3d ( )                                            ;
  C . z  = 0                                                  ;
  for (int i = 0 ; i <= 58 * 4 ; i++ )                        {
    double x = - c [ 58 * 4 - i ] * R5                        ;
    double y = - s [ 58 * 4 - i ] * R5                        ;
    P1 . x = x                                                ;
    P1 . y = y                                                ;
    P1 . z = Z1                                               ;
    P1    += C                                                ;
    P1 . Vertex3d ( )                                         ;
  }                                                           ;
  QtGL::End        (                                        ) ;
  /////////////////////////////////////////////////////////////
  // render left side pie curve surface
  for (int i = 0 ; i < 58 * 4 ; i++ )                         {
    int    j  = i + 1                                         ;
    double x1 = - c [ i ] * R5                                ;
    double y1 = - s [ i ] * R5                                ;
    double x2 = - c [ j ] * R5                                ;
    double y2 = - s [ j ] * R5                                ;
    P1 . x = x1                                               ;
    P1 . y = y1                                               ;
    P1 . z = Z1                                               ;
    P1    += C                                                ;
    P2 . x = x1                                               ;
    P2 . y = y1                                               ;
    P2 . z = Z2                                               ;
    P2    += C                                                ;
    P3 . x = x2                                               ;
    P3 . y = y2                                               ;
    P3 . z = Z2                                               ;
    P3    += C                                                ;
    P4 . x = x2                                               ;
    P4 . y = y2                                               ;
    P4 . z = Z1                                               ;
    P4    += C                                                ;
    QtGL::Quadrilateral (                                   ) ;
    P1 . Vertex3d       (                                   ) ;
    P2 . Vertex3d       (                                   ) ;
    P3 . Vertex3d       (                                   ) ;
    P4 . Vertex3d       (                                   ) ;
    QtGL::End           (                                   ) ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  // render maximum . z right side pie
  QtGL::Polygon    (                                        ) ;
  C . z  = Z2                                                 ;
  C . Vertex3d ( )                                            ;
  C . z  = 0                                                  ;
  for (int i = 0 ; i <= 58 * 4 ; i++ )                        {
    double x =   c [ 58 * 4 - i ] * R5                        ;
    double y = - s [ 58 * 4 - i ] * R5                        ;
    P1 . x = x                                                ;
    P1 . y = y                                                ;
    P1 . z = Z2                                               ;
    P1    += C                                                ;
    P1 . Vertex3d ( )                                         ;
  }                                                           ;
  QtGL::End        (                                        ) ;
  /////////////////////////////////////////////////////////////
  // render minimum . z right side pie
  QtGL::Polygon    (                                        ) ;
  C . z  = Z1                                                 ;
  C . Vertex3d ( )                                            ;
  C . z  = 0                                                  ;
  for (int i = 0 ; i <= 58 * 4 ; i++ )                        {
    double x =   c [ i ] * R5                                 ;
    double y = - s [ i ] * R5                                 ;
    P1 . x = x                                                ;
    P1 . y = y                                                ;
    P1 . z = Z1                                               ;
    P1    += C                                                ;
    P1 . Vertex3d ( )                                         ;
  }                                                           ;
  QtGL::End        (                                        ) ;
  /////////////////////////////////////////////////////////////
  // render right side pie curve surface
  for (int i = 0 ; i < 58 * 4 ; i++ )                         {
    int    j  = i + 1                                         ;
    double x1 = - c [ 58 * 4 - i ] * R5                       ;
    double y1 = - s [ 58 * 4 - i ] * R5                       ;
    double x2 = - c [ 58 * 4 - j ] * R5                       ;
    double y2 = - s [ 58 * 4 - j ] * R5                       ;
    P1 . x = x1                                               ;
    P1 . y = y1                                               ;
    P1 . z = Z1                                               ;
    P1    += C                                                ;
    P2 . x = x1                                               ;
    P2 . y = y1                                               ;
    P2 . z = Z2                                               ;
    P2    += C                                                ;
    P3 . x = x2                                               ;
    P3 . y = y2                                               ;
    P3 . z = Z2                                               ;
    P3    += C                                                ;
    P4 . x = x2                                               ;
    P4 . y = y2                                               ;
    P4 . z = Z1                                               ;
    P4    += C                                                ;
    QtGL::Quadrilateral (                                   ) ;
    P1 . Vertex3d       (                                   ) ;
    P2 . Vertex3d       (                                   ) ;
    P3 . Vertex3d       (                                   ) ;
    P4 . Vertex3d       (                                   ) ;
    QtGL::End           (                                   ) ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  // render maximum . z internal triangle
  C  . z = 0                                                  ;
  P1 . x =   c [ 58 * 4 ] * R6                                ;
  P1 . y = - s [ 58 * 4 ] * R6                                ;
  P1 . z = Z2                                                 ;
  P2 . x = - P1 . x                                           ;
  P2 . y =   P1 . y                                           ;
  P2 . z = Z2                                                 ;
  P1    += C                                                  ;
  P2    += C                                                  ;
  C  . z = Z2                                                 ;
  QtGL::Polygon    (                                        ) ;
  C  . Vertex3d ( )                                           ;
  P1 . Vertex3d ( )                                           ;
  P2 . Vertex3d ( )                                           ;
  QtGL::End        (                                        ) ;
  /////////////////////////////////////////////////////////////
  // render minimum . z internal triangle
  C  . z = Z1                                                 ;
  P1 . z = Z1                                                 ;
  P2 . z = Z1                                                 ;
  QtGL::Polygon    (                                        ) ;
  C  . Vertex3d ( )                                           ;
  P2 . Vertex3d ( )                                           ;
  P1 . Vertex3d ( )                                           ;
  QtGL::End        (                                        ) ;
  /////////////////////////////////////////////////////////////
  // render internal left side triangles
  C  . z = 0                                                  ;
  P1 . x = - c [ 58 * 4 ] * R5                                ;
  P1 . y = - s [ 58 * 4 ] * R5                                ;
  P1 . z = Z1                                                 ;
  P1    += C                                                  ;
  P2 . x = - c [ 58 * 4 ] * R5                                ;
  P2 . y = - s [ 58 * 4 ] * R5                                ;
  P2 . z = Z2                                                 ;
  P2    += C                                                  ;
  P3 . x = - c [ 58 * 4 ] * R6                                ;
  P3 . y = - s [ 58 * 4 ] * R6                                ;
  P3 . z = Z1                                                 ;
  P3    += C                                                  ;
  P4 . x = - c [ 58 * 4 ] * R6                                ;
  P4 . y = - s [ 58 * 4 ] * R6                                ;
  P4 . z = Z2                                                 ;
  P4    += C                                                  ;
  QtGL::Quadrilateral (                                     ) ;
  P1 . Vertex3d       (                                     ) ;
  P3 . Vertex3d       (                                     ) ;
  P4 . Vertex3d       (                                     ) ;
  P2 . Vertex3d       (                                     ) ;
  QtGL::End           (                                     ) ;
  /////////////////////////////////////////////////////////////
  // render internal right side triangles
  C  . z = 0                                                  ;
  P1 . x =   c [ 58 * 4 ] * R5                                ;
  P1 . y = - s [ 58 * 4 ] * R5                                ;
  P1 . z = Z1                                                 ;
  P1    += C                                                  ;
  P2 . x =   c [ 58 * 4 ] * R5                                ;
  P2 . y = - s [ 58 * 4 ] * R5                                ;
  P2 . z = Z2                                                 ;
  P2    += C                                                  ;
  P3 . x =   c [ 58 * 4 ] * R6                                ;
  P3 . y = - s [ 58 * 4 ] * R6                                ;
  P3 . z = Z1                                                 ;
  P3    += C                                                  ;
  P4 . x =   c [ 58 * 4 ] * R6                                ;
  P4 . y = - s [ 58 * 4 ] * R6                                ;
  P4 . z = Z2                                                 ;
  P4    += C                                                  ;
  QtGL::Quadrilateral (                                     ) ;
  P1 . Vertex3d       (                                     ) ;
  P2 . Vertex3d       (                                     ) ;
  P4 . Vertex3d       (                                     ) ;
  P3 . Vertex3d       (                                     ) ;
  QtGL::End           (                                     ) ;
  /////////////////////////////////////////////////////////////
  // render internal side triangles
  C  . z = 0                                                  ;
  P1 . x = - c [ 58 * 4 ] * R6                                ;
  P1 . y = - s [ 58 * 4 ] * R6                                ;
  P1 . z = Z1                                                 ;
  P1    += C                                                  ;
  P2 . x = - c [ 58 * 4 ] * R6                                ;
  P2 . y = - s [ 58 * 4 ] * R6                                ;
  P2 . z = Z2                                                 ;
  P2    += C                                                  ;
  P3 . x =   c [ 58 * 4 ] * R6                                ;
  P3 . y = - s [ 58 * 4 ] * R6                                ;
  P3 . z = Z1                                                 ;
  P3    += C                                                  ;
  P4 . x =   c [ 58 * 4 ] * R6                                ;
  P4 . y = - s [ 58 * 4 ] * R6                                ;
  P4 . z = Z2                                                 ;
  P4    += C                                                  ;
  QtGL::Quadrilateral (                                     ) ;
  P1 . Vertex3d       (                                     ) ;
  P3 . Vertex3d       (                                     ) ;
  P4 . Vertex3d       (                                     ) ;
  P2 . Vertex3d       (                                     ) ;
  QtGL::End           (                                     ) ;
  /////////////////////////////////////////////////////////////
}

void N::ProgressButton::renderUser(void)
{
  QtGL::PushMatrix (                   ) ;
  QtGL::Disable    ( GL_DEPTH_TEST     ) ;
  QtGL::Disable    ( GL_CULL_FACE      ) ;
  QtGL::Disable    ( GL_LINE_SMOOTH    ) ;
  QtGL::Disable    ( GL_POLYGON_SMOOTH ) ;
  ////////////////////////////////////////
  renderDonut      (                   ) ;
  renderPause      (                   ) ;
  renderButton     (                   ) ;
  ////////////////////////////////////////
  QtGL::Enable     ( GL_LINE_SMOOTH    ) ;
  QtGL::Enable     ( GL_POLYGON_SMOOTH ) ;
  QtGL::Enable     ( GL_CULL_FACE      ) ;
  QtGL::Enable     ( GL_DEPTH_TEST     ) ;
  QtGL::PopMatrix  (                   ) ;
}

void N::ProgressButton::Toggle(void)
{
  if ( IsNull ( reporter ) ) return          ;
  bool emits = Value ( "Emit" ) . toBool ( ) ;
  if ( reporter -> running )                 {
    reporter -> setRunning ( false )         ;
    if ( emits ) emit Starting ( )           ;
  } else                                     {
    reporter -> setRunning ( true  )         ;
    if ( emits ) emit Complete ( )           ;
  }                                          ;
}

void N::ProgressButton::PauseOrResume(void)
{
  if ( IsNull ( reporter ) ) return          ;
  bool emits = Value ( "Emit" ) . toBool ( ) ;
  if ( 1 == reporter -> state )              { // running => Pause
    reporter->state = 2                      ;
    if ( emits ) emit Pause  ( )             ;
  } else
  if ( 2 == reporter -> state )              { // running => Resume
    reporter->state = 3                      ;
    if ( emits ) emit Resume ( )             ;
  }                                          ;
}

#endif
