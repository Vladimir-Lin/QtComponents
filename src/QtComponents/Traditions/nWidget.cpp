#include <qtcomponents.h>

N::Widget :: Widget     (QWidget * parent,Plan * p     )
           : QWidget    (          parent              )
           , VirtualGui (          this  ,       p     )
           , Thread     (          0     ,       false )
{
  WidgetClass                                   ;
  addIntoWidget ( parent , this             )   ;
  setAttribute  ( Qt::WA_InputMethodEnabled )   ;
  addConnector  ( "Commando"                    ,
                  Commando                      ,
                  SIGNAL ( timeout      ( ) )   ,
                  this                          ,
                  SLOT   ( DropCommands ( ) ) ) ;
  onlyConnector ( "Commando"                  ) ;
  ///////////////////////////////////////////////
  if ( NotNull ( plan ) )                       {
    Data . Controller = & ( plan->canContinue ) ;
  }                                             ;
}

N::Widget ::~Widget(void)
{
}

void N::Widget::DropCommands(void)
{
  LaunchCommands ( ) ;
}

bool N::Widget::event(QEvent * event)
{
  if (permitGesture() && gestureEvent(event)) return true ;
  return QWidget::event(event)                            ;
}
