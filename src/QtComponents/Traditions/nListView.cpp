#include <qtcomponents.h>

N::ListView:: ListView   ( QWidget * parent,Plan * p     )
            : QListView  (           parent              )
            , VirtualGui (           this  ,       p     )
            , Thread     (           0     ,       false )
{
  WidgetClass                     ;
  addIntoWidget ( parent , this ) ;
  Configure     (               ) ;
}

N::ListView::~ListView (void)
{
}

bool N::ListView::event(QEvent * event)
{
  if (permitGesture() && gestureEvent(event)) return true ;
  return QListView::event(event)                        ;
}

void N::ListView::paintEvent(QPaintEvent * event)
{
  nIsolatePainter(QListView) ;
}

void N::ListView::focusInEvent(QFocusEvent * event)
{
  if (!focusIn (event)) QListView::focusInEvent (event) ;
}

void N::ListView::focusOutEvent(QFocusEvent * event)
{
  if (!focusOut(event)) QListView::focusOutEvent(event) ;
}

void N::ListView::closeEvent(QCloseEvent * event)
{
  if (Shutdown()) event->accept()     ;
  else QListView::closeEvent(event) ;
}

void N::ListView::resizeEvent(QResizeEvent * event)
{
  if (Relocation()) event->accept();
  else QListView::resizeEvent(event);
}

void N::ListView::contextMenuEvent(QContextMenuEvent * event)
{
  if (Menu(event->pos())) event->accept(); else
  QListView::contextMenuEvent(event);
}

void N::ListView::dragEnterEvent(QDragEnterEvent * event)
{
  if (allowDrop(dragDropMode()) && dragEnter(event)) event->acceptProposedAction() ; else {
    if (PassDragDrop) QListView::dragEnterEvent(event);
    else event->ignore() ;
  };
}

void N::ListView::dragLeaveEvent(QDragLeaveEvent * event)
{
  if (removeDrop()) event->accept() ; else {
    if (PassDragDrop) QListView::dragLeaveEvent(event);
    else event->ignore() ;
  };
}

void N::ListView::dragMoveEvent(QDragMoveEvent * event)
{
  if (allowDrop(dragDropMode()) && dragMove(event)) event->acceptProposedAction() ; else {
    if (PassDragDrop) QListView::dragMoveEvent(event);
    else event->ignore() ;
  };
}

void N::ListView::dropEvent(QDropEvent * event)
{
  if (allowDrop(dragDropMode()) && drop(event)) event->acceptProposedAction() ; else {
    if (PassDragDrop) QListView::dropEvent(event);
    else event->ignore() ;
  };
}

void N::ListView::mousePressEvent(QMouseEvent * event)
{
  if (allowDrag(dragDropMode())) dragStart(event) ;
  QListView::mousePressEvent(event)             ;
}

void N::ListView::mouseMoveEvent(QMouseEvent * event)
{
  bool moving = true                             ;
  if (allowDrag(dragDropMode()))                 {
    if (dragMoving(event))                       {
      event->accept()                            ;
      moving = false                             ;
      QListView::mouseReleaseEvent(event)      ;
    }                                            ;
  }                                              ;
  if (moving) QListView::mouseMoveEvent(event) ;
}

void N::ListView::mouseReleaseEvent(QMouseEvent * event)
{
  if (allowDrag(dragDropMode())) dragEnd(event) ;
  if (NotNull(Drag))                            {
    Drag = NULL                                 ;
    event->accept()                             ;
  } else QListView::mouseReleaseEvent(event)  ;
}

bool N::ListView::Shutdown(void)
{
  emit Leave ( this ) ;
  return true         ;
}

bool N::ListView::acceptDrop(QWidget * source,const QMimeData * mime)
{ Q_UNUSED ( source ) ;
  Q_UNUSED ( mime   ) ;
  return false        ;
}

bool N::ListView::dropNew(QWidget * source,const QMimeData * mime,QPoint pos)
{ Q_UNUSED ( source ) ;
  Q_UNUSED ( mime   ) ;
  Q_UNUSED ( pos    ) ;
  return true         ;
}

bool N::ListView::dropMoving(QWidget * source,const QMimeData * mime,QPoint pos)
{ Q_UNUSED ( source ) ;
  Q_UNUSED ( mime   ) ;
  Q_UNUSED ( pos    ) ;
  return true         ;
}

bool N::ListView::dropAppend(QWidget * source,const QMimeData * mime,QPoint pos)
{
  return dropItems ( source , mime , pos ) ;
}

void N::ListView::Configure(void)
{
  setAttribute                 ( Qt::WA_InputMethodEnabled   ) ;
  setAcceptDrops               ( true                        ) ;
  setDragDropMode              ( DragDrop                    ) ;
  setHorizontalScrollBarPolicy ( Qt::ScrollBarAsNeeded       ) ;
  setVerticalScrollBarPolicy   ( Qt::ScrollBarAsNeeded       ) ;
  addConnector                 ( "Commando"                    ,
                                 Commando                      ,
                                 SIGNAL ( timeout      ( ) )   ,
                                 this                          ,
                                 SLOT   ( DropCommands ( ) ) ) ;
  onlyConnector                ( "Commando"                  ) ;
  //////////////////////////////////////////////////////////////
  if ( NotNull ( plan ) )                                      {
    Data . Controller = & ( plan->canContinue )                ;
  }                                                            ;
}

bool N::ListView::Relocation(void)
{
  return false ;
}

bool N::ListView::Menu(QPoint pos)
{
  emit ItemMenu ( this , pos ) ;
  return false                 ;
}

void N::ListView::CopyToClipboard(void)
{
}

void N::ListView::SelectNone(void)
{
}

void N::ListView::SelectAll(void)
{
}

void N::ListView::setFont(void)
{
  changeFont ( ) ;
}

bool N::ListView::dropFont(QWidget * source,QPointF pos,const SUID font)
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

bool N::ListView::dropPen(QWidget * source,QPointF pos,const SUID pen)
{ Q_UNUSED            ( source               ) ;
  Q_UNUSED            ( pos                  ) ;
  nKickOut            ( IsNull(plan) , false ) ;
  Pen             p                            ;
  GraphicsManager GM  ( plan                 ) ;
  EnterSQL            ( SC , plan->sql       ) ;
    p = GM.GetPen     ( SC , pen             ) ;
  LeaveSQL            ( SC , plan->sql       ) ;
  assignPen           ( p                    ) ;
  return true                                  ;
}

bool N::ListView::dropBrush(QWidget * source,QPointF pos,const SUID brush)
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

void N::ListView::assignFont(Font & f)
{
  QListView::setFont ( f ) ;
}

void N::ListView::assignPen(Pen & p)
{ Q_UNUSED ( p ) ;
}

void N::ListView::assignBrush(Brush & brush)
{
  QBrush   B   = brush                          ;
  QPalette P   = palette (                    ) ;
  P . setBrush           ( QPalette::Base , B ) ;
  setPalette             ( P                  ) ;
}

void N::ListView::DropCommands(void)
{
  LaunchCommands ( ) ;
}
