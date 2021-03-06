#include <qtcomponents.h>

N::MdiArea:: MdiArea     (QWidget * parent,Plan * p     )
           : QMdiArea    (          parent              )
           , VirtualGui  (          this  ,       p     )
           , Thread      (          0     ,       false )
           , WindowLists (NULL                          )
{
  WidgetClass                   ;
  addIntoWidget ( parent,this ) ;
  Configure     (             ) ;
}

N::MdiArea::~MdiArea (void)
{
}

void N::MdiArea::focusInEvent(QFocusEvent * event)
{
  if (!focusIn (event))            {
    QMdiArea::focusInEvent (event) ;
  }                                ;
  MenuStatus ( )                   ;
}

void N::MdiArea::focusOutEvent(QFocusEvent * event)
{
  if (!focusOut(event))            {
    QMdiArea::focusOutEvent(event) ;
  }                                ;
  MenuStatus ( )                   ;
}

void N::MdiArea::contextMenuEvent(QContextMenuEvent * event)
{
  if (Menu(event->pos())) event->accept(); else
  QMdiArea::contextMenuEvent(event)           ;
}

void N::MdiArea::dragEnterEvent(QDragEnterEvent * event)
{
  if (dragEnter(event)) event->acceptProposedAction() ; else {
    if (PassDragDrop) QMdiArea::dragEnterEvent(event)        ;
    else event->ignore()                                     ;
  }                                                          ;
}

void N::MdiArea::dragLeaveEvent(QDragLeaveEvent * event)
{
  if (removeDrop()) event->accept() ; else            {
    if (PassDragDrop) QMdiArea::dragLeaveEvent(event) ;
    else event->ignore()                              ;
  }                                                   ;
}

void N::MdiArea::dragMoveEvent(QDragMoveEvent * event)
{
  if (dragMove(event)) event->acceptProposedAction() ; else {
    if (PassDragDrop) QMdiArea::dragMoveEvent(event)        ;
    else event->ignore()                                    ;
  }                                                         ;
}

void N::MdiArea::dropEvent(QDropEvent * event)
{
  if (drop(event)) event->acceptProposedAction() ; else {
    if (PassDragDrop) QMdiArea::dropEvent(event)        ;
    else event->ignore()                                ;
  }                                                     ;
}

bool N::MdiArea::acceptDrop(QWidget * source,const QMimeData * mime)
{
  Q_UNUSED ( source ) ;
  Q_UNUSED ( mime   ) ;
  return true         ;
}

bool N::MdiArea::dropNew(QWidget * source,const QMimeData * mime,QPoint pos)
{
  Q_UNUSED ( source ) ;
  Q_UNUSED ( mime   ) ;
  Q_UNUSED ( pos    ) ;
  return true         ;
}

bool N::MdiArea::dropMoving(QWidget * source,const QMimeData * mime,QPoint pos)
{
  Q_UNUSED ( source ) ;
  Q_UNUSED ( mime   ) ;
  Q_UNUSED ( pos    ) ;
  return true         ;
}

bool N::MdiArea::dropAppend(QWidget * source,const QMimeData * mime,QPoint pos)
{
  return dropItems ( source , mime , pos ) ;
}

void N::MdiArea::Connect(QWidget * widget)
{
  nConnect ( widget , SIGNAL(Adjustment(QWidget*,QSize))   ,
             this   , SLOT  (Adjustment(QWidget*,QSize)) ) ;
  nConnect ( widget , SIGNAL(Adjustment(QWidget*      ))   ,
             this   , SLOT  (Adjustment(QWidget*      )) ) ;
  nConnect ( widget , SIGNAL(Leave     (QWidget*      ))   ,
             this   , SLOT  (Leave     (QWidget*      )) ) ;
}

void N::MdiArea::Adjustment(QWidget * widget,QSize size)
{
  QMdiSubWindow * msw = Casting(QMdiSubWindow,widget)                   ;
  if (IsNull(msw)) return                                               ;
  QSize ws = size                                                       ;
  QRect mw = geometry()                                                 ;
  QSize wm = QSize(mw.width(),mw.height())                              ;
  QRect fg = msw->frameGeometry()                                       ;
  QRect wg = msw->geometry()                                            ;
  QSize ms = QSize(fg.width(),fg.height())                              ;
  QSize ds = QSize(wg.width(),wg.height())                              ;
  ms -= ds                                                              ;
  ms += ws                                                              ;
  wm -= ms                                                              ;
  ds  = QSize((wm.width()*(rand()%16)/16),(wm.height()*(rand()%16)/16)) ;
  if (ds.width ()<0) ds.setWidth (0)                                    ;
  if (ds.height()<0) ds.setHeight(0)                                    ;
  msw->move(ds.width(),ds.height())                                     ;
  msw->resize(ms)                                                       ;
  msw->setWindowIcon(widget->windowIcon())                              ;
  MenuStatus ( )                                                        ;
  update     ( )                                                        ;
}

void N::MdiArea::Adjustment(QWidget * widget)
{
  QMdiSubWindow * msw = Casting(QMdiSubWindow,widget)                   ;
  if (IsNull(msw)) return                                               ;
  QSize ws = widget -> size ( )                                         ;
  QRect mw = geometry()                                                 ;
  QSize wm = QSize(mw.width(),mw.height())                              ;
  QRect fg = msw->frameGeometry()                                       ;
  QRect wg = msw->geometry()                                            ;
  QSize ms = QSize(fg.width(),fg.height())                              ;
  QSize ds = QSize(wg.width(),wg.height())                              ;
  ms -= ds                                                              ;
  ms += ws                                                              ;
  wm -= ms                                                              ;
  ds  = QSize((wm.width()*(rand()%16)/16),(wm.height()*(rand()%16)/16)) ;
  if (ds.width ()<0) ds.setWidth (0)                                    ;
  if (ds.height()<0) ds.setHeight(0)                                    ;
  msw->move(ds.width(),ds.height())                                     ;
  msw->resize(ms)                                                       ;
  msw->setWindowIcon(widget->windowIcon())                              ;
  MenuStatus ( )                                                        ;
  update     ( )                                                        ;
}

void N::MdiArea::Leave(QWidget * widget)
{ Q_UNUSED          ( widget ) ;
  MenuStatus        (        ) ;
  update            (        ) ;
  emit childChanged (        ) ;
}

QMdiSubWindow * N::MdiArea::append(QWidget * widget)
{
  MdiSubWindow * msw                                    ;
  msw  = new MdiSubWindow (                           ) ;
  msw -> setWidget        ( widget                    ) ;
  msw -> setAttribute     ( Qt::WA_DeleteOnClose      ) ;
  msw -> setAttribute     ( Qt::WA_InputMethodEnabled ) ;
  addSubWindow            ( msw                       ) ;
  return                    msw                         ;
}

void N::MdiArea::Fit(QWidget * widget)
{
  QSize ws = widget->size()                                             ;
  QMdiSubWindow * msw = append(widget)                                  ;
  msw->setFont(plan->fonts[N::Fonts::Default])                          ;
  QRect mw = geometry()                                                 ;
  QSize wm = QSize(mw.width(),mw.height())                              ;
  QRect fg = msw->frameGeometry()                                       ;
  QRect wg = msw->geometry()                                            ;
  QSize ms = QSize(fg.width(),fg.height())                              ;
  QSize ds = QSize(wg.width(),wg.height())                              ;
  ms -= ds                                                              ;
  ms += ws                                                              ;
  wm -= ms                                                              ;
  ds  = QSize((wm.width()*(rand()%16)/16),(wm.height()*(rand()%16)/16)) ;
  if (ds.width ()<0) ds.setWidth (0)                                    ;
  if (ds.height()<0) ds.setHeight(0)                                    ;
  msw->move(ds.width(),ds.height())                                     ;
  msw->resize(ms)                                                       ;
  msw->setWindowIcon(widget->windowIcon())                              ;
  MenuStatus ( )                                                        ;
  update     ( )                                                        ;
}

void N::MdiArea::Attach(QWidget * widget)
{
  QMdiSubWindow * msw = append(widget)                           ;
  msw->setFont(plan->fonts[N::Fonts::Default])                   ;
  QRect mw = geometry()                                          ;
  QSize sw(mw.width()/4,mw.height()/4)                           ;
  QSize sr(rand()%16,rand()%16)                                  ;
  msw->move(sr.width()*sw.width()/16,sr.height()*sw.height()/16) ;
  msw->resize(sw.width()*3,sw.height()*3)                        ;
  msw->setWindowIcon(widget->windowIcon())                       ;
  MenuStatus ( )                                                 ;
  update     ( )                                                 ;
}

void N::MdiArea::Attach(QWidget * widget,int direction)
{
  QMdiSubWindow * msw = append(widget)                    ;
  msw->setFont(plan->fonts[N::Fonts::Default])            ;
  QRect  mw = geometry()                                  ;
  QSize  sh = widget->sizeHint()                          ;
  QSize  gw                                               ;
  QPoint sp                                               ;
  switch (direction)                                      {
    case 0                                                :
      gw = widget->size()                                 ;
      sp.setX(((mw.width ()-gw.width ())/16)*(rand()%16)) ;
      sp.setY(((mw.height()-gw.height())/16)*(rand()%16)) ;
      if (gw.width()<sh.width())                          {
        gw.setWidth(sh.width())                           ;
      }                                                   ;
      if (gw.height()<sh.height())                        {
        gw.setHeight(sh.height())                         ;
      }                                                   ;
    break                                                 ;
    case Qt::Vertical                                     :
      sp.setX     ((mw.width()/16)*(rand()%10))           ;
      sp.setY     (0)                                     ;
      gw.setWidth (mw.width ()/5)                         ;
      gw.setHeight(mw.height()  )                         ;
      if (gw.width()<sh.width())                          {
        gw.setWidth(sh.width())                           ;
      }                                                   ;
    break                                                 ;
    case Qt::Horizontal                                   :
      sp.setX     (0)                                     ;
      sp.setY     ((mw.height()/16)*(rand()%8))           ;
      gw.setWidth (mw.width())                            ;
      gw.setHeight(mw.height()/3)                         ;
      if (gw.height()<sh.height())                        {
        gw.setHeight(sh.height())                         ;
      }                                                   ;
    break                                                 ;
  }                                                       ;
  msw->move          ( sp                   )             ;
  msw->resize        ( gw                   )             ;
  msw->setWindowIcon ( widget->windowIcon() )             ;
  MenuStatus         (                      )             ;
  update             (                      )             ;
}

void N::MdiArea::subActivated(QMdiSubWindow * window)
{
  if (IsNull(window)) emit lastClosed() ;
  MenuStatus ()                         ;
  update     ()                         ;
}

void N::MdiArea::Subwindow(void)
{
  setViewMode (SubWindowView) ;
  MenuStatus  (             ) ;
  update      (             ) ;
}

void N::MdiArea::Tabbed(void)
{
  setViewMode (TabbedView) ;
  MenuStatus  (          ) ;
  update      (          ) ;
}

void N::MdiArea::Tile(void)
{
  tileSubWindows ( ) ;
  MenuStatus     ( ) ;
  update         ( ) ;
}

void N::MdiArea::Cascade(void)
{
  cascadeSubWindows  ( ) ;
  MenuStatus         ( ) ;
  update             ( ) ;
}

void N::MdiArea::CloseAll(void)
{
  closeAllSubWindows ( ) ;
  MenuStatus         ( ) ;
  update             ( ) ;
}

bool N::MdiArea::contains(QString accName)
{
  QList<QMdiSubWindow *> subws = subWindowList()   ;
  QMdiSubWindow       *  subw                      ;
  foreach (subw,subws)                             {
    if (subw->widget()->accessibleName()==accName) {
      return true                                  ;
    }                                              ;
  }                                                ;
  return false                                     ;
}

QWidget * N::MdiArea::findWidget(QString accName)
{
  QList<QMdiSubWindow *> subws = subWindowList()   ;
  QMdiSubWindow       *  subw                      ;
  foreach (subw,subws)                             {
    if (subw->widget()->accessibleName()==accName) {
      return subw->widget()                        ;
    }                                              ;
  }                                                ;
  return NULL                                      ;
}

QList<QWidget *> N::MdiArea::getWidgets(QString accName)
{
  QList<QWidget       *> Widgets                   ;
  QList<QMdiSubWindow *> subws = subWindowList()   ;
  QMdiSubWindow       *  subw                      ;
  foreach (subw,subws)                             {
    if (subw->widget()->accessibleName()==accName) {
      Widgets << subw->widget()                    ;
    }                                              ;
  }                                                ;
  return Widgets                                   ;
}

void N::MdiArea::setWindowMenu(QMenu * menu)
{
  WindowLists = menu                         ;
  if (IsNull(WindowLists)) return            ;
  WindowLists -> setEnabled ( false )        ;
  connect(WindowLists,SIGNAL(aboutToShow())  ,
          this       ,SLOT  (menuToShow ())) ;
}

void N::MdiArea::menuToShow(void)
{
  nDropOut ( IsNull(WindowLists) )                                ;
  WindowLists -> clear()                                          ;
  MenuActions  . clear()                                          ;
  QList<QMdiSubWindow *> subws = subWindowList ( )                ;
  for (int i=0;i<subws.count();i++)                               {
    QAction * a = WindowLists->addAction(subws[i]->windowTitle()) ;
    a -> setCheckable ( true )                                    ;
    nConnect ( a    , SIGNAL ( toggled         (bool))            ,
               this , SLOT   ( subwindowChecked(bool))          ) ;
    MenuActions << a                                              ;
  }                                                               ;
}

void N::MdiArea::subwindowChecked(bool)
{
  if (IsNull(WindowLists)) return                  ;
  QList<QMdiSubWindow *> subws = subWindowList ( ) ;
  if (subws.count()!=MenuActions.count()) return   ;
  for (int i=0;i<subws.count();i++)                {
    if (MenuActions[i]->isChecked())               {
      subws [i] -> show  (          )              ;
      setActiveSubWindow ( subws[i] )              ;
    }                                              ;
  }                                                ;
  MenuActions  . clear()                           ;
  WindowLists -> clear()                           ;
}

void N::MdiArea::MenuStatus(void)
{
  if (IsNull(plan)) return                                       ;
  plan -> processEvents ()                                       ;
  QList<QMdiSubWindow *> subws = subWindowList ( )               ;
  bool arrangement    = ( subws.count() > 0 )                    ;
  if (NotNull(WindowLists)) WindowLists->setEnabled(arrangement) ;
  QAction * closeall  = plan->Action(N::Menus::CloseAll )        ;
  QAction * cascade   = plan->Action(N::Menus::Cascade  )        ;
  QAction * tile      = plan->Action(N::Menus::Tile     )        ;
  QAction * subwindow = plan->Action(N::Menus::Subwindow)        ;
  QAction * tabbed    = plan->Action(N::Menus::Tabbed   )        ;
  if (NotNull(closeall )) closeall  -> setEnabled  (arrangement) ;
  if (NotNull(cascade  )) cascade   -> setEnabled  (arrangement) ;
  if (NotNull(tile     )) tile      -> setEnabled  (arrangement) ;
  if (NotNull(subwindow)) subwindow -> blockSignals(true       ) ;
  if (NotNull(tabbed   )) tabbed    -> blockSignals(true       ) ;
  switch (viewMode())                                            {
    case SubWindowView                                           :
      if (NotNull(subwindow)) subwindow -> setEnabled (false   ) ;
      if (NotNull(tabbed   )) tabbed    -> setEnabled (true    ) ;
    break                                                        ;
    case TabbedView                                              :
      if (NotNull(subwindow)) subwindow -> setEnabled (true    ) ;
      if (NotNull(tabbed   )) tabbed    -> setEnabled (false   ) ;
      if (arrangement)                                           {
        if (NotNull(cascade)) cascade   -> setEnabled (false   ) ;
        if (NotNull(tile   )) tile      -> setEnabled (false   ) ;
      }                                                          ;
    break                                                        ;
  }                                                              ;
  if (NotNull(subwindow)) subwindow -> blockSignals(false      ) ;
  if (NotNull(tabbed   )) tabbed    -> blockSignals(false      ) ;
  if (!arrangement)                                              {
//    DisableAllActions (            )                             ;
    AssignAction      ( Label , "" )                             ;
  }                                                              ;
}

void N::MdiArea::Configure(void)
{
  setViewMode                  ( SubWindowView                      ) ;
  setAttribute                 ( Qt::WA_InputMethodEnabled          ) ;
  setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff             ) ;
  setVerticalScrollBarPolicy   ( Qt::ScrollBarAlwaysOff             ) ;
  setAcceptDrops               ( true                               ) ;
  setDropFlag                  ( DropUrls , true                    ) ;
  /////////////////////////////////////////////////////////////////////
  Shadow = new QGraphicsDropShadowEffect ( this )                     ;
  setGraphicsEffect ( Shadow )                                        ;
  Shadow -> setBlurRadius ( 3                     )                   ;
  Shadow -> setColor      ( QColor  (224,224,224) )                   ;
  Shadow -> setOffset     ( QPointF (  3,  3    ) )                   ;
  Shadow -> setEnabled    ( true                  )                   ;
  /////////////////////////////////////////////////////////////////////
  addConnector  ( "Activated"                                         ,
                  this , SIGNAL(subWindowActivated(QMdiSubWindow*))   ,
                  this , SLOT  (subActivated      (QMdiSubWindow*)) ) ;
  addConnector  ( "Commando"                                          ,
                  Commando                                            ,
                  SIGNAL ( timeout      ( ) )                         ,
                  this                                                ,
                  SLOT   ( DropCommands ( ) )                       ) ;
  onlyConnector ( "Activated"                                       ) ;
  onlyConnector ( "Commando"                                        ) ;
  /////////////////////////////////////////////////////////////////////
  if ( NotNull ( plan ) )                                             {
    Data . Controller = & ( plan->canContinue )                       ;
  }                                                                   ;
}

bool N::MdiArea::dropUrls(QWidget * source,QPointF pos,const QList<QUrl> & urls)
{ Q_UNUSED  ( source ) ;
  Q_UNUSED  ( pos    ) ;
  emit Files( urls   ) ;
  return true          ;
}

void N::MdiArea::DropCommands(void)
{
  LaunchCommands ( ) ;
}

bool N::MdiArea::Menu(QPoint pos)
{ Q_UNUSED    ( pos       )                                                                        ;
  nScopedMenu ( mm , this )                                                                        ;
  QAction     * aa                                                                                 ;
  QMenu       * me                                                                                 ;
  //////////////////////////////////////////////////////////////////////////////////////////////////
  me = mm . addMenu ( tr("Scroll bar")                                                           ) ;
  mm . add ( me,60001,tr("Horizontal"),true,horizontalScrollBarPolicy() == Qt::ScrollBarAsNeeded ) ;
  mm . add ( me,60002,tr("Vertical"  ),true,verticalScrollBarPolicy  () == Qt::ScrollBarAsNeeded ) ;
  //////////////////////////////////////////////////////////////////////////////////////////////////
  mm . setFont ( plan                )                                                             ;
  aa = mm.exec (                     )                                                             ;
  nKickOut     ( IsNull(aa) , true   )                                                             ;
  //////////////////////////////////////////////////////////////////////////////////////////////////
  switch ( mm [ aa ] )                                                                             {
    case 60001                                                                                     :
      if ( aa->isChecked() ) setHorizontalScrollBarPolicy ( Qt::ScrollBarAsNeeded  )               ;
                        else setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff )               ;
    break                                                                                          ;
    case 60002                                                                                     :
      if ( aa->isChecked() ) setVerticalScrollBarPolicy   ( Qt::ScrollBarAsNeeded  )               ;
                        else setVerticalScrollBarPolicy   ( Qt::ScrollBarAlwaysOff )               ;
    break                                                                                          ;
  }                                                                                                ;
  return true                                                                                      ;
}
