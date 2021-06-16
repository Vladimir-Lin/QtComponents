#include <qtcomponents.h>

N::TableView:: TableView  ( QWidget * parent,Plan * p     )
             : QTableView (           parent              )
             , VirtualGui (           this  ,       p     )
             , Thread     (           0     ,       false )
{
  WidgetClass                                   ;
  addIntoWidget ( parent , this               ) ;
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

N::TableView::~TableView (void)
{
}

bool N::TableView::event(QEvent * event)
{
  if (permitGesture() && gestureEvent(event)) return true ;
  return QTableView::event(event)                        ;
}

void N::TableView::paintEvent(QPaintEvent * event)
{
  nIsolatePainter(QTableView) ;
}

void N::TableView::focusInEvent(QFocusEvent * event)
{
  if (!focusIn (event)) QTableView::focusInEvent (event) ;
}

void N::TableView::focusOutEvent(QFocusEvent * event)
{
  if (!focusOut(event)) QTableView::focusOutEvent(event) ;
}

void N::TableView::resizeEvent(QResizeEvent * event)
{
  if (Relocation()) event->accept();
  else QTableView::resizeEvent(event);
}

void N::TableView::contextMenuEvent(QContextMenuEvent * event)
{
  QTableView::contextMenuEvent(event);
}

void N::TableView::dragEnterEvent(QDragEnterEvent * event)
{
  if (allowDrop(dragDropMode()) && dragEnter(event)) event->acceptProposedAction() ;
  else QTableView::dragEnterEvent(event);
}

void N::TableView::dragLeaveEvent(QDragLeaveEvent * event)
{
  if (removeDrop()) event->accept() ;
  else QTableView::dragLeaveEvent(event);
}

void N::TableView::dragMoveEvent(QDragMoveEvent * event)
{
  if (allowDrop(dragDropMode()) && dragMove(event)) event->acceptProposedAction() ;
  else QTableView::dragMoveEvent(event);
}

void N::TableView::dropEvent(QDropEvent * event)
{
  if (allowDrop(dragDropMode()) && drop(event)) event->acceptProposedAction() ;
  else QTableView::dropEvent(event);
}

void N::TableView::mousePressEvent(QMouseEvent * event)
{
  if (allowDrag(dragDropMode()) && dragStart(event)) event->accept() ;
  else QTableView::mousePressEvent(event);
}

void N::TableView::mouseMoveEvent(QMouseEvent * event)
{
  if (allowDrag(dragDropMode()) && dragMoving(event)) event->accept() ;
  else QTableView::mouseMoveEvent(event);
}

void N::TableView::mouseReleaseEvent(QMouseEvent * event)
{
  if (allowDrag(dragDropMode()) && dragEnd(event)) event->accept() ;
  else QTableView::mouseReleaseEvent(event);
}

void N::TableView::closeEvent(QCloseEvent * event)
{
  if (Shutdown()) event->accept();
  else QTableView::closeEvent(event);
}

bool N::TableView::Shutdown(void)
{
  emit Leave(this) ;
  return true ;
}

bool N::TableView::Relocation(void)
{
  return false ;
}

void N::TableView::setFont(void)
{
  changeFont ( ) ;
}

void N::TableView::DropCommands(void)
{
  LaunchCommands ( ) ;
}
