#include <qtcomponents.h>

N::ControlPad:: ControlPad         ( QWidget      * parent , Plan * p )
              : Splitter           ( Qt::Vertical , parent ,        p )
              , AttachDock         (                                p )
              , dockingOrientation ( 0                                )
              , dockingPlace       ( Qt::RightDockWidgetArea          )
              , dockingPlaces      ( Qt::TopDockWidgetArea            |
                                     Qt::BottomDockWidgetArea         |
                                     Qt::LeftDockWidgetArea           |
                                     Qt::RightDockWidgetArea          )
              , ToolStack          ( NULL                             )
              , ViewStack          ( NULL                             )
              , Top                ( NULL                             )
              , ButtonPad          ( NULL                             )
              , Close              ( NULL                             )
              , Position           ( NULL                             )
              , Tools              ( NULL                             )
              , Empty              ( NULL                             )
              , Lastest            ( 1                                )
{
  Configure ( ) ;
}

N::ControlPad::~ControlPad (void)
{
}

void N::ControlPad::Configure(void)
{
  QString sss    = "QStackedWidget { background: rgb(255,255,255) ; }"       ;
  ToolStack      = new QStackedWidget  ( this                         )      ;
  ViewStack      = new QStackedWidget  ( this                         )      ;
  Top            = new QSplitter       ( Qt::Horizontal , ToolStack   )      ;
  ButtonPad      = new QWidget         ( Top                          )      ;
  Close          = new QToolButton     ( ButtonPad                    )      ;
  Position       = new QToolButton     ( ButtonPad                    )      ;
  Tools          = new QComboBox       ( Top                          )      ;
  Empty          = new QLabel          ( ViewStack                    )      ;
  ////////////////////////////////////////////////////////////////////////////
  ViewStack -> setStyleSheet           ( sss                          )      ;
  ////////////////////////////////////////////////////////////////////////////
  ToolStack -> setMinimumHeight        ( 28                           )      ;
  ToolStack -> setMaximumHeight        ( 28                           )      ;
  addWidget                            ( ViewStack                    )      ;
  addWidget                            ( ToolStack                    )      ;
  ViewStack -> addWidget               ( Empty                        )      ;
  ////////////////////////////////////////////////////////////////////////////
  Top       -> setHandleWidth          ( 0                            )      ;
  Top       -> setMinimumHeight        ( 28                           )      ;
  Top       -> setMaximumHeight        ( 28                           )      ;
  ToolStack -> addWidget               ( Top                          )      ;
  ////////////////////////////////////////////////////////////////////////////
  Top       -> addWidget               ( ButtonPad                    )      ;
  Top       -> addWidget               ( Tools                        )      ;
  ButtonPad -> setMinimumWidth         ( 56                           )      ;
  ButtonPad -> setMaximumWidth         ( 56                           )      ;
  ////////////////////////////////////////////////////////////////////////////
  Close     -> setGeometry             (  0 ,  0 , 28 , 28            )      ;
  Close     -> setAutoRaise            ( true                         )      ;
  Close     -> setIcon                 ( QIcon(":/images/close.png")  )      ;
  Close     -> setToolTip              ( tr("Close control widget")   )      ;
  ////////////////////////////////////////////////////////////////////////////
  Position  -> setGeometry             ( 28 ,  0 , 28 , 28            )      ;
  Position  -> setAutoRaise            ( true                         )      ;
  Position  -> setIcon                 ( QIcon(":/images/hide.png" )  )      ;
  Position  -> setToolTip              ( tr("Change docking position"))      ;
  ////////////////////////////////////////////////////////////////////////////
  setHandleWidth                       ( 1                            )      ;
  setMinimumWidth                      ( 160                          )      ;
  setMinimumHeight                     ( 160                          )      ;
  ////////////////////////////////////////////////////////////////////////////
  ToolStack -> setCurrentWidget        ( Top                          )      ;
  ViewStack -> setCurrentWidget        ( Empty                        )      ;
  ////////////////////////////////////////////////////////////////////////////
  Close     -> setEnabled              ( false                        )      ;
  Tools     -> setEnabled              ( false                        )      ;
  Tools     -> setEditable             ( true                         )      ;
  Empty     -> setText                 ( tr("No controller" )         )      ;
  Empty     -> setAlignment            ( Qt::AlignCenter              )      ;
  ////////////////////////////////////////////////////////////////////////////
  ViewStack      -> setMouseTracking   ( true                         )      ;
  ViewStack      -> setFocusPolicy     ( Qt::WheelFocus               )      ;
  ////////////////////////////////////////////////////////////////////////////
  addConnector  ( "Leave"                                                    ,
                  this   , SIGNAL ( SendLeave   (QObject*))                  ,
                  this   , SLOT   ( ActualLeave (QObject*))                ) ;
  addConnector  ( "Add"                                                      ,
                  this   , SIGNAL ( SendAdd   (QString,QWidget*,QObject*))   ,
                  this   , SLOT   ( ActualAdd (QString,QWidget*,QObject*)) ) ;
  addConnector  ( "Tools"                                                    ,
                  Tools  , SIGNAL ( activated    (int) )                     ,
                  this   , SLOT   ( WidgetChanged(int) )                   ) ;
  addConnector  ( "Close"                                                    ,
                  Close    , SIGNAL ( clicked        () )                    ,
                  this     , SLOT   ( CloseWidget    () )                  ) ;
  addConnector  ( "Position"                                                 ,
                  Position , SIGNAL ( clicked        () )                    ,
                  this     , SLOT   ( ChangePosition () )                  ) ;
  onlyConnector ( "Leave"                                                  ) ;
  onlyConnector ( "Add"                                                    ) ;
  onlyConnector ( "Tools"                                                  ) ;
  onlyConnector ( "Close"                                                  ) ;
  onlyConnector ( "Position"                                               ) ;
  ////////////////////////////////////////////////////////////////////////////
  ToolStack -> show    (      )                                              ;
  ViewStack -> show    (      )                                              ;
  Top       -> show    (      )                                              ;
  ButtonPad -> show    (      )                                              ;
  Close     -> show    (      )                                              ;
  Position  -> show    (      )                                              ;
  Tools     -> show    (      )                                              ;
  Empty     -> show    (      )                                              ;
  plan      -> setFont ( this )                                              ;
}

void N::ControlPad::Docking        (
       QMainWindow      *  Main  ,
       QString             title ,
       Qt::DockWidgetArea  area  ,
       Qt::DockWidgetAreas areas )
{
  AttachDock::Docking(Main,this,title,area,areas) ;
  nConnect(Dock,SIGNAL(visibilityChanged(bool))   ,
           this,SLOT  (Visible          (bool)) ) ;
}

void N::ControlPad::Visible(bool visible)
{
  Visiblity(visible) ;
}

void N::ControlPad::DockIn(bool shown)
{
  Show       ( shown ) ;
  Relocation (       ) ;
}

void N::ControlPad::resizeEvent(QResizeEvent * event)
{
  QSplitter::resizeEvent ( event ) ;
  Relocation             (       ) ;
}

void N::ControlPad::Relocation(void)
{
}

void N::ControlPad::Leave(QWidget * widget)
{
  Leave ( (QObject *)widget ) ;
}

void N::ControlPad::Leave(QObject * object)
{
  emit SendLeave ( object ) ;
}

void N::ControlPad::Detach(QWidget * widget)
{
  int index = -1                                ;
  if ( ! WidgetId . contains( widget ) ) return ;
  index = WidgetId [ widget ]                   ;
  if ( index < 0 ) return                       ;
  Delete      ( widget )                        ;
  FindCurrent ( index  )                        ;
}

void N::ControlPad::Delete(QWidget * widget)
{
  int index = -1                              ;
  if ( ! WidgetId.contains( widget ) ) return ;
  index = WidgetId [ widget ]                 ;
  if ( index < 0 ) return                     ;
  /////////////////////////////////////////////
  Parents   . take ( widget )                 ;
  WidgetId  . take ( widget )                 ;
  WidgetMap . take ( index  )                 ;
  Titles    . take ( index  )                 ;
  /////////////////////////////////////////////
  int pos = -1                                ;
  for (int i=0;pos<0 && i<Tools->count();i++) {
    int v = Tools->itemData(i).toInt()        ;
    if ( v == index ) pos = i                 ;
  }                                           ;
  if ( pos < 0 ) return                       ;
  /////////////////////////////////////////////
  Tools  -> removeItem  ( pos )               ;
  widget -> deleteLater (     )               ;
}

void N::ControlPad::addControl(QString name,QWidget * widget,QWidget * parent)
{
  nConnect ( parent , SIGNAL ( Leave (QWidget *) )   ,
             this   , SLOT   ( Leave (QWidget *) ) ) ;
  emit SendAdd ( name , widget , (QObject *)widget ) ;
}

void N::ControlPad::addControl(QString name,QWidget * widget,QObject * parent)
{
  nConnect ( parent , SIGNAL ( Leave (QObject *) )   ,
             this   , SLOT   ( Leave (QObject *) ) ) ;
  emit SendAdd ( name , widget , parent )            ;
}

void N::ControlPad::ActualLeave(QObject * object)
{
  int index = Tools->currentIndex()        ;
  if (index<0) return                      ;
  index = Tools->itemData(index).toInt()   ;
  if (index<0) return                      ;
  //////////////////////////////////////////
  QList<QWidget *> Ws = Parents . keys ( ) ;
  QList<QWidget *> Ds                      ;
  for (int i=0;i<Ws.count();i++)           {
    QWidget * w = Ws [ i ]                 ;
    if ( object == Parents [ w ] )         {
      Ds << w                              ;
    }                                      ;
  }                                        ;
  if ( Ds . count ( ) <= 0 ) return        ;
  //////////////////////////////////////////
  for (int i=0;i<Ds.count();i++)           {
    QWidget * w = Ds [ i ]                 ;
    Delete ( w )                           ;
  }                                        ;
  //////////////////////////////////////////
  FindCurrent (  index )                   ;
}

void N::ControlPad::ActualAdd(QString name,QWidget * widget,QObject * parent)
{
  Lastest ++                                   ;
  widget    -> setParent        ( ViewStack )  ;
  ViewStack -> addWidget        ( widget    )  ;
  ViewStack -> setCurrentWidget ( widget    )  ;
  //////////////////////////////////////////////
  Parents   [ widget  ] = parent               ;
  WidgetId  [ widget  ] = Lastest              ;
  WidgetMap [ Lastest ] = widget               ;
  Titles    [ Lastest ] = name                 ;
  //////////////////////////////////////////////
  int index = Tools -> count ( )               ;
  Close  -> setEnabled      ( true           ) ;
  Tools  -> setEnabled      ( true           ) ;
  Tools  -> addItem         ( name , Lastest ) ;
  Tools  -> blockSignals    ( true           ) ;
  Tools  -> setCurrentIndex ( index          ) ;
  Tools  -> blockSignals    ( false          ) ;
}

void N::ControlPad::ChangePosition(void)
{
  QMdiSubWindow * mdi  = Casting(QMdiSubWindow,parent())      ;
  QDockWidget   * dock = Casting(QDockWidget  ,parent())      ;
  nIfSafe(dock) emit attachMdi  ( this , dockingOrientation ) ;
  nIfSafe(mdi ) emit attachDock ( this                        ,
                                  windowTitle ( )             ,
                                  dockingPlace                ,
                                  dockingPlaces             ) ;
}

void N::ControlPad::FindCurrent(int)
{
  if (Tools->count()<=0)                   {
    ViewStack -> setCurrentWidget (Empty)  ;
    Close     -> setEnabled       (false)  ;
    Tools     -> setEnabled       (false)  ;
    Alert ( Error )                        ;
    return                                 ;
  }                                        ;
  //////////////////////////////////////////
  int index = Tools->currentIndex()        ;
  if (index<0) return                      ;
  index = Tools->itemData(index).toInt()   ;
  if ( index < 0 ) return                  ;
  //////////////////////////////////////////
  if ( !WidgetMap.contains(index) ) return ;
  QWidget * w = WidgetMap [ index ]        ;
  ViewStack -> setCurrentWidget ( w )      ;
  Alert ( Click )                          ;
}

void N::ControlPad::CloseWidget(void)
{
  int index = Tools->currentIndex()        ;
  if (index<0) return                      ;
  index = Tools->itemData(index).toInt()   ;
  if ( index < 0 ) return                  ;
  if ( !WidgetMap.contains(index) ) return ;
  QWidget * w = WidgetMap [ index ]        ;
  Delete      ( w     )                    ;
  FindCurrent ( index )                    ;
}

void N::ControlPad::WidgetChanged (int index)
{
  int wid = Tools->itemData(index).toInt()            ;
  if ( wid <= 0 ) return                              ;
  ViewStack -> setCurrentWidget ( WidgetMap [ wid ] ) ;
}

QWidget * N::ControlPad::Find(QString anw)
{
  CUIDs IDs = WidgetMap . keys ( )        ;
  if ( IDs . count ( ) <= 0 ) return NULL ;
  int id                                  ;
  foreach ( id , IDs )                    {
    if ( WidgetMap . contains ( id ) )    {
      QWidget * w = WidgetMap [ id ]      ;
      if ( NULL != w )                    {
        QString anv                       ;
        anv = w -> accessibleName ( )     ;
        if ( anv == anw )                 {
          return w                        ;
        }                                 ;
      }                                   ;
    }                                     ;
  }                                       ;
  return NULL                             ;
}
