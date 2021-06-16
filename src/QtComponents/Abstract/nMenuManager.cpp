#include <qtcomponents.h>

N::MenuManager:: MenuManager(QWidget * parent)
{
  menu  = new QMenu    ( parent                           ) ;
  menu -> setAttribute ( Qt::WA_InputMethodEnabled , true ) ;
}

N::MenuManager::~MenuManager(void)
{
  menu -> deleteLater ( ) ;
  menu  = NULL            ;
}

QAction * N::MenuManager::exec(QPoint pos)
{
  if (actions.count()<=0) return NULL ;
  return menu->exec(pos)              ;
}

void N::MenuManager::add(NAMEs Menu)
{
  UUIDs Uuids = Menu.keys() ;
  SUID  uuid                ;
  foreach (uuid,Uuids)      {
    add(uuid,Menu[uuid])    ;
  }                         ;
}

QAction * N::MenuManager::add(int Id,QString text)
{
  QAction   * a = menu->addAction(text) ;
  actions  << a                         ;
  IDs [ a ] = Id                        ;
  return a                              ;
}

QAction * N::MenuManager::add(int Id,QIcon icon,QString text)
{
  QAction   * a = menu->addAction(icon,text) ;
  actions  << a                              ;
  IDs [ a ] = Id                             ;
  return a                                   ;
}

QAction * N::MenuManager::add(int Id,QString text,bool checkable,bool checked)
{
  QAction   * a = menu->addAction(text) ;
  actions  << a                         ;
  IDs [ a ] = Id                        ;
  a -> setCheckable ( checkable )       ;
  a -> setChecked   ( checked   )       ;
  return a                              ;
}

QAction * N::MenuManager::add(int Id,QIcon icon,QString text,bool checkable,bool checked)
{
  QAction   * a = menu->addAction(icon,text) ;
  actions  << a                              ;
  IDs [ a ] = Id                             ;
  a -> setCheckable ( checkable )            ;
  a -> setChecked   ( checked   )            ;
  return a                                   ;
}

QAction * N::MenuManager::addSeparator (void)
{
  return menu -> addSeparator ( ) ;
}

QMenu * N::MenuManager::addMenu(QString title)
{
  QMenu * m = menu -> addMenu( title ) ;
  menus << m                           ;
  return  m                            ;
}

QMenu * N::MenuManager::addMenu(QMenu * m,QString title)
{
  QMenu * n = m -> addMenu( title ) ;
  menus << n                        ;
  return  n                         ;
}

QAction * N::MenuManager::add(QMenu * m,int Id,QString text)
{
  QAction  * a = m->addAction(text) ;
  actions << a                      ;
  IDs[a]   = Id                     ;
  return a                          ;
}

QAction * N::MenuManager::add(QMenu * m,int Id,QIcon icon,QString text)
{
  QAction  * a = m->addAction(icon,text) ;
  actions << a                           ;
  IDs[a]   = Id                          ;
  return a                               ;
}

QAction * N::MenuManager::add(QMenu * m,int Id,QString text,bool checkable,bool checked)
{
  QAction   * a = m->addAction(text) ;
  actions  << a                      ;
  IDs [ a ] = Id                     ;
  a -> setCheckable ( checkable )    ;
  a -> setChecked   ( checked   )    ;
  return a                           ;
}

QAction * N::MenuManager::add(QMenu * m,int Id,QIcon icon,QString text,bool checkable,bool checked)
{
  QAction   * a = m->addAction(icon,text) ;
  actions  << a                           ;
  IDs [ a ] = Id                          ;
  a -> setCheckable ( checkable )         ;
  a -> setChecked   ( checked   )         ;
  return a                                ;
}

QAction * N::MenuManager::addSeparator(QMenu * m)
{
  return m -> addSeparator ( ) ;
}

QAction * N::MenuManager::add(int Id,QWidget * W)
{
  QWidgetAction * widgetAction = new QWidgetAction(menu->parentWidget()) ;
  widgetAction->setDefaultWidget(W)                                      ;
  QAction       * a            = (QAction *)widgetAction                 ;
  menu     -> addAction ( a )                                            ;
  actions  << a                                                          ;
  IDs     [  a ] = Id                                                    ;
  Widgets [ Id ] = W                                                     ;
  return a                                                               ;
}

QAction * N::MenuManager::add(QMenu * m,int Id,QWidget * W)
{
  QWidgetAction * widgetAction = new QWidgetAction(menu->parentWidget()) ;
  widgetAction->setDefaultWidget(W)                                      ;
  QAction       * a            = (QAction *)widgetAction                 ;
  m        -> addAction ( a )                                            ;
  actions  << a                                                          ;
  IDs     [ a  ] = Id                                                    ;
  Widgets [ Id ] = W                                                     ;
  return a                                                               ;
}

bool N::MenuManager::contains(QAction * action)
{
  nKickOut ( IsNull(action) , false  ) ;
  return actions . contains ( action ) ;
}

int N::MenuManager::operator [] (QAction * action)
{
  if (!IDs.contains(action)) return -1 ;
  return IDs [ action ]                ;
}

void N::MenuManager::setFont(QFont font)
{
  menu -> setFont ( font )          ;
  for (int i=0;i<menus.count();i++) {
    menus[i]->setFont(font)         ;
  }                                 ;
}

void N::MenuManager::setFont(Font f)
{
  menu -> setFont ( f )             ;
  for (int i=0;i<menus.count();i++) {
    menus[i]->setFont(f)            ;
  }                                 ;
}

void N::MenuManager::setFont(Plan * plan)
{
  setFont ( plan -> fonts [ N::Fonts::Menu ] ) ;
}

QActionGroup * N::MenuManager::group(int Id)
{
  if ( ! actionGroups . contains ( Id ) ) return NULL ;
  return actionGroups [ Id ]                          ;
}

int N::MenuManager::setGroup(int Id,QActionGroup * group)
{
  actionGroups [ Id ]  = group ;
  return Id                    ;
}

QWidget * N::MenuManager::widget(int Id)
{
  if (!Widgets.contains(Id)) return NULL ;
  return Widgets [ Id ]                  ;
}
