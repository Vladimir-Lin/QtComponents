#include <qtcomponents.h>

N::DoubleSpinBox :: DoubleSpinBox  (QWidget * parent,Plan * p)
                  : QDoubleSpinBox (          parent         )
                  , VirtualGui     (          this  ,       p)
                  , External       (NULL                     )
{
  setAttribute  ( Qt::WA_InputMethodEnabled                  ) ;
  addConnector  ( "Value"                                      ,
                  this    , SIGNAL ( valueChanged (double) )   ,
                  this    , SLOT   ( assignValue  (double) ) ) ;
  addConnector  ( "Commando"                                   ,
                  Commando                                     ,
                  SIGNAL ( timeout      ( ) )                  ,
                  this                                         ,
                  SLOT   ( DropCommands ( ) )                ) ;
  onlyConnector ( "Value"                                    ) ;
  onlyConnector ( "Commando"                                 ) ;
}

N::DoubleSpinBox ::~DoubleSpinBox(void)
{
}

void N::DoubleSpinBox::DropCommands(void)
{
  LaunchCommands ( ) ;
}

void N::DoubleSpinBox::assignValue(double value)
{
  nDropOut ( IsNull(External) ) ;
  (*External) = value           ;
}
