#include <qtcomponents.h>

#ifdef QT_OPENGL_LIB

typedef struct         {
  N::SelectItem * item ;
  N::PickItem   * box  ;
} PrivatePickItem      ;

typedef struct            {
  N::RangeBar * range     ;
  N::PickItem * box       ;
  int           direction ;
} PrivateRangeBar         ;

typedef struct        {
  N::SceneWidget * me ;
} SwClassStructure    ;

N::PickItem:: PickItem    ( QObject * parent , Plan * p )
            : SceneWidget (           parent ,        p )
            , UsingCamera ( NULL                        )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::PickItem:: PickItem    ( QObject * parent , Plan * p , SceneDestructor * des )
            : SceneWidget (           parent ,        p ,                   des )
            , UsingCamera ( NULL                                                )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::PickItem::~PickItem (void)
{
}

void N::PickItem::Configure(void)
{
  //////////////////////////////////////////////////////////////////////
  QObject::setProperty ( "Type"          , "PickItem"                ) ;
  setVariable          ( "Type"          , "PickItem"                ) ;
  setVariable          ( "Focus"         , false                     ) ;
  setVariable          ( "Hold"          , false                     ) ;
  setVariable          ( "Menu"          , false                     ) ;
  setVariable          ( "Mouse"         , true                      ) ;
  setVariable          ( "Hover"         , true                      ) ;
  setVariable          ( "Emit"          , true                      ) ;
  setVariable          ( "Finished"      , false                     ) ;
  setVariable          ( "StartDrag"     , false                     ) ;
  setVariable          ( "Dragging"      , false                     ) ;
  //////////////////////////////////////////////////////////////////////
  setVariable          ( "Selectable"    , true                      ) ;
  setVariable          ( "Movable"       , false                     ) ;
  setVariable          ( "Resizable"     , false                     ) ;
  setVariable          ( "Margin"        , 3                         ) ;
  //////////////////////////////////////////////////////////////////////
  setVariable          ( "Top/Line"      , true                      ) ;
  setVariable          ( "Bottom/Line"   , true                      ) ;
  setVariable          ( "Left/Line"     , true                      ) ;
  setVariable          ( "Right/Line"    , true                      ) ;
  setVariable          ( "Top/Left"      , true                      ) ;
  setVariable          ( "Top/Right"     , true                      ) ;
  setVariable          ( "Bottom/Left"   , true                      ) ;
  setVariable          ( "Bottom/Right"  , true                      ) ;
  //////////////////////////////////////////////////////////////////////
  setVariable          ( "Shell"         , "Always"                  ) ;
  setVariable          ( "Arrange"       , "Top/Bottom"              ) ;
  setVariable          ( "Align"         , "Left/Right"              ) ;
  //////////////////////////////////////////////////////////////////////
//  setVariable          ( "SelectionMode" , "None"                    ) ;
  setVariable          ( "SelectionMode" , "Single"                  ) ;
//  setVariable          ( "SelectionMode" , "Contiguous"              ) ;
//  setVariable          ( "SelectionMode" , "Extended"                ) ;
//  setVariable          ( "SelectionMode" , "Multiple"                ) ;
  //////////////////////////////////////////////////////////////////////
  setVariable          ( "ProgressUUID"   , 0                        ) ;
  setVariable          ( "HorizontalUUID" , 0                        ) ;
  setVariable          ( "VerticalUUID"   , 0                        ) ;
  setVariable          ( "HScroll"        , false                    ) ;
  setVariable          ( "HScrollX"       , 0                        ) ;
  setVariable          ( "HScrollY"       , 2                        ) ;
  setVariable          ( "HScrollV"       , "Bottom"                 ) ;
  setVariable          ( "VScroll"        , false                    ) ;
  setVariable          ( "VScrollX"       , -20                      ) ;
  setVariable          ( "VScrollY"       , -40                      ) ;
  setVariable          ( "VScrollH"       , "Right"                  ) ;
  setVariable          ( "VScrollV"       , "Top"                    ) ;
  //////////////////////////////////////////////////////////////////////
  setVariable          ( "HeaderAlign"    , "Top/Left"               ) ;
  setVariable          ( "HeaderX"        ,  20                      ) ;
  setVariable          ( "HeaderY"        , -36                      ) ;
  //////////////////////////////////////////////////////////////////////
  setVariable          ( "TopMargin"      , 50                       ) ;
  setVariable          ( "BottomMargin"   , 30                       ) ;
  setVariable          ( "LeftMargin"     , 20                       ) ;
  setVariable          ( "RightMargin"    , 30                       ) ;
  //////////////////////////////////////////////////////////////////////
//  setVariable          ( "Access"         , "Full"                   ) ;
//  setVariable          ( "Access"         , "Divisions"              ) ;
//  setVariable          ( "Access"         , "Limits"                 ) ;
  setVariable          ( "Access"         , "First"                  ) ;
//  setVariable          ( "Access"         , "Second"                 ) ;
  setVariable          ( "Sorting"        , Qt::AscendingOrder       ) ;
//  setVariable          ( "Sorting"        , Qt::DescendingOrder      ) ;
  setVariable          ( "ByItem"         , "position"               ) ;
  setVariable          ( "T1"             , Types::Gallery           ) ;
  setVariable          ( "T2"             , Types::Picture           ) ;
  setVariable          ( "T3"             , Types::Picture           ) ;
  setVariable          ( "Relation"       , Groups::Subordination    ) ;
  setVariable          ( "First"          , 0                        ) ;
  setVariable          ( "Second"         , 0                        ) ;
  setVariable          ( "Table"          , ""                       ) ;
  setVariable          ( "StartId"        , 0                        ) ;
  setVariable          ( "TitleColor" , QColor (   0 , 0 , 0 , 192 ) ) ;
  setVariable          ( "HeaderSize" , QSize  ( 256 , 32  )         ) ;
  setVariable          ( "TextPixels"     , 12                       ) ;
  setVariable          ( "TextLength"     , 40                       ) ;
  setVariable          ( "CurrentNode"    , 0                        ) ;
  //////////////////////////////////////////////////////////////////////
  ControlPoint at      ( 0 , 0 , 0 , 1                               ) ;
  ControlPoint zp      ( 0 , 0 , 0 , 1                               ) ;
  ControlPoint scale   ( 1 , 1 , 1 , 1                               ) ;
  ControlPoint rotate  ( 0 , 0 , 1 , 0                               ) ;
  //////////////////////////////////////////////////////////////////////
  at     . DOF = ControlPoint::DofTranslate                            ;
  zp     . DOF = ControlPoint::DofTranslate                            ;
  scale  . DOF = ControlPoint::DofScale                                ;
  rotate . DOF = ControlPoint::DofRotate                               ;
  //////////////////////////////////////////////////////////////////////
  addDof               ( 0 , at                                      ) ;
  addDof               ( 1 , zp                                      ) ;
  addDof               ( 2 , scale                                   ) ;
  addDof               ( 3 , rotate                                  ) ;
  //////////////////////////////////////////////////////////////////////
  horizontalIndex = 0                                                  ;
  verticalIndex   = 0                                                  ;
}

void N::PickItem::render(Camera & camera,QMap<int,Matrix> & matrices)
{
  if ( isLocked ( "Operate" ) ) return       ;
  LockAt               ( "Operate"         ) ;
  UsingCamera = &camera                      ;
  UsingMatrix = matrices                     ;
  UnlockAt             ( "Operate"         ) ;
  SceneObject::render  ( camera , matrices ) ;
}

void N::PickItem::renderFaces(void)
{
  SceneWidget::renderFaces ( ) ;
  renderSelectRect         ( ) ;
}

bool N::PickItem::FocusIn(void)
{
  nKickOut ( IsNull ( plan ) , false ) ;
  return true                          ;
}

bool N::PickItem::FocusOut(void)
{
  return false ;
}

void N::PickItem::ClosePad(SUID u)
{
  if ( ! PadItems . contains ( u ) ) return               ;
  int i = PadItems . indexOf ( u )                        ;
  if ( i >= 0 ) PadItems . takeAt ( i )                   ;
  /////////////////////////////////////////////////////////
  CloseChild  ( u )                                       ;
  ArrangePads (   )                                       ;
}

void N::PickItem::ArrangePads(void)
{
  if ( PadItems . count ( ) <= 0   ) return                 ;
  ///////////////////////////////////////////////////////////
  LockAt   ( "Operate" )                                    ;
  ///////////////////////////////////////////////////////////
  for (int i=0;i<PadItems.count();i++)                      {
    SUID u = PadItems [ i ]                                 ;
    SceneObject * sox                                       ;
    sox  = ChildOf<SceneObject> ( u )                       ;
    sox -> DOFs [ 0 ] . x = maximum . x - 40 - ( 40 * i )   ;
    sox -> DOFs [ 0 ] . y = maximum . y - sox -> length . y ;
    sox -> Finish ( )                                       ;
    sox -> Dual   ( )                                       ;
  }                                                         ;
  ///////////////////////////////////////////////////////////
  UnlockAt ( "Operate" )                                    ;
}

int N::PickItem::AtRegion(ControlPoint & At)
{
  return RectRegion ( At ) ;
}

bool N::PickItem::Spot     (
       ControlPoint & From ,
       ControlPoint & To   ,
       ControlPoint & At   )
{
  if (   Value ( "Finalize" ) . toBool ( ) ) return false ;
  if ( ! Value ( "Mouse"    ) . toBool ( ) ) return false ;
  return xymSpot ( From , To , At )                       ;
}

bool N::PickItem::LocalClicked (
       ControlPoint & From     ,
       ControlPoint & To       ,
       ControlPoint & At       ,
       BMAPs        & buttons  ,
       bool           after    ,
       bool           overlap  )
{
  if ( hasFunction ( "Dragging" ) ) return false ;
  if ( ! after )                                 {
    if ( buttons [ Universe::MouseLeft   ] )     {
      if ( ! isFocus ( ) )                       {
        Alert ( Click )                          ;
      }                                          ;
      setFocus ( true )                          ;
//      setVariable  ( "Hit" , true    )           ;
    } else                                       {
      if ( Value ( "Hit" ) . toBool ( ) )        {
        setVariable      ( "Hit" , false   )     ;
      }                                          ;
    }                                            ;
    return true                                  ;
  }                                              ;
  ////////////////////////////////////////////////
  if ( ! overlap )                               {
    return true                                  ;
  }                                              ;
  ////////////////////////////////////////////////
  return true                                    ;
}

bool N::PickItem::LocalVector (
       ControlPoint & From    ,
       ControlPoint & To      ,
       ControlPoint & At      ,
       BMAPs        & buttons ,
       bool           after   ,
       bool           overlap )
{
  if ( ! after )                                                 {
    //////////////////////////////////////////////////////////////
    if ( buttons [ Universe::MouseLeft ] )                       {
      if ( ! isFocus ( ) )                                       {
        Alert ( Click )                                          ;
      }                                                          ;
      setFocus ( true )                                          ;
    } else                                                       {
      if ( Value ( "Hit" ) . toBool ( ) )                        {
        return MouseEditing ( From , To , At , buttons , false ) ;
      }                                                          ;
    }                                                            ;
    //////////////////////////////////////////////////////////////
    return true                                                  ;
  }                                                              ;
  ////////////////////////////////////////////////////////////////
  return MouseEditing ( From , To , At , buttons , false )       ;
}

bool N::PickItem::LocalHover (
       ControlPoint & From      ,
       ControlPoint & To        ,
       ControlPoint & At        ,
       BMAPs        & buttons   ,
       bool           after     ,
       bool           overlap   )
{
  if ( ! after )                                              {
    QPointF AT  ( At . x , At . y   )                         ;
    setVariable ( "CurrentPos" , AT )                         ;
    return true                                               ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  if ( ! overlap )                                            {
    if ( MouseEditing ( From , To , At , buttons , true ) )   {
      return true                                             ;
    }                                                         ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  int region = AtRegion ( At )                                ;
  if ( region <= 0 )                                          {
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
  AssignCursor ( region )                                     ;
  /////////////////////////////////////////////////////////////
  return true                                                 ;
}

bool N::PickItem::MouseClicked (
       ControlPoint & From     ,
       ControlPoint & To       ,
       BMAPs        & buttons  )
{
  if ( hasFunction ( "Finalize" ) ) return false            ;
  if ( hasFunction ( "Dragging" ) ) return false            ;
  return SceneObject::CursorClicked ( From , To , buttons ) ;
}

bool N::PickItem::MouseVector (
       ControlPoint & From    ,
       ControlPoint & To      ,
       BMAPs        & buttons )
{
  if ( hasFunction ( "Finalize" ) ) return false           ;
  if ( hasFunction ( "Dragging" ) ) return false           ;
  if ( buttons [ Universe::MouseLeft ]                    &&
       hasFunction   ( "StartDrag"      )                ) {
    ControlPoint At                                        ;
    Collide ( From , To , At )                             ;
    if ( beginDrag   ( From , To , At ) ) return true      ;
  }                                                        ;
  return SceneObject::CursorVector ( From , To , buttons ) ;
}

bool N::PickItem::MouseHover  (
       ControlPoint & From    ,
       ControlPoint & To      ,
       BMAPs        & buttons )
{
  if (   Value ( "Finalize" ) . toBool ( ) ) return false ;
  if ( hasFunction ( "Dragging" )          ) return false ;
  return SceneObject::CursorHover ( From , To , buttons ) ;
}

bool N::PickItem::MouseMove   (
       ControlPoint & From1   ,
       ControlPoint & To1     ,
       ControlPoint & From2   ,
       ControlPoint & To2     ,
       BMAPs        & buttons )
{
  return false ;
}

void N::PickItem::setContainer(ControlPoint & minp,ControlPoint & maxp)
{
  AssignPoint ( "MinPoint" , minp ) ;
  AssignPoint ( "MaxPoint" , maxp ) ;
}

void N::PickItem::setBox(ControlPoint & box)
{
  AssignPoint ( "BoxPoint" , box ) ;
}

void N::PickItem::setGap(ControlPoint & gap)
{
  AssignPoint ( "GapPoint" , gap ) ;
}

void N::PickItem::setBase(ControlPoint & bp)
{
  AssignPoint ( "BasePoint" , bp ) ;
}

void N::PickItem::setAppear(ControlPoint & appear)
{
  AssignPoint ( "AppearPoint" , appear ) ;
}

void N::PickItem::setDefaultMin(ControlPoint & minp)
{
  AssignPoint ( "DefaultMin" , minp ) ;
}

void N::PickItem::setDefaultMax(ControlPoint & maxp)
{
  AssignPoint ( "DefaultMax" , maxp ) ;
}

void N::PickItem::setTitle(QString title)
{
  QColor       tc = Value ( "TitleColor" ) . value < QColor > ( ) ;
  QSize        ss = Value ( "HeaderSize" ) . toSize           ( ) ;
  TextObject * to = GetTitle (                                  ) ;
  ControlPoint at = GetPoint ( "HeaderCorner"                   ) ;
  /////////////////////////////////////////////////////////////////
  at . t    = 1                                                   ;
  at . DOF  = ControlPoint::DofTranslate                          ;
  /////////////////////////////////////////////////////////////////
  setVariable        ( "WindowTitle" , title                    ) ;
  to -> addDof       ( 0     , at                               ) ;
  to -> setTextColor ( tc                                       ) ;
  to -> setTextRange ( 10001 , ss                               ) ;
  to -> setText      ( title                                    ) ;
  to -> Finish       (                                          ) ;
  to -> Dual         (                                          ) ;
}

void N::PickItem::SortBy(int orderby,QString item)
{
  setVariable ( "Sorting" , orderby ) ;
  setVariable ( "ByItem"  , item    ) ;
}

void N::PickItem::setAccess(QString method)
{
  setVariable   ( "Access" , method     ) ;
  method = method . toLower ( )           ;
  if ( "first"  == method )               {
    setVariable ( "ByItem" , "position" ) ;
  }                                       ;
  if ( "second" == method )               {
    setVariable ( "ByItem" , "reversal" ) ;
  }                                       ;
}

int N::PickItem::lineCount(void)
{
  QString      arrange = Value ( "Arrange" ) . toString ( ) ;
  QString      align   = Value ( "Align"   ) . toString ( ) ;
  ControlPoint base                                         ;
  ControlPoint box                                          ;
  ControlPoint gap                                          ;
  ControlPoint minp                                         ;
  ControlPoint maxp                                         ;
  ///////////////////////////////////////////////////////////
  if ( ( "Left/Right" == arrange )                        ) {
    if ( "Top/Bottom" == align )                            {
    } else
    if ( "Bottom/Top" == align )                            {
    } else                                                  {
      return 1                                              ;
    }                                                       ;
  }                                                         ;
  ///////////////////////////////////////////////////////////
  if ( ( "Right/Left" == arrange )                        ) {
    if ( "Top/Bottom" == align )                            {
    } else
    if ( "Bottom/Top" == align )                            {
    } else                                                  {
      return 1                                              ;
    }                                                       ;
  }                                                         ;
  ///////////////////////////////////////////////////////////
  if ( Variables . contains ( "BasePoint" ) )               {
    base = GetPoint ( "BasePoint" )                         ;
  } else                                                    {
    return 0                                                ;
  }                                                         ;
  ///////////////////////////////////////////////////////////
  if ( Variables . contains ( "BoxPoint" ) )                {
    box  = GetPoint ( "BoxPoint" )                          ;
  } else                                                    {
    return 0                                                ;
  }                                                         ;
  ///////////////////////////////////////////////////////////
  if ( Variables . contains ( "GapPoint" ) )                {
    gap  = GetPoint ( "GapPoint" )                          ;
  } else                                                    {
    return 0                                                ;
  }                                                         ;
  ///////////////////////////////////////////////////////////
  if ( Variables . contains ( "MinPoint" ) )                {
    minp = GetPoint ( "MinPoint" )                          ;
  } else                                                    {
    return 0                                                ;
  }                                                         ;
  ///////////////////////////////////////////////////////////
  if ( Variables . contains ( "MaxPoint" ) )                {
    maxp = GetPoint ( "MaxPoint" )                          ;
  } else                                                    {
    return 0                                                ;
  }                                                         ;
  ///////////////////////////////////////////////////////////
  double bv = base . y                                      ;
  double gv = gap  . y                                      ;
  double lv = minp . y                                      ;
  double rv = maxp . y                                      ;
  double ag = gv                                            ;
  double dr                                                 ;
  ///////////////////////////////////////////////////////////
  if ( ag < 0                 ) ag = -ag                    ;
  if ( ag < 0.000000000000001 ) return  0                   ;
  ///////////////////////////////////////////////////////////
  if ( gv > 0 )                                             {
    dr  = gv - box . y                                      ;
    dr += rv - bv + 0.1                                     ;
  } else                                                    {
    dr  = gv + lv - bv - 0.1                                ;
  }                                                         ;
  ///////////////////////////////////////////////////////////
  return (int) ( dr / gv )                                  ;
}

int N::PickItem::columnCount(void)
{
  QString      arrange = Value ( "Arrange" ) . toString ( ) ;
  QString      align   = Value ( "Align"   ) . toString ( ) ;
  ControlPoint base                                         ;
  ControlPoint gap                                          ;
  ControlPoint minp                                         ;
  ControlPoint maxp                                         ;
  ///////////////////////////////////////////////////////////
  if ( ( "Top/Bottom" == arrange )                        ) {
    if ( "Left/Right" == align )                            {
    } else
    if ( "Right/Left" == align )                            {
    } else                                                  {
      return 1                                              ;
    }                                                       ;
  }                                                         ;
  ///////////////////////////////////////////////////////////
  if ( ( "Bottom/Top" == arrange )                        ) {
    if ( "Left/Right" == align )                            {
    } else
    if ( "Right/Left" == align )                            {
    } else                                                  {
      return 1                                              ;
    }                                                       ;
  }                                                         ;
  ///////////////////////////////////////////////////////////
  if ( Variables . contains ( "BasePoint" ) )               {
    base = GetPoint ( "BasePoint" )                         ;
  } else                                                    {
    return 0                                                ;
  }                                                         ;
  ///////////////////////////////////////////////////////////
  if ( Variables . contains ( "GapPoint" ) )                {
    gap  = GetPoint ( "GapPoint" )                          ;
  } else                                                    {
    return 0                                                ;
  }                                                         ;
  ///////////////////////////////////////////////////////////
  if ( Variables . contains ( "MinPoint" ) )                {
    minp = GetPoint ( "MinPoint" )                          ;
  } else                                                    {
    return 0                                                ;
  }                                                         ;
  ///////////////////////////////////////////////////////////
  if ( Variables . contains ( "MaxPoint" ) )                {
    maxp = GetPoint ( "MaxPoint" )                          ;
  } else                                                    {
    return 0                                                ;
  }                                                         ;
  ///////////////////////////////////////////////////////////
  double bv = base . x                                      ;
  double gv = gap  . x                                      ;
  double lv = minp . x                                      ;
  double rv = maxp . x                                      ;
  double ag = gv                                            ;
  double dr                                                 ;
  ///////////////////////////////////////////////////////////
  if ( ag < 0                 ) ag = -ag                    ;
  if ( ag < 0.000000000000001 ) return  0                   ;
  ///////////////////////////////////////////////////////////
  if ( gv > 0 )                                             {
    dr = rv - bv                                            ;
  } else                                                    {
    dr = lv - bv                                            ;
  }                                                         ;
  ///////////////////////////////////////////////////////////
  return (int) ( dr / gv )                                  ;
}

int N::PickItem::depthCount(void)
{
  ControlPoint base                           ;
  ControlPoint gap                            ;
  ControlPoint minp                           ;
  ControlPoint maxp                           ;
  /////////////////////////////////////////////
  if ( Variables . contains ( "BasePoint" ) ) {
    base = GetPoint ( "BasePoint" )           ;
  } else                                      {
    return 0                                  ;
  }                                           ;
  /////////////////////////////////////////////
  if ( Variables . contains ( "GapPoint" ) )  {
    gap  = GetPoint ( "GapPoint" )            ;
  } else                                      {
    return 0                                  ;
  }                                           ;
  /////////////////////////////////////////////
  if ( Variables . contains ( "MinPoint" ) )  {
    minp = GetPoint ( "MinPoint" )            ;
  } else                                      {
    return 0                                  ;
  }                                           ;
  /////////////////////////////////////////////
  if ( Variables . contains ( "MaxPoint" ) )  {
    maxp = GetPoint ( "MaxPoint" )            ;
  } else                                      {
    return 0                                  ;
  }                                           ;
  /////////////////////////////////////////////
  double bv = base . z                        ;
  double gv = gap  . z                        ;
  double lv = minp . z                        ;
  double rv = maxp . z                        ;
  double ag = gv                              ;
  double dr                                   ;
  /////////////////////////////////////////////
  if ( ag < 0                 ) ag = -ag      ;
  if ( ag < 0.000000000000001 ) return  0     ;
  /////////////////////////////////////////////
  if ( gv > 0 )                               {
    dr = rv - bv                              ;
  } else                                      {
    dr = lv - bv                              ;
  }                                           ;
  /////////////////////////////////////////////
  return (int) ( dr / gv )                    ;
}

SUID N::PickItem::OnItem   (
       ControlPoint & From ,
       ControlPoint & To   ,
       ControlPoint & At   )
{
  ControlPoint p1                                          ;
  ControlPoint p2                                          ;
  SUID         u                                           ;
  //////////////////////////////////////////////////////////
  p1 = matrices [ 2 ] * From                               ;
  p2 = matrices [ 2 ] * To                                 ;
  u  = Nearest ( p1 , p2 , At )                            ;
  if ( u <= 0                                   ) return 0 ;
  if ( ! CurrentItems . contains ( u )          ) return 0 ;
  if ( ! SceneObject::children . contains ( u ) ) return 0 ;
  return u                                                 ;
}

bool N::PickItem::dropNew       (
       QWidget         * widget ,
       const QMimeData * mime   ,
       ControlPoint    & From   ,
       ControlPoint    & To     ,
       ControlPoint    & At     )
{
  SUID u = OnItem ( From , To , At )                  ;
  /////////////////////////////////////////////////////
  if ( u <= 0 ) return false                          ;
  SelectItem * item                                   ;
  item = ChildOf<SelectItem> ( u )                    ;
  if ( IsNull ( item )                 ) return false ;
  u  =  item -> Value ( "UUID" ) . toULongLong ( )    ;
  if ( u <= 0                          ) return false ;
  return dropHandler ( mime )                         ;
}

bool N::PickItem::dropMoving    (
       QWidget         * widget ,
       const QMimeData * mime   ,
       ControlPoint    & From   ,
       ControlPoint    & To     ,
       ControlPoint    & At     )
{
  SUID u = OnItem ( From , To , At )                  ;
  /////////////////////////////////////////////////////
  if ( u <= 0 ) return false                          ;
  SelectItem * item                                   ;
  item = ChildOf<SelectItem> ( u )                    ;
  if ( IsNull ( item )                 ) return false ;
  u  =  item -> Value ( "UUID" ) . toULongLong ( )    ;
  if ( u <= 0                          ) return false ;
  return dropHandler ( mime )                         ;
}

bool N::PickItem::dropAppend    (
       QWidget         * widget ,
       const QMimeData * mime   ,
       ControlPoint    & From   ,
       ControlPoint    & To     ,
       ControlPoint    & At     )
{
  SUID u = OnItem ( From , To , At )                 ;
  ////////////////////////////////////////////////////
  if ( u > 0 )                                       {
    SelectItem * item                                ;
    item = ChildOf<SelectItem> ( u )                 ;
    if ( NotNull ( item ) )                          {
      u = item -> Value ( "UUID" ) . toULongLong ( ) ;
    } else u = 0                                     ;
  }                                                  ;
  setVariable      ( "DropUUID" , u         )        ;
  AssignPoint      ( "DropFrom" , From      )        ;
  AssignPoint      ( "DropTo"   , To        )        ;
  AssignPoint      ( "DropAt"   , At        )        ;
  return dropItems ( widget     , mime , At )        ;
}

bool N::PickItem::removeDrop(void)
{
  bool dropIn = hasFunction ( "DropIn" ) ;
  setVariable ( "DropIn" , false )       ;
  return dropIn                          ;
}

bool N::PickItem::beginDrag (
       ControlPoint & From  ,
       ControlPoint & To    ,
       ControlPoint & At    )
{
  if ( ! hasFunction ( "StartDrag" ) ) return false ;
  if ( NotNull ( Drag ) )                           {
    setVariable ( "StartDrag" , false )             ;
    return false                                    ;
  }                                                 ;
  if ( ! hasItem ( From , To , At ) )               {
    setVariable ( "StartDrag" , false )             ;
    return false                                    ;
  }                                                 ;
  ///////////////////////////////////////////////////
  mimeDrag = dragMime ( From , To , At )            ;
  ///////////////////////////////////////////////////
  if ( IsNull ( mimeDrag ) )                        {
    setVariable ( "StartDrag" , false )             ;
    return false                                    ;
  }                                                 ;
  setVariable   ( "Dragging" , true  )              ;
  return true                                       ;
}

UUIDs N::PickItem::SelectedItems(void)
{
  UUIDs R                                                                ;
  UUIDs U = CurrentItems                                                 ;
  SUID  u                                                                ;
  if ( U . count ( ) <= 0 ) return R                                     ;
  foreach ( u , U )                                                      {
    SceneObject * sox  = ChildOf<SceneObject> ( u )                      ;
    if ( NotNull ( sox ) )                                               {
      QByteArray pointer                                                 ;
      sox -> ObjectPointer ( pointer )                                   ;
      if ( pointer . size ( ) >= sizeof(SwClassStructure) )              {
        SwClassStructure * scs = (SwClassStructure *) pointer . data ( ) ;
        SUID sid = scs -> me -> Value ( "UUID" ) . toULongLong ( )       ;
        if ( scs -> me -> hasFunction ( "Checked" ) )                    {
          if ( ! R . contains ( sid ) ) R << sid                         ;
        }                                                                ;
      }                                                                  ;
    }                                                                    ;
  }                                                                      ;
  return R                                                               ;
}

int N::PickItem::addItem(SelectItem * item,bool bounding)
{
  PrivatePickItem * ppi = new PrivatePickItem (               )        ;
  SUID              u   = appendChild         ( 100001 , item )        ;
  ControlPoint      minp                                               ;
  ControlPoint      maxp                                               ;
  item -> Finish ( )                                                   ;
  item -> Dual   ( )                                                   ;
  if ( bounding )                                                      {
    if ( item -> BoundingBox ( minp , maxp ) )                         {
      AddPoint ( minp )                                                ;
      AddPoint ( maxp )                                                ;
    }                                                                  ;
  }                                                                    ;
  Finish ( )                                                           ;
  Dual   ( )                                                           ;
  item -> DynamicFunctions [ "Selection" ] = N::PickItem::AcceptSelect ;
  item -> userobjs         [ "Selection" ] = ppi                       ;
  item -> setUniverse   ( UniverseUuid ( ) )                           ;
  item -> setParentUuid ( node             )                           ;
  ppi  -> item                             = item                      ;
  ppi  -> box                              = this                      ;
  CurrentItems << u                                                    ;
  return SceneObject::children . count ( )                             ;
}

N::SelectItem * N::PickItem::CurrentItem(void)
{
  SUID          nuid = Value ( "CurrentNode" ) . toULongLong ( )   ;
  if ( nuid <= 0   ) return NULL                                   ;
  SceneObject * sox  = ChildOf<SceneObject> ( nuid )               ;
  if ( NULL == sox ) return NULL                                   ;
  QByteArray pointer                                               ;
  sox -> ObjectPointer ( pointer )                                 ;
  if ( pointer . size ( ) < sizeof(SwClassStructure) ) return NULL ;
  SwClassStructure * scs = (SwClassStructure *) pointer . data ( ) ;
  return Casting ( SelectItem , scs -> me )                        ;
}

N::SelectItem * N::PickItem::NearestItem(ControlPoint & From,ControlPoint & To)
{
  ControlPoint At                                                  ;
  SUID         nuid = OnItem ( From , To , At )                    ;
  if ( nuid <= 0 ) return NULL                                     ;
  SceneObject * sox  = ChildOf<SceneObject> ( nuid )               ;
  if ( NULL == sox ) return NULL                                   ;
  QByteArray pointer                                               ;
  sox -> ObjectPointer ( pointer )                                 ;
  if ( pointer . size ( ) < sizeof(SwClassStructure) ) return NULL ;
  SwClassStructure * scs = (SwClassStructure *) pointer . data ( ) ;
  return Casting ( SelectItem , scs -> me )                        ;
}

N::SelectItem * N::PickItem::New(void)
{
  SelectItem * item = new SelectItem ( NULL , plan , destructor ) ;
  ControlPoint at     ( 0 , 0 ,  0 , 1 )                          ;
  ControlPoint zp     ( 0 , 0 ,  0 , 1 )                          ;
  ControlPoint scale  ( 1 , 1 ,  1 , 1 )                          ;
  ControlPoint rotate ( 0 , 1 ,  0 , 0 )                          ;
  /////////////////////////////////////////////////////////////////
  if ( Variables . contains ( "DefaultMin" ) )                    {
    item -> minimum = GetPoint ( "DefaultMin"  )                  ;
  }                                                               ;
  /////////////////////////////////////////////////////////////////
  if ( Variables . contains ( "DefaultMax" ) )                    {
    item -> maximum = GetPoint ( "DefaultMax"  )                  ;
  }                                                               ;
  /////////////////////////////////////////////////////////////////
  if ( Variables . contains ( "AppearPoint" ) )                   {
    at              = GetPoint ( "AppearPoint" )                  ;
  }                                                               ;
  /////////////////////////////////////////////////////////////////
  at     . DOF = ControlPoint::DofTranslate                       ;
  zp     . DOF = ControlPoint::DofTranslate                       ;
  scale  . DOF = ControlPoint::DofScale                           ;
  rotate . DOF = ControlPoint::DofRotate                          ;
  /////////////////////////////////////////////////////////////////
  item  -> gui = gui                                              ;
  item  -> addDof ( 0 , at     )                                  ;
  item  -> addDof ( 1 , zp     )                                  ;
  item  -> addDof ( 2 , scale  )                                  ;
  item  -> addDof ( 3 , rotate )                                  ;
  /////////////////////////////////////////////////////////////////
  BindingMenu ( item )                                            ;
  /////////////////////////////////////////////////////////////////
  return item                                                     ;
}

N::SelectItem * N::PickItem::NewIcon(QImage * image,QSize s)
{
  SelectItem * si = PickItem::New  (                          ) ;
  IconObject * io = new IconObject ( NULL , plan , destructor ) ;
  ///////////////////////////////////////////////////////////////
  io -> minimum = ControlPoint     (   4 ,   4 ,  2 , 1       ) ;
  io -> maximum = ControlPoint     ( 132 , 132 , 26 , 1       ) ;
  io -> setIcon                    ( 10001 , image            ) ;
  io -> setIconSize                ( s                        ) ;
  io -> addSequence                ( 12 , RenderUser          ) ;
  ///////////////////////////////////////////////////////////////
  si -> Finish                     (                          ) ;
  si -> Dual                       (                          ) ;
  si -> addSequence                ( 11 , RenderChildren      ) ;
  ///////////////////////////////////////////////////////////////
  PickItem::addItem                ( si , false               ) ;
  ///////////////////////////////////////////////////////////////
  si -> addItem                    ( io                       ) ;
  si -> setVariable                ( "IconNode" , io -> node  ) ;
  si -> setCheckable               ( true                     ) ;
  ///////////////////////////////////////////////////////////////
  return si                                                     ;
}

N::SelectItem * N::PickItem::NewItem(QString text,QImage * image,QSize s)
{
  int          align = Qt::AlignHCenter                           |
                       Qt::AlignTop                               |
                       Qt::TextWordWrap                           ;
  int          pixel = Value ( "TextPixels" ) . toInt ( )         ;
  int          tlen  = Value ( "TextLength" ) . toInt ( )         ;
  QFont        f     = plan->fonts[Fonts::Editor].toQFont()       ;
  SelectItem * si = PickItem::New  (                            ) ;
  IconObject * io = new IconObject ( NULL , plan , destructor   ) ;
  TextObject * to = new TextObject ( NULL , plan , destructor   ) ;
  /////////////////////////////////////////////////////////////////
  io -> minimum = ControlPoint     (   0 ,  40 ,  2 , 1         ) ;
  io -> maximum = ControlPoint     ( 128 , 168 , 26 , 1         ) ;
  io -> setIcon                    ( 10001 , image              ) ;
  io -> setIconSize                ( s                          ) ;
  io -> addSequence                ( 12 , RenderUser            ) ;
  /////////////////////////////////////////////////////////////////
  to -> minimum = ControlPoint     (   0 ,   0 ,  2 , 1         ) ;
  to -> maximum = ControlPoint     ( 128 ,  32 , 26 , 1         ) ;
  to -> setVariable                ( "Length" , tlen            ) ;
  to -> setTextFlags               ( align                      ) ;
  to -> setFont                    ( f                          ) ;
  to -> setPixelSize               ( pixel                      ) ;
  to -> setTextRange               ( 10001 , QSize ( 128 , 32 ) ) ;
  to -> setTextColor               ( QColor ( 0 , 0 , 0 , 192 ) ) ;
  to -> setText                    ( text                       ) ;
  to -> addSequence                ( 12 , RenderUser            ) ;
  /////////////////////////////////////////////////////////////////
  si -> setVariable                ( "Shell"    , "Never"       ) ;
  si -> Finish                     (                            ) ;
  si -> Dual                       (                            ) ;
  si -> addSequence                ( 11 , RenderChildren        ) ;
  /////////////////////////////////////////////////////////////////
  PickItem::addItem                ( si , false                 ) ;
  /////////////////////////////////////////////////////////////////
  si -> addItem                    ( io                         ) ;
  si -> addItem                    ( to                         ) ;
  si -> setCheckable               ( true                       ) ;
  si -> setVariable                ( "IconNode" , io -> node    ) ;
  si -> setVariable                ( "TextNode" , to -> node    ) ;
  si -> setVariable                ( "ItemName" , text          ) ;
  /////////////////////////////////////////////////////////////////
  return si                                                       ;
}

N::SelectItem * N::PickItem::NewText(QString text,QSize s)
{
  int          align = Qt::AlignLeft | Qt::AlignVCenter           ;
  int          pixel = Value ( "TextPixels" ) . toInt ( )         ;
  int          tlen  = Value ( "TextLength" ) . toInt ( )         ;
  QFont        f     = plan->fonts[Fonts::Editor].toQFont()       ;
  SelectItem * si = PickItem::New  (                            ) ;
  TextObject * to = new TextObject ( NULL , plan , destructor   ) ;
  double       ww = s . width      (                            ) ;
  double       hh = s . height     (                            ) ;
  /////////////////////////////////////////////////////////////////
  to -> minimum = ControlPoint     (      2 ,      2 ,  2 , 1   ) ;
  to -> maximum = ControlPoint     ( ww + 2 , hh + 2 , 26 , 1   ) ;
  to -> setVariable                ( "Length" , tlen            ) ;
  to -> setTextFlags               ( align                      ) ;
  to -> setFont                    ( f                          ) ;
  to -> setPixelSize               ( pixel                      ) ;
  to -> setTextRange               ( 10001 , s                  ) ;
  to -> setTextColor               ( QColor ( 0 , 0 , 0 , 192 ) ) ;
  to -> setText                    ( text                       ) ;
  to -> addSequence                ( 12 , RenderUser            ) ;
  /////////////////////////////////////////////////////////////////
  si -> setVariable                ( "Shell"    , "Never"       ) ;
  si -> Finish                     (                            ) ;
  si -> Dual                       (                            ) ;
  si -> addSequence                ( 11 , RenderChildren        ) ;
  /////////////////////////////////////////////////////////////////
  PickItem::addItem                ( si , false                 ) ;
  /////////////////////////////////////////////////////////////////
  si -> addItem                    ( to                         ) ;
  si -> setCheckable               ( true                       ) ;
  si -> setVariable                ( "TextNode" , to -> node    ) ;
  si -> setVariable                ( "ItemName" , text          ) ;
  /////////////////////////////////////////////////////////////////
  return si                                                       ;
}

N::IconObject * N::PickItem::IconItem (SelectItem * item)
{
  SUID node = item -> Value ( "IconNode" ) . toULongLong ( ) ;
  if ( node <= 0 ) return NULL                               ;
  return item -> ChildOf < IconObject > ( node )             ;
}

N::TextObject * N::PickItem::TextItem (SelectItem * item)
{
  SUID node = item -> Value ( "TextNode" ) . toULongLong ( ) ;
  if ( node <= 0 ) return NULL                               ;
  return item -> ChildOf < TextObject > ( node )             ;
}

N::TextObject * N::PickItem::GetTitle(void)
{
  int          align = Qt::AlignLeft | Qt::AlignVCenter       ;
  QFont        f     = plan->fonts[Fonts::Editor].toQFont()   ;
  TextObject * to    = NULL                                   ;
  SUID         uu    = 0                                      ;
  /////////////////////////////////////////////////////////////
  if ( Variables . contains ( "TitleUUID" ) )                 {
    uu = Value ( "TitleUUID" ) . toULongLong ( )              ;
    if ( uu > 0 )                                             {
      to = ChildOf<TextObject> ( uu )                         ;
      if ( NotNull ( to ) ) return to                         ;
    }                                                         ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  to  = new TextObject         ( NULL , plan , destructor   ) ;
  /////////////////////////////////////////////////////////////
  to -> minimum = ControlPoint (   0 ,  0 ,  4 , 1          ) ;
  to -> maximum = ControlPoint ( 256 , 32 , 28 , 1          ) ;
  to -> setTextFlags           ( align                      ) ;
  to -> setFont                ( f                          ) ;
  to -> setPixelSize           ( 24                         ) ;
  to -> setTextColor           ( QColor ( 0 , 0 , 0 , 192 ) ) ;
  to -> addSequence            ( 12  , RenderUser           ) ;
  to -> setCheckable           (                false       ) ;
  to -> setVariable            ( "Mouse"      , false       ) ;
  to -> setVariable            ( "Selectable" , false       ) ;
  to -> setVariable            ( "Clickable"  , false       ) ;
  to -> setVariable            ( "Emit"       , false       ) ;
  to -> setVariable            ( "Shell"      , false       ) ;
  /////////////////////////////////////////////////////////////
  uu  = appendChild            ( 130001 , to                ) ;
  /////////////////////////////////////////////////////////////
  to -> Finish                 (                            ) ;
  to -> Dual                   (                            ) ;
  to -> setUniverse            ( UniverseUuid ( )           ) ;
  to -> setParentUuid          ( node                       ) ;
  /////////////////////////////////////////////////////////////
  setVariable                  ( "TitleUUID" , uu           ) ;
  /////////////////////////////////////////////////////////////
  return to                                                   ;
}

N::IconObject * N::PickItem::AddButton(void)
{
  IconObject * io = new IconObject ( NULL , plan , destructor )    ;
  SUID         uu = 0                                              ;
  ControlPoint at = ControlPoint   ( 0 , 0 , 0 , 1            )    ;
  //////////////////////////////////////////////////////////////////
  at  . x       = maximum . x - 40 - ( 40 * PadItems . count ( ) ) ;
  at  . y       = maximum . y - 40                                 ;
  at  . z       = minimum . z + 4                                  ;
  at  . t       = 1                                                ;
  at  . DOF     = ControlPoint::DofTranslate                       ;
  //////////////////////////////////////////////////////////////////
  io -> minimum = ControlPoint     (  0 ,  0 ,  0 , 1         )    ;
  io -> maximum = ControlPoint     ( 40 , 40 , 24 , 1         )    ;
  io -> addSequence                ( 12 , RenderUser          )    ;
  //////////////////////////////////////////////////////////////////
  uu  = appendChild                ( 130001 , io              )    ;
  //////////////////////////////////////////////////////////////////
  io -> addDof                     ( 0 , at                   )    ;
  io -> Finish                     (                          )    ;
  io -> Dual                       (                          )    ;
  io -> setUniverse                ( UniverseUuid ( )         )    ;
  io -> setParentUuid              ( node                     )    ;
  //////////////////////////////////////////////////////////////////
  PadItems << io -> node                                           ;
  //////////////////////////////////////////////////////////////////
  return io                                                        ;
}

N::IconObject * N::PickItem::NewButton(QImage * image,QSize s)
{
  IconObject * io = AddButton (               ) ;
  io -> setIcon               ( 10001 , image ) ;
  io -> setIconSize           ( s             ) ;
  return io                                     ;
}

N::ProgressButton * N::PickItem::ProgressTool(void)
{
  ProgressButton * pb = new ProgressButton ( NULL , plan , destructor ) ;
  SUID             uu = 0                                               ;
  ControlPoint     at = ControlPoint       ( 0 , 0 , 0 , 1            ) ;
  ///////////////////////////////////////////////////////////////////////
  at  . x       = maximum . x - 40 - ( 40 * PadItems . count ( ) )      ;
  at  . y       = maximum . y - 40                                      ;
  at  . z       = minimum . z + 4                                       ;
  at  . t       = 1                                                     ;
  at  . DOF     = ControlPoint::DofTranslate                            ;
  ///////////////////////////////////////////////////////////////////////
  pb -> minimum = ControlPoint             (  0 ,  0 ,  0 , 1         ) ;
  pb -> maximum = ControlPoint             ( 40 , 40 , 24 , 1         ) ;
  pb -> addSequence                        ( 12 , RenderUser          ) ;
  ///////////////////////////////////////////////////////////////////////
  uu  = appendChild                        ( 130001 , pb              ) ;
  ///////////////////////////////////////////////////////////////////////
  pb -> addDof                             ( 0 , at                   ) ;
  pb -> Finish                             (                          ) ;
  pb -> Dual                               (                          ) ;
  pb -> setUniverse                        ( UniverseUuid ( )         ) ;
  pb -> setParentUuid                      ( node                     ) ;
  ///////////////////////////////////////////////////////////////////////
  PadItems . prepend ( pb -> node )                                     ;
  ///////////////////////////////////////////////////////////////////////
  return pb                                                             ;
}

N::RangeBar * N::PickItem::ScrollBar(void)
{
  RangeBar * rb = new RangeBar ( NULL , plan , destructor      ) ;
  SUID       uu = 0                                              ;
  ////////////////////////////////////////////////////////////////
  rb -> minimum = ControlPoint (               0 ,  0 ,  4 , 1 ) ;
  rb -> maximum = ControlPoint ( length . x - 18 , 18 , 28 , 1 ) ;
  rb -> addSequence            ( 12 , RenderFaces              ) ;
  ////////////////////////////////////////////////////////////////
  uu  = appendChild            ( 130001 , rb                   ) ;
  ////////////////////////////////////////////////////////////////
  rb -> Finish                 (                               ) ;
  rb -> Dual                   (                               ) ;
  rb -> setUniverse            ( UniverseUuid ( )              ) ;
  rb -> setParentUuid          ( node                          ) ;
  ////////////////////////////////////////////////////////////////
  return rb                                                      ;
}

N::RangeBar * N::PickItem::ScrollBar(Qt::Orientation orientation)
{
  RangeBar * rb = NULL                                         ;
  switch ( orientation )                                       {
    case Qt::Vertical                                          :
      if ( Variables . contains ( "VScrollUuid" ) )            {
        SUID u = Value ( "VScrollUuid" ) . toULongLong ( )     ;
        if ( u > 0 ) rb = ChildOf<RangeBar> ( u )              ;
      }                                                        ;
      //////////////////////////////////////////////////////////
      if ( IsNull ( rb ) )                                     {
        PrivateRangeBar * prb = new PrivateRangeBar ( )        ;
        ControlPoint xt = GetPoint ( "VScrollPos" )            ;
        ControlPoint rt = GetPoint ( "VSBAngle"   )            ;
        ////////////////////////////////////////////////////////
        xt . DOF  = ControlPoint::DofTranslate                 ;
        rt . DOF  = ControlPoint::DofRotate                    ;
        ////////////////////////////////////////////////////////
        rb  = ScrollBar (                                )     ;
        ////////////////////////////////////////////////////////
        rb -> userobjs [ "Indexing" ] = prb                    ;
        rb -> DynamicFunctions [ "Indexing" ] = AcceptIndexing ;
        rb -> maximum . x = maximum . y  - 60                  ;
        rb -> addDof    ( 0 , xt                         )     ;
        rb -> addDof    ( 1 , rt                         )     ;
        rb -> Finish    (                                )     ;
        rb -> Dual      (                                )     ;
        setVariable     ( "VScrollUuid" , rb -> node     )     ;
        ////////////////////////////////////////////////////////
        prb -> range     = rb                                  ;
        prb -> box       = this                                ;
        prb -> direction = Qt::Vertical                        ;
      }                                                        ;
      //////////////////////////////////////////////////////////
    break                                                      ;
    case Qt::Horizontal                                        :
      if ( Variables . contains ( "HScrollUuid" ) )            {
        SUID u = Value ( "HScrollUuid" ) . toULongLong ( )     ;
        if ( u > 0 ) rb = ChildOf<RangeBar> ( u )              ;
      }                                                        ;
      //////////////////////////////////////////////////////////
      if ( IsNull ( rb ) )                                     {
        PrivateRangeBar * prb = new PrivateRangeBar ( )        ;
        ControlPoint at = GetPoint ( "HScrollPos" )            ;
        at . t    = 1                                          ;
        at . DOF  = ControlPoint::DofTranslate                 ;
        ////////////////////////////////////////////////////////
        rb = ScrollBar (                                 )     ;
        ////////////////////////////////////////////////////////
        rb -> userobjs [ "Indexing" ] = prb                    ;
        rb -> DynamicFunctions [ "Indexing" ] = AcceptIndexing ;
        rb -> addDof   ( 0 , at                          )     ;
        rb -> Finish   (                                 )     ;
        rb -> Dual     (                                 )     ;
        setVariable    ( "HScrollUuid" , rb -> node      )     ;
        ////////////////////////////////////////////////////////
        prb -> range     = rb                                  ;
        prb -> box       = this                                ;
        prb -> direction = Qt::Horizontal                      ;
      }                                                        ;
      //////////////////////////////////////////////////////////
    break                                                      ;
  }                                                            ;
  return rb                                                    ;
}

bool N::PickItem::setScrollBar(Qt::Orientation orientation,bool enabled)
{
  RangeBar * rb = ScrollBar ( orientation ) ;
  visibilities [ rb -> node ] = enabled     ;
  switch ( orientation )                    {
    case Qt::Vertical                       :
      setVariable ( "VScroll" , enabled )   ;
    break                                   ;
    case Qt::Horizontal                     :
      setVariable ( "HScroll" , enabled )   ;
    break                                   ;
  }                                         ;
  return enabled                            ;
}

bool N::PickItem::isInside(ControlPoints & Box,SelectItem * item)
{
  ControlPoints IB                                                  ;
  if ( item -> BoundingBox ( IB [ 0 ] , IB [ 1 ] ) )                {
    visibilities [ item -> node ] = SceneBox::isInside ( Box , IB ) ;
  }                                                                 ;
  return visibilities [ item -> node ]                              ;
}

void N::PickItem::CleanItems(void)
{
  UUIDs U = CurrentItems             ;
  SUID  u                            ;
  LockAt               ( "Operate" ) ;
  CurrentItems . clear (           ) ;
  UnlockAt             ( "Operate" ) ;
  foreach              ( u , U     ) {
    CloseChild         ( u         ) ;
  }                                  ;
}

void N::PickItem::atDoubleClicked(SelectItem * item)
{
}

void N::PickItem::atClicked(SelectItem * item)
{
}

void N::PickItem::atSelected(SelectItem * item)
{
}

void N::PickItem::atSelectClicked(SelectItem * item)
{
}

void N::PickItem::doSelection(SelectItem * item)
{
  QString sel        = Value ( "SelectionMode" ) . toString ( )              ;
  bool    selectable = Value ( "Selectable"    ) . toBool   ( )              ;
  bool    emits      = Value ( "Emit"          ) . toBool   ( )              ;
  SUID    u                                                                  ;
  ////////////////////////////////////////////////////////////////////////////
  sel = sel . toLower ( )                                                    ;
  ////////////////////////////////////////////////////////////////////////////
  if ( ! selectable )                                                        {
    item -> setVariable ( "Checked" , false )                                ;
    return                                                                   ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( emits ) emit Selected ( item )                                        ;
  atSelected                 ( item )                                        ;
  ////////////////////////////////////////////////////////////////////////////
  if ( "contiguous" == sel )                                                 {
    return                                                                   ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( "extended"   == sel )                                                 {
    return                                                                   ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( "multiple"   == sel )                                                 {
    return                                                                   ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( "single"     == sel )                                                 {
    if ( ! item -> isChecked ( ) )                                           {
      item -> setChecked ( true )                                            ;
      if ( emits ) emit SelectClicked ( item )                               ;
      atSelectClicked                 ( item )                               ;
    } else                                                                   {
      if ( emits ) emit Clicked       ( item )                               ;
      atClicked                       ( item )                               ;
    }                                                                        ;
    setVariable ( "CurrentNode" , item -> node )                             ;
    foreach ( u , CurrentItems )                                             {
      SelectItem * sox = ChildOf<SelectItem>(u)                              ;
      if ( sox != item )                                                     {
        sox -> setChecked ( false )                                          ;
      }                                                                      ;
    }                                                                        ;
    return                                                                   ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( "none"       == sel )                                                 {
    foreach ( u , CurrentItems )                                             {
      SelectItem * sox = ChildOf<SelectItem>(u)                              ;
      sox -> setChecked ( false )                                            ;
    }                                                                        ;
    return                                                                   ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
}

void N::PickItem::ItemSelections(void)
{
  QString sel        = Value ( "SelectionMode" ) . toString ( ) ;
  bool    selectable = Value ( "Selectable"    ) . toBool   ( ) ;
  ///////////////////////////////////////////////////////////////
  sel = sel . toLower ( )                                       ;
  ///////////////////////////////////////////////////////////////
  if ( ! selectable ) return                                    ;
  if ( "none"       == sel ) return                             ;
  if ( "single"     == sel ) return                             ;
  ///////////////////////////////////////////////////////////////
  if ( "contiguous" == sel )                                    {
    MarkSelections ( )                                          ;
    return                                                      ;
  }                                                             ;
  ///////////////////////////////////////////////////////////////
  if ( "extended"   == sel )                                    {
    MarkSelections ( )                                          ;
    return                                                      ;
  }                                                             ;
  ///////////////////////////////////////////////////////////////
  if ( "multiple"   == sel )                                    {
    MarkSelections ( )                                          ;
    return                                                      ;
  }                                                             ;
}

int N::PickItem::Selecting(SelectItem * sox,QVariants & v)
{
  bool pressed = v [ 0 ]          . toBool ( )                           ;
  bool hit     = v [ 1 ]          . toBool ( )                           ;
  bool dbc     = v [ 2 ]          . toBool ( )                           ;
  bool emits   = Value ( "Emit" ) . toBool ( )                           ;
  ////////////////////////////////////////////////////////////////////////
  if ( dbc )                                                             {
    if ( emits ) emit DoubleClicked ( sox )                              ;
    atDoubleClicked                 ( sox )                              ;
  } else                                                                 {
    if ( hit && ( ! pressed ) ) doSelection ( sox )                      ;
  }                                                                      ;
  ////////////////////////////////////////////////////////////////////////
  if ( userobjs . contains ( "Selection" ) )                             {
    void    * Handler = userobjs [ "Selection" ]                         ;
    QVariants V                                                          ;
    V << sox -> Value ( "UUID"    ) . toULongLong ( )                    ;
    V << sox -> Value ( "Checked" ) . toBool      ( )                    ;
    V << dbc                                                             ;
    CallDynamic ( "Selection" , this , Handler , V )                     ;
  }                                                                      ;
  ////////////////////////////////////////////////////////////////////////
  return 0                                                               ;
}

int N::PickItem::AcceptSelect(void * data,void * dispatcher,QVariants & v)
{
  if ( NULL == data       ) return 0                     ;
  if ( NULL == dispatcher ) return 0                     ;
  PrivatePickItem * ppi = (PrivatePickItem *) dispatcher ;
  ////////////////////////////////////////////////////////
  SelectItem * siu = ppi -> item                         ;
  PickItem   * piu = ppi -> box                          ;
  ////////////////////////////////////////////////////////
  if ( NULL == siu        ) return 0                     ;
  if ( NULL == piu        ) return 0                     ;
  ////////////////////////////////////////////////////////
  return piu -> Selecting ( siu , v )                    ;
}

int N::PickItem::Indexing(RangeBar * rbu,int direction,QVariants & v)
{
  qint64 s = v [ 0 ] . toLongLong ( ) ; // start
  qint64 e = v [ 1 ] . toLongLong ( ) ; // end
  qint64 p = v [ 2 ] . toLongLong ( ) ; // page
  qint64 i = v [ 3 ] . toLongLong ( ) ; // index
  /////////////////////////////////////

  /////////////////////////////////////
  return 0                            ;
}

int N::PickItem::AcceptIndexing(void * data,void * dispatcher,QVariants & v)
{
  if ( NULL == data       ) return 0                     ;
  if ( NULL == dispatcher ) return 0                     ;
  PrivateRangeBar * prb = (PrivateRangeBar *) dispatcher ;
  ////////////////////////////////////////////////////////
  RangeBar * rbu = prb -> range                          ;
  PickItem * piu = prb -> box                            ;
  ////////////////////////////////////////////////////////
  if ( NULL == rbu        ) return 0                     ;
  if ( NULL == piu        ) return 0                     ;
  ////////////////////////////////////////////////////////
  return piu -> Indexing ( rbu , prb -> direction , v )  ;
}

void N::PickItem::MarkSelections(void)
{
  QRectF       R = SelectionArea ( )                        ;
  UUIDs        U = SceneObject::children . keys ( )         ;
  SUID         u                                            ;
  qint64       i = 0                                        ;
  ControlPoint minp                                         ;
  ControlPoint maxp                                         ;
  ///////////////////////////////////////////////////////////
  while ( ForUuid ( u , i , U ) ) if ( visibilities [ u ] ) {
    SceneObject * sox = ChildOf<SceneObject> ( u )          ;
    if ( NotNull ( sox ) )                                  {
      QString tn = sox -> Value ( "Type" ) . toString ( )   ;
      if ( "Select" == tn )                                 {
        SelectItem * item = (SelectItem *) sox              ;
        if ( item -> BoundingBox ( minp , maxp ) )          {
          QRectF X                                          ;
          X . setLeft   ( minp . x )                        ;
          X . setTop    ( minp . y )                        ;
          X . setRight  ( maxp . x )                        ;
          X . setBottom ( maxp . y )                        ;
          if ( R . intersects ( X ) )                       {
            item -> setChecked ( true )                     ;
          }                                                 ;
        }                                                   ;
      }                                                     ;
    }                                                       ;
  }                                                         ;
}

void N::PickItem::AssignCursor(int region)
{
  QString sel        = Value ( "SelectionMode" ) . toString ( ) ;
  bool    selectable = Value ( "Selectable"    ) . toBool   ( ) ;
  ///////////////////////////////////////////////////////////////
  sel = sel . toLower ( )                                       ;
  ///////////////////////////////////////////////////////////////
  if ( "none"       == sel ) selectable = false                 ;
  if ( "single"     == sel ) selectable = false                 ;
  ///////////////////////////////////////////////////////////////
  switch ( region )                                             {
    case 0                                                      : // 0 - Outside
    break                                                       ;
    case 1                                                      : // 1 - Inside
      if ( selectable )                                         {
        setCursor ( Qt::CrossCursor     )                       ;
        return                                                  ;
      }                                                         ;
      if ( Value ( "Movable" ) . toBool ( ) )                   {
        setCursor ( Qt::OpenHandCursor  )                       ;
        ToolTip   (                     )                       ;
        return                                                  ;
      }                                                         ;
    break                                                       ;
    case 2                                                      : // 2 - left
      if ( selectable )                                         {
        setCursor ( Qt::CrossCursor     )                       ;
        return                                                  ;
      }                                                         ;
      if ( Value ( "Left/Line" ) . toBool ( ) )                 {
        if ( Value ( "Resizable" ) . toBool ( ) )               {
          setCursor ( Qt::SizeHorCursor   )                     ;
          ToolTip   (                     )                     ;
          return                                                ;
        }                                                       ;
      }                                                         ;
    break                                                       ;
    case 3                                                      : // 3 - right
      if ( selectable )                                         {
        setCursor ( Qt::CrossCursor     )                       ;
        return                                                  ;
      }                                                         ;
      if ( Value ( "Right/Line" ) . toBool ( ) )                {
        if ( Value ( "Resizable" ) . toBool ( ) )               {
          setCursor ( Qt::SizeHorCursor   )                     ;
          ToolTip   (                     )                     ;
          return                                                ;
        }                                                       ;
      }                                                         ;
    break                                                       ;
    case 4                                                      : // 4 - top
      if ( selectable )                                         {
        setCursor ( Qt::CrossCursor     )                       ;
        return                                                  ;
      }                                                         ;
      if ( Value ( "Top/Line" ) . toBool ( ) )                  {
        if ( Value ( "Resizable" ) . toBool ( ) )               {
          setCursor ( Qt::SizeVerCursor   )                     ;
          ToolTip   (                     )                     ;
          return                                                ;
        }                                                       ;
      }                                                         ;
    break                                                       ;
    case 5                                                      : // 5 - bottom
      if ( selectable )                                         {
        setCursor ( Qt::CrossCursor     )                       ;
        return                                                  ;
      }                                                         ;
      if ( Value ( "Bottom/Line" ) . toBool ( ) )               {
        if ( Value ( "Resizable" ) . toBool ( ) )               {
          setCursor ( Qt::SizeVerCursor   )                     ;
          ToolTip   (                     )                     ;
          return                                                ;
        }                                                       ;
      }                                                         ;
    break                                                       ;
    case 6                                                      : // 6 - top    / left
      if ( selectable )                                         {
        setCursor ( Qt::CrossCursor     )                       ;
        return                                                  ;
      }                                                         ;
      if ( Value ( "Top/Left" ) . toBool ( ) )                  {
        if ( Value ( "Resizable" ) . toBool ( ) )               {
          setCursor ( Qt::SizeFDiagCursor )                     ;
          ToolTip   (                     )                     ;
          return                                                ;
        }                                                       ;
      }                                                         ;
    break                                                       ;
    case 7                                                      : // 7 - top    / right
      if ( selectable )                                         {
        setCursor ( Qt::CrossCursor     )                       ;
        return                                                  ;
      }                                                         ;
      if ( Value ( "Top/Right" ) . toBool ( ) )                 {
        if ( Value ( "Resizable" ) . toBool ( ) )               {
          setCursor ( Qt::SizeBDiagCursor )                     ;
          ToolTip   (                     )                     ;
          return                                                ;
        }                                                       ;
      }                                                         ;
    break                                                       ;
    case 8                                                      : // 8 - bottom / left
      if ( selectable )                                         {
        setCursor ( Qt::CrossCursor     )                       ;
        return                                                  ;
      }                                                         ;
      if ( Value ( "Bottom/Left" ) . toBool ( ) )               {
        if ( Value ( "Resizable" ) . toBool ( ) )               {
          setCursor ( Qt::SizeBDiagCursor )                     ;
          ToolTip   (                     )                     ;
          return                                                ;
        }                                                       ;
      }                                                         ;
    break                                                       ;
    case 9                                                      : // 9 - bottom / right
      if ( selectable )                                         {
        setCursor ( Qt::CrossCursor     )                       ;
        return                                                  ;
      }                                                         ;
      if ( Value ( "Bottom/Right" ) . toBool ( ) )              {
        if ( Value ( "Resizable" ) . toBool ( ) )               {
          setCursor ( Qt::SizeFDiagCursor )                     ;
          ToolTip   (                     )                     ;
          return                                                ;
        }                                                       ;
      }                                                         ;
    break                                                       ;
  }                                                             ;
  setCursor ( Qt::ArrowCursor )                                 ;
}

void N::PickItem::ArrangeScrollBars(void)
{
  bool hscroll = Value ( "HScroll" ) . toBool ( )          ;
  bool vscroll = Value ( "VScroll" ) . toBool ( )          ;
  if ( ( ! vscroll ) && ( ! hscroll ) ) return             ;
  //////////////////////////////////////////////////////////
  if ( vscroll && hscroll )                                {
    RangeBar   * rv = ScrollBar ( Qt::Vertical          )  ;
    RangeBar   * rh = ScrollBar ( Qt::Horizontal        )  ;
    double       vx = Value ( "VScrollX" ) . toDouble ( )  ;
    double       vy = Value ( "VScrollY" ) . toDouble ( )  ;
    double       hx = Value ( "HScrollX" ) . toDouble ( )  ;
    double       hy = Value ( "HScrollY" ) . toDouble ( )  ;
    QString      vh = Value ( "VScrollH" ) . toString ( )  ;
    QString      vv = Value ( "VScrollV" ) . toString ( )  ;
    QString      hv = Value ( "HScrollV" ) . toString ( )  ;
    ControlPoint vt = GetPoint  ( "VScrollPos"          )  ;
    ControlPoint ht = GetPoint  ( "HScrollPos"          )  ;
    ////////////////////////////////////////////////////////
    vh = vh . toLower ( )                                  ;
    vv = vv . toLower ( )                                  ;
    hv = hv . toLower ( )                                  ;
    ////////////////////////////////////////////////////////
    LockAt       ( "Operate"         )                     ;
    ////////////////////////////////////////////////////////
    rh -> minimum . x = 0                                  ;
    rh -> maximum . x = length . x + vx                    ;
    ////////////////////////////////////////////////////////
    rv -> minimum . x = 0                                  ;
    rv -> maximum . x = length . y - rh -> length . y - hx ;
    ////////////////////////////////////////////////////////
    ht . x            = minimum . x + hx                   ;
    ////////////////////////////////////////////////////////
    if ( "top"    == hv )                                  {
      ht . y             = maximum . y + hy                ;
    }                                                      ;
    if ( "bottom" == hv )                                  {
      ht . y             = minimum . y + hy                ;
    }                                                      ;
    ////////////////////////////////////////////////////////
    if ( "left"   == vh )                                  {
      vt . x             = minimum . x + vx                ;
    }                                                      ;
    if ( "right"  == vh )                                  {
      vt . x             = maximum . x + vx                ;
    }                                                      ;
    ////////////////////////////////////////////////////////
    if ( "top"    == vv )                                  {
      vt . y             = maximum . y + vy                ;
      rv -> maximum . x += vy                              ;
    }                                                      ;
    if ( "bottom" == vv )                                  {
      vt . y             = minimum . y + vy                ;
      rv -> maximum . x -= vy                              ;
    }                                                      ;
    ////////////////////////////////////////////////////////
    ht . t            = 1                                  ;
    ht . DOF          = ControlPoint::DofTranslate         ;
    ////////////////////////////////////////////////////////
    vt . t            = 1                                  ;
    vt . DOF          = ControlPoint::DofTranslate         ;
    ////////////////////////////////////////////////////////
    AssignPoint  ( "VScrollPos" , vt )                     ;
    AssignPoint  ( "HScrollPos" , ht )                     ;
    ////////////////////////////////////////////////////////
    rv -> addDof ( 0            , vt )                     ;
    rv -> Finish (                   )                     ;
    rv -> Dual   (                   )                     ;
    ////////////////////////////////////////////////////////
    rh -> addDof ( 0            , ht )                     ;
    rh -> Finish (                   )                     ;
    rh -> Dual   (                   )                     ;
    ////////////////////////////////////////////////////////
    UnlockAt     ( "Operate"         )                     ;
    ////////////////////////////////////////////////////////
    return                                                 ;
  }                                                        ;
  //////////////////////////////////////////////////////////
  if ( vscroll )                                           {
    RangeBar   * rv = ScrollBar ( Qt::Vertical          )  ;
    double       x  = Value ( "VScrollX" ) . toDouble ( )  ;
    double       y  = Value ( "VScrollY" ) . toDouble ( )  ;
    QString      h  = Value ( "VScrollH" ) . toString ( )  ;
    QString      v  = Value ( "VScrollV" ) . toString ( )  ;
    ControlPoint at = GetPoint ( "VScrollPos"           )  ;
    ////////////////////////////////////////////////////////
    h = h . toLower ( )                                    ;
    v = v . toLower ( )                                    ;
    ////////////////////////////////////////////////////////
    LockAt       ( "Operate"         )                     ;
    ////////////////////////////////////////////////////////
    rv -> minimum . x = 0                                  ;
    rv -> maximum . x = length . y + y                     ;
    ////////////////////////////////////////////////////////
    if ( "left"   == h )                                   {
      at . x          = minimum . x + x                    ;
    }                                                      ;
    if ( "right"  == h )                                   {
      at . x          = maximum . x + x                    ;
    }                                                      ;
    ////////////////////////////////////////////////////////
    if ( "top"    == v )                                   {
      at . y          = maximum . y + y                    ;
    }                                                      ;
    if ( "bottom" == v )                                   {
      at . y          = minimum . y + y                    ;
    }                                                      ;
    ////////////////////////////////////////////////////////
    at . t            = 1                                  ;
    at . DOF          = ControlPoint::DofTranslate         ;
    ////////////////////////////////////////////////////////
    AssignPoint  ( "VScrollPos" , at )                     ;
    rv -> addDof ( 0            , at )                     ;
    rv -> Finish (                   )                     ;
    rv -> Dual   (                   )                     ;
    ////////////////////////////////////////////////////////
    UnlockAt     ( "Operate"         )                     ;
    ////////////////////////////////////////////////////////
    return                                                 ;
  }                                                        ;
  //////////////////////////////////////////////////////////
  if ( hscroll )                                           {
    RangeBar   * rh = ScrollBar ( Qt::Horizontal        )  ;
    double       x  = Value ( "HScrollX" ) . toDouble ( )  ;
    double       y  = Value ( "HScrollY" ) . toDouble ( )  ;
    QString      v  = Value ( "HScrollV" ) . toString ( )  ;
    ControlPoint at = GetPoint ( "HScrollPos"           )  ;
    ////////////////////////////////////////////////////////
    v = v . toLower ( )                                    ;
    ////////////////////////////////////////////////////////
    LockAt       ( "Operate"         )                     ;
    ////////////////////////////////////////////////////////
    rh -> minimum . x = 0                                  ;
    rh -> maximum . x = length . x                         ;
    ////////////////////////////////////////////////////////
    at . x            = minimum . x + x                    ;
    ////////////////////////////////////////////////////////
    if ( "top"    == v )                                   {
      at . y          = maximum . y + y                    ;
    }                                                      ;
    if ( "bottom" == v )                                   {
      at . y          = minimum . y + y                    ;
    }                                                      ;
    ////////////////////////////////////////////////////////
    at . t            = 1                                  ;
    at . DOF          = ControlPoint::DofTranslate         ;
    ////////////////////////////////////////////////////////
    AssignPoint  ( "HScrollPos" , at )                     ;
    rh -> addDof ( 0            , at )                     ;
    rh -> Finish (                   )                     ;
    rh -> Dual   (                   )                     ;
    ////////////////////////////////////////////////////////
    UnlockAt     ( "Operate"         )                     ;
    ////////////////////////////////////////////////////////
    return                                                 ;
  }                                                        ;
}

void N::PickItem::ArrangeTitle(void)
{
  if ( ! Variables . contains ( "TitleUUID" ) ) return        ;
  /////////////////////////////////////////////////////////////
  QString      align = Value ( "HeaderAlign" ) . toString ( ) ;
  double       hx    = Value ( "HeaderX"     ) . toDouble ( ) ;
  double       hy    = Value ( "HeaderY"     ) . toDouble ( ) ;
  TextObject * to    = GetTitle (                           ) ;
  ControlPoint at    = GetPoint ( "HeaderCorner"            ) ;
  /////////////////////////////////////////////////////////////
  if ( "Top/Line"     == align )                              {
    at . y = maximum . y + hy                                 ;
  }                                                           ;
  if ( "Bottom/Line"  == align )                              {
    at . y = minimum . y + hy                                 ;
  }                                                           ;
  if ( "Left/Line"    == align )                              {
    at . x = minimum . x + hx                                 ;
  }                                                           ;
  if ( "Right/Line"   == align )                              {
    at . x = maximum . x + hx                                 ;
  }                                                           ;
  if ( "Top/Left"     == align )                              {
    at . x = minimum . x + hx                                 ;
    at . y = maximum . y + hy                                 ;
  }                                                           ;
  if ( "Top/Right"    == align )                              {
    at . x = maximum . x + hx                                 ;
    at . y = maximum . y + hy                                 ;
  }                                                           ;
  if ( "Bottom/Left"  == align )                              {
    at . x = minimum . x + hx                                 ;
    at . y = minimum . y + hy                                 ;
  }                                                           ;
  if ( "Bottom/Right" == align )                              {
    at . x = maximum . x + hx                                 ;
    at . y = minimum . y + hy                                 ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  at . t    = 1                                               ;
  at . DOF  = ControlPoint::DofTranslate                      ;
  /////////////////////////////////////////////////////////////
  AssignPoint        ( "HeaderCorner" , at                  ) ;
  to -> addDof       ( 0              , at                  ) ;
  to -> Finish       (                                      ) ;
  to -> Dual         (                                      ) ;
}

void N::PickItem::ArrangeItem(SUID u,qint64 z,qint64 columns,qint64 rows)
{
  SelectItem * si = ChildOf<SelectItem> ( u )                ;
  if ( IsNull ( si ) ) return                                ;
  ////////////////////////////////////////////////////////////
  QString       arrange = Value ( "Arrange" ) . toString ( ) ;
  QString       align   = Value ( "Align"   ) . toString ( ) ;
  ControlPoint  b       = GetPoint ( "BasePoint" )           ;
  ControlPoint  g       = GetPoint ( "GapPoint"  )           ;
  int           x       = 0                                  ;
  int           y       = 0                                  ;
  ControlPoint  at                                           ;
  ControlPoints CB                                           ;
  ////////////////////////////////////////////////////////////
  at = b                                                     ;
  ////////////////////////////////////////////////////////////
  if ( ( "Top/Bottom" == arrange )                          ||
       ( "Bottom/Top" == arrange )                         ) {
    if ( "Left/Right" == align )                             {
      x        = z % columns                                 ;
      y        = z / columns                                 ;
      at . x  += g . x * x                                   ;
      at . y  += g . y * y                                   ;
    } else
    if ( "Right/Left" == align )                             {
      x        = z % columns                                 ;
      y        = z / columns                                 ;
      at . x  += g . x * x                                   ;
      at . y  += g . y * y                                   ;
    } else                                                   {
      at . y  += g . y * z                                   ;
    }                                                        ;
  }                                                          ;
  ////////////////////////////////////////////////////////////
  if ( ( "Left/Right" == arrange )                          ||
       ( "Right/Left" == arrange )                         ) {
    if ( "Top/Bottom" == align )                             {
      x        = z / rows                                    ;
      y        = z % rows                                    ;
      at . x  += g . x * x                                   ;
      at . y  += g . y * y                                   ;
    } else
    if ( "Bottom/Top" == align )                             {
      x        = z / rows                                    ;
      y        = z % rows                                    ;
      at . x  += g . x * x                                   ;
      at . y  += g . y * y                                   ;
    } else                                                   {
      at . x  += g . x * z                                   ;
    }                                                        ;
  }                                                          ;
  ////////////////////////////////////////////////////////////
  at . t   = 1                                               ;
  at . DOF = ControlPoint::DofTranslate                      ;
  CB [ 0 ] = GetPoint ( "MinPoint" )                         ;
  CB [ 1 ] = GetPoint ( "MaxPoint" )                         ;
  LockAt       ( "Operate" )                                 ;
  si -> addDof ( 0  , at   )                                 ;
  si -> Finish (           )                                 ;
  si -> Dual   (           )                                 ;
  isInside     ( CB , si   )                                 ;
  UnlockAt     ( "Operate" )                                 ;
}

void N::PickItem::ArrangeItems(qint64 startId,UUIDs & U)
{
  int      c = columnCount ( )    ;
  int      r = lineCount   ( )    ;
  qint64   i = startId            ;
  qint64   z = 0                  ;
  SUID     u                      ;
  /////////////////////////////////
  while ( ForUuid ( u , z , U ) ) {
    visibilities [ u ] = false    ;
  }                               ;
  /////////////////////////////////
  z = 0                           ;
  while ( ForUuid ( u , i , U ) ) {
    ArrangeItem ( u , z , c , r ) ;
    z++                           ;
  }                               ;
}

void N::PickItem::RearrangeItems(UUIDs & U)
{
  QString      arrange = Value ( "Arrange"      ) . toString ( )  ;
  QString      align   = Value ( "Align"        ) . toString ( )  ;
  double       TM      = Value ( "TopMargin"    ) . toDouble ( )  ;
  double       BM      = Value ( "BottomMargin" ) . toDouble ( )  ;
  double       LM      = Value ( "LeftMargin"   ) . toDouble ( )  ;
  double       RM      = Value ( "RightMargin"  ) . toDouble ( )  ;
  int          c       = columnCount ( )                          ;
  int          r       = lineCount   ( )                          ;
  int          p       = c * r                                    ;
  qint64       i       = Value ( "CurrentPageIndex" ) . toInt ( ) ;
  ControlPoint b       = GetPoint ( "BasePoint" )                 ;
  ControlPoint g       = GetPoint ( "GapPoint"  )                 ;
  ControlPoint ip      = GetPoint ( "MinPoint"  )                 ;
  ControlPoint ap      = GetPoint ( "MaxPoint"  )                 ;
  /////////////////////////////////////////////////////////////////
  ip . x = minimum . x + LM                                       ;
  ip . y = minimum . y + BM                                       ;
  ap . x = maximum . x - RM                                       ;
  ap . y = maximum . y - TM                                       ;
  setContainer ( ip , ap )                                        ;
  /////////////////////////////////////////////////////////////////
  if ( ( "Top/Bottom" == arrange )                              ) {
    if ( "Left/Right" == align )                                  {
      b  . x = minimum . x + LM                                   ;
      b  . y = maximum . y - TM + g . y                           ;
    } else
    if ( "Right/Left" == align )                                  {
      b  . x = minimum . x + LM                                   ;
      b  . y = maximum . y - TM + g . y                           ;
    } else                                                        {
      b  . x = minimum . x + LM                                   ;
      b  . y = maximum . y - TM + g . y                           ;
    }                                                             ;
  }                                                               ;
  /////////////////////////////////////////////////////////////////
  if ( ( "Bottom/Top" == arrange )                              ) {
    if ( "Left/Right" == align )                                  {
      b  . x = minimum . x + LM                                   ;
      b  . y = minimum . y + BM                                   ;
    } else
    if ( "Right/Left" == align )                                  {
      b  . x = minimum . x + LM                                   ;
      b  . y = minimum . y + BM                                   ;
    } else                                                        {
      b  . x = minimum . x + LM                                   ;
      b  . y = minimum . y + BM                                   ;
    }                                                             ;
  }                                                               ;
  /////////////////////////////////////////////////////////////////
  if ( ( "Left/Right" == arrange )                              ) {
    if ( "Top/Bottom" == align )                                  {
      b  . x = minimum . x + LM                                   ;
      b  . y = maximum . y - TM + g . y                           ;
    } else
    if ( "Bottom/Top" == align )                                  {
      b  . x = minimum . x + LM                                   ;
      b  . y = minimum . y + BM                                   ;
    } else                                                        {
      b  . x = minimum . x + LM                                   ;
      b  . y = maximum . y - TM + g . y                           ;
    }                                                             ;
  }                                                               ;
  /////////////////////////////////////////////////////////////////
  if ( ( "Right/Left" == arrange )                              ) {
    if ( "Top/Bottom" == align )                                  {
      b  . x = minimum . x + LM                                   ;
      b  . y = maximum . y - TM + g . y                           ;
    } else
    if ( "Bottom/Top" == align )                                  {
      b  . x = minimum . x + LM                                   ;
      b  . y = minimum . y + BM                                   ;
    } else                                                        {
      b  . x = minimum . x + LM                                   ;
      b  . y = maximum . y - TM + g . y                           ;
    }                                                             ;
  }                                                               ;
  /////////////////////////////////////////////////////////////////
  setBase ( b )                                                   ;
  /////////////////////////////////////////////////////////////////
  if ( ( i + p ) > U . count ( ) ) i = U . count ( ) - p          ;
  if ( i < 0 ) i = 0                                              ;
  /////////////////////////////////////////////////////////////////
  ArrangeItems ( i , U )                                          ;
}

void N::PickItem::UpdateVScroll(qint64 total)
{
  QString align = Value ( "Align" ) . toString ( ) ;
  qint64  c     = columnCount ( )                  ;
  qint64  r     = lineCount   ( )                  ;
  qint64  page                                     ;
  //////////////////////////////////////////////////
  if ( "Left/Right" == align )                     {
    page  = c * r                                  ;
  } else
  if ( "Right/Left" == align )                     {
    page  = c * r                                  ;
  } else                                           {
    page  = r                                      ;
  }                                                ;
  //////////////////////////////////////////////////
  setScrollBar ( Qt::Vertical , ( total > page ) ) ;
  if ( total > page )                              {
    RangeBar * rb = ScrollBar ( Qt::Vertical )     ;
    verticalIndex = 0                              ;
    rb -> setVariable ( "Emit" , false )           ;
    rb -> setRange    ( 0 , total - 1  )           ;
    rb -> setPage     ( page           )           ;
    rb -> setStep     ( c              )           ;
    rb -> assignIndex ( &verticalIndex )           ;
    rb -> setVariable ( "Emit" , true  )           ;
    visibilities [ rb -> node ] = true             ;
  }                                                ;
}

void N::PickItem::UpdateHScroll(qint64 total)
{
  QString align = Value ( "Align" ) . toString ( )   ;
  qint64  c    = columnCount ( )                     ;
  qint64  r    = lineCount   ( )                     ;
  qint64  page                                       ;
  ////////////////////////////////////////////////////
  if ( "Top/Bottom" == align )                       {
    page = c * r                                     ;
  } else
  if ( "Bottom/Top" == align )                       {
    page = c * r                                     ;
  } else                                             {
    page = c                                         ;
  }                                                  ;
  ////////////////////////////////////////////////////
  setScrollBar ( Qt::Horizontal , ( total > page ) ) ;
  if ( total > page )                                {
    RangeBar * rb = ScrollBar ( Qt::Horizontal )     ;
    horizontalIndex = 0                              ;
    rb -> setVariable ( "Emit" , false   )           ;
    rb -> setRange    ( 0 , total - 1    )           ;
    rb -> setPage     ( page             )           ;
    rb -> setStep     ( c                )           ;
    rb -> assignIndex ( &horizontalIndex )           ;
    rb -> setVariable ( "Emit" , true    )           ;
    visibilities [ rb -> node ] = true               ;
  }                                                  ;
}

bool N::PickItem::AllowMenu  (
       QWidget      * widget ,
       QPointF        pos    ,
       ControlPoint & From   ,
       ControlPoint & To     ,
       ControlPoint & At     ,
       bool         & answer )
{
  answer = false                                               ;
  if ( ! Value ( "Mouse" ) . toBool ( ) ) return false         ;
  setCursor ( Qt::ArrowCursor )                                ;
  //////////////////////////////////////////////////////////////
  if ( ! Collide   ( From , To , At           ) ) return false ;
  if (   ChildMenu ( widget , pos , From , To ) )              {
    answer = true                                              ;
    return false                                               ;
  }                                                            ;
  //////////////////////////////////////////////////////////////
  return true                                                  ;
}

bool N::PickItem::prepare(void)
{
  return true ;
}

bool N::PickItem::startup(void)
{
  return true ;
}

#endif
