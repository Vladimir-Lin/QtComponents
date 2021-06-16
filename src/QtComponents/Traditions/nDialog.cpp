#include <qtcomponents.h>

N::Dialog :: Dialog     (QWidget * parent,Plan * p     )
           : QDialog    (          parent              )
           , VirtualGui (          this  ,       p     )
           , Thread     (          0     ,       false )
{
  WidgetClass                                   ;
  setAttribute ( Qt::WA_InputMethodEnabled    ) ;
  ///////////////////////////////////////////////
  if ( NotNull ( plan ) )                       {
    Data . Controller = & ( plan->canContinue ) ;
  }                                             ;
}

N::Dialog ::~Dialog(void)
{
}
