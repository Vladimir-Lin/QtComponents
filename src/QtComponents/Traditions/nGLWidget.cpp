#include <qtcomponents.h>

N::GLWidget :: GLWidget   (const QGLFormat & format,QWidget * parent,Plan * p)
             : QGLWidget  (                  format,          parent         )
             , VirtualGui (                                   this  ,       p)
             , Thread     (0,false                                           )
{
  WidgetClass                                   ;
  addIntoWidget ( parent , this               ) ;
  setAttribute  ( Qt::WA_InputMethodEnabled   ) ;
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

N::GLWidget ::~GLWidget(void)
{
}

void N::GLWidget::DropCommands(void)
{
  LaunchCommands ( ) ;
}

bool N::GLWidget::event(QEvent * event)
{
  if (permitGesture() && gestureEvent(event)) return true ;
  return QGLWidget::event(event)                          ;
}
