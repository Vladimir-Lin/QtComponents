#include <qtcomponents.h>

N::Scintilla:: Scintilla          ( QWidget * parent , Plan * p     )
             : QsciScintilla      (           parent                )
             , VirtualGui         (           this   ,        p     )
             , Thread             (           0      ,        false )
             , AttachDock         (                           p     )
             , CommandSequence    ( new QTimer ( this )             )
             , dockingOrientation ( 0                               )
             , dockingPlace       ( Qt::RightDockWidgetArea         )
             , dockingPlaces      ( Qt::AllDockWidgetAreas          )
{
  WidgetClass                     ;
  addIntoWidget ( parent , this ) ;
  Configure     (               ) ;
}

N::Scintilla::~Scintilla (void)
{
}

void N::Scintilla::ThreadEvent(void)
{
  nDropOut ( IsNull ( plan ) ) ;
  plan -> processEvents ( )    ;
}

void N::Scintilla::AtBusy(void)
{
  nDropOut ( IsNull ( plan ) ) ;
  plan -> StartBusy ( )        ;
}

void N::Scintilla::OnRelax(void)
{
  nDropOut ( IsNull ( plan ) ) ;
  plan -> StopBusy ( )         ;
}

void N::Scintilla::Configure (void)
{
  setAttribute                 ( Qt::WA_InputMethodEnabled ) ;
  setHorizontalScrollBarPolicy ( Qt::ScrollBarAsNeeded     ) ;
  setVerticalScrollBarPolicy   ( Qt::ScrollBarAsNeeded     ) ;
  plan            -> setFont   ( this                      ) ;
  CommandSequence -> setParent ( this                      ) ;
  LimitValues [ 37714 ] = 300                                ;
  ////////////////////////////////////////////////////////////
  addConnector  ( "Follow"                                   ,
                  SIGNAL( Follow          (int) )            ,
                  SLOT  ( Execute         (int) )          ) ;
  addConnector  ( "Busy"                                     ,
                  SIGNAL( OnBusy          (   ) )            ,
                  SLOT  ( AtBusy          (   ) )          ) ;
  addConnector  ( "Relax"                                    ,
                  SIGNAL( GoRelax         (   ) )            ,
                  SLOT  ( OnRelax         (   ) )          ) ;
  addConnector  ( "Trigger"                                  ,
                  SIGNAL( TriggerCommand  (   ) )            ,
                  SLOT  ( StartCommand    (   ) )          ) ;
  addConnector  ( "Commando"                                 ,
                  Commando                                   ,
                  SIGNAL ( timeout        ( ) )              ,
                  this                                       ,
                  SLOT   ( DropCommands   ( ) )            ) ;
  addConnector  ( "Sequence"                                 ,
                  CommandSequence                            ,
                  SIGNAL ( timeout        ( ) )              ,
                  this                                       ,
                  SLOT   ( CommandHandler ( ) )            ) ;
  ////////////////////////////////////////////////////////////
  onlyConnector ( "Follow"   )                               ;
  onlyConnector ( "Busy"     )                               ;
  onlyConnector ( "Relax"    )                               ;
  onlyConnector ( "Commando" )                               ;
  onlyConnector ( "Sequence" )                               ;
  ////////////////////////////////////////////////////////////
  if ( NotNull ( plan ) )                                    {
    Data . Controller = & ( plan->canContinue )              ;
  }                                                          ;
}

void N::Scintilla::focusInEvent(QFocusEvent * event)
{
  if (!focusIn (event)) QsciScintilla::focusInEvent (event) ;
}

void N::Scintilla::focusOutEvent(QFocusEvent * event)
{
  if (!focusOut(event)) QsciScintilla::focusOutEvent(event) ;
}

void N::Scintilla::resizeEvent(QResizeEvent * event)
{
  if (Relocation()) event->accept();
  else QsciScintilla::resizeEvent(event);
}

void N::Scintilla::contextMenuEvent(QContextMenuEvent * event)
{
  if (Menu(event->pos())) event->accept(); else
  QsciScintilla::contextMenuEvent(event);
}

void N::Scintilla::closeEvent(QCloseEvent * e)
{
  if ( Shutdown ( ) )               {
    e -> accept               (   ) ;
  } else                            {
    QsciScintilla::closeEvent ( e ) ;
  }                                 ;
}

bool N::Scintilla::Shutdown(void)
{
  emit Leave ( this ) ;
  return true         ;
}

void N::Scintilla::Docking        (
       QMainWindow      *  Main  ,
       QString             title ,
       Qt::DockWidgetArea  area  ,
       Qt::DockWidgetAreas areas )
{
  AttachDock::Docking(Main,this,title,area,areas) ;
  nConnect(Dock,SIGNAL(visibilityChanged(bool))   ,
           this,SLOT  (Visible          (bool)) ) ;
}

void N::Scintilla::Visible(bool visible)
{
  Visiblity ( visible ) ;
}

void N::Scintilla::DockIn(bool shown)
{
  Show ( shown ) ;
}

void N::Scintilla::DockingMenu(MenuManager & Menu)
{
  QMdiSubWindow  * mdi    = Casting(QMdiSubWindow,parent()) ;
  QDockWidget    * dock   = Casting(QDockWidget  ,parent()) ;
  if (NotNull(dock) || NotNull(mdi)) Menu.addSeparator()    ;
  nIfSafe(dock) Menu.add(1000001,tr("Move to window area")) ;
  nIfSafe(mdi ) Menu.add(1000002,tr("Move to dock area"  )) ;
}

bool N::Scintilla::RunDocking(MenuManager & Menu,QAction * action)
{
  switch (Menu[action])                        {
    case 1000001                               :
      emit attachMdi (this,dockingOrientation) ;
    break                                      ;
    case 1000002                               :
      emit attachDock                          (
        this                                   ,
        windowTitle()                          ,
        dockingPlace                           ,
        dockingPlaces                        ) ;
    break                                      ;
    default: return false                      ;
  }                                            ;
  return true                                  ;
}

void N::Scintilla::run(int type,ThreadData * data)
{
}

bool N::Scintilla::startup(void)
{
  return false ;
}

void N::Scintilla::pendingStartup(void)
{
  VarArgs V          ;
  V << 10001         ;
  addSequence  ( V ) ;
  StartCommand (   ) ;
}

void N::Scintilla::StartCommand(void)
{
  nDropOut ( Commanding )                            ;
  CommandSequence -> start ( LimitValues [ 37714 ] ) ;
}

void N::Scintilla::CommandHandler(void)
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

bool N::Scintilla::RunCommand(VarArgs & arguments)
{
  if (arguments.count()<1) return false ;
  VarArgs V = arguments                 ;
  int     c = V[0].toInt()              ;
  switch ( c )                          {
    case 10001                          :
      startup (           )             ;
    break                               ;
    case 10011                          :
    case 10012                          :
    case 11001                          :
      V . takeAt ( 0 )                  ;
      start   ( c , V )                 ;
    break                               ;
    default                             :
    return false                        ;
  }                                     ;
  return true                           ;
}

void N::Scintilla::DropCommands(void)
{
  LaunchCommands ( ) ;
}

void N::Scintilla::Execute(int command)
{
  start ( command ) ;
}

bool N::Scintilla::Relocation(void)
{
  return false ;
}

bool N::Scintilla::Menu(QPoint pos)
{
  return false ;
}
