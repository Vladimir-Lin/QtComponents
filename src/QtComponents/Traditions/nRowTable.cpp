#include <qtcomponents.h>

N::RowTable:: RowTable        ( QWidget * parent , Plan * p             )
            : TableWidget     (           parent ,        p             )
            , Group           ( 0 , Types::None , Groups::Subordination )
            , CommandSequence ( new QTimer ( this )                     )
            , Commanding      ( false                                   )
            , HeaderName      ( NULL                                    )
            , ItemRow         ( 0                                       )
            , ItemColumn      ( 0                                       )
            , ItemEditing     ( NULL                                    )
            , ItemWidget      ( NULL                                    )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::RowTable::~RowTable ( void)
{
}

QSize N::RowTable::sizeHint (void) const
{
  return QSize ( 640 , 480 ) ;
}

void N::RowTable::setTable(QString table)
{
  MasterTable = table ;
}

void N::RowTable::AtBusy(void)
{
  plan->StartBusy ( ) ;
}

void N::RowTable::OnRelax(void)
{
  plan->StopBusy ( ) ;
}

void N::RowTable::showMessage(QString message)
{
  emit setMessage ( message ) ;
}

void N::RowTable::assignMessage(QString message)
{
  plan -> showMessage ( message ) ;
}

void N::RowTable::AutoResize(void)
{
  SuitableColumns ( ) ;
  repaint         ( ) ;
}

void N::RowTable::SuitableColumns(void)
{
  SuitableColumns ( columnCount() ) ;
}

void N::RowTable::SuitableColumns(int columns)
{
  nFullLoop (i,columns)       {
    resizeColumnToContents(i) ;
  }                           ;
}

bool N::RowTable::hasItem(void)
{
  return ( Items.count()>0 ) ;
}

bool N::RowTable::startDrag(QMouseEvent * event)
{
  Items.clear()                                                 ;
  QTableWidgetItem * atItem = itemAt(event->pos())              ;
  nKickOut ( IsNull(atItem)                           , false ) ;
  nKickOut ( !IsMask(event->buttons(),Qt::LeftButton) , false ) ;
  dragPoint = event->pos    ( )                                 ;
  Items     = selectedItems ( )                                 ;
  nKickOut ( !PassDragDrop                            , true  ) ;
  return false                                                  ;
}

bool N::RowTable::fetchDrag(QMouseEvent * event)
{
  nKickOut ( !IsMask(event->buttons(),Qt::LeftButton) , false ) ;
  QPoint pos = event->pos()                                     ;
  pos -= dragPoint                                              ;
  return ( pos.manhattanLength() > qApp->startDragDistance() )  ;
}

void N::RowTable::dragDone(Qt::DropAction dropIt,QMimeData * mime)
{
  AbstractGui::dragDone(dropIt,mime)  ;
}

bool N::RowTable::finishDrag(QMouseEvent * event)
{
  Q_UNUSED ( event )   ;
   if (Items.count()>0) {
     Items.clear()      ;
     return false       ;
   }                    ;
   Items.clear()        ;
   return true          ;
}

bool N::RowTable::acceptDrop(QWidget * source,const QMimeData * mime)
{ Q_UNUSED ( source ) ;
  Q_UNUSED ( mime   ) ;
  return true         ;
}

bool N::RowTable::dropNew(QWidget * source,const QMimeData * mime,QPoint pos)
{ Q_UNUSED ( source ) ;
  Q_UNUSED ( mime   ) ;
  Q_UNUSED ( pos    ) ;
  return false        ;
}

bool N::RowTable::dropMoving(QWidget * source,const QMimeData * mime,QPoint pos)
{ Q_UNUSED ( source ) ;
  Q_UNUSED ( mime   ) ;
  Q_UNUSED ( pos    ) ;
  return false        ;
}

bool N::RowTable::dropAppend(QWidget * source,const QMimeData * mime,QPoint pos)
{
  return dropItems ( source , mime , pos ) ;
}

bool N::RowTable::removeDrop(void)
{
  return false ;
}

void N::RowTable::ThreadEvent(void)
{
  plan -> processEvents ( ) ;
}

void N::RowTable::StartCommand(void)
{
  nDropOut ( Commanding )                            ;
  CommandSequence -> start ( LimitValues [ 37714 ] ) ;
}

void N::RowTable::CommandHandler(void)
{
  nDropOut ( Commanding )         ;
  Commanding = true               ;
  while ( Sequences.count() > 0 ) {
    RunCommand ( Sequences[0] )   ;
    Sequences . takeAt ( 0 )      ;
  }                               ;
  CommandSequence -> stop ( )     ;
  Commanding = false              ;
}

void N::RowTable::assignWidget(int row,int column,QWidget * widget)
{
  setCellWidget ( row , column , widget ) ;
}

void N::RowTable::Configure (void)
{
  AlterTables [ Tables :: Names  ] = PlanTable(Names )               ;
  AlterTables [ Tables :: Groups ] = PlanTable(Groups)               ;
  ////////////////////////////////////////////////////////////////////
  LimitValues [     0 ] =   0                                        ;
  LimitValues [     1 ] =  30                                        ;
  LimitValues [     2 ] =   0                                        ;
  LimitValues [    11 ] = (int)Qt::AscendingOrder                    ;
  LimitValues [    49 ] =   1                                        ;
  LimitValues [    60 ] =  10                                        ;
  LimitValues [    61 ] =  10                                        ;
  LimitValues [    75 ] =   0                                        ;
  LimitValues [    76 ] = 100                                        ;
  LimitValues [    77 ] = 500                                        ;
  LimitValues [    81 ] =   1                                        ;
  LimitValues [ 37714 ] = 300                                        ;
  ////////////////////////////////////////////////////////////////////
  setFunction                   ( 2001 , false                     ) ; // name or names, true is names
  setFunction                   ( 2002 , true                      ) ; // append immediately
  ////////////////////////////////////////////////////////////////////
  setAcceptDrops                ( true                             ) ;
  setDragDropMode               ( DragDrop                         ) ;
  setHorizontalScrollBarPolicy  ( Qt::ScrollBarAsNeeded            ) ;
  setVerticalScrollBarPolicy    ( Qt::ScrollBarAsNeeded            ) ;
  plan -> setFont               ( this                             ) ;
  ////////////////////////////////////////////////////////////////////
  nConnect ( this      , SIGNAL ( AutoFit      ( ) )                 ,
             this      , SLOT   ( AutoResize   ( ) )               ) ;
  nConnect ( this      , SIGNAL ( Follow       (int) )               ,
             this      , SLOT   ( Execute      (int) )             ) ;
  nConnect ( Commando  , SIGNAL ( timeout      ( ) )                 ,
             this      , SLOT   ( DropCommands ( ) )               ) ;
  nConnect ( this      , SIGNAL ( OnBusy       ( ) )                 ,
             this      , SLOT   ( AtBusy       ( ) )               ) ;
  nConnect ( this      , SIGNAL ( GoRelax      ( ) )                 ,
             this      , SLOT   ( OnRelax      ( ) )               ) ;
  nConnect ( this      , SIGNAL ( putWidget    (int,int,QWidget*))   ,
             this      , SLOT   ( assignWidget (int,int,QWidget*)) ) ;
  nConnect ( this      , SIGNAL ( setMessage   (QString))            ,
             this      , SLOT   ( assignMessage(QString))          ) ;
  ////////////////////////////////////////////////////////////////////
  CommandSequence -> setParent ( this )                              ;
  nConnect ( this            , SIGNAL ( TriggerCommand ( ) )         ,
             this            , SLOT   ( StartCommand   ( ) )       ) ;
  nConnect ( CommandSequence , SIGNAL ( timeout        ( ) )         ,
             this            , SLOT   ( CommandHandler ( ) )       ) ;
}

void N::RowTable::Execute(int command)
{
  start ( command ) ;
}

bool N::RowTable::RunCommand(VarArgs & arguments)
{
  if (arguments.count()<1) return false ;
  VarArgs V = arguments                 ;
  UUIDs   U                             ;
  int     c = V [ 0 ] . toInt ( )       ;
  switch         ( c     )              {
    case 10001                          :
      startup    (       )              ;
    break                               ;
    case 10011                          :
    case 10012                          :
    case 11001                          :
    case 30002                          :
    case 30003                          :
      V . takeAt ( 0     )              ;
      start      ( c , V )              ;
    break                               ;
    case 12001                          :
      ArgsToUuids ( 1 , V , U )         ;
      plan -> processEvents ( )         ;
      setSelections ( U )               ;
    break                               ;
    default                             :
    return false                        ;
  }                                     ;
  return true                           ;
}

void N::RowTable::run(int Type,ThreadData * data)
{
  switch   ( Type ) {
    case 10001      :
      List (      ) ;
    break           ;
  }                 ;
}

bool N::RowTable::startup(void)
{
  clear (       ) ;
  start ( 10001 ) ;
  return true     ;
}

bool N::RowTable::isOwner(void)
{
  if ( isFirst  ( ) ) return true ;
  if ( isSecond ( ) ) return true ;
  return false                    ;
}

void N::RowTable::FolderLanguage(void)
{
  if ( ! isFirst ( ) ) return            ;
  int OL = vLanguageId                   ;
  AbstractGui :: assignLanguage ( this ) ;
  if ( OL == vLanguageId ) return        ;
  GroupItems GI ( plan )                 ;
  EnterSQL ( SC , plan->sql )            ;
    GI . assignLanguage                  (
      SC                                 ,
      first                              ,
      t1                                 ,
      vLanguageId                      ) ;
  ErrorSQL ( SC , plan->sql )            ;
  LeaveSQL ( SC , plan->sql )            ;
}

void N::RowTable::ResumeLanguage(void)
{
  if ( isFirst() && ( LimitValues [ 81 ] > 0 ) )      {
    GroupItems GI ( plan )                            ;
    EnterSQL ( SC , plan->sql )                       ;
      int L                                           ;
      L = GI . usingLanguage(SC,first,t1,vLanguageId) ;
      if (L>0) vLanguageId = L                        ;
      LimitValues [ 81 ] --                           ;
    ErrorSQL ( SC , plan->sql )                       ;
    LeaveSQL ( SC , plan->sql )                       ;
  }                                                   ;
}

bool N::RowTable::LoadUuids(SqlConnection & SC,UUIDs & Uuids)
{
  GroupItems GI ( plan )                                     ;
  int           startId =                 LimitValues [  0 ] ;
  int           page    =                 LimitValues [  1 ] ;
  int           total   =                 LimitValues [  2 ] ;
  Qt::SortOrder order   = (Qt::SortOrder) LimitValues [ 11 ] ;
  GI . GroupTable = AlterTables [ Tables::Groups ]           ;
  if (page<=0) page = total                                  ;
  if (isFirst())                                             {
    Uuids = GI . Subordination                               (
              SC                                             ,
              first                                          ,
              t1                                             ,
              t2                                             ,
              relation                                       ,
              SC . OrderBy   ( "position" , order          ) ,
              SC . sql.Limit ( startId    , page         ) ) ;
  } else
  if (isSecond())                                            {
    Uuids = GI . GetOwners                                   (
              SC                                             ,
              second                                         ,
              t1                                             ,
              t2                                             ,
              relation                                       ,
              SC . OrderBy   ( "id"       , order          ) ,
              SC . sql.Limit ( startId    , page         ) ) ;
  } else                                                     {
    Uuids = SC.Uuids                                         (
              MasterTable                                    ,
              "uuid"                                         ,
              QString ( "%1 %2"                              )
              . arg   ( SC.OrderBy   ( "id"    , order )     )
              . arg   ( SC.sql.Limit ( startId , page  ) ) ) ;
  }                                                          ;
  return ( Uuids . count ( ) > 0 )                           ;
}

bool N::RowTable::LoadCells(SqlConnection & SC,int row,SUID uuid)
{
  for (int i=0;i<columnCount();i++)  {
    LoadCell ( SC , row , i , uuid ) ;
  }                                  ;
  return true                        ;
}

bool N::RowTable::LoadCell(SqlConnection & SC,int row,int column,SUID uuid)
{
  switch ( column )                                   {
    case 0                                            :
      if (isFunction(2001))                           {
        return LoadNames ( SC , row , column , uuid ) ;
      }                                               ;
    return LoadName      ( SC , row , column , uuid ) ;
  }                                                   ;
  return true                                         ;
}

bool N::RowTable::LoadName(SqlConnection & SC,int row,int column,SUID uuid)
{
  NewTableWidgetItem ( it )               ;
  QString n                               ;
  n = SC.getName                          (
        AlterTables [ Tables::Names ]     ,
        "uuid"                            ,
        vLanguageId                       ,
        uuid                            ) ;
  it -> setText ( n                     ) ;
  setFont       ( it , Fonts::TableView ) ;
  emit putItem  ( row , column , it     ) ;
  return true                             ;
}

bool N::RowTable::LoadNames(SqlConnection & SC,int row,int column,SUID u)
{
  NewTableWidgetItem ( it )               ;
  if (u>0)                                {
    int L = -1                            ;
    if (LimitValues.contains(9))          {
      L = LimitValues [ 9 ]               ;
    }                                     ;
    UUIDs U                               ;
    Manager :: NameUuids                  (
      *plan                               ,
      SC                                  ,
      u                                   ,
      U                                 ) ;
    if (U.count()>0)                      {
      QString n = ""                      ;
      UUIDs   X                           ;
      NAMEs   N                           ;
      X << U [ 0 ]                        ;
      Manager :: UuidNames                (
        *plan                             ,
        SC                                ,
        X                                 ,
        N                               ) ;
      if (N.contains(U[0]))               {
        n = N [ U [ 0 ] ]                 ;
      }                                   ;
      if (n.length()>0)                   {
        if (L>0)                          {
          if (n.length()>L)               {
            n = n . left ( L )            ;
            n += " ..."                   ;
          }                               ;
        }                                 ;
        it -> setText  ( n )              ;
      }                                   ;
    }                                     ;
  }                                       ;
  setFont       ( it , Fonts::TableView ) ;
  emit putItem  ( row , column , it     ) ;
  return true                             ;
}

bool N::RowTable::LoadColumn(SqlConnection & SC,int column,UUIDs & Uuids)
{
  for (int i=0;i<Uuids.count();i++)         {
    LoadCell ( SC , i , column , Uuids[i] ) ;
  }                                         ;
  return true                               ;
}

bool N::RowTable::LoadItems(SqlConnection & SC,UUIDs & Uuids)
{
  for (int i=0;i<Uuids.count();i++) {
    LoadCells ( SC , i , Uuids[i] ) ;
  }                                 ;
  return true                       ;
}

void N::RowTable::List(void)
{
  emit OnBusy  ( )              ;
  EnterSQL ( SC , plan->sql )   ;
    UUIDs U                     ;
    if (LoadUuids(SC,U))        {
      setRowCount ( U.count() ) ;
      LoadItems   ( SC , U    ) ;
    }                           ;
  LeaveSQL ( SC , plan->sql )   ;
  emit GoRelax ( )              ;
  emit AutoFit ( )              ;
}

void N::RowTable::Paste(int row,int column,QString text)
{
}

void N::RowTable::Paste(int row,QString text)
{
}

void N::RowTable::Paste(void)
{
}

void N::RowTable::ExportHtml(void)
{
}

void N::RowTable::ExportTeX(void)
{
}

void N::RowTable::Export(void)
{
}

void N::RowTable::Copy(void)
{
}

void N::RowTable::Original(void)
{
}

void N::RowTable::ZoomIn(void)
{
}

void N::RowTable::ZoomOut(void)
{
}

void N::RowTable::setSelections(UUIDs & Uuids)
{
}

void N::RowTable::SortingMenu(MenuManager & Menu,QMenu * me)
{
  Menu . add ( me , 90301 , tr("Sorting") , true , isSortingEnabled() ) ;
  Menu . add ( me , 90302 , tr("Ascending sort" )                     ) ;
  Menu . add ( me , 90303 , tr("Descending sort")                     ) ;
}

bool N::RowTable::RunSorting(MenuManager & Menu,QAction * action)
{
  switch (Menu[action])                                           {
    case 90301                                                    :
      setSortingEnabled ( action->isChecked()                   ) ;
    break                                                         ;
    case 90302                                                    :
      sortByColumn      ( currentColumn() , Qt::AscendingOrder  ) ;
    break                                                         ;
    case 90303                                                    :
      sortByColumn      ( currentColumn() , Qt::DescendingOrder ) ;
    break                                                         ;
    default                                                       :
    return false                                                  ;
  }                                                               ;
  return true                                                     ;
}

void N::RowTable::AdjustMenu(MenuManager & mm,QMenu * me)
{
  mm . addSeparator ( me                                  ) ;
  mm . add          ( me , 90201 , tr("Set font"        ) ) ;
  mm . add          ( me , 90202 , tr("Select language" ) ) ;
  mm . add          ( me , 90203 , tr("Set minimum size") ) ;
  mm . add          ( me , 90204 , tr("Set maximum size") ) ;
  mm . add          ( me , 90205 , tr("Set style sheet" ) ) ;
}

bool N::RowTable::RunAdjustment(MenuManager & Menu,QAction * action)
{
  switch (Menu[action])                                                  {
    nFastCast ( 90201 , setFont           (                          ) ) ;
    nFastCast ( 90202 , assignLanguage    ( this                     ) ) ;
    nFastCast ( 90203 , assignMinimumSize ( this                     ) ) ;
    nFastCast ( 90204 , assignMaximumSize ( this                     ) ) ;
    nFastCast ( 90205 , assignStyleSheet  ( tr("Style sheet") , this ) ) ;
    default: return false                                                ;
  }                                                                      ;
  return true                                                            ;
}

void N::RowTable::SelectionsMenu(MenuManager & Menu,QMenu * me)
{
  Menu . add ( me , 90401 , tr("Copy selections to clipboard") ) ;
  Menu . add ( me , 90402 , tr("Select all" )                  ) ;
  Menu . add ( me , 90403 , tr("Select none")                  ) ;
}

bool N::RowTable::RunSelections(MenuManager & Menu,QAction * action)
{
  switch (Menu[action])                  {
    nFastCast ( 90401 , Copy       ( ) ) ;
    nFastCast ( 90402 , SelectAll  ( ) ) ;
    nFastCast ( 90403 , SelectNone ( ) ) ;
    default: return false                ;
  }                                      ;
  return true                            ;
}

bool N::RowTable::PageChanged(int StartId,int PageSize)
{
  if (isLoading()) return false         ;
  if ( ( StartId  != LimitValues[0] )  ||
       ( PageSize != LimitValues[1] ) ) {
    LimitValues [ 0 ] = StartId         ;
    LimitValues [ 1 ] = PageSize        ;
    startup ( )                         ;
    return true                         ;
  }                                     ;
  return false                          ;
}

QMenu * N::RowTable::PageMenu    (
          MenuManager & mm       ,
          QString       total    ,
          int         & StartId  ,
          int         & PageSize )
{
  if ( isLoading()         ) return NULL                       ;
  if ( LimitValues[2] <= 0 ) return NULL                       ;
  //////////////////////////////////////////////////////////////
  QMenu   * mp  = NULL                                         ;
  QAction * aa  = NULL                                         ;
  SpinBox * spb = NULL                                         ;
  SpinBox * spp = NULL                                         ;
  QString   tms = QString(total).arg(LimitValues[2])           ;
  //////////////////////////////////////////////////////////////
  StartId  = LimitValues[0]                                    ;
  PageSize = LimitValues[1]                                    ;
  spb      = new SpinBox  ( NULL , plan                      ) ;
  spp      = new SpinBox  ( NULL , plan                      ) ;
  spb     -> setRange     ( 0    , LimitValues[2]            ) ;
  spp     -> setRange     ( 0    , LimitValues[2]            ) ;
  spb     -> setValue     ( StartId                          ) ;
  spp     -> setValue     ( PageSize                         ) ;
  mp       = mm . addMenu ( tr("Page")                       ) ;
  aa       = mm . add     ( mp , 90551 , tms                 ) ;
  aa      -> setEnabled   ( false                            ) ;
  mm       . addSeparator ( mp                               ) ;
  mm       . add          ( mp , 90561 , tr("Home"         ) ) ;
  mm       . add          ( mp , 90562 , tr("Previous page") ) ;
  mm       . add          ( mp , 90563 , tr("Next page"    ) ) ;
  mm       . add          ( mp , 90564 , tr("End page"     ) ) ;
  mm       . addSeparator ( mp                               ) ;
  mm       . add          ( mp , 90571 , spb                 ) ;
  mm       . add          ( mp , 90572 , spp                 ) ;
  //////////////////////////////////////////////////////////////
  spb     -> External = &StartId                               ;
  spp     -> External = &PageSize                              ;
  return mp                                                    ;
}

bool N::RowTable::RunPageMenu (
       MenuManager & mm         ,
       QAction     * aa         ,
       int         & StartId    ,
       int         & PageSize   )
{
  switch ( mm [ aa ] )               {
    case 90561                       :
      StartId = 0                    ;
    break                            ;
    case 90562                       :
      StartId -= PageSize            ;
      if (StartId<0) StartId = 0     ;
    break                            ;
    case 90563                       :
      StartId += PageSize            ;
      if (StartId>=LimitValues[2])   {
        StartId = LimitValues[2] - 1 ;
      }                              ;
    break                            ;
    case 90564                       :
      StartId  = LimitValues [ 2 ]   ;
      StartId -= PageSize            ;
      if (StartId<0) StartId = 0     ;
    break                            ;
    default                          :
    return false                     ;
  }                                  ;
  return true                        ;
}
