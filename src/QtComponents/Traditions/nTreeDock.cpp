#include <qtcomponents.h>

N::TreeDock:: TreeDock           ( QWidget * parent , Plan * p )
            : TreeWidget         (           parent ,        p )
            , AttachDock         (                           p )
            , dockingOrientation ( 0                           )
            , dockingPlace       ( Qt::RightDockWidgetArea     )
            , dockingPlaces      ( Qt::TopDockWidgetArea       |
                                   Qt::BottomDockWidgetArea    |
                                   Qt::LeftDockWidgetArea      |
                                   Qt::RightDockWidgetArea     )
{
  WidgetClass                                                       ;
  setRootIsDecorated      ( false                                 ) ;
  setAlternatingRowColors ( true                                  ) ;
  MountClicked            ( 2                                     ) ;
  setFunction             ( N::AttachDock::FunctionDocking , true ) ;
  LocalMsgs [ AttachToMdi  ] = tr("Move to window area")            ;
  LocalMsgs [ AttachToDock ] = tr("Move to dock area"  )            ;
}

N::TreeDock::~TreeDock (void)
{
}

void N::TreeDock::Docking        (
       QMainWindow      *  Main  ,
       QString             title ,
       Qt::DockWidgetArea  area  ,
       Qt::DockWidgetAreas areas )
{
  AttachDock::Docking(Main,this,title,area,areas) ;
  nConnect(Dock,SIGNAL(visibilityChanged(bool))   ,
           this,SLOT  (Visible          (bool)) ) ;
}

void N::TreeDock::Visible(bool visible)
{
  Visiblity(visible) ;
}

void N::TreeDock::DockIn(bool shown)
{
  Show(shown);
}

QTreeWidgetItem * N::TreeDock::addItem(QString text,SUID uuid,int column)
{
  NewTreeWidgetItem (IT                      ) ;
  IT->setText       (column,text             ) ;
  IT->setData       (column,Qt::UserRole,uuid) ;
  addTopLevelItem   (IT                      ) ;
  return IT                                    ;
}

QTreeWidgetItem * N::TreeDock::addItem(QIcon icon,QString text,SUID uuid,int column)
{
  NewTreeWidgetItem (IT                      ) ;
  IT->setText       (column,text             ) ;
  IT->setIcon       (column,icon             ) ;
  IT->setData       (column,Qt::UserRole,uuid) ;
  addTopLevelItem   (IT                      ) ;
  return IT                                    ;
}

void N::TreeDock::doubleClicked(QTreeWidgetItem * item,int column)
{
  SUID uuid = nTreeUuid(item,column) ;
  emit Clicked (uuid)                ;
}

void N::TreeDock::DockingMenu(MenuManager & Menu)
{
  if ( ! isFunction ( N::AttachDock::FunctionDocking ) ) return          ;
  QMdiSubWindow  * mdi    = Casting(QMdiSubWindow,parent())              ;
  QDockWidget    * dock   = Casting(QDockWidget  ,parent())              ;
  if (NotNull(dock) || NotNull(mdi)) Menu . addSeparator ( )             ;
  nIfSafe(dock) Menu . add ( AttachToMdi  , LocalMsgs [ AttachToMdi  ] ) ;
  nIfSafe(mdi ) Menu . add ( AttachToDock , LocalMsgs [ AttachToDock ] ) ;
}

bool N::TreeDock::RunDocking(MenuManager & Menu,QAction * action)
{
  switch (Menu[action])                        {
    case AttachToMdi                           :
      emit attachMdi (this,dockingOrientation) ;
    break                                      ;
    case AttachToDock                          :
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
