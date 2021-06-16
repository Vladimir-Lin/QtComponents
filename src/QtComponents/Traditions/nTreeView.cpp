#include <qtcomponents.h>

N::TreeView:: TreeView   ( QWidget * parent , Plan * p     )
            : QTreeView  (           parent                )
            , VirtualGui (           this   ,        p     )
            , Thread     (           0      ,        false )
{
  WidgetClass                     ;
  addIntoWidget ( parent , this ) ;
  Configure     (               ) ;
}

N::TreeView::~TreeView (void)
{
}

bool N::TreeView::event(QEvent * event)
{
  if (permitGesture() && gestureEvent(event)) return true ;
  return QTreeView::event(event)                        ;
}

void N::TreeView::paintEvent(QPaintEvent * event)
{
  nIsolatePainter(QTreeView) ;
}

void N::TreeView::focusInEvent(QFocusEvent * event)
{
  if (!focusIn (event)) QTreeView::focusInEvent (event) ;
}

void N::TreeView::focusOutEvent(QFocusEvent * event)
{
  if (!focusOut(event)) QTreeView::focusOutEvent(event) ;
}

void N::TreeView::resizeEvent(QResizeEvent * event)
{
  if (Relocation()) event->accept();
  else QTreeView::resizeEvent(event);
}

void N::TreeView::contextMenuEvent(QContextMenuEvent * event)
{
  if (Menu(event->pos())) event->accept(); else
  QTreeView::contextMenuEvent(event);
}

void N::TreeView::dragEnterEvent(QDragEnterEvent * event)
{
  if (allowDrop(dragDropMode()) && dragEnter(event)) event->acceptProposedAction() ; else {
    if (PassDragDrop) QTreeView::dragEnterEvent(event);
    else event->ignore() ;
  };
}

void N::TreeView::dragLeaveEvent(QDragLeaveEvent * event)
{
  if (removeDrop()) event->accept() ; else {
    if (PassDragDrop) QTreeView::dragLeaveEvent(event);
    else event->ignore() ;
  };
}

void N::TreeView::dragMoveEvent(QDragMoveEvent * event)
{
  if (allowDrop(dragDropMode()) && dragMove(event)) event->acceptProposedAction() ; else {
    if (PassDragDrop) QTreeView::dragMoveEvent(event);
    else event->ignore() ;
  };
}

void N::TreeView::dropEvent(QDropEvent * event)
{
  if (allowDrop(dragDropMode()) && drop(event)) event->acceptProposedAction() ; else {
    if (PassDragDrop) QTreeView::dropEvent(event);
    else event->ignore() ;
  };
}

void N::TreeView::mousePressEvent(QMouseEvent * event)
{
  if (allowDrag(dragDropMode())) dragStart(event) ;
  QTreeView::mousePressEvent(event)             ;
}

void N::TreeView::mouseMoveEvent(QMouseEvent * event)
{
  bool moving = true                             ;
  if (allowDrag(dragDropMode()))                 {
    if (dragMoving(event))                       {
      event->accept()                            ;
      moving = false                             ;
      QTreeView::mouseReleaseEvent(event)      ;
    }                                            ;
  }                                              ;
  if (moving) QTreeView::mouseMoveEvent(event) ;
}

void N::TreeView::mouseReleaseEvent(QMouseEvent * event)
{
  if (allowDrag(dragDropMode())) dragEnd(event) ;
  if (NotNull(Drag))                            {
    Drag = NULL                                 ;
    event->accept()                             ;
  } else QTreeView::mouseReleaseEvent(event)  ;
}

void N::TreeView::closeEvent(QCloseEvent * event)
{
  if (Shutdown()) event->accept(); else
  QTreeView::closeEvent(event)      ;
}

bool N::TreeView::Shutdown(void)
{
  emit Leave ( this ) ;
  return true         ;
}

void N::TreeView::Configure(void)
{
  setAttribute                 ( Qt::WA_InputMethodEnabled ) ;
  setDragDropMode              ( DragDrop                  ) ;
  setRootIsDecorated           ( true                      ) ;
  setAlternatingRowColors      ( true                      ) ;
  setHorizontalScrollBarPolicy ( Qt::ScrollBarAsNeeded     ) ;
  setVerticalScrollBarPolicy   ( Qt::ScrollBarAsNeeded     ) ;
  addConnector  ( "Commando"                                 ,
                  Commando , SIGNAL ( timeout      ( ) )     ,
                  this     , SLOT   ( DropCommands ( ) )   ) ;
  onlyConnector ( "Commando"                               ) ;
  ////////////////////////////////////////////////////////////
  if ( NotNull ( plan ) )                                    {
    Data . Controller = & ( plan->canContinue )              ;
  }                                                          ;
}

bool N::TreeView::Relocation(void)
{
  return false ;
}

bool N::TreeView::Menu(QPoint pos)
{ Q_UNUSED ( pos ) ;
  return false     ;
}

bool N::TreeView::acceptDrop(QWidget * source,const QMimeData * mime)
{ Q_UNUSED ( source ) ;
  Q_UNUSED ( mime   ) ;
  return false        ;
}

bool N::TreeView::dropNew(QWidget * source,const QMimeData * mime,QPoint pos)
{ Q_UNUSED ( source ) ;
  Q_UNUSED ( mime   ) ;
  Q_UNUSED ( pos    ) ;
  return true         ;
}

bool N::TreeView::dropMoving(QWidget * source,const QMimeData * mime,QPoint pos)
{ Q_UNUSED ( source ) ;
  Q_UNUSED ( mime   ) ;
  Q_UNUSED ( pos    ) ;
  return true         ;
}

bool N::TreeView::dropAppend(QWidget * source,const QMimeData * mime,QPoint pos)
{
  return dropItems ( source , mime , pos ) ;
}

void N::TreeView::CopyToClipboard(void)
{
}

void N::TreeView::SelectNone(void)
{
}

void N::TreeView::SelectAll(void)
{
}

void N::TreeView::setFont(void)
{
  changeFont ( ) ;
}

bool N::TreeView::dropFont(QWidget * source,QPointF pos,const SUID font)
{ Q_UNUSED           ( source               ) ;
  Q_UNUSED           ( pos                  ) ;
  nKickOut           ( IsNull(plan) , false ) ;
  Font            f                          ;
  GraphicsManager GM ( plan                 ) ;
  EnterSQL           ( SC , plan->sql       ) ;
    f = GM.GetFont   ( SC , font            ) ;
  LeaveSQL           ( SC , plan->sql       ) ;
  assignFont         ( f                    ) ;
  return true                                 ;
}

bool N::TreeView::dropPen(QWidget * source,QPointF pos,const SUID pen)
{ Q_UNUSED           ( source               ) ;
  Q_UNUSED           ( pos                  ) ;
  nKickOut           ( IsNull(plan) , false ) ;
  Pen             p                           ;
  GraphicsManager GM ( plan                 ) ;
  EnterSQL           ( SC , plan->sql       ) ;
    p = GM.GetPen    ( SC , pen             ) ;
  LeaveSQL           ( SC , plan->sql       ) ;
  assignPen          ( p                    ) ;
  return true                                 ;
}

bool N::TreeView::dropBrush(QWidget * source,QPointF pos,const SUID brush)
{ Q_UNUSED           ( source               ) ;
  Q_UNUSED           ( pos                  ) ;
  nKickOut           ( IsNull(plan) , false ) ;
  Brush           b                           ;
  GraphicsManager GM ( plan                 ) ;
  EnterSQL           ( SC , plan->sql       ) ;
    b = GM.GetBrush  ( SC , brush           ) ;
  LeaveSQL           ( SC , plan->sql       ) ;
  assignBrush        ( b                    ) ;
  return true                                 ;
}

void N::TreeView::assignFont(Font & f)
{
  QTreeView::setFont ( f )    ;
}

void N::TreeView::assignPen(Pen & p)
{ Q_UNUSED ( p ) ;
}

void N::TreeView::assignBrush(Brush & brush)
{
  QBrush   B   = brush                            ;
  QPalette P   = palette (                      ) ;
  P . setBrush           ( QPalette::Base , B   ) ;
  setPalette             ( P                    ) ;
}

void N::TreeView::DropCommands(void)
{
  LaunchCommands ( ) ;
}
