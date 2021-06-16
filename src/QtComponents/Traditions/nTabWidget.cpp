#include <qtcomponents.h>

N::TabWidget:: TabWidget  ( QWidget * parent,Plan * p     )
             : QTabWidget (           parent              )
             , VirtualGui (           this  ,       p     )
             , Thread     (           0     ,       false )
{
  WidgetClass                     ;
  addIntoWidget ( parent , this ) ;
  Configure     (               ) ;
}

N::TabWidget::~TabWidget (void)
{
}

void N::TabWidget::paintEvent(QPaintEvent * event)
{
  nIsolatePainter(QTabWidget) ;
}

void N::TabWidget::focusInEvent(QFocusEvent * event)
{
  if (!focusIn (event)) QTabWidget::focusInEvent (event) ;
}

void N::TabWidget::focusOutEvent(QFocusEvent * event)
{
  if (!focusOut(event)) QTabWidget::focusOutEvent(event) ;
}

void N::TabWidget::closeEvent(QCloseEvent * event)
{
  if (Shutdown()) event->accept()    ;
  else QTabWidget::closeEvent(event) ;
}

void N::TabWidget::resizeEvent(QResizeEvent * event)
{
  if (Relocation()) event->accept()   ;
  else QTabWidget::resizeEvent(event) ;
}

void N::TabWidget::showEvent(QShowEvent * e)
{
  QTabWidget::showEvent ( e ) ;
  Relocation            (   ) ;
}

void N::TabWidget::contextMenuEvent(QContextMenuEvent * event)
{
  if (Menu(event->pos())) event->accept(); else {
    QTabWidget::contextMenuEvent(event)         ;
  }                                             ;
}

bool N::TabWidget::event(QEvent * event)
{
  if (permitGesture() && gestureEvent(event)) return true ;
  return QTabWidget::event(event)                         ;
}

bool N::TabWidget::Shutdown(void)
{
  emit Leave ( this ) ;
  return true         ;
}

void N::TabWidget::Configure(void)
{
  setAcceptDrops           ( true )             ;
  tabBar ( ) -> setMovable ( true )             ;
  setAttribute  ( Qt::WA_InputMethodEnabled   ) ;
  addConnector  ( "Commando"                    ,
                  Commando                      ,
                  SIGNAL ( timeout      ( ) )   ,
                  this                          ,
                  SLOT   ( DropCommands ( ) ) ) ;
  onlyConnector ( "Commando"                  ) ;
  ///////////////////////////////////////////////
  if ( NotNull ( plan ) )                       {
    Data . Controller = & ( plan->canContinue ) ;
  }                                             ;
}

bool N::TabWidget::Relocation(void)
{
  return false ;
}

bool N::TabWidget::Menu(QPoint pos)
{
  emit ItemMenu ( this , pos ) ;
  return false                 ;
}

void N::TabWidget::CopyToClipboard(void)
{
}

void N::TabWidget::SelectNone(void)
{
}

void N::TabWidget::SelectAll(void)
{
}

void N::TabWidget::setFont(void)
{
  changeFont ( ) ;
}

void N::TabWidget::DropCommands(void)
{
  LaunchCommands ( ) ;
}
