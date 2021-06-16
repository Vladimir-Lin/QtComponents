#include <qtcomponents.h>

#ifdef QT_OPENGL_LIB

N::ProgressObject:: ProgressObject ( QObject * parent , Plan * p )
                  : SceneWidget    (           parent ,        p )
                  , reporter       ( NULL                        )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::ProgressObject:: ProgressObject ( QObject * parent , Plan * p , SceneDestructor * des )
                  : SceneWidget    (           parent ,        p ,                   des )
                  , reporter       ( NULL                                                )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::ProgressObject::~ProgressObject (void)
{
  if ( NotNull(reporter) )  {
    reporter -> Leaving ( ) ;
    reporter  = NULL        ;
  }                         ;
}

void N::ProgressObject::Configure(void)
{
  ControlPoint color                                   ;
  color  = QColor       ( 192 ,  192 , 192 , 192     ) ;
  addColor              (   0 , color                ) ;
  color  = ControlPoint (   0 ,    0 ,   1 , 0.15    ) ;
  addColor              (   1 , color                ) ;
  color  = ControlPoint ( 0.5 ,  0.5 ,   1 , 0.15    ) ;
  addColor              (   2 , color                ) ;
  color  = ControlPoint ( 0.2 ,  0.2 ,   1 , 0.30    ) ;
  addColor              (   3 , color                ) ;
  color  = ControlPoint ( 0.6 ,  0.6 ,   1 , 0.30    ) ;
  addColor              (   4 , color                ) ;
  color  = ControlPoint (   0 ,    0 ,   0 , 0.20    ) ;
  addColor              (   5 , color                ) ;
  //////////////////////////////////////////////////////
  QObject::setProperty  ( "Type"        , "Progress" ) ;
  setVariable           ( "Type"        , "Progress" ) ;
  setVariable           ( "Focus"       , false      ) ;
  setVariable           ( "Hold"        , false      ) ;
  setVariable           ( "Menu"        , false      ) ;
  //////////////////////////////////////////////////////
  setVariable           ( "MidColor"    , 1          ) ;
  setVariable           ( "SideColor"   , 2          ) ;
  setVariable           ( "DoneMid"     , 3          ) ;
  setVariable           ( "DoneSide"    , 4          ) ;
  setVariable           ( "Scale"       , 90         ) ;
  setVariable           ( "Distance"    , 0.10       ) ;
}

void N::ProgressObject::setReporter(ProgressReporter * r)
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

void N::ProgressObject::renderFaces(void)
{
  QtGL::PushMatrix ( )                                                       ;
  ////////////////////////////////////////////////////////////////////////////
  ControlPoints P                                                            ;
  ControlPoint  minp                                                         ;
  ControlPoint  maxp                                                         ;
  int           cmid                                                         ;
  int           cside                                                        ;
  int           dmid                                                         ;
  int           dside                                                        ;
  int           total                                                        ;
  int           value                                                        ;
  double        length = ( maximum . x - minimum . x )                       ;
  double        dist   = Value ( "Distance" ) . toDouble ( )                 ;
  ////////////////////////////////////////////////////////////////////////////
  cmid     = Value ( "MidColor"  ) . toInt ( )                               ;
  cside    = Value ( "SideColor" ) . toInt ( )                               ;
  dmid     = Value ( "DoneMid"   ) . toInt ( )                               ;
  dside    = Value ( "DoneSide"  ) . toInt ( )                               ;
  ////////////////////////////////////////////////////////////////////////////
  minp     = minimum                                                         ;
  maxp     = maximum                                                         ;
  minp.y  += dist                                                            ;
  maxp.y  -= dist                                                            ;
  minp.z  += dist                                                            ;
  maxp.z  -= dist                                                            ;
  P [ 0 ]  = minp                                                            ;
  P [ 1 ]  = maxp                                                            ;
  P [ 2 ]  = colors [ cmid  ]                                                ;
  P [ 3 ]  = colors [ cside ]                                                ;
  GradientBox ( P )                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( NULL == reporter ) return                                             ;
  ////////////////////////////////////////////////////////////////////////////
  minp     = minimum                                                         ;
  maxp     = maximum                                                         ;
  total    = reporter -> total                                               ;
  value    = reporter -> value                                               ;
  length  /= total                                                           ;
  length  *= value                                                           ;
  length  += minp . x                                                        ;
  maxp . x = length                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  P [ 0 ]  = minp                                                            ;
  P [ 1 ]  = maxp                                                            ;
  P [ 2 ]  = colors [ dmid  ]                                                ;
  P [ 3 ]  = colors [ dside ]                                                ;
  GradientBox ( P )                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  QtGL::PopMatrix  ( )                                                       ;
}

#endif
