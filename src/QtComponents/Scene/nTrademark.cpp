#include <qtcomponents.h>

//////////////////////////////////////////////////////////////////////////////
// Calculation for 3D N Word
//
// Long side length = sqrt ( 1 / 2 )        = 0.7071068
// N Bar width      = 1 - sqrt ( 1 / 2 )    = 0.2928932
// Mid Bar width    = sqrt ( ( 1 - sqrt ( 1 / 2 ) ) * ( 1 - sqrt ( 1 / 2 ) ) * 2 )
//                                          = 0.4142135
// Mid Bar height   = 1 - ( Mid Bar width ) = 0.5857865
//////////////////////////////////////////////////////////////////////////////

static N::PackedPoint NPP [ ] =                                                 {
/* 000 */  { 0.0000000f - 0.50f , 0.0000000f - 0.50f , 1.0000000f - 0.50f , 0 } ,
/* 001 */  { 0.2928932f - 0.50f , 0.0000000f - 0.50f , 1.0000000f - 0.50f , 0 } ,
/* 002 */  { 0.7071068f - 0.50f , 0.0000000f - 0.50f , 1.0000000f - 0.50f , 0 } ,
/* 003 */  { 1.0000000f - 0.50f , 0.0000000f - 0.50f , 1.0000000f - 0.50f , 0 } ,
/* 004 */  { 0.0000000f - 0.50f , 1.0000000f - 0.50f , 1.0000000f - 0.50f , 0 } ,
/* 005 */  { 0.2928932f - 0.50f , 1.0000000f - 0.50f , 1.0000000f - 0.50f , 0 } ,
/* 006 */  { 0.7071068f - 0.50f , 1.0000000f - 0.50f , 1.0000000f - 0.50f , 0 } ,
/* 007 */  { 1.0000000f - 0.50f , 1.0000000f - 0.50f , 1.0000000f - 0.50f , 0 } ,
/* 008 */  { 0.2928932f - 0.50f , 0.5857865f - 0.50f , 1.0000000f - 0.50f , 0 } ,
/* 009 */  { 0.7071068f - 0.50f , 0.4142135f - 0.50f , 1.0000000f - 0.50f , 0 } ,
/* 010 */  { 0.0000000f - 0.50f , 0.0000000f - 0.50f , 0.0000000f - 0.50f , 0 } ,
/* 011 */  { 0.2928932f - 0.50f , 0.0000000f - 0.50f , 0.0000000f - 0.50f , 0 } ,
/* 012 */  { 0.7071068f - 0.50f , 0.0000000f - 0.50f , 0.0000000f - 0.50f , 0 } ,
/* 013 */  { 1.0000000f - 0.50f , 0.0000000f - 0.50f , 0.0000000f - 0.50f , 0 } ,
/* 014 */  { 0.0000000f - 0.50f , 1.0000000f - 0.50f , 0.0000000f - 0.50f , 0 } ,
/* 015 */  { 0.2928932f - 0.50f , 1.0000000f - 0.50f , 0.0000000f - 0.50f , 0 } ,
/* 016 */  { 0.7071068f - 0.50f , 1.0000000f - 0.50f , 0.0000000f - 0.50f , 0 } ,
/* 017 */  { 1.0000000f - 0.50f , 1.0000000f - 0.50f , 0.0000000f - 0.50f , 0 } ,
/* 018 */  { 0.2928932f - 0.50f , 0.4142135f - 0.50f , 0.0000000f - 0.50f , 0 } ,
/* 019 */  { 0.7071068f - 0.50f , 0.5857865f - 0.50f , 0.0000000f - 0.50f , 0 } ,
/* 020 */  { 0.0000000f - 0.50f , 0.0000000f - 0.50f , 0.2928932f - 0.50f , 0 } ,
/* 021 */  { 0.0000000f - 0.50f , 0.0000000f - 0.50f , 0.7071068f - 0.50f , 0 } ,
/* 022 */  { 0.0000000f - 0.50f , 1.0000000f - 0.50f , 0.2928932f - 0.50f , 0 } ,
/* 023 */  { 0.0000000f - 0.50f , 1.0000000f - 0.50f , 0.7071068f - 0.50f , 0 } ,
/* 024 */  { 0.0000000f - 0.50f , 0.5857865f - 0.50f , 0.2928932f - 0.50f , 0 } ,
/* 025 */  { 0.0000000f - 0.50f , 0.4142135f - 0.50f , 0.7071068f - 0.50f , 0 } ,
/* 026 */  { 0.2928932f - 0.50f , 0.0000000f - 0.50f , 0.2928932f - 0.50f , 0 } ,
/* 027 */  { 0.2928932f - 0.50f , 0.0000000f - 0.50f , 0.7071068f - 0.50f , 0 } ,
/* 028 */  { 0.2928932f - 0.50f , 1.0000000f - 0.50f , 0.2928932f - 0.50f , 0 } ,
/* 029 */  { 0.2928932f - 0.50f , 1.0000000f - 0.50f , 0.7071068f - 0.50f , 0 } ,
/* 030 */  { 0.2928932f - 0.50f , 0.5857865f - 0.50f , 0.2928932f - 0.50f , 0 } ,
/* 031 */  { 0.2928932f - 0.50f , 0.4142135f - 0.50f , 0.7071068f - 0.50f , 0 } ,
/* 032 */  { 1.0000000f - 0.50f , 0.0000000f - 0.50f , 0.2928932f - 0.50f , 0 } ,
/* 033 */  { 1.0000000f - 0.50f , 0.0000000f - 0.50f , 0.7071068f - 0.50f , 0 } ,
/* 034 */  { 1.0000000f - 0.50f , 1.0000000f - 0.50f , 0.2928932f - 0.50f , 0 } ,
/* 035 */  { 1.0000000f - 0.50f , 1.0000000f - 0.50f , 0.7071068f - 0.50f , 0 } ,
/* 036 */  { 1.0000000f - 0.50f , 0.4142135f - 0.50f , 0.2928932f - 0.50f , 0 } ,
/* 037 */  { 1.0000000f - 0.50f , 0.5857865f - 0.50f , 0.7071068f - 0.50f , 0 } ,
/* 038 */  { 0.7071068f - 0.50f , 0.0000000f - 0.50f , 0.2928932f - 0.50f , 0 } ,
/* 039 */  { 0.7071068f - 0.50f , 0.0000000f - 0.50f , 0.7071068f - 0.50f , 0 } ,
/* 040 */  { 0.7071068f - 0.50f , 1.0000000f - 0.50f , 0.2928932f - 0.50f , 0 } ,
/* 041 */  { 0.7071068f - 0.50f , 1.0000000f - 0.50f , 0.7071068f - 0.50f , 0 } ,
/* 042 */  { 0.7071068f - 0.50f , 0.4142135f - 0.50f , 0.2928932f - 0.50f , 0 } ,
/* 043 */  { 0.7071068f - 0.50f , 0.5857865f - 0.50f , 0.7071068f - 0.50f , 0 } ,
/* 044 */  { 0.2928932f - 0.50f , 0.5857865f - 0.50f , 0.7071068f - 0.50f , 0 } ,
/* 045 */  { 0.7071068f - 0.50f , 0.4142135f - 0.50f , 0.7071068f - 0.50f , 0 } ,
/* 046 */  { 0.2928932f - 0.50f , 0.4142135f - 0.50f , 0.2928932f - 0.50f , 0 } ,
/* 047 */  { 0.7071068f - 0.50f , 0.5857865f - 0.50f , 0.2928932f - 0.50f , 0 } ,
}                                                                               ;

static int TrademarkListing [ ] = {
   /* Front N */
   0 ,  1                         ,
   1 ,  8                         ,
   8 ,  2                         ,
   2 ,  3                         ,
   3 ,  7                         ,
   7 ,  6                         ,
   6 ,  9                         ,
   9 ,  5                         ,
   5 ,  4                         ,
   4 ,  0                         ,
  /* Front Internal N */
  21 , 27                         ,
  31 , 44                         ,
  44 , 39                         ,
  39 , 33                         ,
  23 , 29                         ,
  29 , 45                         ,
  45 , 43                         ,
  41 , 35                         ,
  /* Back N */
  13 , 12                         ,
  12 , 19                         ,
  19 , 11                         ,
  11 , 10                         ,
  10 , 14                         ,
  14 , 15                         ,
  15 , 18                         ,
  18 , 16                         ,
  16 , 17                         ,
  17 , 13                         ,
  /* Back Internal N */
  20 , 26                         ,
  26 , 47                         ,
  47 , 42                         ,
  38 , 32                         ,
  22 , 28                         ,
  30 , 46                         ,
  46 , 40                         ,
  40 , 34                         ,
  /* Right N */
   3 , 33                         ,
  33 , 37                         ,
  37 , 32                         ,
  32 , 13                         ,
  17 , 34                         ,
  34 , 36                         ,
  36 , 35                         ,
  35 ,  7                         ,
  /* Right Internal N */
   2 , 39                         ,
  43 , 38                         ,
  38 , 12                         ,
  16 , 40                         ,
  42 , 41                         ,
  41 ,  6                         ,
  /* Left N */
  10 , 20                         ,
  20 , 24                         ,
  24 , 21                         ,
  21 ,  0                         ,
   4 , 23                         ,
  23 , 25                         ,
  25 , 22                         ,
  22 , 14                         ,
  /* Left Internal N */
  11 , 26                         ,
  30 , 27                         ,
  27 ,  1                         ,
   5 , 29                         ,
  31 , 28                         ,
  28 , 15                         ,
  /* Horizontal Bars */
   8 , 44                         ,
   9 , 45                         ,
  37 , 43                         ,
  36 , 42                         ,
  19 , 47                         ,
  18 , 46                         ,
  24 , 30                         ,
  25 , 31                       } ;

static int TrademarkFaces   [ ] = {
  /* Front N Face */
   0 ,  1 ,  5 ,  4               ,
   2 ,  3 ,  7 ,  6               ,
   8 ,  2 ,  9 ,  5               ,
  /* Right N Face */
   3 , 33 , 35 ,  7               ,
  32 , 13 , 17 , 34               ,
  37 , 32 , 36 , 35               ,
  /* Back N Face */
  13 , 12 , 16 , 17               ,
  11 , 10 , 14 , 15               ,
  19 , 11 , 18 , 16               ,
  /* Left N Face */
  10 , 20 , 22 , 14               ,
  21 ,  0 ,  4 , 23               ,
  24 , 21 , 25 , 22               ,
  /* Internal Faces */
  44 , 29 , 45 , 39               ,
  43 , 41 , 42 , 38               ,
  47 , 40 , 46 , 26               ,
  30 , 28 , 31 , 27               ,
  /* Up Faces */
   4 ,  5 , 29 , 23               ,
   6 ,  7 , 35 , 41               ,
  40 , 34 , 17 , 16               ,
  22 , 28 , 15 , 14               ,
  /* Down Faces */
   0 , 21 , 27 ,  1               ,
   2 , 39 , 33 ,  3               ,
  38 , 12 , 13 , 32               ,
  20 , 10 , 11 , 26               ,
  /* Left Bottom Internal Faces */
   1 , 27 , 44 ,  8               ,
  33 , 39 , 43 , 37               ,
  12 , 38 , 47 , 19               ,
  20 , 26 , 30 , 24               ,
  /* Right Top Internal Faces */
   6 , 41 , 45 ,  9               ,
  34 , 40 , 42 , 36               ,
  15 , 28 , 46 , 18               ,
  23 , 29 , 31 , 25               ,
  /* Mid Up Internal Faces */
   9 , 45 , 29 ,  5               ,
  36 , 42 , 41 , 35               ,
  18 , 46 , 40 , 16               ,
  25 , 31 , 28 , 22               ,
  /* Mid Down Internal Faces */
   8 , 44 , 39 ,  2               ,
  37 , 43 , 38 , 32               ,
  19 , 47 , 26 , 11               ,
  24 , 30 , 27 , 21             } ;

//////////////////////////////////////////////////////////////////////////////

N::Trademark:: Trademark   ( QObject * parent , Plan * p )
             : SceneWidget (           parent ,        p )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::Trademark:: Trademark   ( QObject * parent , Plan * p , SceneDestructor * d )
             : SceneWidget (           parent ,        p ,                   d )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::Trademark::~Trademark (void)
{
}

void N::Trademark::Configure(void)
{
  QObject::setProperty   ( "Type"          , "Trademark"                   ) ;
  setVariable            ( "Type"          , "Trademark"                   ) ;
  setVariable            ( "Focus"         , false                         ) ;
  setVariable            ( "Hold"          , false                         ) ;
  setVariable            ( "Menu"          , true                          ) ;
  setVariable            ( "Mouse"         , true                          ) ;
  setVariable            ( "Hover"         , true                          ) ;
  setVariable            ( "Emit"          , true                          ) ;
  setVariable            ( "Rotation"      , "No"                          ) ;
  setVariable            ( "Length"        , 64                            ) ;
  setVariable            ( "Thickness"     , 1.75                          ) ;
  setVariable            ( "LineColor"     , 1                             ) ;
  setVariable            ( "FaceColor"     , 3                             ) ;
  setVariable            ( "Lines"         , 72                            ) ;
  setVariable            ( "Faces"         , 40                            ) ;
  ////////////////////////////////////////////////////////////////////////////
  SceneNode::setProperty ( GL_CULL_FACE    , false                         ) ;
  SceneNode::setProperty ( GL_DEPTH_TEST   , false                         ) ;
  ////////////////////////////////////////////////////////////////////////////
  ControlPoint at        ( 0 , 0 , 0 , 1                                   ) ;
  ControlPoint zp        ( 0 , 0 , 0 , 1                                   ) ;
  ControlPoint scale     ( 1 , 1 , 1 , 1                                   ) ;
  ControlPoint rotatez   ( 0 , 0 , 1 , 0                                   ) ;
  ControlPoint rotatey   ( 0 , 1 , 0 , 0                                   ) ;
  ControlPoint rotatex   ( 1 , 0 , 0 , 0                                   ) ;
  ////////////////////////////////////////////////////////////////////////////
  at      . DOF = ControlPoint::DofTranslate                                 ;
  zp      . DOF = ControlPoint::DofTranslate                                 ;
  scale   . DOF = ControlPoint::DofScale                                     ;
  rotatex . DOF = ControlPoint::DofRotate                                    ;
  rotatey . DOF = ControlPoint::DofRotate                                    ;
  rotatez . DOF = ControlPoint::DofRotate                                    ;
  ////////////////////////////////////////////////////////////////////////////
  addDof                 ( 0 , at                                          ) ;
  addDof                 ( 1 , zp                                          ) ;
  addDof                 ( 2 , scale                                       ) ;
  addDof                 ( 3 , rotatez                                     ) ;
  addDof                 ( 4 , rotatey                                     ) ;
  addDof                 ( 5 , rotatex                                     ) ;
  ////////////////////////////////////////////////////////////////////////////
  addColor               ( 0 , ControlPoint ( 0.75 , 0.75 , 0.75 , 0.75 )  ) ;
  addColor               ( 1 , ControlPoint ( 0    , 0    , 1    , 0.25 )  ) ;
  addColor               ( 2 , ControlPoint ( 1    , 0    , 0    , 0.35 )  ) ;
  addColor               ( 3 , ControlPoint ( 0.47 , 0.65 , 0.33 , 0.25 )  ) ;
  addColor               ( 4 , ControlPoint ( 0    , 0    , 0    , 0.10 )  ) ;
  ////////////////////////////////////////////////////////////////////////////
  packedPoints = NPP                                                         ;
  lines        = TrademarkListing                                            ;
  faces        = TrademarkFaces                                              ;
  ////////////////////////////////////////////////////////////////////////////
  minimum      = ControlPoint ( -32 , -32 , -32 )                            ;
  maximum      = ControlPoint (  32 ,  32 ,  32 )                            ;
}

void N::Trademark::setLength(double L)
{
  double l = L / 2                         ;
  setVariable             ( "Length" , L ) ;
  minimum  = ControlPoint ( -l , -l , -l ) ;
  maximum  = ControlPoint (  l ,  l ,  l ) ;
  Finish                  (              ) ;
  Dual                    (              ) ;
}

void N::Trademark::setPoints(PackedPoint * pts)
{
  packedPoints = pts ;
}

void N::Trademark::setLines(int * l)
{
  lines = l ;
}

void N::Trademark::setFaces(int * f)
{
  faces = f ;
}

void N::Trademark::renderSegments(void)
{
  int    C = Value ( "LineColor" ) . toInt    ( )                            ;
  int    P = Value ( "Lines"     ) . toInt    ( ) * 2                        ;
  double L = Value ( "Length"    ) . toDouble ( )                            ;
  double T = Value ( "Thickness" ) . toDouble ( )                            ;
  ////////////////////////////////////////////////////////////////////////////
  QtGL::Enable           ( GL_LINE_SMOOTH                     )              ;
  QtGL::Enable           ( GL_POLYGON_SMOOTH                  )              ;
  QtGL::Hint             ( GL_LINE_SMOOTH_HINT    , GL_NICEST )              ;
  QtGL::Hint             ( GL_POLYGON_SMOOTH_HINT , GL_NICEST )              ;
  QtGL::LineWidth        ( T                                  )              ;
  ////////////////////////////////////////////////////////////////////////////
  QtGL::PushMatrix       (                                    )              ;
  QtGL::Lines            (                                    )              ;
  colors [ C ] . Color4d (                                    )              ;
  ////////////////////////////////////////////////////////////////////////////
  for                    ( int i = 0 ; i < P ; i++            )              {
    ControlPoint v                                                           ;
    int          p = lines   [ i ]                                           ;
    v . x = L * packedPoints [ p ] . x                                       ;
    v . y = L * packedPoints [ p ] . y                                       ;
    v . z = L * packedPoints [ p ] . z                                       ;
    v . Vertex3d ( )                                                         ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  QtGL::End              (                                    )              ;
  QtGL::PopMatrix        (                                    )              ;
  ////////////////////////////////////////////////////////////////////////////
  QtGL::Disable          ( GL_LINE_SMOOTH                     )              ;
  QtGL::LineWidth        ( 1.0f                               )              ;
}

void N::Trademark::renderFaces(void)
{
  int    C = Value ( "FaceColor" ) . toInt    ( )                            ;
  int    P = Value ( "Faces"     ) . toInt    ( ) * 4                        ;
  double L = Value ( "Length"    ) . toDouble ( )                            ;
  ////////////////////////////////////////////////////////////////////////////
  QtGL::Disable          ( GL_LINE_SMOOTH                     )              ;
  QtGL::Disable          ( GL_POLYGON_SMOOTH                  )              ;
  ////////////////////////////////////////////////////////////////////////////
  QtGL::PushMatrix       (                                    )              ;
  QtGL::Quadrilateral    (                                    )              ;
  colors [ C ] . Color4d (                                    )              ;
  ////////////////////////////////////////////////////////////////////////////
  for                    ( int i = 0 ; i < P ; i++            )              {
    ControlPoint v                                                           ;
    int          p = faces   [ i ]                                           ;
    v . x = L * packedPoints [ p ] . x                                       ;
    v . y = L * packedPoints [ p ] . y                                       ;
    v . z = L * packedPoints [ p ] . z                                       ;
    v . Vertex3d ( )                                                         ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  QtGL::End              (                                    )              ;
  QtGL::PopMatrix        (                                    )              ;
}

bool N::Trademark::FocusIn(void)
{
  nKickOut     ( IsNull ( plan ) , false                           ) ;
  ////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////
  return true                                                        ;
}

bool N::Trademark::FocusOut(void)
{
  return false ;
}

bool N::Trademark::Spot    (
       ControlPoint & From ,
       ControlPoint & To   ,
       ControlPoint & At   )
{
  if ( NULL == packedPoints ) return false                   ;
  if ( NULL == faces        ) return false                   ;
  int F = Value ( "Faces" ) . toInt ( )                      ;
  if ( F <= 0 ) return false                                 ;
  ////////////////////////////////////////////////////////////
  bool         collision = false                             ;
  int          fi        = 0                                 ;
  double       L         = Value ( "Length" ) . toDouble ( ) ;
  double       M         = DBL_MAX                           ;
  double       dS                                            ;
  ControlPoint C                                             ;
  ControlPoint P                                             ;
  ControlPoint Z0                                            ;
  ControlPoint Z1                                            ;
  ControlPoint Z3                                            ;
  ControlPoint P1                                            ;
  ControlPoint P2                                            ;
  ControlPoint dP                                            ;
  ////////////////////////////////////////////////////////////
  P1 = From                                                  ;
  P2 = To                                                    ;
  ////////////////////////////////////////////////////////////
  for (int i = 0 ; i < F ; i++ , fi += 4 )                   {
    int z0 = faces [ fi     ]                                ;
    int z1 = faces [ fi + 1 ]                                ;
    int z3 = faces [ fi + 3 ]                                ;
    //////////////////////////////////////////////////////////
    Z0 . x = L * packedPoints [ z0 ] . x                     ;
    Z0 . y = L * packedPoints [ z0 ] . y                     ;
    Z0 . z = L * packedPoints [ z0 ] . z                     ;
    //////////////////////////////////////////////////////////
    Z1 . x = L * packedPoints [ z1 ] . x                     ;
    Z1 . y = L * packedPoints [ z1 ] . y                     ;
    Z1 . z = L * packedPoints [ z1 ] . z                     ;
    //////////////////////////////////////////////////////////
    Z3 . x = L * packedPoints [ z3 ] . x                     ;
    Z3 . y = L * packedPoints [ z3 ] . y                     ;
    Z3 . z = L * packedPoints [ z3 ] . z                     ;
    //////////////////////////////////////////////////////////
    if ( IntersectRectangle ( P , Z0 , Z1 , Z3 , P1 , P2 ) ) {
      dP . x = P . x - P1 . x                                ;
      dP . y = P . y - P1 . y                                ;
      dP . z = P . z - P1 . z                                ;
      dS     = ( dP . x * dP . x )                           +
               ( dP . y * dP . y )                           +
               ( dP . z * dP . z )                           ;
      if ( ! collision )                                     {
        collision = true                                     ;
        C         = P                                        ;
        M         = dS                                       ;
      } else                                                 {
        if ( dS < M )                                        {
          C       = P                                        ;
          M       = dS                                       ;
        }                                                    ;
      }                                                      ;
    }                                                        ;
  }                                                          ;
  ////////////////////////////////////////////////////////////
  if ( collision ) At = C                                    ;
  ////////////////////////////////////////////////////////////
  return collision                                           ;
}

bool N::Trademark::MouseVector (
       ControlPoint & From     ,
       ControlPoint & To       ,
       BMAPs        & buttons  )
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
      return true                                              ;
    } else                                                     {
      int region = AtRegion ( At )                             ;
      switch ( region )                                        {
        case 0                                                 :
          if ( ! grab ) setVariable  ( "Hit"  , false )        ;
          emit assignCursor ( Qt::ArrowCursor      )           ;
        break                                                  ;
        case 1                                                 :
          emit assignCursor ( Qt::ClosedHandCursor )           ;
          setVariable       ( "P1"   , At . x      )           ;
          setVariable       ( "P2"   , At . x      )           ;
          setVariable       ( "Hit"  , true        )           ;
          setVariable       ( "Grab" , true        )           ;
        break                                                  ;
      }                                                        ;
    }                                                          ;
  } else                                                       {
    if ( Value ( "Hit" ) . toBool ( ) )                        {
      emit assignCursor ( Qt::ArrowCursor )                    ;
      setVariable       ( "Hit"  , false  )                    ;
      setVariable       ( "Grab" , false  )                    ;
      return true                                              ;
    } else                                                     {
      emit assignCursor ( Qt::ArrowCursor )                    ;
    }                                                          ;
  }                                                            ;
  return true                                                  ;
}

bool N::Trademark::MouseHover (
       ControlPoint & From    ,
       ControlPoint & To      ,
       BMAPs        & buttons )
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
    return true                                               ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  int region = AtRegion ( At )                                ;
  if ( ( ! grab ) && ( region <= 0 ) )                        {
    emit assignCursor ( Qt::ArrowCursor )                     ;
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
    return false                                              ;
    case 1                                                    :
      emit assignCursor ( Qt::OpenHandCursor )                ;
    break                                                     ;
    default                                                   :
    break                                                     ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  return true                                                 ;
}

bool N::Trademark::MouseMove  (
       ControlPoint & From1   ,
       ControlPoint & To1     ,
       ControlPoint & From2   ,
       ControlPoint & To2     ,
       BMAPs        & buttons )
{
  return false ;
}

// 0 - Outside
// 1 - Inside
int N::Trademark::AtRegion(ControlPoint & At)
{
  if ( ! Between ( At , minimum , maximum ) ) return 0 ;
  //////////////////////////////////////////////////////
  return 1                                             ;
}

bool N::Trademark::Menu      (
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
  return true                                                                ;
}

QScriptValue N::Trademark::TrademarkAttachment(QScriptContext * context,QScriptEngine * engine)
{
  N::Trademark * ntm = new N::Trademark ( engine , (Plan *) qPlan ) ;
  return engine -> newQObject           ( ntm                     ) ;
}
