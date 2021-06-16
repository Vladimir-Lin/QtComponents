#include <qtcomponents.h>

N::DebugView:: DebugView   ( QWidget * parent , Plan * p )
             : TextBrowser (           parent ,        p )
             , AttachDock  (                           p )
             , Timer       ( NULL                        )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::DebugView::~DebugView (void)
{
  Stop ( ) ;
}

void N::DebugView::Configure(void)
{
  setAttribute                     ( Qt::WA_InputMethodEnabled ) ;
  XmlRpcLogHandler::setVerbosity   ( plan -> Verbose           ) ;
  setLimitValue                    ( 773311 , 250              ) ;
  LocalIcons [ "ZoomIn"  ] = QIcon ( ":/images/zoomin.png"     ) ;
  LocalIcons [ "ZoomOut" ] = QIcon ( ":/images/zoomout.png"    ) ;
  plan  -> setFont                 ( this                      ) ;
  ////////////////////////////////////////////////////////////////
  addConnector ( "Start"                                         ,
                 this                                            ,
                 SIGNAL ( StartFlush ( ) )                       ,
                 this                                            ,
                 SLOT   ( Flush      ( ) )                     ) ;
  onlyConnector ( "Start" )                                      ;
}

void N::DebugView::closeEvent(QCloseEvent * e)
{
  Stop                     (   ) ;
  QTextBrowser::closeEvent ( e ) ;
}

void N::DebugView::contextMenuEvent(QContextMenuEvent * e)
{
  if ( Menu ( e -> pos ( ) ) ) e -> accept ( ) ; else
  QTextBrowser::contextMenuEvent ( e )              ;
}

void N::DebugView::Docking       (
       QMainWindow       * Main  ,
       QString             title ,
       Qt::DockWidgetArea  area  ,
       Qt::DockWidgetAreas areas )
{
  AttachDock::Docking ( Main , this , title , area , areas )  ;
  addConnector  ( "Docking"                                   ,
                  Dock , SIGNAL ( visibilityChanged(bool) )   ,
                  this , SLOT   ( Visible          (bool) ) ) ;
  onlyConnector ( "Docking"                                 ) ;
}

void N::DebugView::Visible(bool visible)
{
  Visiblity ( visible ) ;
}

void N::DebugView::DockIn(bool shown)
{
  Show ( shown ) ;
}

bool N::DebugView::FocusIn(void)
{
  nKickOut          ( IsNull(plan) , false           ) ;
  DisableAllActions (                                ) ;
  AssignAction      ( Label        , windowTitle ( ) ) ;
  LinkAction        ( Save         , Save        ( ) ) ;
  LinkAction        ( Copy         , copy        ( ) ) ;
  LinkAction        ( ZoomIn       , ZoomIn      ( ) ) ;
  LinkAction        ( ZoomOut      , ZoomOut     ( ) ) ;
  LinkAction        ( SelectAll    , selectAll   ( ) ) ;
  if                ( IsNull ( Timer )               ) {
    LinkAction      ( Start        , Startup     ( ) ) ;
  } else                                               {
    LinkAction      ( Stop         , Stop        ( ) ) ;
  }                                                    ;
  return true                                          ;
}

void N::DebugView::Startup(void)
{
  emit StartFlush ( ) ;
}

void N::DebugView::Flush(void)
{
  if ( IsNull ( Timer ) )                      {
    Timer = new QTimer ( this )                ;
    addConnector ( "Flush"                     ,
                   Timer                       ,
                   SIGNAL ( timeout    ( ) )   ,
                   this                        ,
                   SLOT   ( FlushQueue ( ) ) ) ;
    onlyConnector ( "Flush" )                  ;
  }                                            ;
  if ( NotNull ( Timer ) )                     {
    Timer -> start ( LimitValues [ 773311 ] )  ;
  }                                            ;
}

void N::DebugView::Stop(void)
{
  if ( IsNull ( Timer ) ) return ;
  QTimer * E = Timer             ;
  Timer  = NULL                  ;
  E     -> stop        ( )       ;
  E     -> deleteLater ( )       ;
  removeConnector ( "Flush" )    ;
}

void N::DebugView::ZoomIn(void)
{
  zoomIn  ( 2 ) ;
}

void N::DebugView::ZoomOut(void)
{
  zoomOut ( 2 ) ;
}

bool N::DebugView::Menu(QPoint)
{
  QString         msg  = toPlainText ( )                                ;
  QMdiSubWindow * mdi  = Casting ( QMdiSubWindow , parent ( ) )         ;
  QDockWidget   * dock = Casting ( QDockWidget   , parent ( ) )         ;
  MenuManager     mm ( this )                                           ;
  QAction       * aa                                                    ;
  bool            rpc  = false                                          ;
  if ( NotNull ( plan ) )                                               {
    rpc = ( plan -> rpclog == XmlRpcLogHandler::getLogHandler ( )     ) ;
  }                                                                     ;
  mm . add          ( 101 , tr("Clear")                               ) ;
  mm . add          ( 102 , tr("Copy")                                ) ;
  mm . add          ( 103 , tr("Select all")                          ) ;
  if ( msg . length ( ) > 0 ) mm . add ( 104 , tr("Save") )             ;
  mm . addSeparator (                                                 ) ;
  mm . add          ( 111 , tr("Verbose level")                       ) ;
  mm . add          ( 112 , tr("Debug RPC") , true , rpc              ) ;
  mm . addSeparator (                                                 ) ;
  mm . add          ( 201 , LocalIcons [ "ZoomIn"  ] , tr("Zoom in" ) ) ;
  mm . add          ( 202 , LocalIcons [ "ZoomOut" ] , tr("Zoom out") ) ;
  if ( NotNull ( dock ) || NotNull(mdi)) mm . addSeparator (          ) ;
  if ( NotNull ( dock ) ) mm . add (1000001,tr("Move to window area") ) ;
  if ( NotNull ( mdi  ) ) mm . add (1000002,tr("Move to dock area")   ) ;
  ///////////////////////////////////////////////////////////////////////
  mm . setFont      ( plan                                            ) ;
  aa = mm . exec    (                                                 ) ;
  if ( IsNull ( aa ) ) return true                                      ;
  ///////////////////////////////////////////////////////////////////////
  switch ( mm [ aa ] )                                                  {
    case 101                                                            :
      clear     (   )                                                   ;
    break                                                               ;
    case 102                                                            :
      copy      (   )                                                   ;
    break                                                               ;
    case 103                                                            :
      selectAll (   )                                                   ;
    break                                                               ;
    case 104                                                            :
      Save      (   )                                                   ;
    break                                                               ;
    case 111                                                            :
      if ( NotNull ( plan ) )                                           {
        int  verbose = plan -> Verbose                                  ;
        bool okay    = false                                            ;
        verbose = QInputDialog::getInt                                  (
                    this                                                ,
                    tr("Debug verbose level")                           ,
                    tr("Verbose")                                       ,
                    verbose                                             ,
                    0                                                   ,
                    100                                                 ,
                    1                                                   ,
                    &okay                                             ) ;
        if (okay)                                                       {
          plan -> Verbose = verbose                                     ;
          XmlRpcLogHandler::setVerbosity ( plan -> Verbose )            ;
        }                                                               ;
      }                                                                 ;
    break                                                               ;
    case 112                                                            :
      if ( NotNull ( plan ) )                                           {
        rpc = aa -> isChecked ( )                                       ;
        if ( rpc )                                                      {
          XmlRpcErrorHandler::setErrorHandler ( plan -> rpcerr )        ;
          XmlRpcLogHandler  ::setLogHandler   ( plan -> rpclog )        ;
        } else                                                          {
          XmlRpcErrorHandler::setErrorHandler ( plan -> xmlerr )        ;
          XmlRpcLogHandler  ::setLogHandler   ( plan -> xmllog )        ;
        }                                                               ;
      }                                                                 ;
    break                                                               ;
    case 201                                                            :
      ZoomIn  ( )                                                       ;
    break                                                               ;
    case 202                                                            :
      ZoomOut ( )                                                       ;
    break                                                               ;
    case 1000001                                                        :
      emit attachMdi ( this , 0 )                                       ;
    break                                                               ;
    case 1000002                                                        :
      emit attachDock                                                   (
        this                                                            ,
        windowTitle()                                                   ,
        Qt::BottomDockWidgetArea                                        ,
        Qt::TopDockWidgetArea                                           |
        Qt::BottomDockWidgetArea                                      ) ;
    break                                                               ;
    default                                                             :
    break                                                               ;
  }                                                                     ;
  return true                                                           ;
}

void N::DebugView::FlushQueue(void)
{
  if ( ( ! isContinue )                       ||
       ( ( NULL != Data . Controller )        &&
         ( ! ( * ( Data . Controller ) ) ) ) ) {
    Stop ( )                                   ;
    return                                     ;
  }                                            ;
  //////////////////////////////////////////////
  nDropOut ( Queue . count () <= 0 )           ;
  QString M = Queue . join ( "\n"  )           ;
  Queue . clear            (       )           ;
  append                   ( M     )           ;
}

void N::DebugView::Append(const QString & text)
{
  Queue << text ;
}

void N::DebugView::Save(void)
{
  QString msg = toPlainText ( )                                  ;
  if ( msg . length ( ) <= 0 ) return                            ;
  ////////////////////////////////////////////////////////////////
  QString filename = QFileDialog::getSaveFileName                (
                       this                                      ,
                       tr("Save debug message")                  ,
                       plan->Path("Temp")                        ,
                       tr("Report (*.txt)"                   ) ) ;
  if ( filename . length ( ) <= 0 ) return                       ;
  ////////////////////////////////////////////////////////////////
  QByteArray B = msg . toUtf8 ( )                                ;
  if ( ! File::toFile ( filename , B ) )                         {
    Alert ( Error )                                              ;
    return                                                       ;
  }                                                              ;
  Alert   ( Done  )                                              ;
  ////////////////////////////////////////////////////////////////
  QString talk                                                   ;
  talk = tr("Save debug information into %1") . arg ( filename ) ;
  plan -> Talk ( 10 , talk                                     ) ;
}
