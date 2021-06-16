#include <qtcomponents.h>

#ifdef QT_OPENGL_LIB

typedef struct         {
  N::IconObject * icon ;
  N::SelectItem * item ;
} PrivateSelectItem    ;

N::SelectItem:: SelectItem  ( QObject * parent , Plan * p )
              : SceneWidget (           parent ,        p )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::SelectItem:: SelectItem  ( QObject * parent , Plan * p , SceneDestructor * des )
              : SceneWidget (           parent ,        p ,                   des )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::SelectItem::~SelectItem (void)
{
}

void N::SelectItem::Configure(void)
{
  //////////////////////////////////////////////////////
  QObject::setProperty ( "Type"       , "SelectItem" ) ;
  setVariable          ( "Type"       , "Select"     ) ;
  setVariable          ( "Focus"      , false        ) ;
  setVariable          ( "Hold"       , false        ) ;
  setVariable          ( "Menu"       , false        ) ;
  setVariable          ( "Mouse"      , true         ) ;
  setVariable          ( "Hover"      , true         ) ;
  setVariable          ( "Emit"       , true         ) ;
  //////////////////////////////////////////////////////
  setVariable          ( "Selectable" , true         ) ;
  setVariable          ( "Checkable"  , false        ) ;
  setVariable          ( "Checked"    , false        ) ;
  //////////////////////////////////////////////////////
  setVariable          ( "Shell"      , "Selection"  ) ;
}

bool N::SelectItem::FocusIn(void)
{
  return false ;
}

bool N::SelectItem::FocusOut(void)
{
  return false ;
}

bool N::SelectItem::Spot (
       ControlPoint & From  ,
       ControlPoint & To    ,
       ControlPoint & At    )
{
  if ( ! Value ( "Mouse" ) . toBool ( )  ) return false ;
  return xymSpot ( From , To , At )                     ;
}

bool N::SelectItem::MouseClicked (
       ControlPoint & From       ,
       ControlPoint & To         ,
       BMAPs        & buttons    )
{
  if ( ! Value ( "Mouse" ) . toBool ( )  ) return false ;
  if ( ! matrices . contains ( 2 )       ) return false ;
  if ( buttons [ Universe::MouseMiddle ] ) return false ;
  if ( buttons [ Universe::MouseRight  ] ) return false ;
  ///////////////////////////////////////////////////////
  ControlPoint At                                       ;
  if ( ! Collide ( From , To , At )      ) return false ;
  ///////////////////////////////////////////////////////
  bool emits = Value ( "Emit" ) . toBool ( )            ;
  if ( emits ) emit doubleClicked ( )                   ;
  ///////////////////////////////////////////////////////
  if ( userobjs . contains ( "Selection" ) )            {
    void    * Handler = userobjs [ "Selection" ]        ;
    QVariants V                                         ;
    V << false                                          ;
    V << true                                           ;
    V << true                                           ;
    V << At . x                                         ;
    V << At . y                                         ;
    V << At . z                                         ;
    CallDynamic ( "Selection" , this , Handler , V )    ;
  }                                                     ;
  ///////////////////////////////////////////////////////
  return true                                           ;
}

bool N::SelectItem::MouseVector (
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
      Alert ( Click )                                   ;
    }                                                   ;
    setFocus ( true )                                   ;
    setVariable  ( "Hit" , true    )                    ;
  } else                                                {
    if ( Value ( "Hit" ) . toBool ( ) )                 {
      setVariable      ( "Hit" , false   )              ;
    }                                                   ;
  }                                                     ;
  ///////////////////////////////////////////////////////
  ControlPoint p1                                       ;
  ControlPoint p2                                       ;
  UUIDs        U = SceneObject::children . keys ( )     ;
  SUID         u                                        ;
  ///////////////////////////////////////////////////////
  p1 = matrices [ 2 ] * From                            ;
  p2 = matrices [ 2 ] * To                              ;
  ///////////////////////////////////////////////////////
  foreach ( u , U )                                     {
    SceneObject * sox = ChildOf<SceneObject> ( u )      ;
    if ( NULL != sox )                                  {
      sox -> MouseVector ( p1 , p2 , buttons )          ;
    }                                                   ;
  }                                                     ;
  ///////////////////////////////////////////////////////
  return true                                           ;
}

bool N::SelectItem::MouseHover (
       ControlPoint & From         ,
       ControlPoint & To           ,
       BMAPs        & buttons      )
{
  if ( ! Value ( "Mouse" ) . toBool ( )  ) return false ;
  if ( ! isFocus             (  )        ) return false ;
  if ( ! matrices . contains ( 2 )       ) return false ;
  ///////////////////////////////////////////////////////
  ControlPoint At                                       ;
  if ( ! Collide ( From , To , At )      ) return false ;
  ///////////////////////////////////////////////////////
  ControlPoint p1                                       ;
  ControlPoint p2                                       ;
  UUIDs        U = SceneObject::children . keys ( )     ;
  SUID         u                                        ;
  ///////////////////////////////////////////////////////
  p1 = matrices [ 2 ] * From                            ;
  p2 = matrices [ 2 ] * To                              ;
  ///////////////////////////////////////////////////////
  foreach ( u , U )                                     {
    SceneObject * sox = ChildOf<SceneObject> ( u )      ;
    if ( NULL != sox )                                  {
      sox -> MouseHover ( p1 , p2 , buttons )           ;
    }                                                   ;
  }                                                     ;
  ///////////////////////////////////////////////////////
  return true                                           ;
}

bool N::SelectItem::MouseMove (
       ControlPoint & From1   ,
       ControlPoint & To1     ,
       ControlPoint & From2   ,
       ControlPoint & To2     ,
       BMAPs        & buttons )
{
  return false ;
}

int N::SelectItem::addItem(IconObject * item)
{
  PrivateSelectItem * psi = new PrivateSelectItem (               )      ;
  SUID                u   = appendChild           ( 100001 , item )      ;
  ControlPoint        minp                                               ;
  ControlPoint        maxp                                               ;
  item -> Finish        (                  )                             ;
  item -> Dual          (                  )                             ;
  if ( item -> BoundingBox ( minp , maxp ) )                             {
    AddPoint ( minp )                                                    ;
    AddPoint ( maxp )                                                    ;
  }                                                                      ;
  Finish                (                  )                             ;
  Dual                  (                  )                             ;
  item -> setUniverse   ( UniverseUuid ( ) )                             ;
  item -> setParentUuid ( node             )                             ;
  item -> node                             = u                           ;
  item -> DynamicFunctions [ "Selection" ] = N::SelectItem::AcceptSelect ;
  item -> userobjs         [ "Selection" ] = psi                         ;
  psi  -> icon                             = item                        ;
  psi  -> item                             = this                        ;
  return SceneObject::children . count ( )                               ;
}

void N::SelectItem::setCheckable(bool enabled)
{
  UUIDs         U = SceneObject::children . keys ( ) ;
  SUID          u                                    ;
  SceneObject * sox                                  ;
  setVariable ( "Checkable" , enabled )              ;
  foreach ( u , U )                                  {
    sox  = ChildOf<SceneObject>( u )                 ;
    sox -> setVariable ( "Checkable" , enabled )     ;
  }                                                  ;
}

bool N::SelectItem::setChecked(bool enabled)
{
  UUIDs         U = SceneObject::children . keys ( ) ;
  SUID          u                                    ;
  SceneObject * sox                                  ;
  ////////////////////////////////////////////////////
  setVariable ( "Checked" , enabled )                ;
  foreach ( u , U )                                  {
    sox  = ChildOf<SceneObject>( u )                 ;
    sox -> setVariable ( "Checked" , enabled )       ;
  }                                                  ;
  ////////////////////////////////////////////////////
  DecideShell ( )                                    ;
  ////////////////////////////////////////////////////
  return Value ( "Checked" ) . toBool ( )            ;
}

bool N::SelectItem::isChecked(void)
{
  return Value ( "Checked" ) . toBool ( ) ;
}

void N::SelectItem::DecideShell(void)
{
  QString shell   = Value ( "Shell"   ) . toString ( ) ;
  bool    checked = Value ( "Checked" ) . toBool   ( ) ;
  bool    enabled = false                              ;
  //////////////////////////////////////////////////////
  shell = shell . toLower ( )                          ;
  if ( "always"    == shell ) enabled = true      ; else
  if ( "selection" == shell ) enabled = checked        ;
  //////////////////////////////////////////////////////
  LockAt   ( "Operate" )                               ;
  if ( enabled )                                       {
    addSequence ( 31 , AssignColor )                   ;
    addSequence ( 32 , RenderBox   )                   ;
  } else                                               {
    if ( sequences . contains ( 31 ) )                 {
      sequences . remove ( 31 )                        ;
    }                                                  ;
    if ( sequences . contains ( 32 ) )                 {
      sequences . remove ( 32 )                        ;
    }                                                  ;
  }                                                    ;
  UnlockAt ( "Operate" )                               ;
}

int N::SelectItem::Selecting(SceneObject * sox,QVariants & v)
{
  bool   checked   = sox -> Value ( "Checked" ) . toBool ( )             ;
  bool   pressed   = v [ 0 ] . toBool   ( )                              ;
  bool   hit       = v [ 1 ] . toBool   ( )                              ;
  double x         = v [ 2 ] . toDouble ( )                              ;
  double y         = v [ 3 ] . toDouble ( )                              ;
  double z         = v [ 4 ] . toDouble ( )                              ;
  bool   checkable = Value ( "Checkable" ) . toBool   ( )                ;
  bool   emits     = Value ( "Emit"      ) . toBool   ( )                ;
  ////////////////////////////////////////////////////////////////////////
  setChecked ( checked )                                                 ;
  ////////////////////////////////////////////////////////////////////////
  if ( hit && ( ! pressed ) )                                            {
    if ( emits ) emit released ( )                                       ;
    if ( checkable )                                                     {
      if ( emits ) emit toggled ( checked )                              ;
    }                                                                    ;
  }                                                                      ;
  ////////////////////////////////////////////////////////////////////////
  if ( ( ! hit ) && pressed )                                            {
    if ( emits ) emit clicked ( )                                        ;
    if ( checkable )                                                     {
      if ( emits ) emit toggled ( checked )                              ;
    }                                                                    ;
  }                                                                      ;
  ////////////////////////////////////////////////////////////////////////
  if ( userobjs . contains ( "Selection" ) )                             {
    void    * Handler = userobjs [ "Selection" ]                         ;
    QVariants V                                                          ;
    V << pressed                                                         ;
    V << hit                                                             ;
    V << false                                                           ;
    V << x                                                               ;
    V << y                                                               ;
    V << z                                                               ;
    CallDynamic ( "Selection" , this , Handler , V )                     ;
  }                                                                      ;
  ////////////////////////////////////////////////////////////////////////
  return 0                                                               ;
}

int N::SelectItem::AcceptSelect(void * data,void * dispatcher,QVariants & v)
{
  if ( NULL == data       ) return 0                         ;
  if ( NULL == dispatcher ) return 0                         ;
  PrivateSelectItem * psi = (PrivateSelectItem *) dispatcher ;
  ////////////////////////////////////////////////////////////
  IconObject * sox = psi -> icon                             ;
  SelectItem * siu = psi -> item                             ;
  ////////////////////////////////////////////////////////////
  if ( NULL == sox        ) return 0                         ;
  if ( NULL == siu        ) return 0                         ;
  ////////////////////////////////////////////////////////////
  return siu -> Selecting ( sox , v )                        ;
}

#endif
