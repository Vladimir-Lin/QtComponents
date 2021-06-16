#include <qtcomponents.h>

N::ScrollDock:: ScrollDock (QWidget * parent,Plan * p)
              : ScrollArea (          parent,       p)
              , AttachDock (                        p)
{
}

N::ScrollDock::~ScrollDock (void)
{
}

QSize N::ScrollDock::sizeHint (void) const
{
  return SizeSuggestion ( QSize ( 640 , 200 ) ) ;
}

void N::ScrollDock::Docking ( QMainWindow       * Main  ,
                              QString             title ,
                              Qt::DockWidgetArea  area  ,
                              Qt::DockWidgetAreas areas )
{
  AttachDock::Docking ( Main , this , title , area , areas ) ;
  addConnector  ( "Visible"                                  ,
                  Dock                                       ,
                  SIGNAL ( visibilityChanged(bool) )         ,
                  this                                       ,
                  SLOT   ( Visible          (bool) )       ) ;
  onlyConnector ( "Visible"                                ) ;
}

void N::ScrollDock::Visible(bool visible)
{
  Visiblity ( visible ) ;
}

void N::ScrollDock::DockIn(bool shown)
{
  Show ( shown ) ;
}
