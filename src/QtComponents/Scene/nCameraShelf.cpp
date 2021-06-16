#include <qtcomponents.h>

#ifdef QT_OPENGL_LIB

N::CameraShelf:: CameraShelf ( QObject * parent , Plan * p )
               : NamesShelf  (           parent ,        p )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::CameraShelf:: CameraShelf ( QObject * parent , Plan * p , SceneDestructor * des )
               : NamesShelf  (           parent ,        p ,                   des )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::CameraShelf::~CameraShelf (void)
{
}

void N::CameraShelf::Configure(void)
{
  QSize TextRect       ( 128           , 16                  ) ;
  QObject::setProperty ( "Type"        , "CameraShelf"       ) ;
  setVariable          ( "Type"        , "CameraShelf"       ) ;
  setVariable          ( "Menu"        , false               ) ;
  setVariable          ( "Selectable"  , false               ) ;
  setVariable          ( "Movable"     , true                ) ;
  setVariable          ( "Resizable"   , false               ) ;
  setVariable          ( "Suicide"     , true                ) ;
  //////////////////////////////////////////////////////////////
  setVariable          ( "Access"      , "First"             ) ;
  setVariable          ( "AutoRefresh" , false               ) ;
  setVariable          ( "ArrangeBy"   , "Names"             ) ;
  setVariable          ( "ScrollBy"    , "Current"           ) ;
  //////////////////////////////////////////////////////////////
  setVariable          ( "Back"        , true                ) ;
  setVariable          ( "TextRect"    , TextRect            ) ;
  setVariable          ( "TextPixels"  , 15                  ) ;
  setVariable          ( "TextLength"  , 80                  ) ;
}

void N::CameraShelf::run(int type,ThreadData * data)
{
}

void N::CameraShelf::BoxChanged(bool hover)
{ Q_UNUSED ( hover ) ;
  qint64 total = Value ( "Items" ) . toLongLong ( ) ;
  ArrangeTitle      (         )                     ;
  RearrangeItems    (         )                     ;
  ArrangeScrollBars (         )                     ;
  UpdateScrollPages ( total   )                     ;
  ArrangePads       (         )                     ;
}

void N::CameraShelf::FinalizeSelection(void)
{
}

void N::CameraShelf::atDoubleClicked(SelectItem * item)
{
  if ( IsNull ( item ) ) return                      ;
  VarArgs args                                       ;
  args << CiosMenuId ( 89 , 45 , 96 )                ;
  args << item -> Value ( "UUID" ) . toULongLong ( ) ;
  args << node                                       ;
  args << Value ( "Suicide" ) . toBool ( )           ;
  CallRequests  ( args )                             ;
}

int N::CameraShelf::Indexing(RangeBar * rbu,int direction,QVariants & v)
{
  qint64 i = v [ 3 ] . toLongLong ( )     ; // index
  UUIDs  U = CurrentItems                 ;
  setVariable  ( "CurrentPageIndex" , i ) ;
  PickItem::ArrangeItems ( i , U )        ;
  return 0                                ;
}

int N::CameraShelf::Selecting(SelectItem * item,QVariants & v)
{
  bool pressed = v [ 0 ]          . toBool ( )         ;
  bool hit     = v [ 1 ]          . toBool ( )         ;
  bool dbc     = v [ 2 ]          . toBool ( )         ;
  bool emits   = Value ( "Emit" ) . toBool ( )         ;
  //////////////////////////////////////////////////////
  if ( dbc )                                           {
    if ( emits ) emit DoubleClicked ( item )           ;
    atDoubleClicked                 ( item )           ;
  } else                                               {
    if ( hit && ( ! pressed ) )                        {
      SUID u                                           ;
      if ( ! item -> isChecked ( ) )                   {
        item -> setChecked ( true )                    ;
        if ( emits ) emit SelectClicked ( item )       ;
      } else                                           {
        if ( emits ) emit Clicked       ( item )       ;
      }                                                ;
      foreach ( u , CurrentItems )                     {
        SelectItem * sox = ChildOf<SelectItem>(u)      ;
        if ( sox != item )                             {
          sox -> setChecked ( false )                  ;
        }                                              ;
      }                                                ;
    }                                                  ;
  }                                                    ;
  //////////////////////////////////////////////////////
  if ( userobjs . contains ( "Selection" ) )           {
    void    * Handler = userobjs [ "Selection" ]       ;
    QVariants V                                        ;
    V << item -> Value ( "UUID"    ) . toULongLong ( ) ;
    V << item -> Value ( "Checked" ) . toBool      ( ) ;
    V << dbc                                           ;
    CallDynamic ( "Selection" , this , Handler , V )   ;
  }                                                    ;
  //////////////////////////////////////////////////////
  return 0                                             ;
}

bool N::CameraShelf::prepare(void)
{
  ControlPoint at         ( -100 , -140 , 128 ,   1       ) ;
  ControlPoint header     (   10 ,  224 ,   2 ,   1       ) ;
  ControlPoint base       (   10 ,  190 ,   2 ,   1       ) ;
  ControlPoint box        (  150 ,   20 ,  28 ,   1       ) ;
  ControlPoint gap        (    0 ,  -22 ,   0 ,   1       ) ;
  ControlPoint appear     (   10 ,   10 ,   2 ,   1       ) ;
  ControlPoint minp       (    0 ,    0 ,   0 ,   1       ) ;
  ControlPoint maxp       (  150 ,   20 ,  28 ,   1       ) ;
  ControlPoint minz       (   10 ,   10 ,   0 ,   1       ) ;
  ControlPoint maxz       (  170 ,  220 ,  32 ,   1       ) ;
  ControlPoint vscroll    (  180 ,  220 ,   0 ,   1       ) ;
  ControlPoint vsbangle   (    0 ,    0 ,   1 , 270       ) ;
  QSize        headerSize (  128 ,   32                   ) ;
  ///////////////////////////////////////////////////////////
  minimum = ControlPoint  (    0 ,    0 ,   0 ,   1       ) ;
  maximum = ControlPoint  (  200 ,  260 ,  32 ,   1       ) ;
  at      . DOF = ControlPoint::DofTranslate                ;
  ///////////////////////////////////////////////////////////
  addDof                  ( 0              , at           ) ;
  setVariable             ( "HeaderSize"   , headerSize   ) ;
  setVariable             ( "TopMargin"    , 50           ) ;
  setVariable             ( "BottomMargin" , 10           ) ;
  setVariable             ( "LeftMargin"   , 10           ) ;
  setVariable             ( "RightMargin"  , 10           ) ;
  setBase                 ( base                          ) ;
  setBox                  ( box                           ) ;
  setGap                  ( gap                           ) ;
  setAppear               ( appear                        ) ;
  setDefaultMin           ( minp                          ) ;
  setDefaultMax           ( maxp                          ) ;
  setContainer            ( minz , maxz                   ) ;
  AssignPoint             ( "HeaderCorner" , header       ) ;
  AssignPoint             ( "VScrollPos"   , vscroll      ) ;
  AssignPoint             ( "VSBAngle"     , vsbangle     ) ;
  setTitle                ( tr("Cameras")                 ) ;
  Finish                  (                               ) ;
  Dual                    (                               ) ;
  addSequence             (  7 , RenderChildren           ) ;
  addSequence             ( 11 , RenderBox                ) ;
  addSequence             ( 15 , RenderFaces              ) ;
  return true                                               ;
}

void N::CameraShelf::setCameras(SUID current,NAMEs & cameras)
{
  QSize t ( 128 , 16 )                                   ;
  UUIDs U = cameras . keys ( )                           ;
  SUID  z = 0                                            ;
  SUID  u                                                ;
  int   r = lineCount    ( )                             ;
  ////////////////////////////////////////////////////////
  ViewNames = cameras                                    ;
  CleanItems ( )                                         ;
  ////////////////////////////////////////////////////////
  foreach ( u , U )                                      {
    QString      n  = cameras [ u ]                      ;
    SelectItem * si = NewText ( n      , t             ) ;
    si -> setVariable         ( "UUID" , u             ) ;
    ArrangeItem               ( si -> node , z , 1 , r ) ;
    si -> setChecked          ( ( u == current )       ) ;
    z ++                                                 ;
    RealToView [ u ] = si -> node                        ;
  }                                                      ;
}

void N::CameraShelf::CloseSelection(void)
{
  emit CloseObject ( node ) ;
}

bool N::CameraShelf::startup(void)
{
  QImage     * ok = new QImage ( ":/images/ready.png"  ) ;
  IconObject * io = AddButton  (                       ) ;
  io -> setIcon                ( 10001 , ok            ) ;
  io -> setIconSize            ( QSize ( 40 , 40 )     ) ;
  UpdateScrollPages            ( ViewNames . count ( ) ) ;
  BoxChanged                   ( true                  ) ;
  nConnect ( io   , SIGNAL ( released       ( ) )        ,
             this , SLOT   ( CloseSelection ( ) )        ,
             Qt::DirectConnection                      ) ;
  return true                                            ;
}

#endif
