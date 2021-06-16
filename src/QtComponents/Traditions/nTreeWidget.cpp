#include <qtcomponents.h>

N::TreeWidget:: TreeWidget      ( QWidget * parent , Plan * p     )
              : QTreeWidget     (           parent                )
              , VirtualGui      (           this   ,        p     )
              , Thread          (           0      ,        false )
              , CommandSequence ( new QTimer ( this )             )
              , ItemEditing     ( NULL                            )
              , ItemWidget      ( NULL                            )
              , ItemColumn      ( -1                              )
              , InheritClass    ( ""                              )
              , dbClicked       ( false                           )
              , Commanding      ( false                           )
{
  WidgetClass                           ;
  addIntoWidget ( parent , this )       ;
  Configure     (               )       ;
  QStringList headers = defaultHeader() ;
  if (headers.count()>0)                {
    setColumnCount  (headers.count())   ;
    setHeaderLabels (headers        )   ;
  }                                     ;
}

N::TreeWidget::~TreeWidget (void)
{
}

void N::TreeWidget::ThreadEvent(void)
{
  plan -> processEvents ( ) ;
}

void N::TreeWidget::AtBusy(void)
{
  plan->StartBusy ( ) ;
}

void N::TreeWidget::OnRelax(void)
{
  plan->StopBusy ( ) ;
}

void N::TreeWidget::setWaitCursor(void)
{
  setCursor ( Qt::WaitCursor ) ;
}

void N::TreeWidget::setArrowCursor(void)
{
  setCursor ( Qt::ArrowCursor ) ;
}

bool N::TreeWidget::Bustle(void)
{
  Mutex . lock           ( ) ;
  emit assignWaitCursor  ( ) ;
  return true                ;
}

bool N::TreeWidget::Vacancy(void)
{
  emit assignArrowCursor ( ) ;
  Mutex . unlock         ( ) ;
  return true                ;
}

void N::TreeWidget::setEnabling(bool enable)
{
  setEnabled ( enable ) ;
}

void N::TreeWidget::writeSortingEnabled(bool enable)
{
  setSortingEnabled ( enable ) ;
}

void N::TreeWidget::writeToolTip(QString tooltip)
{
  setToolTip ( tooltip ) ;
}

void N::TreeWidget::writeTitle(QString title)
{
  setWindowTitle ( title )                                           ;
  ////////////////////////////////////////////////////////////////////
  QMdiSubWindow * msw = qobject_cast<QMdiSubWindow *> ( parent ( ) ) ;
  if ( NULL != msw ) msw -> setWindowTitle ( title )                 ;
}

void N::TreeWidget::cleanItems(void)
{
  clear ( ) ;
}

bool N::TreeWidget::event(QEvent * event)
{
  if (permitGesture() && gestureEvent(event)) return true ;
  return QTreeWidget::event(event)                        ;
}

bool N::TreeWidget::acceptTapHold(QTapAndHoldGesture * gesture)
{
  if ( !allowGesture ) return false            ;
  QTreeWidgetItem * item   = currentItem()     ;
  if ( IsNull(item)  ) return false            ;
  QPoint pos = gesture->position().toPoint()   ;
  int               column = columnAt(pos.x()) ;
  if ( column < 0    ) return false            ;
  allowGesture = false                         ;
  doubleClicked ( item , column )              ;
  return true                                  ;
}

bool N::TreeWidget::acceptPan(QPanGesture * gesture)
{ Q_UNUSED ( gesture )            ;
  if (!allowGesture) return false ;
  allowGesture = false            ;
  Menu ( QPoint(0,0) )            ;
  return true                     ;
}

void N::TreeWidget::setGui(QWidget * widget)
{
  Gui = widget                         ;
  Commando        -> setParent ( Gui ) ;
  CommandSequence -> setParent ( Gui ) ;
}

void N::TreeWidget::setDesignable(bool gui)
{
  designable = gui                                     ;
  if (gui)                                             {
    setWindowTitle(tr("N::TreeWidget (Editing mode)")) ;
  }                                                    ;
}

QSize N::TreeWidget::SuitableSize(void)
{
  return QSize ( 0 , 0 ) ;
}

void N::TreeWidget::SuitableColumns(void)
{
  nFullLoop (i,columnCount()) {
    resizeColumnToContents(i) ;
  }                           ;
}

void N::TreeWidget::SuitableColumns(int columns)
{
  nFullLoop (i,columns)       {
    resizeColumnToContents(i) ;
  }                           ;
}

void N::TreeWidget::AutoResize(void)
{
  SuitableColumns ( ) ;
  repaint         ( ) ;
}

QSize N::TreeWidget::sizeHint(void) const
{
  return SizeSuggestion ( QSize ( 400 , 320 ) ) ;
}

QStringList N::TreeWidget::defaultHeader(void)
{
  QStringList sl;
  return sl ;
}

QStringList N::TreeWidget::columnStrings(int column)
{
  QStringList S                        ;
  nFullLoop (i,topLevelItemCount())    {
    S << topLevelItem(i)->text(column) ;
  }                                    ;
  return S                             ;
}

CUIDs N::TreeWidget::columnWidths(void)
{
  CUIDs columns               ;
  nFullLoop (i,columnCount()) {
    columns << columnWidth(i) ;
  }                           ;
  return columns              ;
}

void N::TreeWidget::setColumnWidths(CUIDs & widths)
{
  nFullLoop (i,widths.count())  {
    setColumnWidth(i,widths[i]) ;
  }                             ;
}

bool N::TreeWidget::takeItem(QTreeWidgetItem * item)
{
  int index = indexOfTopLevelItem ( item ) ;
  nKickOut ( index < 0 , false )           ;
  takeTopLevelItem ( index )               ;
  return true                              ;
}

void N::TreeWidget::reportItems(void)
{
  QString m                             ;
  int     total                         ;
  total = topLevelItemCount   (       ) ;
  m = tr ( "%1 items" ) . arg ( total ) ;
  emit assignToolTip          ( m     ) ;
  plan -> Talk                ( m     ) ;
}

bool N::TreeWidget::holdItem(void)
{
  QTreeWidgetItem * item = currentItem () ;
  return NotNull ( item )                 ;
}

bool N::TreeWidget::holdItems(void)
{
  QList<QTreeWidgetItem *> Items ;
  Items = selectedItems()        ;
  return ( Items.count()>0 )     ;
}

void N::TreeWidget::assignItems(QTreeWidgetItem * item,QStringList & S)
{
  for (int i=0;i<S.count();i++) item->setText(i,S[i]) ;
}

void N::TreeWidget::installHeader(void)
{
  HeaderView * nhv = new HeaderView(Qt::Horizontal,this,plan)  ;
  setHeader(nhv)                                               ;
  nConnect(nhv ,SIGNAL(HeaderMenu(QHeaderView*,QPoint))        ,
           this,SLOT  (HeaderMenu(QHeaderView*,QPoint))      ) ;
}

void N::TreeWidget::HeaderMenu(QHeaderView * view,QPoint pos)
{
}

void N::TreeWidget::assignHeaderItems(QTreeWidgetItem * head)
{
  setAllAlignments ( head , Qt::AlignCenter ) ;
  setFont          ( head , Fonts::ListView ) ;
  setHeaderItem    ( head                   ) ;
}

void N::TreeWidget::assignHeaderItems(QStringList headers)
{
  NewTreeWidgetItem ( head )          ;
  for (int i=0;i<headers.count();i++) {
    head->setText(i,headers[i])       ;
  }                                   ;
  assignHeaderItems ( head )          ;
}

void N::TreeWidget::paintEvent(QPaintEvent * event)
{
  nIsolatePainter(QTreeWidget) ;
}

void N::TreeWidget::focusInEvent(QFocusEvent * event)
{
  if (!focusIn (event)) QTreeWidget::focusInEvent (event) ;
}

void N::TreeWidget::focusOutEvent(QFocusEvent * event)
{
  if (!focusOut(event)) QTreeWidget::focusOutEvent(event) ;
}

void N::TreeWidget::resizeEvent(QResizeEvent * event)
{
  if (Relocation()) event->accept();
  else QTreeWidget::resizeEvent(event);
}

void N::TreeWidget::contextMenuEvent(QContextMenuEvent * event)
{
  if (Menu(event->pos())) event->accept(); else
  QTreeWidget::contextMenuEvent(event);
}

void N::TreeWidget::dragEnterEvent(QDragEnterEvent * event)
{
  if (allowDrop(dragDropMode()) && dragEnter(event))     {
    event->acceptProposedAction()                        ;
  } else                                                 {
    if (PassDragDrop) QTreeWidget::dragEnterEvent(event) ;
    else event->ignore()                                 ;
  }                                                      ;
}

void N::TreeWidget::dragLeaveEvent(QDragLeaveEvent * event)
{
  if (removeDrop()) event->accept() ; else               {
    if (PassDragDrop) QTreeWidget::dragLeaveEvent(event) ;
    else event->ignore()                                 ;
  }                                                      ;
}

void N::TreeWidget::dragMoveEvent(QDragMoveEvent * event)
{
  if (allowDrop(dragDropMode()) && dragMove(event))      {
    event->acceptProposedAction()                        ;
  } else                                                 {
    if (PassDragDrop) QTreeWidget::dragMoveEvent(event)  ;
    else event->ignore()                                 ;
  }                                                      ;
}

void N::TreeWidget::dropEvent(QDropEvent * event)
{
  if (allowDrop(dragDropMode()) && drop(event))          {
    event->acceptProposedAction()                        ;
  } else                                                 {
    if (PassDragDrop) QTreeWidget::dropEvent(event)      ;
    else event->ignore()                                 ;
  }                                                      ;
}

void N::TreeWidget::mousePressEvent(QMouseEvent * event)
{
  mouseState(event)                               ;
  if (Dumping)                                    {
    event->ignore()                               ;
    return                                        ;
  }                                               ;
  if (allowDrag(dragDropMode())) dragStart(event) ;
  QTreeWidget::mousePressEvent(event)             ;
}

void N::TreeWidget::mouseMoveEvent(QMouseEvent * event)
{
  mouseState(event)                              ;
  if (Dumping)                                   {
    event->ignore()                              ;
    return                                       ;
  }                                              ;
  bool moving = true                             ;
  if (allowDrag(dragDropMode()))                 {
    if (dragMoving(event))                       {
      event->accept()                            ;
      moving = false                             ;
      QTreeWidget::mouseReleaseEvent(event)      ;
      return                                     ;
    }                                            ;
  }                                              ;
  if (moving) QTreeWidget::mouseMoveEvent(event) ;
}

void N::TreeWidget::mouseReleaseEvent(QMouseEvent * event)
{
  mouseState(event)                             ;
  if (Dumping)                                  {
    event->ignore()                             ;
    return                                      ;
  }                                             ;
  if (allowDrag(dragDropMode())) dragEnd(event) ;
  if (NotNull(Drag))                            {
    Drag = NULL                                 ;
    event->accept()                             ;
  } else                                        {
    if ( dbClicked )                            {
      dbClicked = false                         ;
      event -> ignore ( )                       ;
    } else                                      {
      QTreeWidget::mouseReleaseEvent(event)     ;
    }                                           ;
  }                                             ;
}

void N::TreeWidget::mouseDoubleClickEvent(QMouseEvent * event)
{
  if ( dbClicked )                               {
    event -> ignore ( )                          ;
    return                                       ;
  }                                              ;
  dbClicked = true                               ;
  mouseState                           ( event ) ;
  QTreeWidget :: mouseDoubleClickEvent ( event ) ;
}

void N::TreeWidget::keyPressEvent(QKeyEvent * event)
{
  keyState                     ( event ) ;
  QTreeWidget :: keyPressEvent ( event ) ;
}

void N::TreeWidget::keyReleaseEvent(QKeyEvent * event)
{
  keyState                       ( event ) ;
  QTreeWidget :: keyReleaseEvent ( event ) ;
}

void N::TreeWidget::closeEvent(QCloseEvent * event)
{
  if (Shutdown())                  {
    event->accept()                ;
  } else                           {
    QTreeWidget::closeEvent(event) ;
  }                                ;
}

bool N::TreeWidget::Shutdown(void)
{
  emit Leave ( this ) ;
  return true         ;
}

void N::TreeWidget::Configure(void)
{
  setAttribute                 ( Qt::WA_InputMethodEnabled )  ;
  setDragDropMode              ( DragDrop                  )  ;
  setRootIsDecorated           ( true                      )  ;
  setAlternatingRowColors      ( true                      )  ;
  setHorizontalScrollBarPolicy ( Qt::ScrollBarAsNeeded     )  ;
  setVerticalScrollBarPolicy   ( Qt::ScrollBarAsNeeded     )  ;
  plan            -> setFont   ( this                      )  ;
  CommandSequence -> setParent ( this                      )  ;
  setFunction   ( N::AttachDock::FunctionDocking , false   )  ;
  /////////////////////////////////////////////////////////////
  LimitValues [ 37714 ] = 300                                 ;
  /////////////////////////////////////////////////////////////
  LocalIcons  [ "UpArrow"   ] = QIcon ( ":/images/up.png"   ) ;
  LocalIcons  [ "DownArrow" ] = QIcon ( ":/images/down.png" ) ;
  /////////////////////////////////////////////////////////////
  addConnector  ( "AutoFit"                                   ,
                  SIGNAL ( AutoFit        (   ) )             ,
                  SLOT   ( AutoResize     (   ) )           ) ;
  addConnector  ( "ToolTip"                                   ,
                  SIGNAL ( assignToolTip  (QString) )         ,
                  SLOT   ( writeToolTip   (QString) )       ) ;
  addConnector  ( "WindowTitle"                               ,
                  SIGNAL ( assignWindowTitle (QString) )      ,
                  SLOT   ( writeTitle        (QString) )    ) ;
  addConnector  ( "Execute"                                   ,
                  SIGNAL( Follow          (int) )             ,
                  SLOT  ( Execute         (int) )           ) ;
  addConnector  ( "Enabling"                                  ,
                  SIGNAL ( assignEnabling (bool) )            ,
                  SLOT   ( setEnabling    (bool) )          ) ;
  addConnector  ( "Sorting"                                   ,
                  SIGNAL ( assignSortingEnabled (bool) )      ,
                  SLOT   ( writeSortingEnabled  (bool) )    ) ;
  addConnector  ( "Modification"                              ,
                  SIGNAL ( assignModified    (bool) )         ,
                  SLOT   ( setWindowModified (bool) )       ) ;
  addConnector  ( "Busy"                                      ,
                  SIGNAL( OnBusy          (   ) )             ,
                  SLOT  ( AtBusy          (   ) )           ) ;
  addConnector  ( "Relax"                                     ,
                  SIGNAL( GoRelax         (   ) )             ,
                  SLOT  ( OnRelax         (   ) )           ) ;
  addConnector  ( "WaitCursor"                                ,
                  SIGNAL ( assignWaitCursor  ( ) )            ,
                  SLOT   ( setWaitCursor     ( ) )          ) ;
  addConnector  ( "ArrowCursor"                               ,
                  SIGNAL ( assignArrowCursor ( ) )            ,
                  SLOT   ( setArrowCursor    ( ) )          ) ;
  addConnector  ( "Cleanup"                                   ,
                  SIGNAL( clearItems         ( ) )            ,
                  SLOT  ( cleanItems         ( ) )          ) ;
  addConnector  ( "Trigger"                                   ,
                  SIGNAL( TriggerCommand     ( ) )            ,
                  SLOT  ( StartCommand       ( ) )          ) ;
  addConnector  ( "Commando"                                  ,
                  Commando                                    ,
                  SIGNAL ( timeout           ( ) )            ,
                  this                                        ,
                  SLOT   ( DropCommands      ( ) )          ) ;
  addConnector  ( "Sequence"                                  ,
                  CommandSequence                             ,
                  SIGNAL ( timeout           ( ) )            ,
                  this                                        ,
                  SLOT   ( CommandHandler    ( ) )         )  ;
  /////////////////////////////////////////////////////////////
  onlyConnector ( "AutoFit"                                )  ;
  onlyConnector ( "ToolTip"                                )  ;
  onlyConnector ( "WindowTitle"                            )  ;
  onlyConnector ( "Execute"                                )  ;
  onlyConnector ( "Busy"                                   )  ;
  onlyConnector ( "Relax"                                  )  ;
  onlyConnector ( "Enabling"                               )  ;
  onlyConnector ( "Modification"                           )  ;
  onlyConnector ( "Sorting"                                )  ;
  onlyConnector ( "WaitCursor"                             )  ;
  onlyConnector ( "ArrowCursor"                            )  ;
  onlyConnector ( "Cleanup"                                )  ;
  onlyConnector ( "Commando"                               )  ;
  onlyConnector ( "Sequence"                               )  ;
  /////////////////////////////////////////////////////////////
  if ( NotNull ( plan ) )                                     {
    Data . Controller = & ( plan->canContinue )               ;
  }                                                           ;
}

bool N::TreeWidget::Relocation(void)
{
  return false ;
}

bool N::TreeWidget::acceptDrop(QWidget * source,const QMimeData * mime)
{
  return false ;
}

bool N::TreeWidget::dropNew(QWidget * source,const QMimeData * mime,QPoint pos)
{
  return true ;
}

bool N::TreeWidget::dropMoving(QWidget * source,const QMimeData * mime,QPoint pos)
{
  return true ;
}

bool N::TreeWidget::dropAppend(QWidget * source,const QMimeData * mime,QPoint pos)
{
  return dropItems ( source , mime , pos ) ;
}

void N::TreeWidget::selectLanguage (
       QWidget         * widget  ,
       QTreeWidgetItem * item    ,
       int               column  ,
       const char      * method  )
{
  int language = item->data(column,Qt::UserRole).toInt() ;
  QComboBox * combo                                      ;
  combo = new QComboBox (this)                           ;
    combo  << plan->languages                            ;
  (*combo) <= language                                   ;
  ItemEditing = item                                     ;
  ItemColumn  = column                                   ;
  ItemWidget  = combo                                    ;
  setItemWidget ( item , column , combo )                ;
  connect(widget,SIGNAL(activated(int)),this,method    ) ;
  combo -> showPopup ( )                                 ;
}

QLineEdit * N::TreeWidget::setLineEdit   (
              QTreeWidgetItem * item   ,
              int               column ,
              const char      * Signal ,
              const char      * method )
{
  LineEdit * le = new LineEdit(this,plan) ;
  le -> setText ( item->text(column) )    ;
  setItemWidget ( item , column , le )    ;
  ItemEditing = item                      ;
  ItemColumn  = column                    ;
  ItemWidget  = le                        ;
  connect ( le , Signal , this , method ) ;
  return (QLineEdit *)le                  ;
}

QComboBox * N::TreeWidget::setComboBox (
              QTreeWidgetItem * item   ,
              int               column ,
              const char      * Signal ,
              const char      * method )
{
  ComboBox * cb = new ComboBox(this,plan) ;
  setItemWidget ( item , column , cb )    ;
  ItemEditing = item                      ;
  ItemColumn  = column                    ;
  ItemWidget  = cb                        ;
  connect ( cb , Signal , this , method ) ;
  return (QComboBox *)cb                  ;
}

QSpinBox * N::TreeWidget::setSpinBox    (
             QTreeWidgetItem * item   ,
             int               column ,
             int               Min    ,
             int               Max    ,
             const char      * Signal ,
             const char      * method )
{
  SpinBox * sb = new SpinBox(this,plan)   ;
  QString s = item->text(column)          ;
  sb -> setRange ( Min , Max          )   ;
  sb -> setValue ( s.toInt()          )   ;
  setItemWidget  ( item , column , sb )   ;
  ItemEditing = item                      ;
  ItemColumn  = column                    ;
  ItemWidget  = sb                        ;
  connect ( sb , Signal , this , method ) ;
  return (QSpinBox *)sb                   ;
}

QDoubleSpinBox * N::TreeWidget::setDoubleSpin (
                   QTreeWidgetItem * item   ,
                   int               column ,
                   double            Min    ,
                   double            Max    ,
                   const char      * Signal ,
                   const char      * method )
{
  DoubleSpinBox * sb = new DoubleSpinBox(this,plan) ;
  QString s = item->text(column)                    ;
  sb -> setRange ( Min , Max         )              ;
  sb -> setValue ( s.toDouble ( )    )              ;
  setItemWidget ( item , column , sb )              ;
  ItemEditing = item                                ;
  ItemColumn  = column                              ;
  ItemWidget  = sb                                  ;
  connect ( sb , Signal , this , method )           ;
  return (QDoubleSpinBox *)sb                       ;
}

void N::TreeWidget::removeOldItem(bool checkUuid,int column)
{
  if (IsNull(ItemEditing)) return                ;
  SUID    uuid = 0                               ;
  QString name = ""                              ;
  if (checkUuid)                                 {
    uuid = nTreeUuid(ItemEditing,column)         ;
    name = ItemEditing->text(ItemColumn)         ;
  }                                              ;
  removeItemWidget (ItemEditing,ItemColumn)      ;
  if (checkUuid && uuid<=0 && name.length()<=0)  {
    int index = indexOfTopLevelItem(ItemEditing) ;
    takeTopLevelItem(index)                      ;
  }                                              ;
  ItemEditing = NULL                             ;
  ItemWidget  = NULL                             ;
  ItemColumn  = -1                               ;
  if (!plan->Booleans["Desktop"])                {
    allowGesture = true                          ;
  }                                              ;
}

void N::TreeWidget::CopyToClipboard(void)
{
  QTreeWidgetItem * item = currentItem () ;
  nDropOut ( IsNull(item) )               ;
  int cc = currentColumn()                ;
  QString text = item -> text (cc)        ;
  qApp -> clipboard() -> setText (text)   ;
  QString m                               ;
  m = tr("duplicate text to clipboard")   ;
  plan->Talk(m)                           ;
}

void N::TreeWidget::CopyIt(void)
{
  CopyToClipboard ( ) ;
}

void N::TreeWidget::SelectNone(void)
{
  QString m                                   ;
  m = tr("Clear selections")                  ;
  plan->Talk(m)                               ;
  nFullLoop(i,topLevelItemCount())            {
    QTreeWidgetItem * it = topLevelItem ( i ) ;
    it   -> setSelected   ( false )           ;
    plan -> processEvents (       )           ;
  }                                           ;
}

void N::TreeWidget::SelectAll(void)
{
  QString m                                   ;
  m = tr("Select all items")                  ;
  plan->Talk(m)                               ;
  nFullLoop(i,topLevelItemCount())            {
    QTreeWidgetItem * it = topLevelItem ( i ) ;
    it   -> setSelected   ( true  )           ;
    plan -> processEvents (       )           ;
  }                                           ;
}

void N::TreeWidget::setFont(void)
{
  changeFont ( ) ;
}

void N::TreeWidget::Language(void)
{
  AbstractGui::assignLanguage ( this ) ;
}

void N::TreeWidget::setAllExpanded(bool expand)
{
  QString m                                     ;
  if (expand) m = tr("Expand all items"  )      ;
         else m = tr("Collapse all items")      ;
  plan->Talk(m)                                 ;
  nFullLoop(i,topLevelItemCount())              {
    QTreeWidgetItem * item = topLevelItem ( i ) ;
    item->setExpanded(expand)                   ;
  }                                             ;
}

void N::TreeWidget::MountClicked(int clicks)
{
  switch (clicks)                                        {
    case 1                                               :
      QObject::disconnect                                (
        this                                             ,
        SIGNAL(itemClicked(QTreeWidgetItem*,int))        ,
        NULL                                             ,
        NULL                                           ) ;
      nConnect                                           (
        this                                             ,
        SIGNAL(itemClicked      (QTreeWidgetItem*,int))  ,
        this                                             ,
        SLOT  (singleClicked    (QTreeWidgetItem*,int))) ;
    break                                                ;
    case 2                                               :
      QObject::disconnect                                (
        this                                             ,
        SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int))  ,
        NULL                                             ,
        NULL                                           ) ;
      nConnect                                           (
        this                                             ,
        SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int))  ,
        this                                             ,
        SLOT  (doubleClicked    (QTreeWidgetItem*,int))) ;
    break                                                ;
    case 9                                               :
      QObject::disconnect                                (
        this                                             ,
        SIGNAL(itemChanged(QTreeWidgetItem*,int))        ,
        NULL                                             ,
        NULL                                           ) ;
      nConnect                                           (
        this                                             ,
        SIGNAL(itemChanged      (QTreeWidgetItem*,int))  ,
        this                                             ,
        SLOT  (stateChanged     (QTreeWidgetItem*,int))) ;
    break                                                ;
  }                                                      ;
}

void N::TreeWidget::singleClicked(QTreeWidgetItem * item,int column)
{
  Q_UNUSED ( item   ) ;
  Q_UNUSED ( column ) ;
}

void N::TreeWidget::doubleClicked(QTreeWidgetItem * item,int column)
{
  Q_UNUSED ( item   ) ;
  Q_UNUSED ( column ) ;
}

void N::TreeWidget::stateChanged(QTreeWidgetItem * item,int column)
{
  Q_UNUSED ( item   ) ;
  Q_UNUSED ( column ) ;
}

void N::TreeWidget::setAlignment(int position,int alignment)
{
  Alignments [ position ] = alignment ;
}

void N::TreeWidget::setAlignments(QTreeWidgetItem * item)
{
  CUIDs IDs = Alignments . keys ()                      ;
  int   id                                              ;
  foreach (id,IDs)                                      {
    item -> setTextAlignment ( id , Alignments [ id ] ) ;
  }                                                     ;
}

void N::TreeWidget::setAllAlignments(QTreeWidgetItem * item,int alignment)
{
  nFullLoop ( i , columnCount() )       {
    item->setTextAlignment(i,alignment) ;
  }                                     ;
}

void N::TreeWidget::setFont(QTreeWidgetItem * item,Font & f)
{
  nFullLoop ( i , columnCount() ) {
    item->setFont(i,f)            ;
  }                               ;
}

void N::TreeWidget::setFont(QTreeWidgetItem * item,int FontId)
{
  nFullLoop ( i , columnCount() )        {
    item->setFont(i,plan->fonts[FontId]) ;
  }                                      ;
}

UUIDs N::TreeWidget::selectedUuids(int column)
{
  UUIDs Uuids                         ;
  nFullLoop(i,topLevelItemCount())    {
    QTreeWidgetItem * item            ;
    item = topLevelItem(i)            ;
    if (item->isSelected())           {
      Uuids << nTreeUuid(item,column) ;
    }                                 ;
  }                                   ;
  return Uuids                        ;
}

UUIDs N::TreeWidget::itemUuids(int column)
{
  UUIDs Uuids                                 ;
  for (int i=0;i<topLevelItemCount();i++)     {
    QTreeWidgetItem * it = topLevelItem ( i ) ;
    Uuids << nTreeUuid ( it , column )        ;
  }                                           ;
  return Uuids                                ;
}

QMimeData * N::TreeWidget::standardMime(QString objectName)
{
  UUIDs Uuids                                    ;
  SUID  uuid  = 0                                ;
  ////////////////////////////////////////////////
  Uuids = selectedUuids(0)                       ;
  if (Uuids.count()<=0)                          {
    QTreeWidgetItem * it = currentItem()         ;
    if (NotNull(it))                             {
      uuid = nTreeUuid(it,0)                     ;
    }                                            ;
  }                                              ;
  ////////////////////////////////////////////////
  nKickOut(Uuids.count()<=0 && uuid == 0,NULL)   ;
  if (Uuids.count()==1)                          {
    uuid  = Uuids [0]                            ;
    Uuids . clear ( )                            ;
  }                                              ;
  ////////////////////////////////////////////////
  QMimeData * mime = new QMimeData()             ;
  QString UUID  = objectName + "/uuid"           ;
  QString UUIDS = objectName + "/uuids"          ;
  if (Uuids.count()==0)                          {
    setMime ( mime , UUID  , uuid  )             ;
  } else                                         {
    setMime ( mime , UUIDS , Uuids )             ;
  }                                              ;
  return mime                                    ;
}

bool N::TreeWidget::dropFont(QWidget * source,QPointF pos,const SUID font)
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

bool N::TreeWidget::dropPen(QWidget * source,QPointF pos,const SUID pen)
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

bool N::TreeWidget::dropBrush(QWidget * source,QPointF pos,const SUID brush)
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

void N::TreeWidget::assignFont(Font & font)
{
  QTreeWidget::setFont ( font )    ;
  nFullLoop(i,topLevelItemCount()) {
    QTreeWidgetItem * item         ;
    item = topLevelItem(i)         ;
    nFullLoop(j,columnCount())     {
      item -> setFont ( j , font ) ;
    }                              ;
  }                                ;
}

void N::TreeWidget::assignPen(Pen & p)
{ Q_UNUSED ( p ) ;
}

void N::TreeWidget::assignBrush(Brush & brush)
{
  QBrush   B   = brush                            ;
  QPalette P   = palette (                      ) ;
  P . setBrush           ( QPalette::Base , B   ) ;
  setPalette             ( P                    ) ;
}

QString N::TreeWidget::writeCpp(void)
{
  #define NL C << ""
  #define NB C << "  "
  QStringList C                                                                ;
  QString     I = InheritClass                                                 ;
  int         L = I.length()                                                   ;
  QString     S = " "                                                          ;
  int         DD = 0                                                           ;
  S = S.repeated(L)                                                            ;
  C << QString("#include <Exciton>")                                           ;
  C << QString("#include \"%1.hpp\"").arg(I)                                   ;
  NL                                                                           ;
  C << QString("%1:: %2(QWidget * parent,N::Plan * plan)").arg(I).arg(I)       ;
  C << QString("%1 : N::TreeWidget ( parent , plan )"   ).arg(S)               ;
  C << "{"                                                                     ;
  C << "  Configure ( ) ;"                                                     ;
  C << "}"                                                                     ;
  NL                                                                           ;
  C << QString("%1::~%2(void)").arg(I).arg(I)                                  ;
  C << "{"                                                                     ;
  C << "}"                                                                     ;
  NL                                                                           ;
  C << QString("void %1::Configure(void)").arg(I)                              ;
  C << "{"                                                                     ;
  C << "  NewTreeWidgetItem       (head                              )      ;" ;
  C << "  ///////////////////////////////////////////////////////////////////" ;
  C << QString("  setWindowTitle ( tr(\"%1\") ) ;").arg(windowTitle())         ;
  C << QString("  setAccessibleName ( \"%1\" ) ;").arg(I)                      ;
  C << "  ///////////////////////////////////////////////////////////////////" ;
  C << QString("  setColumnCount ( %1 ) ;").arg(columnCount())                 ;
  C << QString("  setRootIsDecorated ( %1 ) ;").arg(rootIsDecorated() ? "true" : "false" ) ;
  C << QString("  setAlternatingRowColors ( %1 ) ;").arg(alternatingRowColors() ? "true" : "false" ) ;
  C << "  setSelectionMode ( ExtendedSelection ) ;"                            ;
  C << "  ///////////////////////////////////////////////////////////////////" ;
  if (NotNull(headerItem()))                                                   {
    QTreeWidgetItem * hit = headerItem()                                       ;
    for (int i=0;i<columnCount();i++)                                          {
      C << QString("  head -> setText ( %1 , tr(\"%2\") ) ;").arg(i).arg(hit->text(i)) ;
    }                                                                          ;
    for (int i=0;i<columnCount();i++)                                          {
      if (Alignments.contains(i))                                              {
        QStringList AL                                                         ;
        QString     AN                                                         ;
        if (IsMask(Alignments[i],Qt::AlignLeft   )) AL << "Qt::AlignLeft"      ;
        if (IsMask(Alignments[i],Qt::AlignRight  )) AL << "Qt::AlignRight"     ;
        if (IsMask(Alignments[i],Qt::AlignHCenter)) AL << "Qt::AlignHCenter"   ;
        if (IsMask(Alignments[i],Qt::AlignJustify)) AL << "Qt::AlignJustify"   ;
        if (IsMask(Alignments[i],Qt::AlignTop    )) AL << "Qt::AlignTop"       ;
        if (IsMask(Alignments[i],Qt::AlignBottom )) AL << "Qt::AlignBottom"    ;
        if (IsMask(Alignments[i],Qt::AlignVCenter)) AL << "Qt::AlignVCenter"   ;
        AN = AL.join(" | ")                                                    ;
        C << QString("  setAlignment(%1,%2) ;").arg(i).arg(AN)                 ;
      }                                                                        ;
    }                                                                          ;
    C << "  for (int i=0;i<columnCount();i++) {"                               ;
    C << "    head->setTextAlignment(i,Qt::AlignCenter) ;"                     ;
    C << "  };"                                                                ;
    C << "  setHeaderItem ( head ) ;"                                          ;
  }                                                                            ;
  C << "  ///////////////////////////////////////////////////////////////////" ;
  C << "  Plan -> setFont ( this ) ;"                                          ;
  if (EditAttributes.contains(13) && EditAttributes[13])                       {
    if (EditAttributes[13]) DD |= QAbstractItemView::DragOnly                  ;
  }                                                                            ;
  if (EditAttributes.contains(14) && EditAttributes[14])                       {
    if (EditAttributes[14]) DD |= QAbstractItemView::DropOnly                  ;
  }                                                                            ;
  switch (DD)                                                                  {
    case NoDragDrop                                                            :
      C << "  setDragDropMode ( NoDragDrop ) ;"                                ;
    break                                                                      ;
    case DragOnly                                                              :
      C << "  setDragDropMode ( DragOnly   ) ;"                                ;
    break                                                                      ;
    case DropOnly                                                              :
      C << "  setDragDropMode ( DropOnly   ) ;"                                ;
    break                                                                      ;
    case DragDrop                                                              :
      C << "  setDragDropMode ( DragDrop   ) ;"                                ;
    break                                                                      ;
  }                                                                            ;
  C << "  ///////////////////////////////////////////////////////////////////" ;
  if (EditAttributes.contains(11) && EditAttributes[11])                       {
    C << "  connect (this,SIGNAL(itemClicked      (QTreeWidgetItem*,int))   ," ;
    C << "           this,SLOT  (singleClicked    (QTreeWidgetItem*,int)) ) ;" ;
  }                                                                            ;
  if (EditAttributes.contains(12) && EditAttributes[12])                       {
    C << "  connect (this,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int))   ," ;
    C << "           this,SLOT  (doubleClicked    (QTreeWidgetItem*,int)) ) ;" ;
  }                                                                            ;
  C << "}"                                                                     ;
  NL                                                                           ;
  C << QString("bool %1::FocusIn(void)").arg(I)                                ;
  C << "{"                                                                     ;
  C << "  return true ;"                                                       ;
  C << "}"                                                                     ;
  NL                                                                           ;
  if (EditAttributes.contains(13) && EditAttributes[13])                       {
    C << QString("bool %1::hasItem(void)").arg(I)                              ;
    C << "{"                                                                   ;
    C << "  QTreeWidgetItem * item = currentItem () ;"                         ;
    C << "  return NotNull ( item )                 ;"                         ;
    C << "}"                                                                   ;
    NL                                                                         ;
    C << QString("bool %1::startDrag(QMouseEvent * event)").arg(I)             ;
    C << "{"                                                                   ;
    C << "  QTreeWidgetItem * atItem = itemAt(event->pos())               ;"   ;
    C << "  nKickOut (  IsNull(atItem)                          , false ) ;"   ;
    C << "  nKickOut ( !IsMask(event->buttons(),Qt::LeftButton) , false ) ;"   ;
    C << "  dragPoint = event->pos()                                      ;"   ;
    C << "  nKickOut ( !atItem->isSelected()                    , false ) ;"   ;
    C << "  nKickOut ( !PassDragDrop                            , false ) ;"   ;
    C << "  return true                                                   ;"   ;
    C << "}"                                                                   ;
    NL                                                                         ;
    C << QString("bool %1::fetchDrag(QMouseEvent * event)").arg(I)             ;
    C << "{"                                                                   ;
    C << "  nKickOut ( !IsMask(event->buttons(),Qt::LeftButton) , false ) ;"   ;
    C << "  QPoint pos = event->pos()                                     ;"   ;
    C << "  pos -= dragPoint                                              ;"   ;
    C << "  return ( pos.manhattanLength() > qApp->startDragDistance() )  ;"   ;
    C << "}"                                                                   ;
    NL                                                                         ;
    C << QString("QMimeData * %1::dragMime(void)").arg(I)                      ;
    C << "{"                                                                   ;
    C << QString("  return standardMime(\"%1\") ;").arg(I)                     ;
    C << "}"                                                                   ;
    NL                                                                         ;
    C << QString("void %1::dragDone(Qt::DropAction dropIt,QMimeData * mime)").arg(I) ;
    C << "{"                                                                   ;
    C << "}"                                                                   ;
    NL                                                                         ;
    C << QString("bool %1::finishDrag(QMouseEvent * event)").arg(I)            ;
    C << "{"                                                                   ;
    C << "  return true ;"                                                     ;
    C << "}"                                                                   ;
    NL                                                                         ;
  }                                                                            ;
  if (EditAttributes.contains(14) && EditAttributes[14])                       {
    C << QString("bool %1::acceptDrop(QWidget * source,const QMimeData * mime)").arg(I) ;
    C << "{"                                                                   ;
    C << "  if (source==this) return false ;"                                  ;
    C << "  return dropHandler ( mime )    ;"                                  ;
    C << "}"                                                                   ;
    NL                                                                         ;
    C << QString("bool %1::dropNew(QWidget * source,const QMimeData * mime,QPoint pos)").arg(I) ;
    C << "{"                                                                   ;
    C << "  if (source==this) return false           ;" ;
    C << "  return true ;"                                                     ;
    C << "}"                                                                   ;
    NL                                                                         ;
    C << QString("bool %1::dropMoving(QWidget * source,const QMimeData * mime,QPoint pos)").arg(I) ;
    C << "{"                                                                   ;
    C << "  if (source==this) return false           ;" ;
    C << "  return true ;"                                                     ;
    C << "}"                                                                   ;
    NL                                                                         ;
    C << QString("bool %1::dropAppend(QWidget * source,const QMimeData * mime,QPoint pos)").arg(I) ;
    C << "{"                                                                   ;
    C << "  if (source==this) return false           ;"                        ;
    C << "  return dropItems ( source , mime , pos ) ;"                        ;
    C << "}"                                                                   ;
    NL                                                                         ;
    C << QString("QString %1::MimeType(const QMimeData * mime)").arg(I)        ;
    C << "{"                                                                   ;
    C << "  return nVirtualGui::MimeType(mime,\"whatever/uuid;whatever/uuids\") ; " ;
    C << "}"                                                                   ;
    NL                                                                         ;
    C << QString("UUIDs %1::MimeUuids(const QMimeData * mime,QString mimetype)").arg(I) ;
    C << "{"                                                                   ;
    C << "  UUIDs Uuids                            ;"                          ;
    C << "  QByteArray data = mime->data(mimetype) ;"                          ;
    C << "  if (data.size()<=0) return Uuids       ;"                          ;
    C << "  if (mimetype==\"whatever/uuid\")       {"                          ;
    C << "    SUID * suid = (SUID *)data.data()    ;"                          ;
    C << "    Uuids << (*suid)                     ;"                          ;
    C << "  } else"                                                            ;
    C << "  if (mimetype==\"whatever/uuids\")      {"                          ;
    C << "    SUID * suid  = (SUID *)data.data()   ;"                          ;
    C << "    int    total = (int)suid[0]          ;"                          ;
    C << "    for (int i=0;i<total;i++)            {"                          ;
    C << "      Uuids << suid[i+1]                 ;"                          ;
    C << "      Plan->processEvents()              ;"                          ;
    C << "    }                                    ;"                          ;
    C << "  }                                      ;"                          ;
    C << "  return Uuids                           ;"                          ;
    C << "}"                                                                   ;
    NL                                                                         ;
  }                                                                            ;
  if (EditAttributes.contains(11) && EditAttributes[11])                       {
    C << QString("void %1::singleClicked(QTreeWidgetItem * item,int column)").arg(I) ;
    C << "{"                                                                   ;
    C << "}"                                                                   ;
    NL                                                                         ;
  }                                                                            ;
  if (EditAttributes.contains(12) && EditAttributes[12])                       {
    C << QString("void %1::doubleClicked(QTreeWidgetItem * item,int column)").arg(I) ;
    C << "{"                                                                   ;
    if (EditStyles.count()>0)                                                  {
      QMap<int,bool> ES                                                        ;
      CUIDs K = EditStyles.keys()                                              ;
      int   k                                                                  ;
      ES[1] = false                                                            ;
      ES[2] = false                                                            ;
      ES[3] = false                                                            ;
      ES[4] = false                                                            ;
      foreach (k,K)                                                            {
        switch (EditStyles[k])                                                 {
          case 1 : ES[1] = true ; break                                        ;
          case 2 : ES[2] = true ; break                                        ;
          case 3 : ES[3] = true ; break                                        ;
          case 4 : ES[4] = true ; break                                        ;
        }                                                                      ;
      }                                                                        ;
      if (ES[1]) C << "  QLineEdit      * le = NULL ;"                         ;
      if (ES[2]) C << "  QComboBox      * cb = NULL ;"                         ;
      if (ES[3]) C << "  QSpinBox       * sb = NULL ;"                         ;
      if (ES[4]) C << "  QDoubleSpinBox * ds = NULL ;"                         ;
      C << "  removeOldItem ()      ;"                                         ;
      C << "  switch (column) {"                                               ;
      foreach (k,K)                                                            {
        C << QString("    case %1 :").arg(k)                                   ;
        switch (EditStyles[k])                                                 {
          case 1                                                               :
            C << "      le  = setLineEdit(item,column,SIGNAL(editingFinished()),\"\") ;" ;
            C << "      le -> setFocus ( Qt::TabFocusReason ) ;"               ;
          break                                                                ;
          case 2                                                               :
            C << "      cb  = setComboBox(item,column,SIGNAL(valueChanged(int)),\"\") ;" ;
            C << "      cb -> showPopup ( ) ;"                                 ;
          break                                                                ;
          case 3                                                               :
            C << "      sb  = setSpinBox(item,column,0,100000,SIGNAL(editingFinished()),\"\") ;" ;
          break                                                                ;
          case 4                                                               :
            C << "      ds  = setDoubleSpin(item,column,0,10000000000.0,SIGNAL(editingFinished()),\"\") ;" ;
          break                                                                ;
        }                                                                      ;
        C << "    break;"                                                      ;
      }                                                                        ;
      C << "  } ;"                                                             ;
    }                                                                          ;
    C << "}"                                                                   ;
    NL                                                                         ;
  }                                                                            ;
  C << QString("bool %1::startup(void)").arg(I)                                ;
  C << "{"                                                                     ;
  C << "  return true ;"                                                       ;
  C << "}"                                                                     ;
  NL                                                                           ;
  C << QString("bool %1::Menu(QPoint pos)").arg(I)                             ;
  C << "{"                                                                     ;
  C << "  return true ;"                                                       ;
  C << "}"                                                                     ;
  NL                                                                           ;
  return C.join("\n")                                                          ;
  #undef NL
  #undef NB
}

QString N::TreeWidget::writeHpp(void)
{
  #define NL H << ""
  #define NB H << "    "
  QStringList H                                                                ;
  QString     I = InheritClass                                                 ;
  QString     U = I.toUpper()                                                  ;
  H << QString("#ifndef %1_HPP").arg(U)                                        ;
  H << QString("#define %1_HPP").arg(U)                                        ;
  NL                                                                           ;
  H << "#include <Rishon>"                                                     ;
  NL                                                                           ;
  H << QString("class %1 : public nTreeWidget").arg(I)                         ;
  H << "{"                                                                     ;
  H << "  Q_OBJECT"                                                            ;
  H << "  public:"                                                             ;
  NB                                                                           ;
  H << QString("    explicit %1 (nStandardConstructor) ;").arg(I)              ;
  H << QString("    virtual ~%1 (void) ;").arg(I)                              ;
  NB                                                                           ;
  H << "  protected:"                                                          ;
  NB                                                                           ;
  if (EditAttributes.contains(13) && EditAttributes[13])                       {
    H << "    QPoint dragPoint ;"                                              ;
    NB                                                                         ;
  }                                                                            ;
  H << "    virtual bool FocusIn   (void) ;"                                   ;
  H << "    virtual void Configure (void) ;"                                   ;
  NB                                                                           ;
  if (EditAttributes.contains(13) && EditAttributes[13])                       {
    H << "    virtual bool        hasItem    (void) ;"                         ;
    H << "    virtual bool        startDrag  (QMouseEvent * event) ;"          ;
    H << "    virtual bool        fetchDrag  (QMouseEvent * event) ;"          ;
    H << "    virtual QMimeData * dragMime   (void) ;"                         ;
    H << "    virtual void        dragDone   (Qt::DropAction dropIt,QMimeData * mime) ;" ;
    H << "    virtual bool        finishDrag (QMouseEvent * event) ;"          ;
    NB                                                                         ;
  }                                                                            ;
  if (EditAttributes.contains(14) && EditAttributes[14])                       {
    H << "    virtual bool        acceptDrop (QWidget * source,const QMimeData * mime);" ;
    H << "    virtual bool        dropNew    (QWidget * source,const QMimeData * mime,QPoint pos);" ;
    H << "    virtual bool        dropMoving (QWidget * source,const QMimeData * mime,QPoint pos);" ;
    H << "    virtual bool        dropAppend (QWidget * source,const QMimeData * mime,QPoint pos);" ;
    NB                                                                         ;
    H << "    virtual QString     MimeType   (const QMimeData * mime);" ;
    H << "    virtual UUIDs       MimeUuids  (const QMimeData * mime,QString mimetype) ;" ;
    NB                                                                         ;
  }                                                                            ;
  H << "  private:"                                                            ;
  NB                                                                           ;
  H << "  public slots:"                                                       ;
  NB                                                                           ;
  H << "    virtual bool startup (void) ;"                                     ;
  NB                                                                           ;
  H << "  protected slots:"                                                    ;
  NB                                                                           ;
  H << "    virtual bool Menu(QPoint pos) ;"                                   ;
  if (EditAttributes.contains(11) && EditAttributes[11])                       {
    H << "    virtual void singleClicked(QTreeWidgetItem * item,int column) ;" ;
  }                                                                            ;
  if (EditAttributes.contains(12) && EditAttributes[12])                       {
    H << "    virtual void doubleClicked(QTreeWidgetItem * item,int column) ;" ;
  }                                                                            ;
  NB                                                                           ;
  H << "  private slots:"                                                      ;
  NB                                                                           ;
  NB                                                                           ;
  H << "  signals:"                                                            ;
  NB                                                                           ;
  H << "} ;"                                                                   ;
  NL                                                                           ;
  H << QString("#endif // %1_HPP").arg(U)                                      ;
  NL                                                                           ;
  return H.join("\n")                                                          ;
  #undef NL
  #undef NB
}

QString N::TreeWidget::toHtml(QTreeWidgetItem * item,bool align)
{
  QString m = ""                              ;
  m += "<tr>"                                 ;
  m += "\n"                                   ;
  for (int i=0;i<columnCount();i++)           {
    int alignment = item->textAlignment(i)    ;
    if (align)                                {
      if (IsMask(alignment,Qt::AlignLeft   )) {
        m += "<td align=left>"                ;
      } else
      if (IsMask(alignment,Qt::AlignRight  )) {
        m += "<td align=right>"               ;
      } else
      if (IsMask(alignment,Qt::AlignHCenter)) {
        m += "<td align=center>"              ;
      } else                                  {
        m += "<td>"                           ;
      }                                       ;
    } else                                    {
      m += "<td>"                             ;
    }                                         ;
    m += item->text(i)                        ;
    m += "</td>"                              ;
    m += "\n"                                 ;
  }                                           ;
  m += "</tr>"                                ;
  m += "\n"                                   ;
  return m                                    ;
}

QString N::TreeWidget::toHtml(bool alignment)
{
  QString html                            ;
  for (int i=0;i<topLevelItemCount();i++) {
    QTreeWidgetItem * it                  ;
    it    = topLevelItem ( i )            ;
    html += toHtml ( it , alignment )     ;
    html += "\n"                          ;
  }                                       ;
  return html                             ;
}

QString N::TreeWidget::toTeX(QTreeWidgetItem * item,bool align)
{
  QString     m = ""                ;
  QStringList s                     ;
  for (int i=0;i<columnCount();i++) {
    s << item->text(i)              ;
  }                                 ;
  m += s.join("\n&\n")              ;
  m += "\\\\"                       ;
  m += "\\hline"                    ;
  m += "\n"                         ;
  return m                          ;
}

QString N::TreeWidget::toTeX(bool alignment)
{
  QTreeWidgetItem * head                  ;
  QString tex = ""                        ;
  tex += "\\begin{tabular}"               ;
  head = headerItem()                     ;
  if (NotNull(head) && alignment)         {
    QStringList L                         ;
    tex += "{|"                           ;
    for (int i=0;i<columnCount();i++)     {
      int aln = head->textAlignment(i)    ;
      if (IsMask(aln,Qt::AlignLeft   ))   {
        L << "l"                          ;
      } else
      if (IsMask(aln,Qt::AlignRight  ))   {
        L << "r"                          ;
      } else
      if (IsMask(aln,Qt::AlignHCenter))   {
        L << "c"                          ;
      } else                              {
        L << "l"                          ;
      }                                   ;
    }                                     ;
    tex += L.join("|")                    ;
    tex += "|}"                           ;
  }                                       ;
  tex += "\n"                             ;
  tex += "\\hline"                        ;
  tex += "\n"                             ;
  for (int i=0;i<topLevelItemCount();i++) {
    QTreeWidgetItem * it                  ;
    it   = topLevelItem ( i )             ;
    tex += toTeX ( it , alignment )       ;
    tex += "%\n"                          ;
  }                                       ;
  tex += "\\end{tabular}"                 ;
  tex += "\n"                             ;
  return tex                              ;
}

QString N::TreeWidget::toText(QTreeWidgetItem * item,bool align)
{
  QString     m = ""                ;
  QStringList s                     ;
  for (int i=0;i<columnCount();i++) {
    s << item->text(i)              ;
  }                                 ;
  m += s.join("\t")                 ;
  m += "\n"                         ;
  return m                          ;
}

QString N::TreeWidget::toText(bool alignment)
{
  QTreeWidgetItem * head                  ;
  QString           text = ""             ;
  head = headerItem()                     ;
  if (NotNull(head))                      {
    text += toText ( head , alignment )   ;
  }                                       ;
  for (int i=0;i<topLevelItemCount();i++) {
    QTreeWidgetItem * it                  ;
    it   = topLevelItem ( i )             ;
    text += toText ( it , alignment )     ;
  }                                       ;
  return text                             ;
}

QLineEdit * N::TreeWidget::headerEditor(const char * emitter,const char * method)
{
  QHeaderView * hv = header()                ;
  nKickOut ( IsNull(hv) , NULL )             ;
  QLineEdit * le = NULL                      ;
  QSize       hs = hv->size()                ;
  QRect       hr ( QPoint(0,0) , hs        ) ;
  le  = new QLineEdit ( hv                 ) ;
  le -> setGeometry   ( hr                 ) ;
  le -> setFont       ( hv->font()         ) ;
  le -> show          (                    ) ;
  if (NotNull(emitter) && NotNull(method))   {
    connect ( le , emitter , this , method ) ;
  }                                          ;
  le -> setFocus      ( Qt::TabFocusReason ) ;
  return le                                  ;
}

QTreeWidgetItem * N::TreeWidget::uuidAtItem(SUID uuid,int column)
{
  QTreeWidgetItem * item = NULL                           ;
  for (int i=0;IsNull(item) && i<topLevelItemCount();i++) {
    QTreeWidgetItem * it = topLevelItem(i)                ;
    SUID iuid = nTreeUuid(it,column)                      ;
    if (nEqual(iuid,uuid)) item = it                      ;
  }                                                       ;
  return item                                             ;
}

int N::TreeWidget::addItems(int column,QStringList & lists)
{
  for (int i=0;i<lists.count();i++) {
    NewTreeWidgetItem(item)         ;
    item->setText(column,lists[i])  ;
    addTopLevelItem(item)           ;
  }                                 ;
  return topLevelItemCount()        ;
}

SUID N::TreeWidget::atUuid(QPoint pos,int column)
{
  QTreeWidgetItem * it = itemAt ( pos ) ;
  if ( IsNull ( it ) ) return 0         ;
  SUID u = nTreeUuid ( it , column )    ;
  return u                              ;
}

void N::TreeWidget::DropInObjects(ThreadData*)
{
}

void N::TreeWidget::PrepareItem(QTreeWidgetItem*)
{
}

void N::TreeWidget::SortingMenu(MenuManager & Menu,QMenu * me)
{
  Menu . add ( me , 90301 , tr("Sorting") , true , isSortingEnabled() ) ;
  Menu . add ( me , 90302 , tr("Ascending sort" )                     ) ;
  Menu . add ( me , 90303 , tr("Descending sort")                     ) ;
}

bool N::TreeWidget::RunSorting(MenuManager & Menu,QAction * action)
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

void N::TreeWidget::AdjustMenu(MenuManager & mm,QMenu * me)
{
  mm . addSeparator ( me                                  ) ;
  mm . add          ( me , 90201 , tr("Set font"        ) ) ;
  mm . add          ( me , 90202 , tr("Select language" ) ) ;
  mm . add          ( me , 90203 , tr("Set minimum size") ) ;
  mm . add          ( me , 90204 , tr("Set maximum size") ) ;
  mm . add          ( me , 90205 , tr("Set style sheet" ) ) ;
}

bool N::TreeWidget::RunAdjustment(MenuManager & Menu,QAction * action)
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

void N::TreeWidget::SelectionsMenu(MenuManager & Menu,QMenu * me)
{
  Menu . add ( me , 90401 , tr("Copy selections to clipboard") ) ;
  Menu . add ( me , 90402 , tr("Select all" )                  ) ;
  Menu . add ( me , 90403 , tr("Select none")                  ) ;
}

bool N::TreeWidget::RunSelections(MenuManager & Menu,QAction * action)
{
  switch (Menu[action])                  {
    nFastCast ( 90401 , CopyIt     ( ) ) ;
    nFastCast ( 90402 , SelectAll  ( ) ) ;
    nFastCast ( 90403 , SelectNone ( ) ) ;
    default: return false                ;
  }                                      ;
  return true                            ;
}

bool N::TreeWidget::PageChanged(int StartId,int PageSize)
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

QMenu * N::TreeWidget::PageMenu  (
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
  mm       . add          ( mp , 90560 , tr("View all"     ) ) ;
  mm       . add          ( mp , 90561 , tr("Home"         ) ) ;
  mm       . add          ( mp                                 ,
                            90562                              ,
                            LocalIcons  [ "UpArrow"   ]        ,
                            tr("Previous page")              ) ;
  mm       . add          ( mp                                 ,
                            90563                              ,
                            LocalIcons  [ "DownArrow" ]        ,
                            tr("Next page")                  ) ;
  mm       . add          ( mp , 90564 , tr("End page"     ) ) ;
  mm       . addSeparator ( mp                               ) ;
  mm       . add          ( mp , 90571 , spb                 ) ;
  mm       . add          ( mp , 90572 , spp                 ) ;
  //////////////////////////////////////////////////////////////
  spb     -> External = &StartId                               ;
  spp     -> External = &PageSize                              ;
  return mp                                                    ;
}

bool N::TreeWidget::RunPageMenu (
       MenuManager & mm         ,
       QAction     * aa         ,
       int         & StartId    ,
       int         & PageSize   )
{
  switch ( mm [ aa ] )               {
    case 90560                       :
      StartId  = 0                   ;
      PageSize = LimitValues [ 2 ]   ;
    break                            ;
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

void N::TreeWidget::PageHome(void)
{
  if ( ! isStopped ( )        ) return    ;
  if ( 0 == LimitValues [ 0 ] ) return    ;
  LimitValues [ 0 ] = 0                   ;
  if ( 0 == LimitValues [ 1 ] )           {
    LimitValues [ 1 ] = LimitValues [ 2 ] ;
  }                                       ;
  startup ( )                             ;
}

void N::TreeWidget::PageEnd(void)
{
  if ( ! isStopped ( ) ) return           ;
  int StartId  = LimitValues [ 2 ]        ;
  if ( 0 == LimitValues [ 1 ] )           {
    LimitValues [ 1 ] = LimitValues [ 2 ] ;
  }                                       ;
  StartId            -= LimitValues [ 1 ] ;
  if ( StartId < 0 ) StartId = 0          ;
  LimitValues [ 0 ] = StartId             ;
  startup ( )                             ;
}

void N::TreeWidget::PageUp(void)
{
  if ( ! isStopped ( ) ) return            ;
  if ( 0 == LimitValues [ 1 ] )            {
    LimitValues [ 1 ]  = LimitValues [ 2 ] ;
  }                                        ;
  LimitValues   [ 0 ] -= LimitValues [ 1 ] ;
  if ( LimitValues [ 0 ] < 0 )             {
    LimitValues [ 0 ] = 0                  ;
  }                                        ;
  startup ( )                              ;
}

void N::TreeWidget::PageDown(void)
{
  if ( ! isStopped ( ) ) return                 ;
  if ( 0 == LimitValues [ 1 ] )                 {
    LimitValues [ 1 ]  = LimitValues [ 2 ]      ;
  }                                             ;
  LimitValues   [ 0 ] += LimitValues [ 1 ]      ;
  if ( LimitValues [ 0 ] >= LimitValues [ 2 ] ) {
    LimitValues [ 0 ]  = LimitValues [ 2 ] - 1  ;
  }                                             ;
  startup ( )                                   ;
}

void N::TreeWidget::StartCommand(void)
{
  nDropOut ( Commanding )                           ;
  CommandSequence -> start ( LimitValues [ 37714 ] ) ;
}

void N::TreeWidget::CommandHandler(void)
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

bool N::TreeWidget::RunCommand(VarArgs & arguments)
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

void N::TreeWidget::pendingStartup(void)
{
  VarArgs V          ;
  V << 10001         ;
  addSequence  ( V ) ;
  StartCommand (   ) ;
}

void N::TreeWidget::ExportToCpp(void)
{
  nDropOut ( InheritClass.length()<=0 )                 ;
  QString d = QFileDialog::getExistingDirectory         (
                this                                    ,
                tr("Export to C++ directory")           ,
                plan->Path("Development")               ,
                QFileDialog::ShowDirsOnly               |
                QFileDialog::DontResolveSymlinks      ) ;
  nDropOut ( d.length() <= 0 )                          ;
  QDir    D ( d )                                       ;
  QString N   = D.dirName( )                            ;
  QString Hpp = writeHpp ( )                            ;
  QString Cpp = writeCpp ( )                            ;
  QString H   = QString("%1.hpp").arg(InheritClass)     ;
  QString C   = QString("%1.cpp").arg(InheritClass)     ;
  QByteArray h = Hpp.toUtf8()                           ;
  QByteArray c = Cpp.toUtf8()                           ;
  QString HF   = D.absoluteFilePath(H)                  ;
  QString CF   = D.absoluteFilePath(C)                  ;
  File::toFile(HF,h)                                    ;
  File::toFile(CF,c)                                    ;
  N = N + ".pri"                                        ;
  N = D.absoluteFilePath(N)                             ;
  QFile F(N)                                            ;
  if (F.exists())                                       {
    QByteArray PRI                                      ;
    if (File::toByteArray(N,PRI))                       {
      QString P = QString::fromUtf8(PRI)                ;
      P.append("\n")                                    ;
      P.append(QString("HEADERS += $${PWD}/%1").arg(H)) ;
      P.append("\n")                                    ;
      P.append("\n")                                    ;
      P.append(QString("SOURCES += $${PWD}/%1").arg(C)) ;
      P.append("\n")                                    ;
      PRI = P.toUtf8()                                  ;
      File::toFile(N,PRI)                               ;
    }                                                   ;
  }                                                     ;
  Alert ( Done )                                        ;
}

bool N::TreeWidget::AppMenu(void)
{
  return Menu(QCursor::pos()) ;
}

bool N::TreeWidget::Menu(QPoint pos)
{ Q_UNUSED ( pos )                                        ;
  if (!designable) return false                           ;
  TextAlignEditor  * TAE                                  ;
  MenuManager        mm(this)                             ;
  QStringList        tis                                  ;
  QTreeWidgetItem  * item                                 ;
  QMenu            * mp                                   ;
  QMenu            * me                                   ;
  QMenu            * ms                                   ;
  QMenu            * mf                                   ;
  QAction          * aa                                   ;
  bool               singleClick = false                  ;
  bool               doubleClick = false                  ;
  bool               doDrag      = false                  ;
  bool               doDrop      = false                  ;
  bool               doDock      = false                  ;
  #define GB(N,ID)                                        \
    if (EditAttributes.contains(ID))                    { \
      N = EditAttributes[ID]                            ; \
    }
  GB ( singleClick , 11 )                                 ;
  GB ( doubleClick , 12 )                                 ;
  GB ( doDrag      , 13 )                                 ;
  GB ( doDrop      , 14 )                                 ;
  GB ( doDock      , 15 )                                 ;
  #undef  GB
  mm.add(101,tr("Assign class name"))                     ;
  mm.add(102,tr("Columns"          ))                     ;
  mm.add(103,tr("Add test items"   ))                     ;
  mm.add(104,tr("Clear items"      ))                     ;
  mm.addSeparator()                                       ;
  mp = mm.addMenu(tr("Properties"))                       ;
  ms = mm.addMenu(tr("Styles"    ))                       ;
  mf = mm.addMenu(tr("Inherits"  ))                       ;
  aa = mm.add(mp,201,tr("Root is decorated"     ))        ;
  aa->setCheckable(true)                                  ;
  aa->setChecked(rootIsDecorated     ())                  ;
  aa = mm.add(mp,202,tr("Alternating row colors"))        ;
  aa->setCheckable(true)                                  ;
  aa->setChecked(alternatingRowColors())                  ;
       mm.add(mp,203,tr("Column alignment"))              ;
  aa = mm.add(mp,204,tr("Column hidden"   ))              ;
  aa->setCheckable(true)                                  ;
  aa->setChecked(isColumnHidden(currentColumn()))         ;
  aa = mm.add(mp,205,tr("Header hidden"   ))              ;
  aa->setCheckable(true)                                  ;
  aa->setChecked(isHeaderHidden())                        ;
  mm.add(ms,311,tr("Set window title" ))                  ;
  mm.add(ms,301,tr("Set column header"))                  ;
  mm.add(ms,302,tr("Set editor"       ))                  ;
  mm.add(ms,303,tr("Single clicked"   ),true,singleClick) ;
  mm.add(ms,304,tr("Double clicked"   ),true,doubleClick) ;
  mm.add(ms,305,tr("Drag"             ),true,doDrag     ) ;
  mm.add(ms,306,tr("Drop"             ),true,doDrop     ) ;
  mm.add(ms,307,tr("Dock"             ),true,doDock     ) ;
  mm.add(mf,401,tr("Classes"          )                 ) ;
  mm.add(mf,402,tr("Functions"        )                 ) ;
  if (InheritClass.length()>0)                            {
    me = mm.addMenu(tr("Export"       ))                  ;
    mm.add(me,901,tr("Export to C++"))                    ;
  }                                                       ;
  mm . setFont(plan)                                      ;
  aa = mm.exec()                                          ;
  if (IsNull(aa)) return true                             ;
  int  columns                                            ;
  bool okay = false                                       ;
  QString ncName                                          ;
  switch (mm[aa])                                         {
    case 101                                              :
      ncName = QInputDialog::getText                      (
                 this                                     ,
                 tr("Set class name")                     ,
                 tr("Class name:")                        ,
                 QLineEdit::Normal                        ,
                 InheritClass                             ,
                 &okay                                  ) ;
      if (okay)                                           {
        InheritClass = ncName                             ;
        setWindowTitle(InheritClass)                      ;
      }                                                   ;
    break                                                 ;
    case 102                                              :
      columns = QInputDialog::getInt                      (
                  this                                    ,
                  tr("Set columns")                       ,
                  tr("Columns:")                          ,
                  columnCount()                           ,
                  1,100,1,&okay                         ) ;
      if (okay)                                           {
        setColumnCount(columns)                           ;
      }                                                   ;
    break                                                 ;
    case 103                                              :
      columns = QInputDialog::getInt                      (
                  this                                    ,
                  tr("Test items")                        ,
                  tr("Items:")                            ,
                  1                                       ,
                  1,10000,1,&okay                       ) ;
      if (okay)                                           {
        for (int i=0;i<columns;i++)                       {
          NewTreeWidgetItem(ztem)                         ;
          for (int j=0;j<columnCount();j++)               {
            QString s                                     ;
            s = QString("%1/%2").arg(i).arg(j)            ;
            ztem->setText(j,s)                            ;
          }                                               ;
          setAlignments(ztem)                             ;
          addTopLevelItem(ztem)                           ;
        }                                                 ;
      }                                                   ;
    break                                                 ;
    case 104                                              :
      clear ( )                                           ;
    break                                                 ;
    case 201                                              :
      setRootIsDecorated     (aa->isChecked())            ;
    break                                                 ;
    case 202                                              :
      setAlternatingRowColors(aa->isChecked())            ;
    break                                                 ;
    case 203                                              :
      TAE = new TextAlignEditor(this)                     ;
      if (Alignments.contains(currentColumn()))           {
        TAE->setAlignment(Alignments[currentColumn()])    ;
      }                                                   ;
      if (TAE->exec()==QDialog::Accepted)                 {
        Alignments[currentColumn()] = TAE->Alignment()    ;
      }                                                   ;
    break                                                 ;
    case 204                                              :
      setColumnHidden(currentColumn(),aa->isChecked())    ;
    break                                                 ;
    case 205                                              :
      setHeaderHidden(aa->isChecked())                    ;
    break                                                 ;
    case 301                                              :
      item   = headerItem()                               ;
      if (IsNull(item)) return true                       ;
      ncName = item->text(currentColumn())                ;
      ncName = QInputDialog::getText                      (
                 this                                     ,
                 tr("Set column label")                   ,
                 tr("Label:")                             ,
                 QLineEdit::Normal                        ,
                 ncName                                   ,
                 &okay                                  ) ;
      if (okay)                                           {
        item->setText(currentColumn(),ncName)             ;
      }                                                   ;
    break                                                 ;
    case 302                                              :
      columns = 0                                         ;
      if (EditStyles.contains(currentColumn()))           {
        columns = EditStyles[currentColumn()]             ;
      }                                                   ;
      tis << tr ( "None"           )                      ;
      tis << tr ( "QLineEdit"      )                      ;
      tis << tr ( "QComboBox"      )                      ;
      tis << tr ( "QSpinBox"       )                      ;
      tis << tr ( "QDoubleSpinBox" )                      ;
      ncName = QInputDialog::getItem                      (
                 this                                     ,
                 tr("Set editor")                         ,
                 tr("Widget")                             ,
                 tis                                      ,
                 columns                                  ,
                 false                                    ,
                 &okay                                  ) ;
      if (okay)                                           {
        columns = tis.indexOf(ncName)                     ;
        if (columns>=0)                                   {
          EditStyles[currentColumn()] = columns           ;
        }                                                 ;
      }                                                   ;
    break                                                 ;
    case 303                                              :
      EditAttributes[11] = aa->isChecked()                ;
    break                                                 ;
    case 304                                              :
      EditAttributes[12] = aa->isChecked()                ;
    break                                                 ;
    case 305                                              :
      EditAttributes[13] = aa->isChecked()                ;
    break                                                 ;
    case 306                                              :
      EditAttributes[14] = aa->isChecked()                ;
    break                                                 ;
    case 307                                              :
      EditAttributes[15] = aa->isChecked()                ;
    break                                                 ;
    case 311                                              :
      ncName = QInputDialog::getText                      (
                 this                                     ,
                 tr("Set window title")                   ,
                 tr("Title:")                             ,
                 QLineEdit::Normal                        ,
                 windowTitle()                            ,
                 &okay                                  ) ;
      if (okay)                                           {
        setWindowTitle(ncName)                            ;
      }                                                   ;
    break                                                 ;
    case 401                                              :
    break                                                 ;
    case 402                                              :
    break                                                 ;
    case 901                                              :
      ExportToCpp ( )                                     ;
    break                                                 ;
  }                                                       ;
  return true                                             ;
}

void N::TreeWidget::DropCommands(void)
{
  LaunchCommands ( ) ;
}

void N::TreeWidget::Execute(int command)
{
  start ( command ) ;
}

void N::TreeWidget::NewItem(int column)
{
  NewTreeWidgetItem ( IT                        ) ;
  IT -> setData     ( column , Qt::UserRole , 0 ) ;
  addTopLevelItem   ( IT                        ) ;
  scrollToItem      ( IT                        ) ;
  doubleClicked     ( IT , column               ) ;
}

void N::TreeWidget::RenameItem(int column)
{
  QTreeWidgetItem * item = currentItem() ;
  nDropOut      ( IsNull(item)  )        ;
  doubleClicked ( item , column )        ;
}

bool N::TreeWidget::startup(void)
{
  return true ;
}

void N::TreeWidget::WaitClear(void)
{
  emit clearItems (    )                                    ;
  while ( ( topLevelItemCount ( ) > 0 ) && NotStopped ( ) ) {
    Time::skip    ( 10 )                                    ;
  }                                                         ;
}
