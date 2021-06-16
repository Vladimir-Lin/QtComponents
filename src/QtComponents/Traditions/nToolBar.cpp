#include <qtcomponents.h>

N::ToolBar :: ToolBar    (QWidget * parent,Plan * p     )
            : QToolBar   (          parent              )
            , VirtualGui (          this  ,       p     )
            , Thread     (          0     ,       false )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::ToolBar ::~ToolBar(void)
{
}

void N::ToolBar::Configure(void)
{
  setAttribute  ( Qt::WA_InputMethodEnabled                      ) ;
  addConnector  ( "Visibility"                                     ,
                  this     , SIGNAL ( visibilityChanged (bool) )   ,
                  this     , SLOT   ( geometryChanged   (bool) ) ) ;
  addConnector  ( "Geometry"                                       ,
                  this     , SIGNAL ( topLevelChanged   (bool) )   ,
                  this     , SLOT   ( geometryChanged   (bool) ) ) ;
  addConnector  ( "Commando"                                       ,
                  Commando                                         ,
                  SIGNAL ( timeout        ( ) )                    ,
                  this                                             ,
                  SLOT   ( DropCommands   ( ) )                  ) ;
  onlyConnector ( "Visibility" )                                   ;
  onlyConnector ( "Geometry"   )                                   ;
  onlyConnector ( "Commando"   )                                   ;
  //////////////////////////////////////////////////////////////////
  if ( NotNull ( plan ) )                                          {
    Data . Controller = & ( plan->canContinue )                    ;
  }                                                                ;
}

void N::ToolBar::resizeEvent(QResizeEvent * e)
{
  QToolBar::resizeEvent ( e ) ;
  Relocation            (   ) ;
}

void N::ToolBar::showEvent(QShowEvent * e)
{
  QToolBar::showEvent ( e ) ;
  Relocation          (   ) ;
}

bool N::ToolBar::Relocation(void)
{
  return false ;
}

void N::ToolBar::geometryChanged(bool)
{
  Relocation ( ) ;
}

void N::ToolBar::DropCommands(void)
{
  LaunchCommands ( ) ;
}
