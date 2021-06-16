#include <qtcomponents.h>

N::StackedWidget :: StackedWidget  ( QWidget * parent , Plan * p )
                  : QStackedWidget (           parent            )
                  , VirtualGui     (           this   ,        p )
                  , Thread         (           0      ,    false )
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

N::StackedWidget ::~StackedWidget(void)
{
}

void N::StackedWidget::DropCommands(void)
{
  LaunchCommands ( ) ;
}

void N::StackedWidget::AttachMenu(QMenu * menu,QActionGroup * group)
{
  for (int i=0;i<count();i++)                           {
    QWidget * w = widget ( i )                          ;
    QAction * a                                         ;
    a      = menu -> addAction ( w -> windowTitle ( ) ) ;
    a     -> setCheckable ( true )                      ;
    group -> addAction    ( a    )                      ;
  }                                                     ;
}
