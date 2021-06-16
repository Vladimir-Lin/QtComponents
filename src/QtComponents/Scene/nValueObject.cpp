#include <qtcomponents.h>

#ifdef QT_OPENGL_LIB

N::ValueObject:: ValueObject ( QObject * parent , Plan * p )
               : SceneWidget (           parent ,        p )
               , iValue      ( NULL                        )
               , dValue      ( NULL                        )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::ValueObject:: ValueObject ( QObject * parent , Plan * p , SceneDestructor * des )
               : SceneWidget (           parent ,        p ,                   des )
               , iValue      ( NULL                                                )
               , dValue      ( NULL                                                )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::ValueObject::~ValueObject (void)
{
}

void N::ValueObject::Configure(void)
{
  ControlPoint color                                   ;
  color  = QColor       ( 192 ,  192 , 192 , 192     ) ;
  addColor              (   0 , color                ) ;
  color  = ControlPoint (   0 ,    0 ,   1 , 0.15    ) ;
  addColor              (   1 , color                ) ;
  color  = ControlPoint ( 0.5 ,  0.5 ,   1 , 0.15    ) ;
  addColor              (   2 , color                ) ;
  color  = ControlPoint ( 0.2 ,  0.2 ,   1 , 0.25    ) ;
  addColor              (   3 , color                ) ;
  color  = ControlPoint ( 0.6 ,  0.6 ,   1 , 0.25    ) ;
  addColor              (   4 , color                ) ;
  color  = ControlPoint ( 0.2 ,  0.2 ,   1 , 0.30    ) ;
  addColor              (   5 , color                ) ;
  color  = ControlPoint ( 0.6 ,  0.6 ,   1 , 0.30    ) ;
  addColor              (   6 , color                ) ;
  color  = ControlPoint ( 0.2 ,  0.2 ,   1 , 0.40    ) ;
  addColor              (   7 , color                ) ;
  color  = ControlPoint ( 0.6 ,  0.6 ,   1 , 0.40    ) ;
  addColor              (   8 , color                ) ;
  color  = ControlPoint (   0 ,    0 ,   0 , 0.20    ) ;
  addColor              (   5 , color                ) ;
  //////////////////////////////////////////////////////
  QObject::setProperty  ( "Type"   , "ValueObject"   ) ;
  setVariable           ( "Type"        , "Value"    ) ;
  setVariable           ( "Focus"       , false      ) ;
  setVariable           ( "Hold"        , false      ) ;
  setVariable           ( "Menu"        , true       ) ;
  setVariable           ( "Mouse"       , true       ) ;
  //////////////////////////////////////////////////////
  setVariable           ( "MidColor"    , 1          ) ;
  setVariable           ( "SideColor"   , 2          ) ;
  setVariable           ( "GetMid"      , 3          ) ;
  setVariable           ( "GetSide"     , 4          ) ;
  setVariable           ( "HoldMid"     , 5          ) ;
  setVariable           ( "HoldSide"    , 6          ) ;
  setVariable           ( "FocusMid"    , 7          ) ;
  setVariable           ( "FocusSide"   , 8          ) ;
  setVariable           ( "Scale"       , 90         ) ;
  setVariable           ( "Distance"    , 2.5        ) ;
  //////////////////////////////////////////////////////
  setVariable           ( "Start"       ,   0.0      ) ;
  setVariable           ( "End"         , 100.0      ) ;
  setVariable           ( "Value"       ,   0.0      ) ;
  setVariable           ( "Step"        ,  10.0      ) ;
  setVariable           ( "Prefer"      , "double"   ) ;
  setVariable           ( "Horizontal"  , true       ) ;
  setVariable           ( "Vertical"    , true       ) ;
  //////////////////////////////////////////////////////
  setVariable           ( "Emit"        , true       ) ;
  //////////////////////////////////////////////////////
  QString TTT = tr("%1 between %2 and %3")             ;
  setVariable           ( "ToolTipTemplate" , TTT    ) ;
}

bool N::ValueObject::FocusIn(void)
{
  nKickOut ( IsNull ( plan ) , false )       ;
  if ( Value ( "Horizontal" ) . toBool ( ) ) {
    LinkAction ( Previous , Previous ( ) )   ;
    LinkAction ( Next     , Next     ( ) )   ;
  }                                          ;
  if ( Value ( "Vertical"   ) . toBool ( ) ) {
    LinkAction ( GoDown   , Previous ( ) )   ;
    LinkAction ( GoUp     , Next     ( ) )   ;
  }                                          ;
  return true                                ;
}

bool N::ValueObject::FocusOut(void)
{
  return false ;
}

void N::ValueObject::setRange(double s,double e)
{
  setVariable ( "Start" , s )                   ;
  setVariable ( "End"   , e )                   ;
  if ( ! Value ( "Emit" ) . toBool ( ) ) return ;
  emit rangeChanged ( s , e )                   ;
}

void N::ValueObject::setStep(double s)
{
  setVariable ( "Step" , s )                    ;
  if ( ! Value ( "Emit" ) . toBool ( ) ) return ;
  emit stepChanged ( s )                        ;
}

void N::ValueObject::setCurrent(qint64 v)
{
  LockAt       ( "Operate"     )      ;
  setVariable  ( "Value" , v   )      ;
  if ( NULL != dValue ) (*dValue) = v ;
  if ( NULL != iValue ) (*iValue) = v ;
  UnlockAt     ( "Operate"     )      ;
  indexChanged (               )      ;
}

void N::ValueObject::setDouble(double v)
{
  LockAt       ( "Operate"     )      ;
  setVariable  ( "Value" , v   )      ;
  if ( NULL != dValue ) (*dValue) = v ;
  if ( NULL != iValue ) (*iValue) = v ;
  UnlockAt     ( "Operate"     )      ;
  indexChanged (               )      ;
}

void N::ValueObject::assignValue(qint64 * v)
{
  LockAt   ( "Operate" )         ;
  iValue = v                     ;
  if ( NULL != v )               {
    setVariable ( "Value" , *v ) ;
  }                              ;
  UnlockAt ( "Operate" )         ;
}

void N::ValueObject::assignValue(double * v)
{
  LockAt   ( "Operate" )         ;
  dValue = v                     ;
  if ( NULL != v )               {
    setVariable ( "Value" , *v ) ;
  }                              ;
  UnlockAt ( "Operate" )         ;
}

void N::ValueObject::indexChanged (void)
{
  if ( ! Value ( "Emit" ) . toBool ( ) ) return ;
  double s = Value ( "Start" ) . toDouble ( )   ;
  double e = Value ( "End"   ) . toDouble ( )   ;
  double v = Value ( "Value" ) . toDouble ( )   ;
  if ( NotNull ( iValue ) ) v = (*iValue)       ;
  if ( NotNull ( dValue ) ) v = (*dValue)       ;
  emit valueChanged (                      )    ;
  emit valueChanged ( (SceneObject *) this )    ;
  emit valueChanged (                 this )    ;
  emit valueChanged ( (qint64) v           )    ;
  emit valueChanged ( v                    )    ;
}

bool N::ValueObject::MouseVector (
       ControlPoint & From       ,
       ControlPoint & To         ,
       BMAPs        & buttons    )
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
      Alert    ( Click )                                       ;
    }                                                          ;
    setFocus ( true   )                                        ;
    if ( Value ( "Hit" ) . toBool ( ) )                        {
      toValue         ( At            )                        ;
      ToolTip         (               )                        ;
      return true                                              ;
    } else                                                     {
      int region = AtRegion ( At )                             ;
      switch ( region )                                        {
        case 0                                                 :
          setVariable ( "Hit" , false )                        ;
        break                                                  ;
        case 1                                                 : // Less
        case 2                                                 : // Greater
          toValue     ( At            )                        ;
          setVariable ( "Hit" , true  )                        ;
          ToolTip     (               )                        ;
        break                                                  ;
      }                                                        ;
    }                                                          ;
  } else                                                       {
    if ( Value ( "Hit" ) . toBool ( ) )                        {
      setVariable ( "Hit" , false )                            ;
      return true                                              ;
    }                                                          ;
  }                                                            ;
  return true                                                  ;
}

bool N::ValueObject::MouseHover (
       ControlPoint & From      ,
       ControlPoint & To        ,
       BMAPs        & buttons   )
{
  if ( ! Value ( "Mouse" ) . toBool ( )  ) return false             ;
  if ( ! isFocus             (  )        ) return false             ;
  if ( ! matrices . contains ( 2 )       ) return false             ;
  ///////////////////////////////////////////////////////////////////
  ControlPoint At                                                   ;
  if ( ! Collide ( From , To , At )      ) return false             ;
  ///////////////////////////////////////////////////////////////////
  if ( Value ( "Hit" ) . toBool ( ) )                               {
    toValue ( At )                                                  ;
    ToolTip (    )                                                  ;
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
    case 2                                                          :
      ToolTip ( )                                                   ;
    break                                                           ;
    default                                                         :
    break                                                           ;
  }                                                                 ;
  ///////////////////////////////////////////////////////////////////
  return true                                                       ;
}

bool N::ValueObject::MouseMove (
       ControlPoint & From1    ,
       ControlPoint & To1      ,
       ControlPoint & From2    ,
       ControlPoint & To2      ,
       BMAPs        & buttons  )
{
  return false ;
}

bool N::ValueObject::Spot  (
       ControlPoint & From ,
       ControlPoint & To   ,
       ControlPoint & At   )
{
  return xymSpot ( From , To , At ) ;
}

// 0 - Outside
// 1 - Less
// 2 - Greater
int N::ValueObject::AtRegion(ControlPoint & At)
{
  if ( At . x < minimum . x ) return 0        ;
  if ( At . x > maximum . x ) return 0        ;
  if ( At . y < minimum . y ) return 0        ;
  if ( At . y > maximum . y ) return 0        ;
  /////////////////////////////////////////////
  double p = toPosition ( )                   ;
  if ( p > At . x ) return 1                  ;
  /////////////////////////////////////////////
  return 2                                    ;
}

double N::ValueObject::toPosition(void)
{
  double s = Value ( "Start" ) . toDouble ( ) ;
  double e = Value ( "End"   ) . toDouble ( ) ;
  double v = Value ( "Value" ) . toDouble ( ) ;
  if ( NotNull ( iValue ) ) v = (*iValue)     ;
  if ( NotNull ( dValue ) ) v = (*dValue)     ;
  /////////////////////////////////////////////
  double L = maximum . x - minimum . x        ;
  double V = ( v - s ) / ( e - s )            ;
  /////////////////////////////////////////////
  V *= L                                      ;
  V += minimum . x                            ;
  /////////////////////////////////////////////
  return V                                    ;
}

void N::ValueObject::toValue(ControlPoint & At)
{
  double L = maximum . x - minimum . x        ;
  double d = At      . x - minimum . x        ;
  if ( At . x < minimum . x ) d = 0           ;
  if ( At . x > maximum . x ) d = L           ;
  double s = Value ( "Start" ) . toDouble ( ) ;
  double e = Value ( "End"   ) . toDouble ( ) ;
  d /= L                                      ;
  d *= ( e - s )                              ;
  d += s                                      ;
  setDouble ( d )                             ;
}

void N::ValueObject::Previous(void)
{
  double s = Value ( "Start" ) . toDouble ( ) ;
  double e = Value ( "End"   ) . toDouble ( ) ;
  double v = Value ( "Value" ) . toDouble ( ) ;
  double t = Value ( "Step"  ) . toDouble ( ) ;
  if ( NotNull ( iValue ) ) v = (*iValue)     ;
  if ( NotNull ( dValue ) ) v = (*dValue)     ;
  v -= t                                      ;
  if ( v < s ) v = s                          ;
  if ( v > e ) v = e                          ;
  setDouble ( v )                             ;
}

void N::ValueObject::Next(void)
{
  double s = Value ( "Start" ) . toDouble ( ) ;
  double e = Value ( "End"   ) . toDouble ( ) ;
  double v = Value ( "Value" ) . toDouble ( ) ;
  double t = Value ( "Step"  ) . toDouble ( ) ;
  if ( NotNull ( iValue ) ) v = (*iValue)     ;
  if ( NotNull ( dValue ) ) v = (*dValue)     ;
  v += t                                      ;
  if ( v < s ) v = s                          ;
  if ( v > e ) v = e                          ;
  setDouble ( v )                             ;
}

QString N::ValueObject::ToolTip(void)
{
  double s = Value ( "Start" ) . toDouble ( )                   ;
  double e = Value ( "End"   ) . toDouble ( )                   ;
  double v = Value ( "Value" ) . toDouble ( )                   ;
  if ( NotNull ( iValue ) ) v = (*iValue)                       ;
  if ( NotNull ( dValue ) ) v = (*dValue)                       ;
  ///////////////////////////////////////////////////////////////
  QString AS = ToolTip ( s , e , v )                            ;
  QRect   RX                                                    ;
  ///////////////////////////////////////////////////////////////
  QToolTip::showText ( QCursor::pos() , AS , NULL , RX , 3000 ) ;
  if ( NULL != gui ) gui -> setToolTip ( AS )                   ;
  return AS                                                     ;
}

QString N::ValueObject::ToolTip(double s,double e,double v)
{
  QString TRX = Value ( "ToolTipTemplate" ) . toString (   )   ;
  QString PRF = Value ( "Prefer"          ) . toString (   )   ;
  if ( "double" == PRF . toLower ( ) )                         {
    return QString ( TRX ) . arg ( v ) . arg ( s ) . arg ( e ) ;
  }                                                            ;
  return QString ( TRX                                         )
         . arg   ( (qint64) v                                  )
         . arg   ( (qint64) s                                  )
         . arg   ( (qint64) e                                ) ;
}

void N::ValueObject::renderLayout(void)
{
  ControlPoints P                                ;
  ControlPoint  minp                             ;
  ControlPoint  maxp                             ;
  int           cmid                             ;
  int           cside                            ;
  int           gmid                             ;
  int           gside                            ;
  ////////////////////////////////////////////////
  cmid       = Value ( "MidColor"  ) . toInt ( ) ;
  cside      = Value ( "SideColor" ) . toInt ( ) ;
  gmid       = Value ( "GetMid"    ) . toInt ( ) ;
  gside      = Value ( "GetSide"   ) . toInt ( ) ;
  ////////////////////////////////////////////////
  minp       = minimum                           ;
  maxp       = maximum                           ;
  P   [ 0 ]  = minp                              ;
  P   [ 1 ]  = maxp                              ;
  if ( isFocus ( ) )                             {
    P [ 2 ]  = colors [ gmid  ]                  ;
    P [ 3 ]  = colors [ gside ]                  ;
  } else                                         {
    P [ 2 ]  = colors [ cmid  ]                  ;
    P [ 3 ]  = colors [ cside ]                  ;
  }                                              ;
  GradientBox ( P )                              ;
}

void N::ValueObject::renderGauge(void)
{
  ControlPoints P                                   ;
  ControlPoint  minp                                ;
  ControlPoint  maxp                                ;
  int           dmid                                ;
  int           dside                               ;
  int           fmid                                ;
  int           fside                               ;
  double        pos = toPosition ( )                ;
  double        dist                                ;
  ///////////////////////////////////////////////////
  dmid       = Value ( "HoldMid"   ) . toInt    ( ) ;
  dside      = Value ( "HoldSide"  ) . toInt    ( ) ;
  fmid       = Value ( "FocusMid"  ) . toInt    ( ) ;
  fside      = Value ( "FocusSide" ) . toInt    ( ) ;
  dist       = Value ( "Distance"  ) . toDouble ( ) ;
  ///////////////////////////////////////////////////
  minp       = minimum                              ;
  maxp       = maximum                              ;
  maxp . x   = pos                                  ;
  minp . y  += dist                                 ;
  maxp . y  -= dist                                 ;
  ///////////////////////////////////////////////////
  P   [ 0 ]  = minp                                 ;
  P   [ 1 ]  = maxp                                 ;
  if ( Value ( "Hit" ) . toBool ( ) )               {
    P [ 2 ]  = colors [ fmid  ]                     ;
    P [ 3 ]  = colors [ fside ]                     ;
  } else                                            {
    P [ 2 ]  = colors [ dmid  ]                     ;
    P [ 3 ]  = colors [ dside ]                     ;
  }                                                 ;
  GradientBox ( P )                                 ;
}

void N::ValueObject::renderFaces(void)
{
  QtGL::PushMatrix ( ) ;
  renderLayout     ( ) ;
  renderGauge      ( ) ;
  QtGL::PopMatrix  ( ) ;
}

bool N::ValueObject::Menu    (
       QWidget      * widget ,
       QPointF        pos    ,
       ControlPoint & From   ,
       ControlPoint & To     )
{
  return false ;
}

#endif
