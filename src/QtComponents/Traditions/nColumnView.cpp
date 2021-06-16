#include <qtcomponents.h>

N::ColumnView:: ColumnView  ( QWidget * parent,Plan * p     )
              : QColumnView (           parent              )
              , VirtualGui  (           this  ,       p     )
              , Thread      (           0     ,       false )
{
  WidgetClass                     ;
  addIntoWidget ( parent , this ) ;
  Configure     (               ) ;
}

N::ColumnView::~ColumnView (void)
{
}

void N::ColumnView::paintEvent(QPaintEvent * event)
{
  nIsolatePainter ( QColumnView ) ;
}

void N::ColumnView::focusInEvent(QFocusEvent * event)
{
  if (!focusIn (event)) QColumnView::focusInEvent (event) ;
}

void N::ColumnView::focusOutEvent(QFocusEvent * event)
{
  if (!focusOut(event)) QColumnView::focusOutEvent(event) ;
}

void N::ColumnView::closeEvent(QCloseEvent * event)
{
  if (Shutdown()) event->accept()     ;
  else QColumnView::closeEvent(event) ;
}

void N::ColumnView::resizeEvent(QResizeEvent * event)
{
  if (Relocation()) event->accept();
  else QColumnView::resizeEvent(event);
}

void N::ColumnView::contextMenuEvent(QContextMenuEvent * event)
{
  if (Menu(event->pos())) event->accept(); else
  QColumnView::contextMenuEvent(event);
}

void N::ColumnView::dragEnterEvent(QDragEnterEvent * event)
{
  if (allowDrop(dragDropMode()) && dragEnter(event)) event->acceptProposedAction() ; else {
    if (PassDragDrop) QColumnView::dragEnterEvent(event);
    else event->ignore() ;
  };
}

void N::ColumnView::dragLeaveEvent(QDragLeaveEvent * event)
{
  if (removeDrop()) event->accept() ; else               {
    if (PassDragDrop) QColumnView::dragLeaveEvent(event) ;
    else event->ignore()                                 ;
  }                                                      ;
}

void N::ColumnView::dragMoveEvent(QDragMoveEvent * event)
{
  if (allowDrop(dragDropMode()) && dragMove(event)) event->acceptProposedAction() ; else {
    if (PassDragDrop) QColumnView::dragMoveEvent(event);
    else event->ignore() ;
  };
}

void N::ColumnView::dropEvent(QDropEvent * event)
{
  if (allowDrop(dragDropMode()) && drop(event)) event->acceptProposedAction() ; else {
    if (PassDragDrop) QColumnView::dropEvent(event);
    else event->ignore() ;
  };
}

void N::ColumnView::mousePressEvent(QMouseEvent * event)
{
  if (allowDrag(dragDropMode())) dragStart(event) ;
  QColumnView::mousePressEvent(event)             ;
}

void N::ColumnView::mouseMoveEvent(QMouseEvent * event)
{
  bool moving = true                             ;
  if (allowDrag(dragDropMode()))                 {
    if (dragMoving(event))                       {
      event->accept()                            ;
      moving = false                             ;
      QColumnView::mouseReleaseEvent(event)      ;
    }                                            ;
  }                                              ;
  if (moving) QColumnView::mouseMoveEvent(event) ;
}

void N::ColumnView::mouseReleaseEvent(QMouseEvent * event)
{
  if (allowDrag(dragDropMode())) dragEnd(event) ;
  if (NotNull(Drag))                            {
    Drag = NULL                                 ;
    event->accept()                             ;
  } else QColumnView::mouseReleaseEvent(event)  ;
}

bool N::ColumnView::Shutdown(void)
{
  emit Leave ( this ) ;
  return true         ;
}

bool N::ColumnView::acceptDrop(QWidget * source,const QMimeData * mime)
{ Q_UNUSED ( source ) ;
  Q_UNUSED ( mime   ) ;
  return false        ;
}

bool N::ColumnView::dropNew(QWidget * source,const QMimeData * mime,QPoint pos)
{ Q_UNUSED ( source ) ;
  Q_UNUSED ( mime   ) ;
  Q_UNUSED ( pos    ) ;
  return true         ;
}

bool N::ColumnView::dropMoving(QWidget * source,const QMimeData * mime,QPoint pos)
{ Q_UNUSED ( source ) ;
  Q_UNUSED ( mime   ) ;
  Q_UNUSED ( pos    ) ;
  return true         ;
}

bool N::ColumnView::dropAppend(QWidget * source,const QMimeData * mime,QPoint pos)
{
  return dropItems ( source , mime , pos ) ;
}

bool N::ColumnView::event(QEvent * event)
{
  if (permitGesture() && gestureEvent(event)) return true ;
  return QColumnView::event(event)                        ;
}

void N::ColumnView::Configure(void)
{
  setAttribute                 ( Qt::WA_InputMethodEnabled ) ;
  setAcceptDrops               ( true                      ) ;
  setDragDropMode              ( DragDrop                  ) ;
  setHorizontalScrollBarPolicy ( Qt::ScrollBarAsNeeded     ) ;
  setVerticalScrollBarPolicy   ( Qt::ScrollBarAsNeeded     ) ;
  addConnector  ( "Commando"                                 ,
                  Commando                                   ,
                  SIGNAL ( timeout      ( ) )                ,
                  this                                       ,
                  SLOT   ( DropCommands ( ) )              ) ;
  onlyConnector ( "Commando"                               ) ;
  ////////////////////////////////////////////////////////////
  if ( NotNull ( plan ) )                                    {
    Data . Controller = & ( plan->canContinue )              ;
  }                                                          ;
}

bool N::ColumnView::Relocation(void)
{
  return false ;
}

bool N::ColumnView::Menu(QPoint pos)
{
  emit ItemMenu ( this , pos ) ;
  return false                 ;
}

void N::ColumnView::CopyToClipboard(void)
{
}

void N::ColumnView::SelectNone(void)
{
}

void N::ColumnView::SelectAll(void)
{
}

void N::ColumnView::setFont(void)
{
  changeFont ( ) ;
}

bool N::ColumnView::dropFont(QWidget * source,QPointF pos,const SUID font)
{ Q_UNUSED           ( source               ) ;
  Q_UNUSED           ( pos                  ) ;
  nKickOut           ( IsNull(plan) , false ) ;
  Font            f                           ;
  GraphicsManager GM ( plan                 ) ;
  EnterSQL           ( SC , plan->sql       ) ;
    f = GM.GetFont   ( SC , font            ) ;
  LeaveSQL           ( SC , plan->sql       ) ;
  assignFont         ( f                    ) ;
  return true                                 ;
}

bool N::ColumnView::dropPen(QWidget * source,QPointF pos,const SUID pen)
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

bool N::ColumnView::dropBrush(QWidget * source,QPointF pos,const SUID brush)
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

void N::ColumnView::assignFont(Font & f)
{
  QColumnView::setFont ( f ) ;
}

void N::ColumnView::assignPen(Pen & p)
{ Q_UNUSED ( p ) ;
}

void N::ColumnView::assignBrush(Brush & brush)
{
  QBrush   B   = brush                          ;
  QPalette P   = palette (                    ) ;
  P . setBrush           ( QPalette::Base , B ) ;
  setPalette             ( P                  ) ;
}

void N::ColumnView::DropCommands(void)
{
  LaunchCommands ( ) ;
}
