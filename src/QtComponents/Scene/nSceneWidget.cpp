#include <qtcomponents.h>

typedef struct            {
  N::MenuManager * menu   ;
  QAction        * action ;
  N::SceneWidget * editor ;
  N::SceneWidget * extra  ;
} PrivateMenuBinder       ;

N::SceneWidget:: SceneWidget ( QObject * parent , Plan * p )
               : QObject     (           parent            )
               , QScriptable (                             )
               , SceneObject (                             )
               , Thread      (                0 , false    )
               , plan        (                           p )
               , Drag        ( NULL                        )
               , mimeDrag    ( NULL                        )
               , Dumping     (false                        )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::SceneWidget:: SceneWidget ( QObject * parent , Plan * p ,SceneDestructor * des )
               : QObject     (           parent                                   )
               , QScriptable (                                                    )
               , SceneObject (                                                des )
               , Thread      (                0 , false                           )
               , plan        (                           p                        )
               , Drag        ( NULL                                               )
               , mimeDrag    ( NULL                                               )
               , Dumping     (false                                               )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::SceneWidget::~SceneWidget (void)
{
  shutdown  ( ) ;
}

void N::SceneWidget::Configure (void)
{
  setVariable ( "DropIn"     , false               ) ;
  setVariable ( "Drag"       , false               ) ;
  setVariable ( "Hover"      , true                ) ;
  setVariable ( "Alive"      , false               ) ;
  setVariable ( "Stopped"    , true                ) ;
  setVariable ( "Finalize"   , false               ) ;
  setVariable ( "Suicide"    , false               ) ;
  ////////////////////////////////////////////////////
  setVariable ( "AllowDrag"  , false               ) ;
  setVariable ( "AcceptDrop" , true                ) ;
  ////////////////////////////////////////////////////
  setVariable ( "NameMaps"   , PlanTable(NameMaps) ) ;
  setVariable ( "NameTable"  , PlanTable(Names)    ) ;
  ////////////////////////////////////////////////////
  nConnect ( this , SIGNAL ( assignCursor (int) )    ,
             this , SLOT   ( localCursor  (int) )  ) ;
}

QScriptValue N::SceneWidget::SceneAttachment(QScriptContext * context,QScriptEngine * engine)
{
  N::SceneWidget * nsw = new N::SceneWidget ( engine , (Plan *) qPlan ) ;
  return engine -> newQObject               ( nsw                     ) ;
}

void N::SceneWidget::suicide(void)
{
  delete this ;
}

typedef struct        {
  N::SceneWidget * me ;
} ClassStructure      ;

void N::SceneWidget::ObjectPointer(QByteArray & pointer)
{
  pointer . resize ( sizeof(ClassStructure) )                 ;
  ClassStructure * cs = (ClassStructure *) pointer . data ( ) ;
  cs -> me = this                                             ;
}

int N::SceneWidget::MenuBindings(void * data,void * dispatcher,QVariants & v)
{
  PrivateMenuBinder * pmb = (PrivateMenuBinder *) dispatcher ;
  return pmb -> editor -> MenuBinder ( * ( pmb -> menu )     ,
                                           pmb -> action     ,
                                           v                 ,
                                           dispatcher      ) ;
}

int N::SceneWidget::MenuBinder (
      MenuManager & mm         ,
      QAction     * action     ,
      QVariants   & v          ,
      void        * dispatcher )
{
  bool completed = v [ 0 ] . toBool ( )    ;
  if ( ! completed )                       {
    CallToMenu ( mm , action , false )     ;
    return 1                               ;
  }                                        ;
  return CallToMenu ( mm , action , true ) ;
}

void N::SceneWidget::BindingMenu(SceneObject * s)
{
  PrivateMenuBinder * pmb = new PrivateMenuBinder ( )                     ;
  ::memset(pmb,0,sizeof(PrivateMenuBinder))                               ;
  pmb -> editor = this                                                    ;
  s   -> userobjs         [ "MenuBinder" ] = pmb                          ;
  s   -> DynamicFunctions [ "MenuBinder" ] = N::SceneWidget::MenuBindings ;
}

int N::SceneWidget::CallToMenu (
      MenuManager & mm            ,
      QAction     * aa            ,
      bool          executed      )
{
  if ( ! userobjs . contains ( "MenuBinder" ) ) return 0      ;
  void              * Handler = userobjs [ "MenuBinder" ]     ;
  PrivateMenuBinder * pmb     = (PrivateMenuBinder *) Handler ;
  QVariants V                                                 ;
  V << executed                                               ;
  pmb -> menu   = &mm                                         ;
  pmb -> action = aa                                          ;
  pmb -> extra  = this                                        ;
  return CallDynamic ( "MenuBinder" , this , Handler , V )    ;
}

void N::SceneWidget::ThreadEvent(void)
{
  qApp -> processEvents ( ) ;
}

bool N::SceneWidget::shutdown(void)
{
  if ( ! Value ( "Alive" ) . toBool ( ) )      {
    setVariable ( "Finalize" , true  )         ;
    return true                                ;
  }                                            ;
  setVariable   ( "Alive"    , false )         ;
  setVariable   ( "Finalize" , true  )         ;
  finalize      ( 100                )         ;
  while ( ! Value ( "Stopped" ) . toBool ( ) ) {
    plan -> processEvents (     )              ;
    Time :: skip          ( 200 )              ;
  }                                            ;
  return true                                  ;
}

void N::SceneWidget::localCursor(int cursorType)
{
  setCursor ( (Qt::CursorShape) cursorType ) ;
}

void N::SceneWidget::AssignFocus(void)
{
  if ( ! isFocus ( ) ) {
    Alert ( Click )    ;
  }                    ;
  setFocus ( true )    ;
}

int N::SceneWidget::GroupType(int index)
{
  QString K = QString("T%1").arg(index) ;
  return Value ( K ) . toInt ( )        ;
}

int N::SceneWidget::SortingType(void)
{
  return Value ( "Sorting" ) . toInt ( ) ;
}

int N::SceneWidget::RelationType(void)
{
  return Value ( "Relation" ) . toInt ( ) ;
}

QString N::SceneWidget::SortItem(void)
{
  return Value ( "ByItem" ) . toString ( ) ;
}

QString N::SceneWidget::MainTable(void)
{
  return Value ( "Table" ) . toString ( ) ;
}

SUID N::SceneWidget::FirstUuid(void)
{
  return Value ( "First" ) . toULongLong ( ) ;
}

SUID N::SceneWidget::SecondUuid(void)
{
  return Value ( "Second" ) . toULongLong ( ) ;
}

bool N::SceneWidget::LoadGroups (
       SqlConnection & SC       ,
       int             type     ,
       UUIDs         & uuids    ,
       int             orderby  ,
       QString         item     )
{
  QString options                                           ;
  options = SC . OrderBy ( item , (Qt::SortOrder) orderby ) ;
  uuids   = SC . Uuids                                      (
               PlanTable(Divisions)                         ,
               "uuid"                                       ,
               QString ( "where `type` = %1 %2"             )
               . arg ( type ) . arg ( options )           ) ;
  return ( uuids . count ( ) > 0 )                          ;
}

bool N::SceneWidget::Equal(QImage & image,QSize s)
{
  nKickOut ( image . width  ( ) != s . width  ( ) , false ) ;
  nKickOut ( image . height ( ) != s . height ( ) , false ) ;
  return true                                               ;
}

bool N::SceneWidget::Smaller(QImage & image,QSize s)
{
  nKickOut ( image . width  ( ) > s . width  ( ) , false ) ;
  nKickOut ( image . height ( ) > s . height ( ) , false ) ;
  return true                                              ;
}

QImage * N::SceneWidget::toIcon(QImage * image,QSize s)
{
  if ( Equal ( *image , s ) )                               {
    return new QImage ( *image )                            ;
  }                                                         ;
  ///////////////////////////////////////////////////////////
  QImage I                                                  ;
  if ( ! Smaller ( *image , s ) ) I = toIcon ( *image , s ) ;
                             else I = *image                ;
  ///////////////////////////////////////////////////////////
  QImage * W = new QImage ( s , QImage::Format_ARGB32)      ;
  ::memset ( W -> bits ( ) , 0 , W -> byteCount ( ) )       ;
  int x = s . width  ( ) - I . width  ( )                   ;
  int y = s . height ( ) - I . height ( )                   ;
  ///////////////////////////////////////////////////////////
  QPainter p                                                ;
  p . begin     ( W                 )                       ;
  p . drawImage ( x / 2 , y / 2 , I )                       ;
  p . end       (                   )                       ;
  ///////////////////////////////////////////////////////////
  return W                                                  ;
}

QImage N::SceneWidget::toIcon(QImage & image,QSize s)
{
  if ( Smaller ( image , s )) return image ;
  return image . scaled                    (
           s                               ,
           Qt::KeepAspectRatio             ,
           Qt::SmoothTransformation      ) ;
}

QString N::SceneWidget::FetchName(SqlConnection & SC,SUID u)
{
  return SC . getName         (
           PlanTable(Names)   ,
           "uuid"             ,
           plan -> LanguageId ,
           u                ) ;
}

QString N::SceneWidget::FetchAsynName(SqlConnection & SC,SUID u,int LanguageId)
{
  QString n                                         ;
  QString nt = Value ( "NameTable" ) . toString ( ) ;
  ///////////////////////////////////////////////////
  n = SC . getName                                  (
        nt                                          ,
        "uuid"                                      ,
        LanguageId                                  ,
        u                                         ) ;
  if ( n . length ( ) > 0 ) return n                ;
  ///////////////////////////////////////////////////
  QString Q                                         ;
  Q = SC . sql . SelectFrom                         (
        SC . sql . EncapTable ( "name" )            ,
        nt                                        ) +
        " where "                                   +
        SC . sql . EncapTable ( "uuid" )            +
        " = "                                       +
        QString::number ( u )                       +
        " order by `id` desc ;"                     ;
  SqlLoopNow ( SC , Q )                             ;
    n = SC . String ( 0 )                           ;
    if ( n . length ( ) > 0 ) return n              ;
  SqlLoopErr ( SC , Q )                             ;
  SqlLoopEnd ( SC , Q )                             ;
  return ""                                         ;
}

QString N::SceneWidget::FetchNames(SqlConnection & SC,SUID u)
{
  QString mt   = Value ( "NameMaps"  ) . toString ( )                        ;
  QString nt   = Value ( "NameTable" ) . toString ( )                        ;
  QString name = ""                                                          ;
  SUID    nuid = 0                                                           ;
  QString Q                                                                  ;
  Q = SC . sql . SelectFrom                                                  (
        "name"                                                               ,
        mt                                                                   ,
        QString("where `uuid` = %1 order by `prefer` asc limit 0,1").arg(u)) ;
  if ( SC . Fetch ( Q ) ) nuid = SC . Uuid ( 0 )                             ;
  if ( nuid > 0 )                                                            {
    Q = SC . sql . SelectFrom                                                (
          "name"                                                             ,
          nt                                                                 ,
          QString("where `uuid` = %1 limit 0,1").arg(nuid))                  ;
    if ( SC . Fetch ( Q ) ) name = SC . String ( 0 )                         ;
  }                                                                          ;
  return name                                                                ;
}

SUID N::SceneWidget::AppendGroup(QString name,int type)
{
  GroupItems    GI ( plan        )                                 ;
  SqlConnection SC ( plan -> sql )                                 ;
  SUID          u = 0                                              ;
  if ( SC.open(FunctionString))                                    {
    u = GI . NewDivision ( SC , name , (Types::ObjectTypes) type ) ;
    SC . close  ( )                                                ;
  }                                                                ;
  SC   . remove ( )                                                ;
  return u                                                         ;
}

void N::SceneWidget::ZoomIn(void)
{
  if ( ! Value ( "Resizable" ) . toBool ( ) ) return ;
  ControlPoint z = DOFs [ 2 ]                        ;
  z *= 1.1                                           ;
  LockAt   ( "Operate" )                             ;
  DOFs [ 2 ] . x = z . x                             ;
  DOFs [ 2 ] . y = z . y                             ;
  Finish   (           )                             ;
  Dual     (           )                             ;
  UnlockAt ( "Operate" )                             ;
}

void N::SceneWidget::ZoomOut(void)
{
  if ( ! Value ( "Resizable" ) . toBool ( ) ) return ;
  ControlPoint z = DOFs [ 2 ]                        ;
  z *= 0.9                                           ;
  LockAt   ( "Operate" )                             ;
  DOFs [ 2 ] . x = z . x                             ;
  DOFs [ 2 ] . y = z . y                             ;
  Finish   (           )                             ;
  Dual     (           )                             ;
  UnlockAt ( "Operate" )                             ;
}

void N::SceneWidget::SelectNothing(void)
{
}

void N::SceneWidget::SelectAll(void)
{
}

bool N::SceneWidget::doDrag(void)
{
  if ( NotNull ( mimeDrag ) )                      {
    return endDrag ( )                             ;
  }                                                ;
  //////////////////////////////////////////////////
  UUIDs  U = SceneObject::children . keys ( )      ;
  SUID   u                                         ;
  qint64 i = 0                                     ;
  while ( ForChild ( u , i , U ) )                 {
    SceneObject * sox = ChildOf<SceneObject> ( u ) ;
    if ( sox -> hasDrag ( ) )                      {
      return sox -> doDrag ( )                     ;
    }                                              ;
  }                                                ;
  return false                                     ;
}

bool N::SceneWidget::hasDrag(void)
{
  if ( NotNull ( mimeDrag ) ) return true          ;
  UUIDs  U = SceneObject::children . keys ( )      ;
  SUID   u                                         ;
  qint64 i = 0                                     ;
  while ( ForChild ( u , i , U ) )                 {
    SceneObject * sox = ChildOf<SceneObject> ( u ) ;
    if ( sox -> hasDrag ( ) ) return true          ;
  }                                                ;
  return false                                     ;
}

bool N::SceneWidget::endDrag(void)
{
  QGraphicsView * gv = (QGraphicsView *) gui                    ;
  gv -> setDragMode ( QGraphicsView::ScrollHandDrag )           ;
  ///////////////////////////////////////////////////////////////
  Qt::DropAction dropAction = Qt::MoveAction                    ;
  QCursor        DC     ( Qt::ClosedHandCursor )                ;
  ///////////////////////////////////////////////////////////////
  Dumping = true                                                ;
  Drag    = new QDrag   ( gui                  )                ;
  Drag   -> setMimeData ( mimeDrag             )                ;
  ///////////////////////////////////////////////////////////////
  if ( mimeDrag -> hasImage ( ) )                               {
    QImage image = qvariant_cast<QImage>(mimeDrag->imageData()) ;
    Drag -> setPixmap ( QPixmap::fromImage(image) )             ;
  } else                                                        {
    Drag -> setPixmap ( DC . pixmap ( )           )             ;
  }                                                             ;
  dropAction = Drag -> exec ( Qt::CopyAction | Qt::MoveAction ) ;
  dragDone ( dropAction , mimeDrag )                            ;
  gv -> setDragMode ( QGraphicsView::NoDrag )                   ;
  ///////////////////////////////////////////////////////////////
  Dumping  = false                                              ;
  Drag     = NULL                                               ;
  mimeDrag = NULL                                               ;
  ///////////////////////////////////////////////////////////////
  setVariable ( "Dragging"  , false )                           ;
  setVariable ( "StartDrag" , false )                           ;
  return true                                                   ;
}

int N::SceneWidget::CallTapping(QString tapping,QVariants & args)
{
  if ( ! userobjs . contains ( tapping ) ) return 0 ;
  return CallDynamic ( tapping                      ,
                        this                        ,
                        userobjs [ tapping ]        ,
                        args                      ) ;
}

int N::SceneWidget::CallRequests(QVariants & args)
{
  return CallTapping ( "RequestsFor" , args ) ;
}

int N::SceneWidget::CallBinding(QVariants & args)
{
  return CallTapping ( "BindFunctions" , args ) ;
}

void N::SceneWidget::SortingMenu(MenuManager & mm,QMenu * ms)
{
  Qt::SortOrder sov = (Qt::SortOrder) Value ( "Sorting" ) . toInt ( ) ;
  mm . add ( ms                                                       ,
             CiosMenuId(32,8,1)                                       ,
             tr("Ascending order")                                    ,
             true                                                     ,
             ( Qt::AscendingOrder  == sov )                         ) ;
  mm . add ( ms                                                       ,
             CiosMenuId(32,8,2)                                       ,
             tr("Descending order")                                   ,
             true                                                     ,
             ( Qt::DescendingOrder == sov )                         ) ;
}

bool N::SceneWidget::SortingProcessor(MenuManager & mm,QAction * aa)
{
  Qt::SortOrder sov = (Qt::SortOrder) Value ( "Sorting" ) . toInt ( ) ;
  switch ( mm [ aa ] )                                                {
    case CiosMenuId(32,8,1)                                           :
      setVariable ( "Sorting" , Qt::AscendingOrder  )                 ;
      if ( Qt::AscendingOrder  != sov ) start ( 98011 )               ;
    return true                                                       ;
    case CiosMenuId(32,8,2)                                           :
      setVariable ( "Sorting" , Qt::DescendingOrder )                 ;
      if ( Qt::DescendingOrder != sov ) start ( 98012 )               ;
    return true                                                       ;
  }                                                                   ;
  return false                                                        ;
}

void N::SceneWidget::SelectionMenu(MenuManager & mm,QMenu * ms)
{
  QString sel                                    ;
  ////////////////////////////////////////////////
  sel = Value ( "SelectionMode" ) . toString ( ) ;
  sel = sel                       . toLower  ( ) ;
  ////////////////////////////////////////////////
  mm . add ( ms                                  ,
             320401                              ,
             tr("Clear selections")            ) ;
  mm . add ( ms                                  ,
             320402                              ,
             tr("Select all")                  ) ;
  mm . addSeparator ( ms )                       ;
  mm . add ( ms                                  ,
             320501                              ,
             tr("None")                          ,
             true                                ,
             ( "none" == sel )                 ) ;
  mm . add ( ms                                  ,
             320502                              ,
             tr("Single")                        ,
             true                                ,
             ( "single" == sel )               ) ;
  mm . add ( ms                                  ,
             320503                              ,
             tr("Contiguous")                    ,
             true                                ,
             ( "contiguous" == sel )           ) ;
  mm . add ( ms                                  ,
             320504                              ,
             tr("Extended")                      ,
             true                                ,
             ( "extended" == sel )             ) ;
  mm . add ( ms                                  ,
             320505                              ,
             tr("Multiple")                      ,
             true                                ,
             ( "multiple" == sel )             ) ;
}

void N::SceneWidget::AdjustMenu(MenuManager & mm,QMenu * ma)
{
  QMenu * me                                         ;
  QMenu * ms                                         ;
  ////////////////////////////////////////////////////
  mm . add ( ma                                      ,
             320101                                  ,
             tr("Selectable")                        ,
             true                                    ,
             Value ( "Selectable"   ) . toBool ( ) ) ;
  ms = mm . addMenu ( ma , tr("Selections") )        ;
  mm . addSeparator ( ma )                           ;
  mm . add ( ma                                      ,
             320102                                  ,
             tr("Movable")                           ,
             true                                    ,
             Value ( "Movable"      ) . toBool ( ) ) ;
  mm . add ( ma                                      ,
             320103                                  ,
             tr("Resizable")                         ,
             true                                    ,
             Value ( "Resizable"    ) . toBool ( ) ) ;
  me = mm . addMenu ( ma , tr("Scalibility") )       ;
  mm . addSeparator ( ma )                           ;
  mm . add ( ma                                      ,
             320201                                  ,
             tr("Drop")                              ,
             true                                    ,
             Value ( "AcceptDrop"   ) . toBool ( ) ) ;
  mm . add ( ma                                      ,
             320202                                  ,
             tr("Drag")                              ,
             true                                    ,
             Value ( "AllowDrag"    ) . toBool ( ) ) ;
  ////////////////////////////////////////////////////
  mm . addSeparator ( ma )                           ;
  mm . add ( ma                                      ,
             320203                                  ,
             tr("Follow window size")                ,
             true                                    ,
             Value ( "FollowWindow" ) . toBool ( ) ) ;
  mm . add ( ma                                      ,
             320204                                  ,
             tr("Close after action selected")       ,
             true                                    ,
             Value ( "Suicide" ) . toBool ( )      ) ;
  ////////////////////////////////////////////////////
  mm . add ( me                                      ,
             320301                                  ,
             tr("Top line")                          ,
             true                                    ,
             Value ( "Top/Line"     ) . toBool ( ) ) ;
  mm . add ( me                                      ,
             320302                                  ,
             tr("Bottom line")                       ,
             true                                    ,
             Value ( "Bottom/Line"  ) . toBool ( ) ) ;
  mm . add ( me                                      ,
             320303                                  ,
             tr("Left line")                         ,
             true                                    ,
             Value ( "Left/Line"    ) . toBool ( ) ) ;
  mm . add ( me                                      ,
             320304                                  ,
             tr("Right line")                        ,
             true                                    ,
             Value ( "Right/Line"   ) . toBool ( ) ) ;
  mm . addSeparator ( me )                           ;
  mm . add ( me                                      ,
             320311                                  ,
             tr("Top left corner")                   ,
             true                                    ,
             Value ( "Top/Left"     ) . toBool ( ) ) ;
  mm . add ( me                                      ,
             320312                                  ,
             tr("Top right corner")                  ,
             true                                    ,
             Value ( "Top/Right"    ) . toBool ( ) ) ;
  mm . add ( me                                      ,
             320313                                  ,
             tr("Bottom left corner")                ,
             true                                    ,
             Value ( "Bottom/Left"  ) . toBool ( ) ) ;
  mm . add ( me                                      ,
             320314                                  ,
             tr("Bottom right corner")               ,
             true                                    ,
             Value ( "Bottom/Right" ) . toBool ( ) ) ;
  SelectionMenu ( mm , ms )                          ;
}

bool N::SceneWidget::SelectProcessor(MenuManager & mm,QAction * aa)
{
  switch ( mm [ aa ] )                               {
    case 320401                                      :
      SelectNothing ( )                              ;
    return true                                      ;
    case 320402                                      :
      SelectAll     ( )                              ;
    return true                                      ;
    case 320501                                      :
      setVariable ( "SelectionMode" , "None"       ) ;
    return true                                      ;
    case 320502                                      :
      setVariable ( "SelectionMode" , "Single"     ) ;
    return true                                      ;
    case 320503                                      :
      setVariable ( "SelectionMode" , "Contiguous" ) ;
    return true                                      ;
    case 320504                                      :
      setVariable ( "SelectionMode" , "Extended"   ) ;
    return true                                      ;
    case 320505                                      :
      setVariable ( "SelectionMode" , "Multiple"   ) ;
    return true                                      ;
  }                                                  ;
  return false ;
}

bool N::SceneWidget::AdjustProcessor(MenuManager & mm,QAction * aa)
{
  switch ( mm [ aa ] )                                      {
    case 320101                                             :
      setVariable  ( "Selectable"   , aa -> isChecked ( ) ) ;
    return true                                             ;
    case 320102                                             :
      setVariable  ( "Movable"      , aa -> isChecked ( ) ) ;
    return true                                             ;
    case 320103                                             :
      setVariable  ( "Resizable"    , aa -> isChecked ( ) ) ;
    return true                                             ;
    case 320201                                             :
      setVariable  ( "AcceptDrop"   , aa -> isChecked ( ) ) ;
    return true                                             ;
    case 320202                                             :
      setVariable  ( "AllowDrag"    , aa -> isChecked ( ) ) ;
    return true                                             ;
    case 320203                                             :
      setVariable  ( "FollowWindow" , aa -> isChecked ( ) ) ;
    return true                                             ;
    case 320204                                             :
      setVariable  ( "Suicide"      , aa -> isChecked ( ) ) ;
    return true                                             ;
    case 320301                                             :
      setVariable  ( "Top/Line"     , aa -> isChecked ( ) ) ;
    return true                                             ;
    case 320302                                             :
      setVariable  ( "Bottom/Line"  , aa -> isChecked ( ) ) ;
    return true                                             ;
    case 320303                                             :
      setVariable  ( "Left/Line"    , aa -> isChecked ( ) ) ;
    return true                                             ;
    case 320304                                             :
      setVariable  ( "Right/Line"   , aa -> isChecked ( ) ) ;
    return true                                             ;
    case 320311                                             :
      setVariable  ( "Top/Left"     , aa -> isChecked ( ) ) ;
    return true                                             ;
    case 320312                                             :
      setVariable  ( "Top/Right"    , aa -> isChecked ( ) ) ;
    return true                                             ;
    case 320313                                             :
      setVariable  ( "Bottom/Left"  , aa -> isChecked ( ) ) ;
    return true                                             ;
    case 320314                                             :
      setVariable  ( "Bottom/Right" , aa -> isChecked ( ) ) ;
    return true                                             ;
  }                                                         ;
  return SelectProcessor ( mm , aa )                        ;
}

QAction * N::SceneWidget::connectAction(int Id,QObject * parent,const char * method,bool enable)
{
  if ( IsNull ( plan ) ) return NULL                             ;
  return plan -> connectAction ( Id , parent , method , enable ) ;
}

void N::SceneWidget::CloseChild(SUID u)
{
  if ( ! SceneObject::children . contains ( u ) ) return ;
  LockAt   ( "Operate" )                                 ;
  SceneNode * sn = SceneObject::children [ u ]           ;
  SceneObject::children . remove ( u )                   ;
  if ( NotNull ( sn ) ) delete sn                        ;
  UnlockAt ( "Operate" )                                 ;
}

bool N::SceneWidget::canDrag(void)
{
  return Value ( "AllowDrag" ) . toBool ( ) ;
}

UUIDs N::SceneWidget::GetUuids(QByteArray & data)
{
  UUIDs Uuids                        ;
  SUID * suid  = (SUID *)data.data() ;
  int    total = (int)suid[0]        ;
  for (int i=0;i<total;i++)          {
    Uuids << suid[i+1]               ;
  }                                  ;
  return Uuids                       ;
}

SUID N::SceneWidget::GetUuid(QByteArray & data)
{
  SUID   * suid = (SUID *)data.data() ;
  return (*suid)                      ;
}

QByteArray N::SceneWidget::CreateByteArray(SUID uuid)
{
  return QByteArray((const char *)&uuid,sizeof(SUID));
}

QByteArray N::SceneWidget::CreateByteArray(UUIDs & Uuids)
{
  QByteArray  data                            ;
  data.resize(sizeof(SUID)*(Uuids.count()+1)) ;
  SUID * suid = (SUID *)data.data()           ;
  suid[0] = Uuids.count()                     ;
  for (int i=0;i<Uuids.count();i++)           {
    suid[i+1] = Uuids[i]                      ;
  }                                           ;
  return data                                 ;
}

void N::SceneWidget::setMime(QMimeData * mime,QString mtype,SUID uuid)
{
  QByteArray  data = CreateByteArray(uuid) ;
  mime -> setData ( mtype , data )         ;
}

void N::SceneWidget::setMime(QMimeData * mime,QString mtype,UUIDs & Uuids)
{
  QByteArray  data = CreateByteArray(Uuids) ;
  mime -> setData ( mtype , data )          ;
}

bool N::SceneWidget::dragStart (
       ControlPoint & From     ,
       ControlPoint & To       ,
       ControlPoint & At       ,
       QMouseEvent  * e        )
{
  return startDrag ( From , To , At , e ) ;
}

bool N::SceneWidget::dragMoving (
       ControlPoint & From      ,
       ControlPoint & To        ,
       ControlPoint & At        ,
       QMouseEvent  * e         )
{
  nKickOut ( NotNull     ( Drag                              ) , false ) ;
  nKickOut ( ! IsMask    ( e -> buttons ( ) , Qt::LeftButton ) , false ) ;
  nKickOut ( ! hasItem   ( From , To , At                    ) , false ) ;
  nKickOut ( ! fetchDrag ( From , To , At , e                ) , false ) ;
  ////////////////////////////////////////////////////////////////////////
  QMimeData * mime = dragMime ( From , To , At )                         ;
  ////////////////////////////////////////////////////////////////////////
  if ( IsNull ( mime ) ) return false                                    ;
  QGraphicsView * gv = (QGraphicsView *) gui                             ;
  gv -> setDragMode ( QGraphicsView::ScrollHandDrag )                    ;
  QCursor DC ( Qt::ClosedHandCursor )                                    ;
  Dumping = true                                                         ;
  Drag = new QDrag ( gui )                                               ;
  Qt::DropAction dropAction                                              ;
  Drag -> setMimeData ( mime )                                           ;
  if (mime->hasImage())                                                  {
    QImage image = qvariant_cast<QImage>(mime->imageData())              ;
    Drag -> setPixmap ( QPixmap::fromImage(image) )                      ;
  } else                                                                 {
    Drag -> setPixmap ( DC.pixmap()               )                      ;
  }                                                                      ;
  dropAction = Drag->exec ( Qt::CopyAction | Qt::MoveAction )            ;
  dragDone ( dropAction , mime )                                         ;
  gv -> setDragMode ( QGraphicsView::NoDrag )                            ;
  Dumping = false                                                        ;
  Drag    = NULL                                                         ;
  return true                                                            ;
}

bool N::SceneWidget::dragEnd(QMouseEvent * e)
{
  nKickOut ( ! finishDrag ( e ) , true ) ;
  return false                           ;
}

bool N::SceneWidget::hasItem (
       ControlPoint & From   ,
       ControlPoint & To     ,
       ControlPoint & At     )
{
  return false ;
}

bool N::SceneWidget::startDrag (
       ControlPoint & From     ,
       ControlPoint & To       ,
       ControlPoint & At       ,
       QMouseEvent  * e        )
{
  return false ;
}

bool N::SceneWidget::fetchDrag (
       ControlPoint & From     ,
       ControlPoint & To       ,
       ControlPoint & At       ,
       QMouseEvent  * e        )
{
  return false ;
}

QMimeData * N::SceneWidget::dragMime (
              ControlPoint & From    ,
              ControlPoint & To      ,
              ControlPoint & At      )
{
  return NULL ;
}

void N::SceneWidget::dragDone(Qt::DropAction dropIt,QMimeData * mime)
{
  setCursor ( Qt::ArrowCursor ) ;
  DoProcessEvents               ;
}

bool N::SceneWidget::finishDrag(QMouseEvent * e)
{
  return true ;
}

bool N::SceneWidget::allowDrops(DropTypes dropType)
{
  if (AllowDrops.contains((int)dropType)) {
    return AllowDrops[(int)dropType]      ;
  }                                       ;
  return false                            ;
}

void N::SceneWidget::setDropFlag(DropTypes dropType,bool enabled)
{
  AllowDrops[(int)dropType] = enabled ;
}

bool N::SceneWidget::acceptPrivate(const QMimeData * mime)
{
  return false ;
}

bool N::SceneWidget::dropPrivate(QWidget * source,const QMimeData * mime,ControlPoint pos)
{
  return false ;
}

#define VG(Function,Item)           \
bool N::SceneWidget::Function(void) \
{                                   \
  return allowDrops(Item)         ; \
}

VG( acceptTextDrop      , DropText          )
VG( acceptUrlsDrop      , DropUrls          )
VG( acceptImageDrop     , DropImage         )
VG( acceptHtmlDrop      , DropHtml          )
VG( acceptColorDrop     , DropColor         )
VG( acceptTagDrop       , DropTag           )
VG( acceptPictureDrop   , DropPicture       )
VG( acceptPeopleDrop    , DropPeople        )
VG( acceptVideoDrop     , DropVideo         )
VG( acceptAudioDrop     , DropAudio         )
VG( acceptAlbumDrop     , DropAlbum         )
VG( acceptGenderDrop    , DropGender        )
VG( acceptDivisionDrop  , DropDivision      )
VG( acceptUriDrop       , DropURIs          )
VG( acceptBookmarkDrop  , DropBookmark      )
VG( acceptFont          , DropFont          )
VG( acceptPen           , DropPen           )
VG( acceptBrush         , DropBrush         )
VG( acceptGradient      , DropGradient      )
VG( acceptShapes        , DropShape         )
VG( acceptMembers       , DropMember        )
VG( acceptSets          , DropSet           )
VG( acceptActions       , DropActions       )
VG( acceptDecision      , DropDecision      )
VG( acceptCondition     , DropCondition     )
VG( acceptExecution     , DropExecution     )
VG( acceptSqlTable      , DropSqlTable      )
VG( acceptDatabase      , DropDatabase      )
VG( acceptTask          , DropTask          )
VG( acceptNation        , DropNation        )
VG( acceptContour       , DropContour       )
VG( acceptManifold      , DropManifold      )
VG( acceptSources       , DropSource        )
VG( acceptDocuments     , DropDocument      )
VG( acceptEyes          , DropEyes          )
VG( acceptHairs         , DropHairs         )
VG( acceptKeywords      , DropKeyword       )
VG( acceptTerminologies , DropTerminology   )
VG( acceptKnowledge     , DropKnowledge     )
VG( acceptFields        , DropField         )
VG( acceptKnowledgeBase , DropKnowledgeBase )
VG( acceptSqlColumn     , DropSqlColumn     )
VG( acceptUuids         , DropUuid          )
VG( acceptCommodities   , DropCommodity     )
VG( acceptOrganizations , DropOrganization  )
VG( acceptBlobs         , DropBlob          )
VG( acceptVariables     , DropVariable      )
VG( acceptTorrents      , DropTorrent       )
VG( acceptCameras       , DropCamera        )
VG( acceptFaces         , DropFace          )
VG( acceptColorGroups   , DropColorGroup    )
VG( acceptSetsAlgebras  , DropSetsAlgebra   )
VG( acceptNames         , DropName          )
VG( acceptStars         , DropStar          )
VG( acceptPhonemes      , DropPhoneme       )
VG( acceptModels        , DropModel         )
VG( acceptReality       , DropReality       )
VG( acceptMusic         , DropMusic         )

#undef  VG

bool N::SceneWidget::dropNew    (
       QWidget         * widget ,
       const QMimeData * mime   ,
       ControlPoint    & From   ,
       ControlPoint    & To     ,
       ControlPoint    & At     )
{
  return dropHandler ( mime ) ;
}

bool N::SceneWidget::dropMoving (
       QWidget         * widget ,
       const QMimeData * mime   ,
       ControlPoint    & From   ,
       ControlPoint    & To     ,
       ControlPoint    & At     )
{
  return dropHandler ( mime ) ;
}

bool N::SceneWidget::dropAppend (
       QWidget         * widget ,
       const QMimeData * mime   ,
       ControlPoint    & From   ,
       ControlPoint    & To     ,
       ControlPoint    & At     )
{
  return dropItems ( widget , mime , At ) ;
}

bool N::SceneWidget::removeDrop(void)
{
  bool dropIn = Value ( "DropIn" ) . toBool ( ) ;
  setVariable ( "DropIn" , false )              ;
  return dropIn                                 ;
}

bool N::SceneWidget::dragEnter (
       ControlPoint    & From  ,
       ControlPoint    & To    ,
       QDragEnterEvent * e     )
{
  if ( ! canDrop (                ) ) return false ;
  ControlPoint At                                  ;
  Collide ( From , To , At )                       ;
  return dropNew ( (QWidget *) e -> source   ( )   ,
                               e -> mimeData ( )   ,
                   From                            ,
                   To                              ,
                   At                            ) ;
}

bool N::SceneWidget:: dragMove (
       ControlPoint   & From   ,
       ControlPoint   & To     ,
       QDragMoveEvent * e      )
{
  if ( ! canDrop (                ) ) return false  ;
  ControlPoint At                                   ;
  Collide ( From , To , At )                        ;
  return dropMoving ( (QWidget *) e -> source   ( ) ,
                                  e -> mimeData ( ) ,
                      From                          ,
                      To                            ,
                      At                          ) ;
}

bool N::SceneWidget::drop  (
       ControlPoint & From ,
       ControlPoint & To   ,
       QDropEvent   * e    )
{
  if ( ! canDrop (                ) ) return false  ;
  ControlPoint At                                   ;
  Collide ( From , To , At )                        ;
  return dropAppend ( (QWidget *) e -> source   ( ) ,
                                  e -> mimeData ( ) ,
                      From                          ,
                      To                            ,
                      At                          ) ;
}

bool N::SceneWidget::dropHandler(const QMimeData * mime)
{
  bool Accepted = false                                   ;
  #define CHECK(FORMAT,FUNCX)                             \
    if (mime->hasFormat(FORMAT) && FUNCX()) Accepted = true
  #define VERIF(HasSome,DropF)                            \
    if (mime->HasSome() && DropF()) Accepted = true
  CHECK( "uuid/uuid"           , acceptUuids         ) ;
  CHECK( "uuid/uuids"          , acceptUuids         ) ;
  CHECK( "division/uuid"       , acceptDivisionDrop  ) ;
  CHECK( "division/uuids"      , acceptDivisionDrop  ) ;
  CHECK( "gender/uuid"         , acceptGenderDrop    ) ;
  CHECK( "tag/uuid"            , acceptTagDrop       ) ;
  CHECK( "tag/uuids"           , acceptDivisionDrop  ) ;
  CHECK( "name/uuid"           , acceptNames         ) ;
  CHECK( "name/uuids"          , acceptNames         ) ;
  CHECK( "picture/uuid"        , acceptPictureDrop   ) ;
  CHECK( "picture/uuids"       , acceptPictureDrop   ) ;
  CHECK( "people/uuid"         , acceptPeopleDrop    ) ;
  CHECK( "people/uuids"        , acceptPeopleDrop    ) ;
  CHECK( "audio/uuid"          , acceptAudioDrop     ) ;
  CHECK( "audio/uuids"         , acceptAudioDrop     ) ;
  CHECK( "video/uuid"          , acceptVideoDrop     ) ;
  CHECK( "video/uuids"         , acceptVideoDrop     ) ;
  CHECK( "album/uuid"          , acceptAlbumDrop     ) ;
  CHECK( "album/uuids"         , acceptAlbumDrop     ) ;
  CHECK( "music/uuid"          , acceptMusic         ) ;
  CHECK( "music/uuids"         , acceptMusic         ) ;
  CHECK( "uri/uuid"            , acceptUriDrop       ) ;
  CHECK( "uri/uuids"           , acceptUriDrop       ) ;
  CHECK( "bookmark/uuid"       , acceptBookmarkDrop  ) ;
  CHECK( "bookmark/uuids"      , acceptBookmarkDrop  ) ;
  CHECK( "shape/uuid"          , acceptShapes        ) ;
  CHECK( "shape/uuids"         , acceptShapes        ) ;
  CHECK( "member/uuid"         , acceptMembers       ) ;
  CHECK( "member/uuids"        , acceptMembers       ) ;
  CHECK( "set/uuid"            , acceptSets          ) ;
  CHECK( "set/uuids"           , acceptSets          ) ;
  CHECK( "action/uuid"         , acceptActions       ) ;
  CHECK( "action/uuids"        , acceptActions       ) ;
  CHECK( "decision/uuid"       , acceptDecision      ) ;
  CHECK( "decision/uuids"      , acceptDecision      ) ;
  CHECK( "condition/uuid"      , acceptCondition     ) ;
  CHECK( "condition/uuids"     , acceptCondition     ) ;
  CHECK( "execution/uuid"      , acceptExecution     ) ;
  CHECK( "execution/uuids"     , acceptExecution     ) ;
  CHECK( "sql/uuid"            , acceptSqlTable      ) ;
  CHECK( "sql/uuids"           , acceptSqlTable      ) ;
  CHECK( "database/uuid"       , acceptDatabase      ) ;
  CHECK( "database/uuids"      , acceptDatabase      ) ;
  CHECK( "task/uuid"           , acceptTask          ) ;
  CHECK( "task/uuids"          , acceptTask          ) ;
  CHECK( "nation/uuid"         , acceptNation        ) ;
  CHECK( "nation/uuids"        , acceptNation        ) ;
  CHECK( "contour/uuid"        , acceptContour       ) ;
  CHECK( "contour/uuids"       , acceptContour       ) ;
  CHECK( "manifold/uuid"       , acceptManifold      ) ;
  CHECK( "manifold/uuids"      , acceptManifold      ) ;
  CHECK( "source/uuid"         , acceptSources       ) ;
  CHECK( "source/uuids"        , acceptSources       ) ;
  CHECK( "document/uuid"       , acceptDocuments     ) ;
  CHECK( "document/uuids"      , acceptDocuments     ) ;
  CHECK( "eyes/uuid"           , acceptEyes          ) ;
  CHECK( "eyes/uuids"          , acceptEyes          ) ;
  CHECK( "hairs/uuid"          , acceptHairs         ) ;
  CHECK( "hairs/uuids"         , acceptHairs         ) ;
  CHECK( "keyword/uuid"        , acceptKeywords      ) ;
  CHECK( "keyword/uuids"       , acceptKeywords      ) ;
  CHECK( "terminology/uuid"    , acceptTerminologies ) ;
  CHECK( "terminology/uuids"   , acceptTerminologies ) ;
  CHECK( "knowledge/uuid"      , acceptKnowledge     ) ;
  CHECK( "knowledge/uuids"     , acceptKnowledge     ) ;
  CHECK( "field/uuid"          , acceptFields        ) ;
  CHECK( "field/uuids"         , acceptFields        ) ;
  CHECK( "knowledgebase/uuid"  , acceptKnowledgeBase ) ;
  CHECK( "knowledgebase/uuids" , acceptKnowledgeBase ) ;
  CHECK( "sqlcolumn/uuid"      , acceptSqlColumn     ) ;
  CHECK( "sqlcolumn/uuids"     , acceptSqlColumn     ) ;
  CHECK( "commodity/uuid"      , acceptCommodities   ) ;
  CHECK( "commodity/uuids"     , acceptCommodities   ) ;
  CHECK( "organization/uuid"   , acceptOrganizations ) ;
  CHECK( "organization/uuids"  , acceptOrganizations ) ;
  CHECK( "blob/uuid"           , acceptBlobs         ) ;
  CHECK( "blob/uuids"          , acceptBlobs         ) ;
  CHECK( "variable/uuid"       , acceptVariables     ) ;
  CHECK( "variable/uuids"      , acceptVariables     ) ;
  CHECK( "torrent/uuid"        , acceptTorrents      ) ;
  CHECK( "torrent/uuids"       , acceptTorrents      ) ;
  CHECK( "camera/uuid"         , acceptCameras       ) ;
  CHECK( "camera/uuids"        , acceptCameras       ) ;
  CHECK( "face/uuid"           , acceptFaces         ) ;
  CHECK( "face/uuids"          , acceptFaces         ) ;
  CHECK( "star/uuid"           , acceptStars         ) ;
  CHECK( "star/uuids"          , acceptStars         ) ;
  CHECK( "phoneme/uuid"        , acceptPhonemes      ) ;
  CHECK( "phoneme/uuids"       , acceptPhonemes      ) ;
  CHECK( "model/uuid"          , acceptModels        ) ;
  CHECK( "model/uuids"         , acceptModels        ) ;
  CHECK( "reality/uuid"        , acceptReality       ) ;
  CHECK( "reality/uuids"       , acceptReality       ) ;
  CHECK( "colorgroup/uuid"     , acceptColorGroups   ) ;
  CHECK( "colorgroup/uuids"    , acceptColorGroups   ) ;
  CHECK( "setsalgebra/uuid"    , acceptSetsAlgebras  ) ;
  CHECK( "setsalgebra/uuids"   , acceptSetsAlgebras  ) ;
  CHECK( "font/uuid"           , acceptFont          ) ;
  CHECK( "pen/uuids"           , acceptPen           ) ;
  CHECK( "brush/uuid"          , acceptBrush         ) ;
  CHECK( "gradient/uuids"      , acceptGradient      ) ;
  VERIF( hasImage              , acceptImageDrop     ) ;
  VERIF( hasText               , acceptTextDrop      ) ;
  VERIF( hasHtml               , acceptHtmlDrop      ) ;
  VERIF( hasUrls               , acceptUrlsDrop      ) ;
  VERIF( hasColor              , acceptColorDrop     ) ;
  if ( acceptPrivate ( mime ) ) Accepted = true        ;
  #undef  VERIF
  #undef  CHECK
  return Accepted                                      ;
}

bool N::SceneWidget::dropItems(QWidget * source,const QMimeData * mime,ControlPoint pos)
{
  #define HASD(DUID,FUNCTION) (mime->hasFormat(DUID) && FUNCTION())
  #define DITE(DUID,FUNCTION)                                       \
    QByteArray data   = mime->data ( DUID  ) ;                      \
    SUID       uuid   = GetUuid    ( data  ) ;                      \
    UUIDs      Uuids                         ;                      \
    Uuids << uuid                            ;                      \
    return FUNCTION ( source , pos , Uuids )
  #define SITX(DUID,FUNCTION)                                       \
    QByteArray data   = mime->data ( DUID  ) ;                      \
    UUIDs      Uuids  = GetUuids   ( data  ) ;                      \
    return FUNCTION ( source , pos , Uuids )
  #define SITZ(DUID,FUNCTION)                                       \
    QByteArray data   = mime->data ( DUID  ) ;                      \
    SUID       uuid   = GetUuid    ( data  ) ;                      \
    return FUNCTION ( source , pos , uuid  )
  #define IFCAST(name,Drop,Toss)                                    \
    if (HASD( #name "/uuid" , Drop ))                             { \
        SITZ( #name "/uuid" , Toss )                              ; \
    }
  #define IFBOTH(name,Drop,Toss)                                    \
    if (HASD( #name "/uuid"  , Drop ))                            { \
        DITE( #name "/uuid"  , Toss )                             ; \
    }                                                               \
    if (HASD( #name "/uuids" , Drop ))                            { \
        SITX( #name "/uuids" , Toss )                             ; \
    }
  ///////////////////////////////////////////////////////////////////
  IFBOTH( uuid          , acceptUuids         , dropUuids         ) ;
  IFBOTH( division      , acceptDivisionDrop  , dropDivisions     ) ;
  IFCAST( gender        , acceptGenderDrop    , dropGender        ) ;
  IFBOTH( tag           , acceptTagDrop       , dropTags          ) ;
  IFBOTH( name          , acceptNames         , dropNames         ) ;
  IFBOTH( picture       , acceptPictureDrop   , dropPictures      ) ;
  IFBOTH( people        , acceptPeopleDrop    , dropPeople        ) ;
  IFBOTH( audio         , acceptAudioDrop     , dropAudios        ) ;
  IFBOTH( video         , acceptVideoDrop     , dropVideos        ) ;
  IFBOTH( album         , acceptAlbumDrop     , dropAlbums        ) ;
  IFBOTH( music         , acceptMusic         , dropMusic         ) ;
  IFBOTH( uri           , acceptUriDrop       , dropURIs          ) ;
  IFBOTH( bookmark      , acceptBookmarkDrop  , dropBookmarks     ) ;
  IFBOTH( shape         , acceptShapes        , dropShapes        ) ;
  IFBOTH( member        , acceptMembers       , dropMembers       ) ;
  IFBOTH( set           , acceptSets          , dropSets          ) ;
  IFBOTH( action        , acceptActions       , dropActions       ) ;
  IFBOTH( decision      , acceptDecision      , dropDecision      ) ;
  IFBOTH( condition     , acceptCondition     , dropCondition     ) ;
  IFBOTH( execution     , acceptExecution     , dropExecution     ) ;
  IFBOTH( sql           , acceptSqlTable      , dropSqlTable      ) ;
  IFBOTH( database      , acceptDatabase      , dropDatabase      ) ;
  IFBOTH( task          , acceptTask          , dropTask          ) ;
  IFBOTH( nation        , acceptNation        , dropNation        ) ;
  IFBOTH( contour       , acceptContour       , dropContour       ) ;
  IFBOTH( manifold      , acceptManifold      , dropManifold      ) ;
  IFBOTH( source        , acceptSources       , dropSources       ) ;
  IFBOTH( document      , acceptDocuments     , dropDocuments     ) ;
  IFBOTH( eyes          , acceptEyes          , dropEyes          ) ;
  IFBOTH( hairs         , acceptHairs         , dropHairs         ) ;
  IFBOTH( keyword       , acceptKeywords      , dropKeywords      ) ;
  IFBOTH( terminology   , acceptTerminologies , dropTerminologies ) ;
  IFBOTH( knowledge     , acceptKnowledge     , dropKnowledge     ) ;
  IFBOTH( field         , acceptFields        , dropFields        ) ;
  IFBOTH( knowledgebase , acceptKnowledgeBase , dropKnowledgeBase ) ;
  IFBOTH( sqlcolumn     , acceptSqlColumn     , dropSqlColumn     ) ;
  IFBOTH( commodity     , acceptCommodities   , dropCommodities   ) ;
  IFBOTH( organization  , acceptOrganizations , dropOrganizations ) ;
  IFBOTH( blob          , acceptBlobs         , dropBlobs         ) ;
  IFBOTH( variable      , acceptVariables     , dropVariables     ) ;
  IFBOTH( torrent       , acceptTorrents      , dropTorrents      ) ;
  IFBOTH( camera        , acceptCameras       , dropCameras       ) ;
  IFBOTH( face          , acceptFaces         , dropFaces         ) ;
  IFBOTH( star          , acceptStars         , dropStars         ) ;
  IFBOTH( phoneme       , acceptPhonemes      , dropPhonemes      ) ;
  IFBOTH( model         , acceptModels        , dropModels        ) ;
  IFBOTH( reality       , acceptReality       , dropReality       ) ;
  IFBOTH( colorgroup    , acceptColorGroups   , dropColorGroups   ) ;
  IFBOTH( setsalgebra   , acceptSetsAlgebras  , dropSetsAlgebras  ) ;
  IFCAST( font          , acceptFont          , dropFont          ) ;
  IFCAST( pen           , acceptPen           , dropPen           ) ;
  IFCAST( brush         , acceptBrush         , dropBrush         ) ;
  IFCAST( gradient      , acceptGradient      , dropGradient      ) ;
  ///////////////////////////////////////////////////////////////////
  if (mime->hasImage() && acceptImageDrop())                        {
    QImage image = qvariant_cast<QImage>(mime->imageData())         ;
    return dropImage ( source , pos , image )                       ;
  }                                                                 ;
  if (mime->hasText() && acceptTextDrop())                          {
    return dropText  ( source , pos , mime -> text () )             ;
  }                                                                 ;
  if (mime->hasHtml() && acceptHtmlDrop())                          {
    return dropHtml  ( source , pos , mime -> html () )             ;
  }                                                                 ;
  if (mime->hasUrls() && acceptUrlsDrop())                          {
    return dropUrls  ( source , pos , mime -> urls () )             ;
  }                                                                 ;
  if (mime->hasColor() && acceptColorDrop())                        {
    QColor color = qvariant_cast<QColor>(mime->colorData())         ;
    return dropColor ( source , pos , color )                       ;
  }                                                                 ;
  ///////////////////////////////////////////////////////////////////
  if (acceptPrivate(mime))                                          {
    return dropPrivate ( source , mime , pos )                      ;
  }                                                                 ;
  ///////////////////////////////////////////////////////////////////
  return false                                                      ;
  #undef  IFBOTH
  #undef  IFCAST
  #undef  SITX
  #undef  DITE
  #undef  HASD
}

#define GF(Function,IT)                                      \
bool N::SceneWidget::Function(QWidget * source,ControlPoint pos,IT) \
{                                                            \
  return false ;                                             \
}

GF( dropText  , const QString     & text  )
GF( dropUrls  , const QList<QUrl> & urls  )
GF( dropImage , const QImage      & image )
GF( dropHtml  , const QString     & html  )
GF( dropColor , const QColor      & color )

#undef  GF

#define DG(FUNCTION)                                                            \
bool N::SceneWidget::FUNCTION(QWidget * source,ControlPoint pos,const UUIDs & Uuids) \
{                                                                               \
  Q_UNUSED ( source )                                                         ; \
  Q_UNUSED ( pos    )                                                         ; \
  Q_UNUSED ( Uuids  )                                                         ; \
  return false ;                                                                \
}
#define DX(FUNCTION)                                                             \
bool N::SceneWidget::FUNCTION(QWidget * source,ControlPoint pos,const SUID uuid) \
{                                                                                \
  Q_UNUSED ( source )                                                          ; \
  Q_UNUSED ( pos    )                                                          ; \
  Q_UNUSED ( uuid   )                                                          ; \
  return false ;                                                                 \
}

///////////////////////
DG( dropUuids         )
DG( dropTags          )
DG( dropPictures      )
DG( dropPeople        )
DG( dropAudios        )
DG( dropVideos        )
DG( dropAlbums        )
DG( dropDivisions     )
DG( dropURIs          )
DG( dropBookmarks     )
DG( dropShapes        )
DG( dropMembers       )
DG( dropSets          )
DG( dropActions       )
DG( dropDecision      )
DG( dropCondition     )
DG( dropExecution     )
DG( dropSqlTable      )
DG( dropDatabase      )
DG( dropTask          )
DG( dropNation        )
DG( dropContour       )
DG( dropManifold      )
DG( dropSources       )
DG( dropDocuments     )
DG( dropEyes          )
DG( dropHairs         )
DG( dropKeywords      )
DG( dropTerminologies )
DG( dropKnowledge     )
DG( dropFields        )
DG( dropKnowledgeBase )
DG( dropSqlColumn     )
DG( dropCommodities   )
DG( dropOrganizations )
DG( dropBlobs         )
DG( dropVariables     )
DG( dropTorrents      )
DG( dropCameras       )
DG( dropFaces         )
DG( dropColorGroups   )
DG( dropSetsAlgebras  )
DG( dropNames         )
DG( dropStars         )
DG( dropPhonemes      )
DG( dropModels        )
DG( dropReality       )
DG( dropMusic         )
///////////////////////
DX( dropGender        )
DX( dropFont          )
DX( dropPen           )
DX( dropBrush         )
DX( dropGradient      )
///////////////////////

#undef  DX
#undef  DG
