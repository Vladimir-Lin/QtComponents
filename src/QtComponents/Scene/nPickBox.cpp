#include <qtcomponents.h>

#ifdef QT_OPENGL_LIB

N::PickBox:: PickBox  ( QObject * parent , Plan * p )
           : PickItem (           parent ,        p )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::PickBox:: PickBox  ( QObject * parent , Plan * p , SceneDestructor * des )
           : PickItem (           parent ,        p ,                   des )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::PickBox::~PickBox (void)
{
}

void N::PickBox::Configure(void)
{
  QSize        TextRect ( 512 , 32                         ) ;
  QPointF      PadPoint (  40 , 40                         ) ;
  ControlPoint color                                         ;
  color  = ControlPoint ( 1.00 , 1.00 , 1.0 , 0.95         ) ;
  addColor              (   60 , color                     ) ;
  color  = ControlPoint ( 0.60 , 0.80 , 0.9 , 0.10         ) ;
  addColor              (   61 , color                     ) ;
  color  = ControlPoint ( 0.50 , 0.70 , 0.3 , 0.25         ) ;
  addColor              (   62 , color                     ) ;
  color  = ControlPoint ( 0.70 , 0.30 , 0.5 , 0.35         ) ;
  addColor              (   63 , color                     ) ;
  ////////////////////////////////////////////////////////////
  QObject::setProperty ( "Type"             , "PickBox"    ) ;
  setVariable          ( "Type"             , "PickBox"    ) ;
  ////////////////////////////////////////////////////////////
  setVariable          ( "Back"             , true         ) ;
  setVariable          ( "Side"             , true         ) ;
  setVariable          ( "BackColor"        , 60           ) ;
  setVariable          ( "SideColor"        , 61           ) ;
  setVariable          ( "PadColor"         , 62           ) ;
  setVariable          ( "BorderColor"      , 63           ) ;
  setVariable          ( "PadPoint"         , PadPoint     ) ;
  setVariable          ( "PadAlign"         , "Top"        ) ;
  ////////////////////////////////////////////////////////////
  setVariable          ( "Arrange"          , "Top/Bottom" ) ;
  setVariable          ( "Align"            , "Nothing"    ) ;
  setVariable          ( "BottomMargin"     , 10           ) ;
  ////////////////////////////////////////////////////////////
  setVariable          ( "Items"            , 0            ) ;
  setVariable          ( "CurrentPageIndex" , 0            ) ;
  setVariable          ( "AutoRefresh"      , false        ) ;
  setVariable          ( "ArrangeBy"        , "Name"       ) ;
//  setVariable          ( "ArrangeBy"        , "Language"   ) ;
//  setVariable          ( "ArrangeBy"        , "Names"      ) ;
  setVariable          ( "ScrollBy"         , "Current"    ) ;
//  setVariable          ( "ScrollBy"         , "Start"      ) ;
  ////////////////////////////////////////////////////////////
  setVariable          ( "TextRect"         , TextRect     ) ;
  setVariable          ( "TextPixels"       , 24           ) ;
}

void N::PickBox::renderBox(void)
{
  QString PadAlign = Value ( "PadAlign" ) . toString ( )   ;
  QPointF PadPoint = Value ( "PadPoint" ) . toPointF ( )   ;
  //////////////////////////////////////////////////////////
  QtGL::PushMatrix       (                               ) ;
  QtGL::Disable          ( GL_CULL_FACE                  ) ;
  QtGL::Disable          ( GL_LINE_SMOOTH                ) ;
  QtGL::Disable          ( GL_POLYGON_SMOOTH             ) ;
  //////////////////////////////////////////////////////////
  if                     ( Value ( "Back" ) . toBool ( ) ) { // Back
    assumeColor          ( "BackColor"                   ) ;
    CubeVertex           ( 100 , minimum , maximum       ) ;
  }                                                        ;
  //////////////////////////////////////////////////////////
  if                     ( Value ( "Side" ) . toBool ( ) ) { // Side
    assumeColor          ( "SideColor"                   ) ;
    for                  ( int i = 102 ; i <= 105 ; i++  ) {
      CubeVertex         (   i , minimum , maximum       ) ;
    }                                                      ;
  }                                                        ;
  //////////////////////////////////////////////////////////
  assumeColor            ( "PadColor"                    ) ;
  if ( "Top"    == PadAlign )                              {
    double y = maximum . y - PadPoint . y ( )              ;
    QtGL::Quadrilateral  (                               ) ;
    QtGL::Vertex3d       ( minimum . x , y , maximum . z ) ;
    QtGL::Vertex3d       ( maximum . x , y , maximum . z ) ;
    QtGL::Vertex3d       ( maximum . x , y , minimum . z ) ;
    QtGL::Vertex3d       ( minimum . x , y , minimum . z ) ;
    QtGL::End            (                               ) ;
  }                                                        ;
  if ( "Bottom" == PadAlign )                              {
    double y = minimum . y + PadPoint . y ( )              ;
    QtGL::Quadrilateral  (                               ) ;
    QtGL::Vertex3d       ( minimum . x , y , maximum . z ) ;
    QtGL::Vertex3d       ( maximum . x , y , maximum . z ) ;
    QtGL::Vertex3d       ( maximum . x , y , minimum . z ) ;
    QtGL::Vertex3d       ( minimum . x , y , minimum . z ) ;
    QtGL::End            (                               ) ;
  }                                                        ;
  if ( "Left"   == PadAlign )                              {
    double x = minimum . x + PadPoint . x ( )              ;
    QtGL::Quadrilateral  (                               ) ;
    QtGL::Vertex3d       ( x , minimum . y , maximum . z ) ;
    QtGL::Vertex3d       ( x , maximum . y , maximum . z ) ;
    QtGL::Vertex3d       ( x , maximum . y , maximum . z ) ;
    QtGL::Vertex3d       ( x , minimum . y , maximum . z ) ;
    QtGL::End            (                               ) ;
  }                                                        ;
  if ( "Right"  == PadAlign )                              {
    double x = maximum . x - PadPoint . x ( )              ;
    QtGL::Quadrilateral  (                               ) ;
    QtGL::Vertex3d       ( x , minimum . y , maximum . z ) ;
    QtGL::Vertex3d       ( x , maximum . y , maximum . z ) ;
    QtGL::Vertex3d       ( x , maximum . y , maximum . z ) ;
    QtGL::Vertex3d       ( x , minimum . y , maximum . z ) ;
    QtGL::End            (                               ) ;
  }                                                        ;
  //////////////////////////////////////////////////////////
  assumeColor            ( "BorderColor"                 ) ;
  SceneObject::renderBox (                               ) ;
  if ( "Top"    == PadAlign )                              {
    double y = maximum . y - PadPoint . y ( )              ;
    QtGL::Loop           (                               ) ;
    QtGL::Vertex3d       ( minimum . x , y , maximum . z ) ;
    QtGL::Vertex3d       ( maximum . x , y , maximum . z ) ;
    QtGL::Vertex3d       ( maximum . x , y , minimum . z ) ;
    QtGL::Vertex3d       ( minimum . x , y , minimum . z ) ;
    QtGL::End            (                               ) ;
  }                                                        ;
  if ( "Bottom" == PadAlign )                              {
    double y = minimum . y + PadPoint . y ( )              ;
    QtGL::Loop           (                               ) ;
    QtGL::Vertex3d       ( minimum . x , y , maximum . z ) ;
    QtGL::Vertex3d       ( maximum . x , y , maximum . z ) ;
    QtGL::Vertex3d       ( maximum . x , y , minimum . z ) ;
    QtGL::Vertex3d       ( minimum . x , y , minimum . z ) ;
    QtGL::End            (                               ) ;
  }                                                        ;
  if ( "Left"   == PadAlign )                              {
    double x = minimum . x + PadPoint . x ( )              ;
    QtGL::Loop           (                               ) ;
    QtGL::Vertex3d       ( x , minimum . y , maximum . z ) ;
    QtGL::Vertex3d       ( x , maximum . y , maximum . z ) ;
    QtGL::Vertex3d       ( x , maximum . y , maximum . z ) ;
    QtGL::Vertex3d       ( x , minimum . y , maximum . z ) ;
    QtGL::End            (                               ) ;
  }                                                        ;
  if ( "Right"  == PadAlign )                              {
    double x = maximum . x - PadPoint . x ( )              ;
    QtGL::Loop           (                               ) ;
    QtGL::Vertex3d       ( x , minimum . y , maximum . z ) ;
    QtGL::Vertex3d       ( x , maximum . y , maximum . z ) ;
    QtGL::Vertex3d       ( x , maximum . y , maximum . z ) ;
    QtGL::Vertex3d       ( x , minimum . y , maximum . z ) ;
    QtGL::End            (                               ) ;
  }                                                        ;
  //////////////////////////////////////////////////////////
  QtGL::Enable           ( GL_CULL_FACE                  ) ;
  QtGL::PopMatrix        (                               ) ;
}

void N::PickBox::run(int type,ThreadData * data)
{
  ItemRunner ( type , data ) ;
}

bool N::PickBox::ItemRunner(int type,ThreadData * data)
{
  switch ( type )             {
    case 10001                :
      LoadItems     (       ) ;
    return true               ;
    case 10002                :
      ArrangeItems  (       ) ;
    return true               ;
    case 10003                :
      CleanItems    (       ) ;
    return true               ;
    case 10004                :
      ReportDetails (       ) ;
    return true               ;
    case 10005                :
      endDrag       (       ) ;
    return true               ;
    case 10011                :
      LoadItems     (       ) ;
      CleanItems    (       ) ;
      ArrangeItems  (       ) ;
      start         ( 10004 ) ;
    return true               ;
  }                           ;
  return false                ;
}

void N::PickBox::BoxChanged(bool hover)
{
  qint64 total = Value ( "Items"       ) . toLongLong ( ) ;
  bool   r     = Value ( "AutoRefresh" ) . toBool     ( ) ;
  ArrangeTitle      (         )                           ;
  RearrangeItems    (         )                           ;
  ArrangeScrollBars (         )                           ;
  UpdateScrollPages ( total   )                           ;
  ArrangePads       (         )                           ;
  if                ( ! hover )                           {
    if ( r ) start  ( 10011   )                           ;
  }                                                       ;
}

void N::PickBox::FinalizeSelection(void)
{
  ItemSelections ( ) ;
}

void N::PickBox::ArrangeItems(void)
{
  QString arrangeBy = Value ( "ArrangeBy" ) . toString ( ) ;
  //////////////////////////////////////////////////////////
  if ( "Name"     == arrangeBy ) ArrangeName     ( )       ;
  if ( "Language" == arrangeBy ) ArrangeLanguage ( )       ;
  if ( "Names"    == arrangeBy ) ArrangeNames    ( )       ;
}

void N::PickBox::ArrangeName(void)
{
  SqlConnection  SC ( plan -> sql            )                  ;
  ///////////////////////////////////////////////////////////////
  setVariable       ( "CurrentPageIndex" , 0 )                  ;
  verticalIndex   = Value ( "StartId" ) . toInt ( )             ;
  horizontalIndex = Value ( "StartId" ) . toInt ( )             ;
  ///////////////////////////////////////////////////////////////
  if ( SC . open ( FunctionString ) )                           {
    UUIDs              U      = RealItems                       ;
    int                r      = lineCount    ( )                ;
    SUID               u      = 0                               ;
    qint64             index  = 0                               ;
    qint64             z      = 0                               ;
    ProgressButton   * pb     = ProgressTool         ( )        ;
    ProgressReporter * pr     = new ProgressReporter ( )        ;
    bool               drop   = false                           ;
    QSize              trect  = Value ( "TextRect" ) . toSize() ;
    /////////////////////////////////////////////////////////////
    pr -> total = U . count ( )                                 ;
    pr -> value = 0                                             ;
    pr -> setRunning  ( true )                                  ;
    pr -> Using       (      )                                  ;
    pb -> setReporter ( pr   )                                  ;
    ArrangePads       (      )                                  ;
    /////////////////////////////////////////////////////////////
    while ( ! drop )                                            {
      if ( 0 == pr -> state ) drop = true                       ;
      if ( ! drop )                                             {
        if ( 2 == pr -> state )                                 {
          Time::msleep ( 10 )                                   ;
          continue                                              ;
        }                                                       ;
        pr -> state = 1                                         ;
      }                                                         ;
      if ( ! drop ) drop = ! ForUuid ( u , index , U )          ;
      if ( ! drop )                                             {
        QString  n = FetchName ( SC , u )                       ;
        /////////////////////////////////////////////////////////
        SelectItem * si = NewText ( n , trect                 ) ;
        si -> setVariable         ( "UUID" , u                ) ;
        ArrangeItem               ( si -> node , z , 1 , r    ) ;
        z ++                                                    ;
        pr -> value = z                                         ;
        RealToView [ u ] = si -> node                           ;
      }                                                         ;
    }                                                           ;
    /////////////////////////////////////////////////////////////
    pr -> Leaving                 (                           ) ;
    ClosePad                      ( pb -> node                ) ;
    /////////////////////////////////////////////////////////////
    UpdateScrollPages             ( U . count ( )             ) ;
    BoxChanged                    ( true                      ) ;
    /////////////////////////////////////////////////////////////
    SC . close                    (                           ) ;
  }                                                             ;
  SC   . remove                   (                           ) ;
}

void N::PickBox::ArrangeLanguage(void)
{
  GroupItems     GI ( plan                   )                  ;
  SqlConnection  SC ( plan -> sql            )                  ;
  ///////////////////////////////////////////////////////////////
  setVariable       ( "CurrentPageIndex" , 0 )                  ;
  verticalIndex   = Value ( "StartId" ) . toInt ( )             ;
  horizontalIndex = Value ( "StartId" ) . toInt ( )             ;
  ///////////////////////////////////////////////////////////////
  if ( SC . open ( FunctionString ) )                           {
    UUIDs              U      = RealItems                       ;
    int                L      = 1871                            ;
    int                r      = lineCount    ( )                ;
    SUID               u      = 0                               ;
    qint64             index  = 0                               ;
    qint64             z      = 0                               ;
    ProgressButton   * pb     = ProgressTool         ( )        ;
    ProgressReporter * pr     = new ProgressReporter ( )        ;
    bool               drop   = false                           ;
    QSize              trect  = Value ( "TextRect" ) . toSize() ;
    /////////////////////////////////////////////////////////////
    pr -> total = U . count ( )                                 ;
    pr -> value = 0                                             ;
    pr -> setRunning  ( true )                                  ;
    pr -> Using       (      )                                  ;
    pb -> setReporter ( pr   )                                  ;
    ArrangePads       (      )                                  ;
    /////////////////////////////////////////////////////////////
    L = GI . usingLanguage                                      (
          SC                                                    ,
          FirstUuid()                                           ,
          GroupType ( 1 )                                       ,
          plan->LanguageId                                    ) ;
    if ( L <= 0 ) L = plan->LanguageId                          ;
    setVariable ( "LanguageId" , L )                            ;
    /////////////////////////////////////////////////////////////
    while ( ! drop )                                            {
      if ( 0 == pr -> state ) drop = true                       ;
      if ( ! drop )                                             {
        if ( 2 == pr -> state )                                 {
          Time::msleep ( 10 )                                   ;
          continue                                              ;
        }                                                       ;
        pr -> state = 1                                         ;
      }                                                         ;
      if ( ! drop ) drop = ! ForUuid ( u , index , U )          ;
      if ( ! drop )                                             {
        QString  n = FetchAsynName ( SC , u , L )               ;
        /////////////////////////////////////////////////////////
        SelectItem * si = NewText ( n , trect                 ) ;
        si -> setVariable         ( "UUID" , u                ) ;
        ArrangeItem               ( si -> node , z , 1 , r    ) ;
        z ++                                                    ;
        pr -> value = z                                         ;
        RealToView [ u ] = si -> node                           ;
      }                                                         ;
    }                                                           ;
    /////////////////////////////////////////////////////////////
    pr -> Leaving                 (                           ) ;
    ClosePad                      ( pb -> node                ) ;
    /////////////////////////////////////////////////////////////
    UpdateScrollPages             ( U . count ( )             ) ;
    BoxChanged                    ( true                      ) ;
    /////////////////////////////////////////////////////////////
    SC . close                    (                           ) ;
  }                                                             ;
  SC   . remove                   (                           ) ;
}

void N::PickBox::ArrangeNames(void)
{
  GroupItems     GI ( plan                   )                  ;
  SqlConnection  SC ( plan -> sql            )                  ;
  ///////////////////////////////////////////////////////////////
  setVariable       ( "CurrentPageIndex" , 0 )                  ;
  verticalIndex   = Value ( "StartId" ) . toInt ( )             ;
  horizontalIndex = Value ( "StartId" ) . toInt ( )             ;
  ///////////////////////////////////////////////////////////////
  if ( SC . open ( FunctionString ) )                           {
    UUIDs              U      = RealItems                       ;
    int                L      = 1871                            ;
    int                c      = columnCount  ( )                ;
    int                r      = lineCount    ( )                ;
    SUID               u      = 0                               ;
    qint64             index  = 0                               ;
    qint64             z      = 0                               ;
    ProgressButton   * pb     = ProgressTool         ( )        ;
    ProgressReporter * pr     = new ProgressReporter ( )        ;
    bool               drop   = false                           ;
    QSize              trect  = Value ( "TextRect" ) . toSize() ;
    /////////////////////////////////////////////////////////////
    pr -> total = U . count ( )                                 ;
    pr -> value = 0                                             ;
    pr -> setRunning  ( true )                                  ;
    pr -> Using       (      )                                  ;
    pb -> setReporter ( pr   )                                  ;
    ArrangePads       (      )                                  ;
    /////////////////////////////////////////////////////////////
    L = GI . usingLanguage                                      (
          SC                                                    ,
          FirstUuid()                                           ,
          GroupType ( 1 )                                       ,
          plan->LanguageId                                    ) ;
    if ( L <= 0 ) L = plan->LanguageId                          ;
    setVariable ( "LanguageId" , L )                            ;
    /////////////////////////////////////////////////////////////
    while ( ! drop )                                            {
      if ( 0 == pr -> state ) drop = true                       ;
      if ( ! drop )                                             {
        if ( 2 == pr -> state )                                 {
          Time::msleep ( 10 )                                   ;
          continue                                              ;
        }                                                       ;
        pr -> state = 1                                         ;
      }                                                         ;
      if ( ! drop ) drop = ! ForUuid ( u , index , U )          ;
      if ( ! drop )                                             {
        QString      n  = FetchNames ( SC , u )                 ;
        /////////////////////////////////////////////////////////
        SelectItem * si = NewText ( n , trect                 ) ;
        si -> setVariable         ( "UUID" , u                ) ;
        ArrangeItem               ( si -> node , z , c , r    ) ;
        z ++                                                    ;
        pr -> value = z                                         ;
        RealToView [ u ] = si -> node                           ;
      }                                                         ;
    }                                                           ;
    /////////////////////////////////////////////////////////////
    pr -> Leaving                 (                           ) ;
    ClosePad                      ( pb -> node                ) ;
    /////////////////////////////////////////////////////////////
    UpdateScrollPages             ( U . count ( )             ) ;
    BoxChanged                    ( true                      ) ;
    /////////////////////////////////////////////////////////////
    SC . close                    (                           ) ;
  }                                                             ;
  SC   . remove                   (                           ) ;
}

void N::PickBox::RearrangeItems(void)
{
  UUIDs U = CurrentItems         ;
  PickItem::RearrangeItems ( U ) ;
}

void N::PickBox::UpdateScrollPages(qint64 total)
{
  QString scrollBy = Value ( "ScrollBy" ) . toString ( ) ;
  ////////////////////////////////////////////////////////
  if ( "Current" == scrollBy )                           {
    ScrollByCurrent ( total )                            ;
  }                                                      ;
  ////////////////////////////////////////////////////////
  if ( "Start"   == scrollBy )                           {
    ScrollByStart   ( total )                            ;
  }                                                      ;
}

void N::PickBox::ScrollByStart(qint64 total)
{
  qint64  vi      = Value ( "StartId" ) . toLongLong ( ) ;
  QString arrange = Value ( "Arrange" ) . toString   ( ) ;
  if ( ( "Top/Bottom" == arrange )                      ||
       ( "Bottom/Top" == arrange )                     ) {
    UpdateVScroll ( total )                              ;
    verticalIndex = vi                                   ;
  }                                                      ;
}

void N::PickBox::ScrollByCurrent(qint64 total)
{
  QString arrange = Value ( "Arrange" ) . toString ( ) ;
  qint64 vi                                            ;
  if ( ( "Top/Bottom" == arrange )                    ||
       ( "Bottom/Top" == arrange )                   ) {
    vi = verticalIndex                                 ;
    UpdateVScroll ( total )                            ;
    verticalIndex = vi                                 ;
  }                                                    ;
}

bool N::PickBox::prepare(void)
{
  Finish      (                                  ) ;
  Dual        (                                  ) ;
  addSequence (  7 , SceneObject::RenderChildren ) ;
  addSequence ( 11 , SceneObject::RenderBox      ) ;
  addSequence ( 15 , SceneObject::RenderFaces    ) ;
  return true                                      ;
}

bool N::PickBox::startup(void)
{
  start ( 10011 ) ;
  return true     ;
}

bool N::PickBox::LoadItems(void)
{
  QString access = Value ( "Access" ) . toString ( ) . toLower ( ) ;
  if ( "full"      == access ) return LoadFull      ( )            ;
  if ( "divisions" == access ) return LoadDivisions ( )            ;
  if ( "limits"    == access ) return LoadLimits    ( )            ;
  if ( "first"     == access ) return LoadFirst     ( )            ;
  if ( "second"    == access ) return LoadSecond    ( )            ;
  return false                                                     ;
}

bool N::PickBox::LoadFull(void)
{
  bool          correct = false                              ;
  qint64        total   = 0                                  ;
  UUIDs         U                                            ;
  SqlConnection SC ( plan -> sql )                           ;
  ////////////////////////////////////////////////////////////
  if ( SC . open ( FunctionString ) )                        {
    total = SC . count ( MainTable ( ) )                     ;
    if ( SC . Uuids ( U                                      ,
                      MainTable ( )                          ,
                      "uuid"                                 ,
                      SC . OrderBy                           (
                        SortItem                   ( )       ,
                        (Qt::SortOrder)SortingType ( ) ) ) ) {
      correct = true                                         ;
    }                                                        ;
    SC . close  ( )                                          ;
  }                                                          ;
  SC   . remove ( )                                          ;
  ////////////////////////////////////////////////////////////
  LockAt   ( "Operate" )                                     ;
  if ( correct )                                             {
    RealItems = U                                            ;
  } else                                                     {
    RealItems . clear ( )                                    ;
  }                                                          ;
  setVariable ( "Items" , total )                            ;
  UnlockAt ( "Operate" )                                     ;
  ////////////////////////////////////////////////////////////
  return correct                                             ;
}

bool N::PickBox::LoadDivisions(void)
{
  bool          correct = false                   ;
  UUIDs         U                                 ;
  SqlConnection SC ( plan -> sql )                ;
  /////////////////////////////////////////////////
  if ( SC . open ( FunctionString ) )             {
    if ( LoadGroups ( SC                          ,
                      GroupType   ( 1 )           ,
                      U                           ,
                      SortingType (   )           ,
                      SortItem    (   )       ) ) {
      correct = true                              ;
    }                                             ;
    SC . close  (                               ) ;
  }                                               ;
  SC   . remove (                               ) ;
  /////////////////////////////////////////////////
  LockAt   ( "Operate" )                          ;
  if ( correct )                                  {
    RealItems = U                                 ;
  } else                                          {
    RealItems . clear ( )                         ;
  }                                               ;
  setVariable ( "Items" , RealItems . count ( ) ) ;
  UnlockAt ( "Operate" )                          ;
  /////////////////////////////////////////////////
  return correct                                  ;
}

bool N::PickBox::LoadLimits(void)
{
  bool          correct = false                                   ;
  qint64        startId = Value ( "StartId" ) . toLongLong ( )    ;
  qint64        page    = lineCount   ( )                         ;
  qint64        total   = 0                                       ;
  UUIDs         U                                                 ;
  SqlConnection SC ( plan -> sql )                                ;
  /////////////////////////////////////////////////////////////////
  if ( SC . open ( FunctionString ) )                             {
    total = SC . count ( MainTable ( ) )                          ;
    if ( SC . Uuids ( U                                           ,
                      MainTable ( )                               ,
                      "uuid"                                      ,
                      QString ( "%1 %2"                           )
                      . arg ( SC . OrderBy                        (
                              SortItem                   ( )      ,
                              (Qt::SortOrder)SortingType ( )    ) )
                      . arg ( SC . sql . Limit ( startId , page ) )
                                                              ) ) {
      correct = true                                              ;
    }                                                             ;
    SC . close  ( )                                               ;
  }                                                               ;
  SC   . remove ( )                                               ;
  /////////////////////////////////////////////////////////////////
  LockAt   ( "Operate" )                                          ;
  if ( correct )                                                  {
    RealItems = U                                                 ;
  } else                                                          {
    RealItems . clear ( )                                         ;
  }                                                               ;
  setVariable ( "Items" , total )                                 ;
  UnlockAt ( "Operate" )                                          ;
  /////////////////////////////////////////////////////////////////
  return correct                                                  ;
}

bool N::PickBox::LoadFirst(void)
{
  UUIDs         U                                                         ;
  GroupItems    GI ( plan        )                                        ;
  SqlConnection SC ( plan -> sql )                                        ;
  qint64        total = 0                                                 ;
  /////////////////////////////////////////////////////////////////////////
  int t1 = GroupType ( 1 )                                                ;
  int t2 = GroupType ( 2 )                                                ;
  GI . AutoMap    = true                                                  ;
  GI . GroupTable = GI . LookTable                                        (
                      t1                                                  ,
                      t2                                                  ,
                      RelationType ( )                                  ) ;
  /////////////////////////////////////////////////////////////////////////
  if ( SC . open ( FunctionString ) )                                     {
    int    page    = lineCount    ( )                                     ;
    qint64 startId = Value ( "StartId" ) . toLongLong ( )                 ;
    ///////////////////////////////////////////////////////////////////////
    total = GI . Count                                                    (
              SC                                                          ,
              FirstUuid ( )                                               ,
              t1                                                          ,
              t2                                                          ,
              RelationType ( )                                          ) ;
    ///////////////////////////////////////////////////////////////////////
    U = GI . Subordination                                                (
          SC                                                              ,
          FirstUuid ( )                                                   ,
          t1                                                              ,
          t2                                                              ,
          RelationType ( )                                                ,
          SC . OrderBy ( SortItem ( ) , (Qt::SortOrder) SortingType ( ) ) ,
          SC . sql . Limit ( startId , page )                           ) ;
    ///////////////////////////////////////////////////////////////////////
    SC . close  ( )                                                       ;
  }                                                                       ;
  SC   . remove ( )                                                       ;
  /////////////////////////////////////////////////////////////////////////
  LockAt      ( "Operate"       )                                         ;
  RealItems = U                                                           ;
  setVariable ( "Items" , total )                                         ;
  UnlockAt    ( "Operate"       )                                         ;
  /////////////////////////////////////////////////////////////////////////
  return true                                                             ;
}

bool N::PickBox::LoadSecond(void)
{
  UUIDs         U                                                         ;
  GroupItems    GI ( plan        )                                        ;
  SqlConnection SC ( plan -> sql )                                        ;
  qint64        total = 0                                                 ;
  /////////////////////////////////////////////////////////////////////////
  int t1 = GroupType ( 1 )                                                ;
  int t2 = GroupType ( 2 )                                                ;
  GI . AutoMap    = true                                                  ;
  GI . GroupTable = GI . LookTable                                        (
                      t1                                                  ,
                      t2                                                  ,
                      RelationType ( )                                  ) ;
  /////////////////////////////////////////////////////////////////////////
  if ( SC . open ( FunctionString ) )                                     {
    int    page    = lineCount    ( )                                     ;
    qint64 startId = Value ( "StartId" ) . toLongLong ( )                 ;
    ///////////////////////////////////////////////////////////////////////
    total = GI . Count                                                    (
              SC                                                          ,
              SecondUuid ( )                                              ,
              t1                                                          ,
              t2                                                          ,
              RelationType ( )                                          ) ;
    ///////////////////////////////////////////////////////////////////////
    U = GI . GetOwners                                                    (
          SC                                                              ,
          SecondUuid ( )                                                  ,
          t1                                                              ,
          t2                                                              ,
          RelationType ( )                                                ,
          SC . OrderBy ( SortItem ( ) , (Qt::SortOrder) SortingType ( ) ) ,
          SC . sql . Limit ( startId , page )                           ) ;
    ///////////////////////////////////////////////////////////////////////
    SC . close  ( )                                                       ;
  }                                                                       ;
  SC   . remove ( )                                                       ;
  /////////////////////////////////////////////////////////////////////////
  LockAt      ( "Operate"       )                                         ;
  RealItems = U                                                           ;
  setVariable ( "Items" , total )                                         ;
  UnlockAt    ( "Operate"       )                                         ;
  /////////////////////////////////////////////////////////////////////////
  return true                                                             ;
}

bool N::PickBox::ReportDetails(void)
{
  return false ;
}

#endif
