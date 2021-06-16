#include <qtcomponents.h>

N::ScrollArea :: ScrollArea  ( QWidget * parent , Plan * p )
               : QScrollArea (           parent            )
               , VirtualGui  (           this   ,        p )
{
  addIntoWidget ( parent , this               ) ;
  setAttribute  ( Qt::WA_InputMethodEnabled   ) ;
  addConnector  ( "Commando"                    ,
                  Commando                      ,
                  SIGNAL ( timeout      ( ) )   ,
                  this                          ,
                  SLOT   ( DropCommands ( ) ) ) ;
  onlyConnector ( "Commando"                  ) ;
}

N::ScrollArea ::~ScrollArea(void)
{
}

void N::ScrollArea::DropCommands(void)
{
  LaunchCommands ( ) ;
}
