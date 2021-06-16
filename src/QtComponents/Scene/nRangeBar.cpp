#include <qtcomponents.h>

#ifdef QT_OPENGL_LIB

N::RangeBar:: RangeBar    ( QObject * parent , Plan * p )
            : SceneWidget (           parent ,        p )
            , Index       ( NULL                        )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::RangeBar:: RangeBar    ( QObject * parent , Plan * p , SceneDestructor * des )
            : SceneWidget (           parent ,        p ,                   des )
            , Index       ( NULL                                                )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::RangeBar::~RangeBar (void)
{
}

void N::RangeBar::Configure(void)
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
  addColor              (   9 , color                ) ;
  //////////////////////////////////////////////////////
  QObject::setProperty  ( "Type"        , "Scroll"   ) ;
  setVariable           ( "Type"        , "Scroll"   ) ;
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
  setVariable           ( "MinHolder"   , 10.0       ) ;
  //////////////////////////////////////////////////////
  setVariable           ( "Start"       , 0          ) ;
  setVariable           ( "End"         , 99         ) ;
  setVariable           ( "Page"        , 100        ) ;
  setVariable           ( "Index"       , 0          ) ;
  setVariable           ( "Step"        , 10         ) ;
  //////////////////////////////////////////////////////
  setVariable           ( "Emit"        , true       ) ;
}

qint64 N::RangeBar::Total(void)
{
  qint64 s = Value ( "Start" ) . toLongLong ( ) ;
  qint64 e = Value ( "End"   ) . toLongLong ( ) ;
  return ( e - s + 1 )                          ;
}

qint64 N::RangeBar::CurrentIndex(void)
{
  qint64 i = Value ( "Index" ) . toLongLong ( ) ;
  if ( NULL != Index ) i = (*Index)             ;
  return i                                      ;
}

void N::RangeBar::setTotal(qint64 total)
{
  qint64 s = Value ( "Start" ) . toLongLong ( ) ;
  qint64 e                                      ;
  e = s + total - 1                             ;
  setVariable ( "End" , e )                     ;
  if ( ! Value ( "Emit" ) . toBool ( ) ) return ;
  emit rangeChanged ( s , e )                   ;
}

void N::RangeBar::setRange(qint64 s,qint64 e)
{
  setVariable ( "Start" , s )                   ;
  setVariable ( "End"   , e )                   ;
  if ( ! Value ( "Emit" ) . toBool ( ) ) return ;
  emit rangeChanged ( s , e )                   ;
}

void N::RangeBar::setPage(qint64 page)
{
  setVariable ( "Page" , page )                 ;
  if ( ! Value ( "Emit" ) . toBool ( ) ) return ;
  qint64 i = Value ( "Index" ) . toLongLong ( ) ;
  emit indexChanged ( i , page )                ;
  emit pageChanged  (     page )                ;
}

void N::RangeBar::setStep(qint64 step)
{
  setVariable ( "Step" , step )                 ;
  if ( ! Value ( "Emit" ) . toBool ( ) ) return ;
  emit stepChanged ( step )                     ;
}

void N::RangeBar::setIndex(qint64 idx)
{
  LockAt       ( "Operate"     )      ;
  setVariable  ( "Index" , idx )      ;
  if ( NULL != Index ) (*Index) = idx ;
  UnlockAt     ( "Operate"     )      ;
  indexChanged (               )      ;
}

void N::RangeBar::assignIndex(qint64 * idx)
{
  LockAt   ( "Operate" )           ;
  Index = idx                      ;
  if ( NotNull(idx) )              {
    setVariable ( "Index" , *idx ) ;
  }                                ;
  UnlockAt ( "Operate" )           ;
}

bool N::RangeBar::FocusIn(void)
{
  if ( IsNull(plan) ) return false               ;
  LinkAction ( GoHome       , GoHome       ( ) ) ;
  LinkAction ( GoEnd        , GoEnd        ( ) ) ;
  LinkAction ( PreviousPage , PreviousPage ( ) ) ;
  LinkAction ( NextPage     , NextPage     ( ) ) ;
  return true                                    ;
}

bool N::RangeBar::FocusOut(void)
{
  return false ;
}

void N::RangeBar::GoHome(void)
{
  setIndex ( 0 ) ;
}

void N::RangeBar::GoEnd(void)
{
  qint64 s = Value ( "Start" ) . toLongLong ( ) ;
  qint64 e = Value ( "End"   ) . toLongLong ( ) ;
  qint64 p = Value ( "Page"  ) . toLongLong ( ) ;
  qint64 i = e - p + 1                          ;
  if ( i < s ) i = s                            ;
  setIndex ( i )                                ;
}

void N::RangeBar::PreviousPage(void)
{
  qint64 s = Value ( "Start" ) . toLongLong ( ) ;
  qint64 e = Value ( "End"   ) . toLongLong ( ) ;
  qint64 p = Value ( "Page"  ) . toLongLong ( ) ;
  qint64 t = Value ( "Step"  ) . toLongLong ( ) ;
  qint64 i = Value ( "Index" ) . toLongLong ( ) ;
  if ( NULL != Index ) i = (*Index)             ;
  i -= t                                        ;
  if ( i < s ) i = s                            ;
  setIndex     ( i )                            ;
}

void N::RangeBar::NextPage(void)
{
  qint64 s = Value ( "Start" ) . toLongLong ( ) ;
  qint64 e = Value ( "End"   ) . toLongLong ( ) ;
  qint64 p = Value ( "Page"  ) . toLongLong ( ) ;
  qint64 t = Value ( "Step"  ) . toLongLong ( ) ;
  qint64 i = Value ( "Index" ) . toLongLong ( ) ;
  if ( NULL != Index ) i = (*Index)             ;
  i += t                                        ;
  if ( ( i + p ) > e ) i = e - p + 1            ;
  setIndex     ( i )                            ;
}

void N::RangeBar::CursorIndex(void)
{
  qint64 s = Value ( "Start" ) . toLongLong ( ) ;
  qint64 e = Value ( "End"   ) . toLongLong ( ) ;
  qint64 p = Value ( "Page"  ) . toLongLong ( ) ;
  qint64 i = Value ( "Index" ) . toLongLong ( ) ;
  qint64 t = e - s + 1                          ;
  double c = Shifting ( )                       ;
  if ( NULL != Index ) i = (*Index)             ;
  c /= ( maximum . x - minimum . x )            ;
  c += 0.00000001                               ;
  c *= t                                        ;
  t  = (qint64) c                               ;
  i += t                                        ;
  if (   i       < s ) i = s                    ;
  if ( ( i + p ) > e ) i = e - p + 1            ;
  setIndex ( i )                                ;
}

bool N::RangeBar::Spot (
       ControlPoint & From   ,
       ControlPoint & To     ,
       ControlPoint & At     )
{
  return xymSpot ( From , To , At ) ;
}

bool N::RangeBar::MouseVector (
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
  bool         grab    = hasFunction ( "Grab" )                ;
  bool         collide = Collide ( From , To , At )            ;
  if ( ( ! grab ) && ( ! collide ) ) return false              ;
  //////////////////////////////////////////////////////////////
  if ( buttons [ Universe::MouseLeft   ] )                     {
    if ( ! isFocus ( ) )                                       {
      Alert    ( Click )                                       ;
    }                                                          ;
    setFocus ( true   )                                        ;
    if ( Value ( "Hit" ) . toBool ( ) )                        {
      setVariable ( "P2" , At . x  )                           ;
      ToolTip     (                )                           ;
      return true                                              ;
    } else                                                     {
      int region = AtRegion ( At )                             ;
      switch ( region )                                        {
        case 0                                                 :
          if ( ! grab ) setVariable  ( "Hit"  , false )        ;
        break                                                  ;
        case 1                                                 : // Holder
          setCursor    ( Qt::ClosedHandCursor )                ;
          setVariable  ( "P1"   , At . x      )                ;
          setVariable  ( "P2"   , At . x      )                ;
          setVariable  ( "Hit"  , true        )                ;
          setVariable  ( "Grab" , true        )                ;
        break                                                  ;
        case 2                                                 : // Before
          setCursor    ( Qt::ArrowCursor      )                ;
          setVariable  ( "P1"   , At . x      )                ;
          PreviousPage (                      )                ;
          setVariable  ( "Hit"  , false       )                ;
        break                                                  ;
        case 3                                                 : // After
          setCursor    ( Qt::ArrowCursor      )                ;
          setVariable  ( "P1"   , At . x      )                ;
          NextPage     (                      )                ;
          setVariable  ( "Hit"  , false       )                ;
        break                                                  ;
      }                                                        ;
    }                                                          ;
  } else                                                       {
    if ( Value ( "Hit" ) . toBool ( ) )                        {
      setCursor    ( Qt::ArrowCursor )                         ;
      CursorIndex  (                 )                         ;
      setVariable  ( "Hit"  , false  )                         ;
      setVariable  ( "Grab" , false  )                         ;
      return true                                              ;
    } else                                                     {
      setCursor    ( Qt::ArrowCursor )                         ;
    }                                                          ;
  }                                                            ;
  return true                                                  ;
}

bool N::RangeBar::MouseHover (
       ControlPoint & From         ,
       ControlPoint & To           ,
       BMAPs        & buttons      )
{
  if ( ! Value ( "Mouse" ) . toBool ( )  ) return false       ;
  if ( ! isFocus             (  )        ) return false       ;
  if ( ! matrices . contains ( 2 )       ) return false       ;
  /////////////////////////////////////////////////////////////
  ControlPoint At                                             ;
  bool         grab    = hasFunction ( "Grab" )               ;
  bool         collide = Collide ( From , To , At )           ;
  if ( ( ! grab ) && ( ! collide ) ) return false             ;
  /////////////////////////////////////////////////////////////
  if ( Value ( "Hit" ) . toBool ( ) )                         {
    setVariable ( "P2" , At . x )                             ;
    ToolTip     (               )                             ;
    return true                                               ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  int region = AtRegion ( At )                                ;
  if ( ( ! grab ) && ( region <= 0 ) )                        {
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
    break                                                     ;
    case 1                                                    :
      setCursor ( Qt::OpenHandCursor )                        ;
      ToolTip   (                    )                        ;
    break                                                     ;
    case 2                                                    :
      setCursor ( Qt::ArrowCursor    )                        ;
      ToolTip   (                    )                        ;
    break                                                     ;
    case 3                                                    :
      setCursor ( Qt::ArrowCursor    )                        ;
      ToolTip   (                    )                        ;
    break                                                     ;
    default                                                   :
    break                                                     ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  return true                                                 ;
}

bool N::RangeBar::MouseMove (
       ControlPoint & From1       ,
       ControlPoint & To1         ,
       ControlPoint & From2       ,
       ControlPoint & To2         ,
       BMAPs        & buttons     )
{
  return false ;
}

QString N::RangeBar::ToolTip(void)
{
  qint64    s = Value ( "Start" ) . toLongLong ( )              ;
  qint64    e = Value ( "End"   ) . toLongLong ( )              ;
  qint64    p = Value ( "Page"  ) . toLongLong ( )              ;
  qint64    i = Value ( "Index" ) . toLongLong ( )              ;
  QString   AS                                                  ;
  QString   AR                                                  ;
  QRect     RX                                                  ;
  ///////////////////////////////////////////////////////////////
  if ( NULL != Index ) i = (*Index)                             ;
  ///////////////////////////////////////////////////////////////
  if ( Value ( "Hit" ) . toBool ( ) )                           {
    qint64 t = e - s + 1                                        ;
    double c = Shifting ( )                                     ;
    c /= ( maximum . x - minimum . x )                          ;
    c *= t                                                      ;
    t  = (qint64) c                                             ;
    i += t                                                      ;
    if ( i             < s ) i = s                              ;
    if ( ( i + p - 1 ) > e ) i = e - p + 1                      ;
  }                                                             ;
  ///////////////////////////////////////////////////////////////
  AS = ToolTip ( s , e , i , i + p - 1 )                        ;
  ///////////////////////////////////////////////////////////////
  QToolTip::showText ( QCursor::pos() , AS , NULL , RX , 3000 ) ;
  if ( NULL != gui ) gui -> setToolTip ( AS )                   ;
  return AS                                                     ;
}

QString N::RangeBar::ToolTip(qint64 s,qint64 e,qint64 f,qint64 t)
{
  QString AS                                         ;
  AS  = tr("From %1 to %2" ) . arg ( f ) . arg ( t ) ;
  AS  . append ( "\n" )                              ;
  AS += tr("Range %1 to %2") . arg ( s ) . arg ( e ) ;
  return AS                                          ;
}

N::RangeDouble N::RangeBar::Holder(void)
{
  RangeDouble rv                                         ;
  double      L = maximum . x - minimum . x              ;
  double      m = Value ( "MinHolder" ) . toDouble   ( ) ;
  qint64      s = Value ( "Start"     ) . toLongLong ( ) ;
  qint64      e = Value ( "End"       ) . toLongLong ( ) ;
  qint64      p = Value ( "Page"      ) . toLongLong ( ) ;
  qint64      i = Value ( "Index"     ) . toLongLong ( ) ;
  qint64      t = e - s + 1                              ;
  ////////////////////////////////////////////////////////
  if ( NULL != Index ) i = (*Index)                      ;
  ////////////////////////////////////////////////////////
  rv . L  = i - s                                        ;
  rv . R  = i - s + p                                    ;
  rv . L /= t                                            ;
  rv . R /= t                                            ;
  if ( rv . R > 1.0 ) rv . R = 1.0                       ;
  rv . L *= L                                            ;
  rv . R *= L                                            ;
  rv . L += minimum . x                                  ;
  rv . R += minimum . x                                  ;
  if ( rv . Distance ( ) < m )                           {
    rv . R = rv . L + m                                  ;
    if ( rv . R > maximum . x )                          {
      rv . R = maximum . x                               ;
      rv . L = rv . R - m                                ;
      if ( rv . L < minimum . x ) rv . L = minimum . x   ;
    }                                                    ;
  }                                                      ;
  ////////////////////////////////////////////////////////
  return rv                                              ;
}

// 0 - Outside
// 1 - Holder
// 2 - Before Holder
// 3 - After Holder
int N::RangeBar::AtRegion(ControlPoint & At)
{
  if ( At . x < minimum . x ) return 0         ;
  if ( At . x > maximum . x ) return 0         ;
  if ( At . y < minimum . y ) return 0         ;
  if ( At . y > maximum . y ) return 0         ;
  //////////////////////////////////////////////
  RangeDouble rv = Holder ( )                  ;
  if ( At . x < rv . L ) return 2              ;
  if ( At . x > rv . R ) return 3              ;
  //////////////////////////////////////////////
  return 1                                     ;
}

double N::RangeBar::Shifting(void)
{
  if ( ! Value ( "Hit" ) . toBool ( ) ) return 0 ;
  double      p1 = Value ( "P1" ) . toDouble ( ) ;
  double      p2 = Value ( "P2" ) . toDouble ( ) ;
  double      dp = p2 - p1                       ;
  RangeDouble rv = Holder ( )                    ;
  if ( ( rv . L + dp ) < minimum . x )           {
    dp = minimum . x - rv . L                    ;
  }                                              ;
  if ( ( rv . R + dp ) > maximum . x )           {
    dp = maximum . x - rv . R                    ;
  }                                              ;
  return dp                                      ;
}

void N::RangeBar::indexChanged(void)
{
  if ( ! Value ( "Emit" ) . toBool ( ) ) return     ;
  qint64 s = Value ( "Start" ) . toLongLong ( )     ;
  qint64 e = Value ( "End"   ) . toLongLong ( )     ;
  qint64 p = Value ( "Page"  ) . toLongLong ( )     ;
  qint64 i = Value ( "Index" ) . toLongLong ( )     ;
  emit valueChanged (                      )        ;
  emit valueChanged ( (SceneObject *) this )        ;
  emit valueChanged (                 this )        ;
  emit indexChanged ( i                    )        ;
  emit indexChanged ( i , p                )        ;
  ///////////////////////////////////////////////////
  if ( userobjs . contains ( "Indexing" ) )         {
    void    * Handler = userobjs [ "Indexing" ]     ;
    QVariants V                                     ;
    V << s                                          ;
    V << e                                          ;
    V << p                                          ;
    V << i                                          ;
    CallDynamic ( "Indexing" , this , Handler , V ) ;
  }                                                 ;
}

void N::RangeBar::renderLayout(void)
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

void N::RangeBar::renderHolder(void)
{
  ControlPoints P                                   ;
  ControlPoint  minp                                ;
  ControlPoint  maxp                                ;
  int           dmid                                ;
  int           dside                               ;
  int           fmid                                ;
  int           fside                               ;
  RangeDouble   rv     = Holder   ( )               ;
  double        shift  = Shifting ( )               ;
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
  minp . x   = rv . L                               ;
  maxp . x   = rv . R                               ;
  minp . x  += shift                                ;
  maxp . x  += shift                                ;
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

void N::RangeBar::renderFaces(void)
{
  QtGL::PushMatrix ( ) ;
  renderLayout     ( ) ;
  renderHolder     ( ) ;
  QtGL::PopMatrix  ( ) ;
}

bool N::RangeBar::Menu       (
       QWidget      * widget ,
       QPointF        pos    ,
       ControlPoint & From   ,
       ControlPoint & To     )
{
  if ( ! Value ( "Mouse" ) . toBool ( ) ) return false                       ;
  setCursor ( Qt::ArrowCursor )                                              ;
  ////////////////////////////////////////////////////////////////////////////
  ControlPoint At                                                            ;
  if ( ! Collide ( From , To , At ) ) return false                           ;
  int region = AtRegion ( At )                                               ;
  if ( region <= 0 ) return false                                            ;
  ////////////////////////////////////////////////////////////////////////////
  MenuManager     mm ( widget )                                              ;
  QAction       * aa                                                         ;
  SpinBox       * sb = new SpinBox ( NULL , plan )                           ;
  int             ei = Value ( "Index" ) . toInt ( )                         ;
  int             si = Value ( "Start" ) . toInt ( )                         ;
  int             xi = Value ( "End"   ) . toInt ( )                         ;
  int             pi = Value ( "Page"  ) . toInt ( )                         ;
  ////////////////////////////////////////////////////////////////////////////
  mm . add          ( 101 , tr("Home")          )                            ;
  mm . add          ( 102 , tr("End")           )                            ;
  mm . addSeparator (                           )                            ;
  mm . add          ( 103 , tr("Next page")     )                            ;
  mm . add          ( 104 , tr("Previous page") )                            ;
  mm . addSeparator (                           )                            ;
  ////////////////////////////////////////////////////////////////////////////
  sb -> setRange  ( si , xi - pi + 1 )                                       ;
  sb -> setValue  ( ei               )                                       ;
  mm  . add       ( 901 , sb         )                                       ;
  sb -> External = &ei                                                       ;
  ////////////////////////////////////////////////////////////////////////////
  mm  . setFont   ( plan             )                                       ;
  ////////////////////////////////////////////////////////////////////////////
  aa  = mm . exec (                  )                                       ;
  ////////////////////////////////////////////////////////////////////////////
  if ( ei != Value ( "Index" ) . toInt ( ) )                                 {
    setIndex ( ei )                                                          ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  nKickOut ( IsNull ( aa ) , true )                                          ;
  ////////////////////////////////////////////////////////////////////////////
  switch ( mm [ aa ] )                                                       {
    case  101                                                                :
      GoHome       ( )                                                       ;
    break                                                                    ;
    case  102                                                                :
      GoEnd        ( )                                                       ;
    break                                                                    ;
    case  103                                                                :
      NextPage     ( )                                                       ;
    break                                                                    ;
    case  104                                                                :
      PreviousPage ( )                                                       ;
    break                                                                    ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  return true                                                                ;
}

#endif
