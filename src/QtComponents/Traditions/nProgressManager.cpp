#include <qtcomponents.h>

N::ProgressManager:: ProgressManager ( QWidget * parent , Plan * p )
                   : TreeDock        (           parent ,        p )
                   , Timer           ( NULL                        )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::ProgressManager::~ProgressManager(void)
{
  Shutdown ( ) ;
}

void N::ProgressManager::Configure(void)
{
  PassDragDrop = false                                    ;
  Id           = 0                                        ;
  Fitting      = true                                     ;
  setSuggestion                ( QSize ( 480 , 200    ) ) ;
  NewTreeWidgetItem            ( head                   ) ;
  head -> setText              ( 0 , tr("")             ) ;
  head -> setText              ( 1 , tr("Name"        ) ) ;
  head -> setText              ( 2 , tr("Start time"  ) ) ;
  head -> setText              ( 3 , tr("ETA"         ) ) ;
  head -> setText              ( 4 , tr("Rate"        ) ) ;
  head -> setText              ( 5 , tr("Status"      ) ) ;
  head -> setText              ( 6 , tr("Progress"    ) ) ;
  setWindowTitle               ( tr("Progress Manager") ) ;
  setAccessibleName            ( "N::ProgressManager"   ) ;
  setDragDropMode              ( NoDragDrop             ) ;
  setRootIsDecorated           ( false                  ) ;
  setAlternatingRowColors      ( true                   ) ;
  setSelectionMode             ( SingleSelection        ) ;
  setColumnCount               ( 7                      ) ;
  setHorizontalScrollBarPolicy ( Qt::ScrollBarAsNeeded  ) ;
  setVerticalScrollBarPolicy   ( Qt::ScrollBarAsNeeded  ) ;
  assignHeaderItems            ( head                   ) ;
  plan  -> setFont             ( this                   ) ;
  /////////////////////////////////////////////////////////
  Minimum [-1] = 0                                        ;
  /////////////////////////////////////////////////////////
  LocalIcons [ "Yes"  ] = QIcon(":/images/yes.png")       ;
  LocalIcons [ "Stop" ] = QIcon(":/images/StopPlay.png")  ;
  /////////////////////////////////////////////////////////
  addConnector  ( "Accept"                                ,
                  this   , SIGNAL ( Requesting   ( )    ) ,
                  this   , SLOT   ( Accepting    ( )  ) ) ;
  addConnector  ( "Request"                               ,
                  this   , SIGNAL ( LocalRequest ( )    ) ,
                  this   , SLOT   ( LocalAccept  ( )  ) ) ;
  addConnector  ( "Widths"                                ,
                  this   , SIGNAL ( AdjustWidth  ( )    ) ,
                  this   , SLOT   ( setWidths    ( )  ) ) ;
  addConnector  ( "Switch"                                ,
                  this   , SIGNAL ( EmitTimer    ( )    ) ,
                  this   , SLOT   ( EnsureTimer  ( )  ) ) ;
  /////////////////////////////////////////////////////////
  onlyConnector ( "Accept"                              ) ;
  onlyConnector ( "Request"                             ) ;
  onlyConnector ( "Widths"                              ) ;
  onlyConnector ( "Switch"                              ) ;
  /////////////////////////////////////////////////////////
  LimitValues [ 212001160 ] = 1                           ;
  LimitValues [ 212001161 ] = 0                           ;
  LimitValues [ 212001162 ] = 0                           ;
  LimitValues [ 212001163 ] = 0                           ;
  LimitValues [ 212001164 ] = 0                           ;
  LimitValues [ 212001271 ] = 125                         ;
  /////////////////////////////////////////////////////////
  LocalMsgs   [ 441212001 ] = tr ( "%1.%2 t/s" )          ;
  LocalMsgs   [ 441212002 ] = tr ( "%1.%2 s/t" )          ;
  /////////////////////////////////////////////////////////
  setFunction ( 212001301 , false )                       ;
  setFunction ( 212001302 , false )                       ;
}

void N::ProgressManager::run(int T,ThreadData * data)
{
  switch ( T )                           {
    case 10091                           :
      startLoading (                   ) ;
      GetSettings  ( data -> Arguments ) ;
      stopLoading  (                   ) ;
    break                                ;
  }                                      ;
}

void N::ProgressManager::GetSettings(VarArgs & args)
{
  if ( args . count ( ) <= 0 ) return                             ;
  QString scope = args [ 0 ] . toString ( )                       ;
  plan -> settings . beginGroup ( scope )                         ;
  if ( plan -> settings . contains ( "Fitting" ) )                {
    Fitting = plan -> settings . value ( "Fitting" ) . toBool ( ) ;
  }                                                               ;
  if ( plan -> settings . contains ( "Clean" ) )                  {
    bool ac = plan -> settings . value ( "Clean"   ) . toBool ( ) ;
    LimitValues [ 212001160 ] = ac ? 1 : 0                        ;
  }                                                               ;
  if ( plan -> settings . contains ( "Width" ) )                  {
    if ( plan -> settings . contains ( "Height" ) )               {
      int w = plan -> settings . value ( "Width"  ) . toInt ( )   ;
      int h = plan -> settings . value ( "Height" ) . toInt ( )   ;
      setSuggestion ( QSize ( w , h ) )                           ;
    }                                                             ;
  }                                                               ;
  WIDTHs . clear ( )                                              ;
  for (int i = 0 ; i < columnCount ( ) ; i++ )                    {
    QString W = QString::number ( i )                             ;
    if ( plan -> settings . contains ( W ) )                      {
      int w = plan -> settings . value ( W ) . toInt ( )          ;
      WIDTHs << w                                                 ;
    }                                                             ;
  }                                                               ;
  plan -> settings . endGroup   ( )                               ;
  if ( ! Fitting ) LimitValues [ 212001164 ] = 1                  ;
}

void N::ProgressManager::setWidths(void)
{
  int t = WIDTHs . count ( )                               ;
  for (int i=0;i<t;i++) if ( i < ( columnCount ( ) - 1 ) ) {
    setColumnWidth ( i , WIDTHs [ i ] )                    ;
  }                                                        ;
}

void N::ProgressManager::Recovery(QString scope)
{
  VarArgs args           ;
  args << scope          ;
  start ( 10091 , args ) ;
}

void N::ProgressManager::Store(QString scope)
{
  bool ac = ( LimitValues [ 212001160 ] > 0 )              ;
  plan -> settings . beginGroup ( scope                  ) ;
  plan -> settings . setValue   ( "Fitting" , Fitting    ) ;
  plan -> settings . setValue   ( "Clean"   , ac         ) ;
  plan -> settings . setValue   ( "Width"   , width  ( ) ) ;
  plan -> settings . setValue   ( "Height"  , height ( ) ) ;
  for (int i = 0 ; i < columnCount ( ) ; i++ )             {
    int     w = columnWidth     ( i )                      ;
    QString W = QString::number ( i )                      ;
    plan -> settings . setValue ( W , w                  ) ;
  }                                                        ;
  plan -> settings . endGroup   (                        ) ;
}

void N::ProgressManager::EnsureTimer(void)
{
  if ( IsNull ( Timer ) )                              {
    Timer = new QTimer ( this )                        ;
    addConnector  ( "Timer"                            ,
                    Timer   , SIGNAL ( timeout ( )   ) ,
                    this    , SLOT   ( Update  ( ) ) ) ;
    onlyConnector ( "Timer" )                          ;
  }                                                    ;
  if ( Timer -> isActive ( ) ) return                  ;
  Timer -> start ( LimitValues [ 212001271 ] )         ;
}

void N::ProgressManager::StartFlush(void)
{
  emit EmitTimer ( ) ;
}

bool N::ProgressManager::Shutdown(void)
{
  if ( NotNull ( Commando ) ) Commando -> stop ( ) ;
  if ( NotNull ( Timer    ) )                      {
    QTimer * E = Timer                             ;
    Timer = NULL                                   ;
    E    -> stop        ( )                        ;
    E    -> deleteLater ( )                        ;
  }                                                ;
  return true                                      ;
}

void N::ProgressManager::Report(int k)
{
  if ( k < 0 ) return                                                        ;
  ////////////////////////////////////////////////////////////////////////////
  QDateTime S       = Begins  [ k ]                                          ;
  int       SAT     = StartAt [ k ]                                          ;
  int       Min     = Minimum [ k ]                                          ;
  int       Max     = Maximum [ k ]                                          ;
  bool      checked = true                                                   ;
  QDateTime E                                                                ;
  int       v                                                                ;
  ////////////////////////////////////////////////////////////////////////////
  if ( Values . contains ( k ) && ( NULL != Values [ k ] ) )                 {
    v = * ( Values [ k ] )                                                   ;
  } else                                                                     {
    v = Final [ k ]                                                          ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( Progress . contains ( k ) )                                           {
    Progress   [ k ] -> setFormat ( Formats [ k ] )                          ;
    if ( Max >= Min )                                                        {
      Progress [ k ] -> setRange  ( Min , Max     )                          ;
    }                                                                        ;
    if ( ( v >= Min ) && ( v <= Max ) )                                      {
      Progress [ k ] -> setValue  ( v             )                          ;
    }                                                                        ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  v   -= SAT                                                                 ;
  Max -= SAT                                                                 ;
  if ( ( Max >= Min ) && ( Max > 0 ) && ( Max >= v ) )                       {
    //////////////////////////////////////////////////////////////////////////
    E = Time::ETA ( S , v , Max )                                            ;
    if ( Items . contains ( k ) )                                            {
      Items [ k ] -> setText ( 3 , E . toString ( "yyyy/MM/dd hh:mm:ss" ) )  ;
    }                                                                        ;
    //////////////////////////////////////////////////////////////////////////
    qint64 ds = S . msecsTo ( nTimeNow )                                     ;
    if ( ( v <= 0 ) || ( Max <= 0 ) || ( ds <= 0 ) )                         {
      Items [ k ] -> setText ( 3 , QString ( QChar ( 0x221E ) ) )            ;
      Items [ k ] -> setText ( 4 , QString ( QChar ( 0x05D0 ) ) )            ;
    } else                                                                   {
      ////////////////////////////////////////////////////////////////////////
      qint64 vc = v                                                          ;
      vc *= 1000                                                             ;
      ////////////////////////////////////////////////////////////////////////
      if ( vc > ds )                                                         {
        QString TMS                                                          ;
        double  rx = vc                                                      ;
        TUID    rv                                                           ;
        rx /= ds                                                             ;
        rv  = ((TUID)(rx*1000))%1000                                         ;
        TMS = QString(FREQs[k]).arg((int)rx).arg(rv,3,10,QChar('0'))         ;
        Items [ k ] -> setText ( 4 , TMS )                                   ;
      } else                                                                 {
        QString TMS                                                          ;
        double  rx = ds                                                      ;
        TUID    rv                                                           ;
        rx /= vc                                                             ;
        rv  = ((TUID)(rx*1000))%1000                                         ;
        TMS = QString(FREQr[k]).arg((int)rx).arg(rv,3,10,QChar('0'))         ;
        Items [ k ] -> setText ( 4 , TMS )                                   ;
      }                                                                      ;
    }                                                                        ;
  } else                                                                     {
    if ( Items . contains ( k ) )                                            {
      Items [ k ] -> setText ( 3 , QString ( QChar(0x221E) ) )               ;
      Items [ k ] -> setText ( 4 , QString ( QChar(0x05D0) ) )               ;
    }                                                                        ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( Buttons . contains ( k ) )                                            {
    checked = Buttons [ k ] -> isChecked ( )                                 ;
  }                                                                          ;
  if ( ! checked )                                                           {
    if ( Booleans . contains ( k ) ) (*Booleans[ k ]) = false                ;
    if ( Buttons  . contains ( k ) )   Buttons [ k ] -> setEnabled ( false ) ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( Items . contains ( k ) )                                              {
    QString Z                                                                ;
    Z            = S . toString ( "yyyy/MM/dd hh:mm:ss" )                    ;
    Items [ k ] -> setText      ( 1 , Connects [ k ]    )                    ;
    Items [ k ] -> setText      ( 2 , Z                 )                    ;
    Items [ k ] -> setText      ( 5 , Message  [ k ]    )                    ;
  }                                                                          ;
}

void N::ProgressManager::Update(void)
{
  if ( LimitValues [ 212001161 ] > 0 ) return ;
  if ( LimitValues [ 212001162 ] > 0 ) return ;
  /////////////////////////////////////////////
  if ( LimitValues [ 212001164 ] > 0 )        {
    LimitValues [ 212001164 ] = 0             ;
    setWidths ( )                             ;
  }                                           ;
  /////////////////////////////////////////////
  LimitValues [ 212001161 ] ++                ;
  /////////////////////////////////////////////
  while ( Stoppings . count ( ) > 0 )         {
    int idx = Stoppings . first ( )           ;
    if ( End ( idx ) )                        {
      Stoppings . takeFirst ( )               ;
    }                                         ;
    qApp -> processEvents ( )                 ;
  }                                           ;
  /////////////////////////////////////////////
  while ( EnableButtons . count ( ) > 0 )     {
    int idx = EnableButtons . first ( )       ;
    EnableButtons . takeFirst ( )             ;
    if ( Buttons . contains ( idx ) )         {
      Buttons [ idx ] -> setEnabled ( true )  ;
      Buttons [ idx ] -> setChecked ( true )  ;
    }                                         ;
    qApp -> processEvents ( )                 ;
  }                                           ;
  /////////////////////////////////////////////
  LockGui  (              )                   ;
  QList<int> K = Booleans . keys ( )          ;
  int k                                       ;
  if ( K . count ( ) > 0 )                    {
    foreach ( k , K )                         {
      bool u = false                          ;
      /////////////////////////////////////////
      if ( Booleans . contains ( k ) )        {
        u = *(Booleans[k])                    ;
      }                                       ;
      /////////////////////////////////////////
      if ( u )                                {
        Report     ( k )                      ;
        Time::skip ( 2 )                      ;
      }                                       ;
    }                                         ;
  }                                           ;
  Minimum [ -1 ] ++                           ;
  UnlockGui   ( )                             ;
  /////////////////////////////////////////////
  LocalAccept ( )                             ;
  if ( 0 == ( Minimum [ -1 ] % 10 ) )         {
    Minimum [ -1 ] = 0                        ;
    Clean ( )                                 ;
    if ( Fitting ) emit AutoFit ( )           ;
  }                                           ;
  /////////////////////////////////////////////
  LimitValues [ 212001161 ] --                ;
}

void N::ProgressManager::Accepting(int ID,QString name,QString format)
{
  LockGui                    (                       ) ;
  //////////////////////////////////////////////////////
  NewTreeWidgetItem          ( item                  ) ;
  //////////////////////////////////////////////////////
  QProgressBar    *  bar                               ;
  QToolButton     *  button                            ;
  //////////////////////////////////////////////////////
  QFont f = plan->fonts[Fonts::TreeView] . toQFont ( ) ;
  bar     = new QProgressBar ( NULL                  ) ;
  button  = new QToolButton  ( NULL                  ) ;
  bar    -> setFormat        ( format                ) ;
  bar    -> setFont          ( f                     ) ;
  button -> setEnabled       ( false                 ) ;
  button -> setIcon          ( LocalIcons [ "Stop" ] ) ;
  button -> setCheckable     ( true                  ) ;
  button -> setChecked       ( false                 ) ;
  item   -> setText          ( 1 , name              ) ;
  item   -> setData          ( 0 , Qt::UserRole , 0  ) ;
  //////////////////////////////////////////////////////
  insertTopLevelItem         ( 0 , item              ) ;
  setItemWidget              ( item , 0 , button     ) ;
  setItemWidget              ( item , 6 , bar        ) ;
  //////////////////////////////////////////////////////
  Items    [ ID ] = item                               ;
  Buttons  [ ID ] = button                             ;
  Progress [ ID ] = bar                                ;
  Connects [ ID ] = name                               ;
  Message  [ ID ] = name                               ;
  Formats  [ ID ] = format                             ;
  FREQs    [ ID ] = LocalMsgs [ 441212001 ]            ;
  FREQr    [ ID ] = LocalMsgs [ 441212002 ]            ;
  //////////////////////////////////////////////////////
  UnlockGui                  (                       ) ;
  reportTasks                (                       ) ;
}

typedef struct   {
  int     ID     ;
  QString name   ;
  QString format ;
} LocalPmPacket  ;

void N::ProgressManager::Accepting(void)
{
  emit LocalRequest ( ) ;
}

void N::ProgressManager::LocalAccept(void)
{
  if ( LimitValues [ 212001162 ] > 0 ) return       ;
  LimitValues [ 212001162 ] ++                      ;
  QMutexLocker L ( &QueueMutex )                    ;
  while ( Queues . count ( ) > 0 )                  {
    LocalPmPacket * lpm                             ;
    lpm = (LocalPmPacket *) Queues . first ( )      ;
    Accepting ( lpm->ID , lpm->name , lpm->format ) ;
    Queues . takeAt ( 0 )                           ;
    delete lpm                                      ;
    qApp -> processEvents ( )                       ;
  }                                                 ;
  LimitValues [ 212001162 ] --                      ;
}

int N::ProgressManager::Request(QString name,QString format)
{
  int ID = Id                 ;
  /////////////////////////////
  IdMutex . lock   ( )        ;
  Id++                        ;
  IdMutex . unlock ( )        ;
  /////////////////////////////
  LocalPmPacket * lpm         ;
  lpm = new LocalPmPacket ( ) ;
  lpm -> ID     = ID          ;
  lpm -> name   = name        ;
  lpm -> format = format      ;
  Queues << lpm               ;
  /////////////////////////////
  return ID                   ;
}

void N::ProgressManager::setName(int ID,QString name)
{
  LockGui   ( )          ;
  Connects [ ID ] = name ;
  UnlockGui ( )          ;
}

void N::ProgressManager::setRange(int id,qint64 Min,qint64 Max)
{
  if ( Min >= Max ) return ;
  LockGui   ( )            ;
  Final    [ id ]  = 0     ;
  Minimum  [ id ]  = Min   ;
  Maximum  [ id ]  = Max   ;
  UnlockGui ( )            ;
}

void N::ProgressManager::setMessage(int Id,QString message)
{
  LockGui   ( )            ;
  Message [ Id ] = message ;
  UnlockGui ( )            ;
}

void N::ProgressManager::setFormat(int Id,QString format)
{
  LockGui   ( )           ;
  Formats [ Id ] = format ;
  UnlockGui ( )           ;
}

void N::ProgressManager::setFrequency(int Id,QString cFmt,QString rFmt)
{
  LockGui   ( )       ;
  FREQs [ Id ] = cFmt ;
  FREQr [ Id ] = rFmt ;
  UnlockGui ( )       ;
}

bool N::ProgressManager::isReady(int Id)
{
  return Items . contains ( Id ) ;
}

bool N::ProgressManager::waitForReady(int Id,int msecs)
{
  QDateTime S    = nTimeNow                    ;
  bool      tout = false                       ;
  while ( ( ! isReady ( Id ) ) && ( ! tout ) ) {
    if ( isFunction ( 212001302 ) )            {
      if ( S . msecsTo ( nTimeNow ) > msecs )  {
        tout = true                            ;
        return false                           ;
      }                                        ;
    }                                          ;
    Time::msleep ( 2 )                         ;
    DoProcessEvents                            ;
  }                                            ;
  return true                                  ;
}

void N::ProgressManager::Start(int id,qint64 * Value,bool * Running)
{
  if ( ! waitForReady ( id , 1000 ) ) return               ;
  EnableButtons << id                                      ;
  Values   [ id ]  = Value                                 ;
  Begins   [ id ]  = QDateTime::currentDateTime ( )        ;
  Booleans [ id ]  = Running                               ;
  Final    [ id ]  = 0                                     ;
  if ( ! Minimum . contains ( id ) ) Minimum  [ id ] = 0   ;
  StartAt  [ id ]  = (*Value)                              ;
  if ( ! Maximum . contains ( id ) ) Maximum  [ id ] = 100 ;
  Items    [ id ] -> setData(0,Qt::UserRole,1)             ;
  //////////////////////////////////////////////////////////
  QDateTime E = QDateTime::currentDateTime()               ;
  QString   Z = E . toString ( "yyyy/MM/dd hh:mm:ss" )     ;
  Items    [ id ] -> setText ( 2 , Z )                     ;
}

void N::ProgressManager::Finish(int id)
{
  if ( ! waitForReady ( id , 1000 ) ) return                 ;
  LockGui ( )                                                ;
  if ( Final . contains ( id ) && Values . contains ( id ) ) {
    if ( NotNull ( Values [ id ] ) )                         {
      Final  [ id ] = * ( Values [ id ] )                    ;
      Values [ id ] = NULL                                   ;
    }                                                        ;
  }                                                          ;
  ////////////////////////////////////////////////////////////
  UnlockGui ( )                                              ;
  Stoppings << id                                            ;
}

bool N::ProgressManager::End(int id)
{
  if ( ! Booleans . contains ( id ) ) return false         ;
  //////////////////////////////////////////////////////////
  LockGui   ( )                                            ;
  //////////////////////////////////////////////////////////
  QTreeWidgetItem * item = NULL                            ;
  QProgressBar    * bar  = NULL                            ;
  QToolButton     * tb   = NULL                            ;
  QDateTime         Now  = QDateTime::currentDateTime()    ;
  //////////////////////////////////////////////////////////
  if ( Items    . contains ( id ) ) item = Items    [ id ] ;
  if ( Progress . contains ( id ) ) bar  = Progress [ id ] ;
  if ( Buttons  . contains ( id ) ) tb   = Buttons  [ id ] ;
  //////////////////////////////////////////////////////////
  if ( NotNull(bar ) ) bar -> setValue   ( Final [ id ] )  ;
  if ( NotNull(tb  ) ) tb  -> setEnabled ( false        )  ;
  if ( NotNull(item) )                                     {
    item -> setData(0,Qt::UserRole,2)                      ;
    item -> setText(3,Now.toString("yyyy/MM/dd hh:mm:ss")) ;
  }                                                        ;
  Buttons    . remove ( id )                               ;
  Report              ( id )                               ;
  Booleans   . remove ( id )                               ;
  if ( NotNull ( item ) )                                  {
    removeItemWidget ( item , 0                          ) ;
    item -> setIcon  ( 0    , LocalIcons [ "Yes" ]       ) ;
  }                                                        ;
  //////////////////////////////////////////////////////////
  UnlockGui ( )                                            ;
  return true                                              ;
}

void N::ProgressManager::Clean(void)
{
  bool cleanup = false                      ;
  ///////////////////////////////////////////
  if ( LimitValues [ 212001162 ] <= 0 )     {
    if ( LimitValues [ 212001160 ] > 0 )    {
      cleanup = true                        ;
    }                                       ;
  }                                         ;
  ///////////////////////////////////////////
  if ( LimitValues [ 212001163 ] > 0 )      {
    LimitValues [ 212001163 ] = 0           ;
    cleanup                   = true        ;
  }                                         ;
  ///////////////////////////////////////////
  if ( topLevelItemCount ( ) <= 0 )         {
    cleanup = false                         ;
  }                                         ;
  ///////////////////////////////////////////
  if ( cleanup )                            {
    for (int i=0;i<topLevelItemCount();)    {
      QTreeWidgetItem * it                  ;
      it = topLevelItem ( i      )          ;
      int id = nTreeInt ( it , 0 )          ;
      if (id==2)                            {
        int index = indexOfTopLevelItem(it) ;
        if ( index >= 0 )                   {
          takeTopLevelItem ( index )        ;
        } else i++                          ;
      } else i++                            ;
    }                                       ;
  }                                         ;
  ///////////////////////////////////////////
  reportTasks ( )                           ;
}

void N::ProgressManager::reportTasks(void)
{
  LockGui   ( )                            ;
  //////////////////////////////////////////
  int count = 0                            ;
  for (int i=0;i<topLevelItemCount();i++)  {
    QTreeWidgetItem * it                   ;
    it = topLevelItem(i)                   ;
    int id = nTreeInt(it,0)                ;
    if (id==1) count++                     ;
  }                                        ;
  //////////////////////////////////////////
  UnlockGui ( )                            ;
  //////////////////////////////////////////
  QString m                                ;
  if (count>0)                             {
    m = tr("%1 operations are running"     )
        .arg(count)                        ;
  } else                                   {
    m = tr("Progress Manager")             ;
  }                                        ;
  //////////////////////////////////////////
  setWindowTitle ( m )                     ;
  setToolTip     ( m )                     ;
  //////////////////////////////////////////
  QWidget * w = parentWidget ( )           ;
  nDropOut ( IsNull ( w ) )                ;
  w -> setWindowTitle ( m )                ;
}

bool N::ProgressManager::Menu(QPoint)
{
  nScopedMenu       ( mm  , this                                       ) ;
  QAction * aa                                                           ;
  bool      ac = ( LimitValues [ 212001160 ] > 0 )                       ;
  ////////////////////////////////////////////////////////////////////////
  if ( isFunction ( 212001301 ) )                                        {
    mm . add          ( 201 , tr("Hide") )                               ;
    mm . addSeparator (                  )                               ;
  }                                                                      ;
  ////////////////////////////////////////////////////////////////////////
  mm . add          ( 101 , tr("Clean")                                ) ;
  mm . add          ( 102 , tr("Auto resize columns") , true , Fitting ) ;
  mm . add          ( 103 , tr("Auto clean"         ) , true , ac      ) ;
  mm      . setFont ( plan                                             ) ;
  aa = mm . exec    (                                                  ) ;
  nKickOut          ( IsNull ( aa ) ,true                              ) ;
  ////////////////////////////////////////////////////////////////////////
  switch ( mm [ aa ] )                                                   {
    case 101                                                             :
      LimitValues [ 212001163 ] = 1                                      ;
    break                                                                ;
    case 102                                                             :
      Fitting                   = aa -> isChecked ( )                    ;
    break                                                                ;
    case 103                                                             :
      LimitValues [ 212001160 ] = aa -> isChecked ( ) ? 1 : 0            ;
    break                                                                ;
    case 201                                                             :
      emit Hidden ( this )                                               ;
    break                                                                ;
  }                                                                      ;
  return true                                                            ;
}
