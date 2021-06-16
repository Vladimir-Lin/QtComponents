#include <qtcomponents.h>

N::TableWidget:: TableWidget  ( QWidget * parent,Plan * p     )
               : QTableWidget (           parent              )
               , VirtualGui   (           this  ,       p     )
               , Thread       (           0     ,       false )
{
  WidgetClass                     ;
  addIntoWidget ( parent , this ) ;
  Configure     (               ) ;
}

N::TableWidget::~TableWidget (void)
{
}

void N::TableWidget::ThreadEvent(void)
{
  plan -> processEvents ( ) ;
}

void N::TableWidget::AtBusy(void)
{
  plan -> StartBusy     ( ) ;
}

void N::TableWidget::OnRelax(void)
{
  plan -> StopBusy      ( ) ;
}

void N::TableWidget::setWaitCursor(void)
{
  setCursor ( Qt::WaitCursor ) ;
}

void N::TableWidget::setArrowCursor(void)
{
  setCursor ( Qt::ArrowCursor ) ;
}

bool N::TableWidget::Bustle(void)
{
  Mutex . lock           ( ) ;
  emit assignWaitCursor  ( ) ;
  return true                ;
}

bool N::TableWidget::Vacancy(void)
{
  emit assignArrowCursor ( ) ;
  Mutex . unlock         ( ) ;
  return true                ;
}

QSize N::TableWidget::sizeHint(void) const
{
  return SizeSuggestion ( QSize ( 640 , 480 ) ) ;
}

void N::TableWidget::setEnabling(bool enable)
{
  setEnabled ( enable ) ;
}

void N::TableWidget::writeToolTip(QString tooltip)
{
  setToolTip ( tooltip ) ;
}

void N::TableWidget::writeTitle(QString title)
{
  setWindowTitle ( title )                                           ;
  ////////////////////////////////////////////////////////////////////
  QMdiSubWindow * msw = qobject_cast<QMdiSubWindow *> ( parent ( ) ) ;
  if ( NULL != msw ) msw -> setWindowTitle ( title )                 ;
}

void N::TableWidget::cleanItems(void)
{
  clear ( ) ;
}

void N::TableWidget::changeColumns(int c)
{
  setColumnCount ( c ) ;
}

void N::TableWidget::changeRows(int r)
{
  setRowCount ( r ) ;
}

void N::TableWidget::assignColumns(int c)
{
  if ( columnCount ( ) == c ) return ;
  emit emitColumns ( c )             ;
  while ( c != columnCount ( ) )     {
    Time::skip ( 10 )                ;
  }                                  ;
}

void N::TableWidget::assignRows(int r)
{
  if ( rowCount ( ) == r ) return ;
  emit emitRows ( r )             ;
  while ( r != rowCount ( ) )     {
    Time::skip ( 10 )             ;
  }                               ;
}

bool N::TableWidget::event(QEvent * event)
{
  if (permitGesture() && gestureEvent(event)) return true ;
  return QTableWidget::event(event)                        ;
}

void N::TableWidget::setDesignable(bool gui)
{
  designable = gui                                      ;
  if (designable)                                       {
    setWindowTitle(tr("N::TableWidget (Editing mode)")) ;
  }                                                     ;
}

void N::TableWidget::paintEvent(QPaintEvent * event)
{
  nIsolatePainter(QTableWidget) ;
}

void N::TableWidget::focusInEvent(QFocusEvent * event)
{
  if (!focusIn (event)) QTableWidget::focusInEvent (event) ;
}

void N::TableWidget::focusOutEvent(QFocusEvent * event)
{
  if (!focusOut(event)) QTableWidget::focusOutEvent(event) ;
}

void N::TableWidget::resizeEvent(QResizeEvent * event)
{
  if (Relocation()) event->accept();
  else QTableWidget::resizeEvent(event);
}

void N::TableWidget::contextMenuEvent(QContextMenuEvent * event)
{
  if (Menu(event->pos())) event->accept()    ;
  else QTableWidget::contextMenuEvent(event) ;
}

void N::TableWidget::dragEnterEvent(QDragEnterEvent * event)
{
  if (allowDrop(dragDropMode()) && dragEnter(event)) event->acceptProposedAction() ;
  else QTableWidget::dragEnterEvent(event);
}

void N::TableWidget::dragLeaveEvent(QDragLeaveEvent * event)
{
  if (removeDrop()) event->accept() ;
  else QTableWidget::dragLeaveEvent(event);
}

void N::TableWidget::dragMoveEvent(QDragMoveEvent * event)
{
  if (allowDrop(dragDropMode()) && dragMove(event)) event->acceptProposedAction() ;
  else QTableWidget::dragMoveEvent(event);
}

void N::TableWidget::dropEvent(QDropEvent * event)
{
  if (allowDrop(dragDropMode()) && drop(event)) event->acceptProposedAction() ;
  else QTableWidget::dropEvent(event);
}

void N::TableWidget::mousePressEvent(QMouseEvent * event)
{
  if (allowDrag(dragDropMode()) && dragStart(event)) event->accept() ;
  else QTableWidget::mousePressEvent(event);
}

void N::TableWidget::mouseMoveEvent(QMouseEvent * event)
{
  if (allowDrag(dragDropMode()) && dragMoving(event)) event->accept() ;
  else QTableWidget::mouseMoveEvent(event);
}

void N::TableWidget::mouseReleaseEvent(QMouseEvent * event)
{
  if (allowDrag(dragDropMode()) && dragEnd(event)) event->accept() ;
  else QTableWidget::mouseReleaseEvent(event);
}

void N::TableWidget::closeEvent(QCloseEvent * event)
{
  if (Shutdown()) event->accept();
  else QTableWidget::closeEvent(event);
}

void N::TableWidget::Configure(void)
{
  setAttribute  ( Qt::WA_InputMethodEnabled )                                ;
  ////////////////////////////////////////////////////////////////////////////
  nConnect ( this , SIGNAL ( putItem      (int,int,QTableWidgetItem*) )      ,
             this , SLOT   ( assignItem   (int,int,QTableWidgetItem*) )    ) ;
  nConnect ( this , SIGNAL ( RowsFit                () )                     ,
             this , SLOT   ( resizeRowsToContents   () )                   ) ;
  nConnect ( this , SIGNAL ( ColumnsFit             () )                     ,
             this , SLOT   ( resizeColumnsToContents() )                   ) ;
  addConnector  ( "Commando"                                                 ,
                  Commando                                                   ,
                  SIGNAL ( timeout      ( ) )                                ,
                  this                                                       ,
                  SLOT   ( DropCommands ( ) )                              ) ;
  addConnector  ( "ToolTip"                                                  ,
                  SIGNAL ( assignToolTip  (QString) )                        ,
                  SLOT   ( writeToolTip   (QString) )                      ) ;
  addConnector  ( "WindowTitle"                                              ,
                  SIGNAL ( assignWindowTitle (QString) )                     ,
                  SLOT   ( writeTitle        (QString) )                   ) ;
  addConnector  ( "Enabling"                                                 ,
                  SIGNAL ( assignEnabling (bool) )                           ,
                  SLOT   ( setEnabling    (bool) )                         ) ;
  addConnector  ( "Modification"                                             ,
                  SIGNAL ( assignModified    (bool) )                        ,
                  SLOT   ( setWindowModified (bool) )                      ) ;
  addConnector  ( "Busy"                                                     ,
                  SIGNAL( OnBusy          (   ) )                            ,
                  SLOT  ( AtBusy          (   ) )                          ) ;
  addConnector  ( "Relax"                                                    ,
                  SIGNAL( GoRelax         (   ) )                            ,
                  SLOT  ( OnRelax         (   ) )                          ) ;
  addConnector  ( "WaitCursor"                                               ,
                  SIGNAL ( assignWaitCursor  ( ) )                           ,
                  SLOT   ( setWaitCursor     ( ) )                         ) ;
  addConnector  ( "ArrowCursor"                                              ,
                  SIGNAL ( assignArrowCursor ( ) )                           ,
                  SLOT   ( setArrowCursor    ( ) )                         ) ;
  addConnector  ( "Cleanup"                                                  ,
                  SIGNAL( clearItems         ( ) )                           ,
                  SLOT  ( cleanItems         ( ) )                         ) ;
  addConnector  ( "Columns"                                                  ,
                  SIGNAL( emitColumns        (int) )                         ,
                  SLOT  ( changeColumns      (int) )                       ) ;
  addConnector  ( "Rows"                                                     ,
                  SIGNAL( emitRows           (int) )                         ,
                  SLOT  ( changeRows         (int) )                       ) ;
  ////////////////////////////////////////////////////////////////////////////
  onlyConnector ( "ToolTip"                                                ) ;
  onlyConnector ( "WindowTitle"                                            ) ;
  onlyConnector ( "Busy"                                                   ) ;
  onlyConnector ( "Relax"                                                  ) ;
  onlyConnector ( "Enabling"                                               ) ;
  onlyConnector ( "Modification"                                           ) ;
  onlyConnector ( "WaitCursor"                                             ) ;
  onlyConnector ( "ArrowCursor"                                            ) ;
  onlyConnector ( "Cleanup"                                                ) ;
  onlyConnector ( "Columns"                                                ) ;
  onlyConnector ( "Rows"                                                   ) ;
  onlyConnector ( "Commando"                                               ) ;
  ////////////////////////////////////////////////////////////////////////////
  if ( NotNull ( plan ) )                                                    {
    Data . Controller = & ( plan->canContinue )                              ;
  }                                                                          ;
}

bool N::TableWidget::Shutdown(void)
{
  emit Leave ( this ) ;
  return true         ;
}

bool N::TableWidget::Relocation(void)
{
  return false ;
}

void N::TableWidget::setFont(void)
{
  changeFont ( ) ;
}

bool N::TableWidget::Menu(QPoint pos)
{ Q_UNUSED ( pos ) ;
  return true      ;
}

void N::TableWidget::DropCommands(void)
{
  LaunchCommands ( ) ;
}

N::TableWidgetItems N::TableWidget::horizontalHeaderItems(void)
{
  N::TableWidgetItems items          ;
  for (int i=0;i<columnCount();i++)  {
    items << horizontalHeaderItem(i) ;
  }                                  ;
  return items                       ;
}

N::TableWidgetItems N::TableWidget::verticalHeaderItems(void)
{
  N::TableWidgetItems items        ;
  for (int i=0;i<rowCount();i++)   {
    items << verticalHeaderItem(i) ;
  }                                ;
  return items                     ;
}

N::TableWidgetItems N::TableWidget::allItems(void)
{
  TableWidgetItems items              ;
  for (int i=0;i<rowCount();i++)      {
    for (int j=0;j<columnCount();j++) {
      QTableWidgetItem * it           ;
      it = item(i,j)                  ;
      if (NotNull(it)) items << it    ;
    }                                 ;
  }                                   ;
  return items                        ;
}

void N::TableWidget::setFont(TableWidgetItems & items,Font & font)
{
  QFont f = font.toQFont()          ;
  for (int i=0;i<items.count();i++) {
    items[i]->setFont(f)            ;
  }                                 ;
}

void N::TableWidget::setFont(TableWidgetItems & items,int FontId)
{
  if (!plan->fonts.contains(FontId)) return ;
  Font f = plan->fonts[FontId]              ;
  setFont ( items , f )                     ;
}

void N::TableWidget::setFont(QTableWidgetItem * item,Font & font)
{
  QFont f = font.toQFont( ) ;
  item -> setFont ( f )     ;
}

void N::TableWidget::setFont(QTableWidgetItem * item,int FontId)
{
  if (!plan->fonts.contains(FontId)) return ;
  Font f = plan->fonts[FontId]              ;
  setFont ( item , f )                      ;
}

void N::TableWidget::assignItem(int row,int column,QTableWidgetItem * item)
{
  setItem ( row , column , item ) ;
}

void N::TableWidget::CopyToClipboard(void)
{
  QStringList S                         ;
  ///////////////////////////////////////
  for (int i=0;i<rowCount();i++)        {
    QStringList L                       ;
    L . clear ( )                       ;
    for (int j=0;j<columnCount();j++)   {
      QTableWidgetItem * it             ;
      it = item(i,j)                    ;
      if (NotNull(it))                  {
        L << it->text()                 ;
      } else L << ""                    ;
    }                                   ;
    S << L.join("\t")                   ;
  }                                     ;
  ///////////////////////////////////////
  if (S.count()<=0) return              ;
  ///////////////////////////////////////
  QString m = S.join("\n")              ;
  nSetClipboard (m)                     ;
  ///////////////////////////////////////
  m = tr("duplicate text to clipboard") ;
  plan->Talk(m)                         ;
}

void N::TableWidget::SelectNone(void)
{
  TableWidgetItems items = allItems() ;
  for (int i=0;i<items.count();i++)   {
    items[i]->setSelected ( false )   ;
  }                                   ;
}

void N::TableWidget::SelectAll(void)
{
  TableWidgetItems items = allItems() ;
  for (int i=0;i<items.count();i++)   {
    items[i]->setSelected ( true  )   ;
  }                                   ;
}
