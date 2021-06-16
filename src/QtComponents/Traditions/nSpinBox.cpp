#include <qtcomponents.h>

N::SpinBox :: SpinBox    (QWidget * parent,Plan * p)
            : QSpinBox   (          parent         )
            , VirtualGui (          this  ,       p)
            , External   (NULL                     )
{
  setAttribute  ( Qt::WA_InputMethodEnabled               ) ;
  addConnector  ( "Value"                                   ,
                  this    , SIGNAL ( valueChanged (int) )   ,
                  this    , SLOT   ( assignValue  (int) ) ) ;
  addConnector  ( "Commando"                                ,
                  Commando                                  ,
                  SIGNAL ( timeout      ( ) )               ,
                  this                                      ,
                  SLOT   ( DropCommands ( ) )             ) ;
  onlyConnector ( "Value"                                 ) ;
  onlyConnector ( "Commando"                              ) ;
}

N::SpinBox ::~SpinBox(void)
{
}

void N::SpinBox::DropCommands(void)
{
  LaunchCommands ( ) ;
}

void N::SpinBox::assignValue(int value)
{
  nDropOut ( IsNull(External) ) ;
  (*External) = value           ;
}
