#include <qtcomponents.h>

N::PanWidget:: PanWidget ( QWidget        * parent , Plan * p )
             : Splitter  ( Qt::Horizontal , parent ,        p )
             , Stack     ( NULL                               )
             , Left      ( NULL                               )
             , Right     ( NULL                               )
             , Hidden    ( false                              )
{
  Configure ( ) ;
}

N::PanWidget::~PanWidget (void)
{
}

bool N::PanWidget::isHidden(void)
{
  return Hidden ;
}

void N::PanWidget::setHidden(bool enable)
{
  Hidden = enable ;
}

int N::PanWidget::addWidget(QWidget * widget)
{
  nKickOut ( IsNull(Stack ) , -1 )     ;
  nKickOut ( IsNull(widget) , -1 )     ;
  int index = Stack->addWidget(widget) ;
  CheckIndex ( )                       ;
  return index                         ;
}

int N::PanWidget::count(void) const
{
  nKickOut ( IsNull(Stack) , 0 ) ;
  return Stack -> count ( )      ;
}

int N::PanWidget::currentIndex(void) const
{
  nKickOut ( IsNull(Stack) , -1  ) ;
  return Stack -> currentIndex ( ) ;
}

QWidget * N::PanWidget::currentWidget(void) const
{
  nKickOut ( IsNull(Stack) , NULL ) ;
  return Stack -> currentWidget ( ) ;
}

int N::PanWidget::indexOf(QWidget * widget) const
{
  nKickOut ( IsNull(Stack) , -1  ) ;
  return Stack -> indexOf (widget) ;
}

int N::PanWidget::insertWidget(int index,QWidget * widget)
{
  nKickOut                        ( IsNull(Stack ) , -1     ) ;
  nKickOut                        ( IsNull(widget) , -1     ) ;
  int pos = Stack -> insertWidget ( index          , widget ) ;
  CheckIndex                      (                         ) ;
  return pos                                                  ;
}

void N::PanWidget::removeWidget(QWidget * widget)
{
  nDropOut              ( IsNull(Stack) ) ;
  Stack -> removeWidget ( widget        ) ;
  CheckIndex            (               ) ;
}

QWidget * N::PanWidget::widget(int index) const
{
  nKickOut ( IsNull(Stack) , NULL ) ;
  return Stack -> widget ( index  ) ;
}

void N::PanWidget::setCurrentIndex(int index)
{
  nDropOut                 ( IsNull(Stack) ) ;
  Stack -> setCurrentIndex ( index         ) ;
  CheckIndex               (               ) ;
}

void N::PanWidget::setCurrentWidget(QWidget * widget)
{
  nDropOut                  ( IsNull(Stack) ) ;
  Stack -> setCurrentWidget ( widget        ) ;
  CheckIndex                (               ) ;
}

void N::PanWidget::Configure(void)
{
  setHandleWidth             ( 1                               ) ;
  ////////////////////////////////////////////////////////////////
  Left   = new QToolButton   ( this                            ) ;
  Stack  = new StackedWidget ( this , plan                     ) ;
  Right  = new QToolButton   ( this                            ) ;
  ////////////////////////////////////////////////////////////////
  Left  -> setIcon           ( QIcon(":/images/moveLeft.png" ) ) ;
  Left  -> setAutoRaise      ( true                            ) ;
  ////////////////////////////////////////////////////////////////
  Right -> setIcon           ( QIcon(":/images/moveRight.png") ) ;
  Right -> setAutoRaise      ( true                            ) ;
  ////////////////////////////////////////////////////////////////
  setHandleSize              ( 24                              ) ;
  QSplitter :: addWidget     ( Left                            ) ;
  QSplitter :: addWidget     ( Stack                           ) ;
  QSplitter :: addWidget     ( Right                           ) ;
  setEnabled                 ( false                           ) ;
  ////////////////////////////////////////////////////////////////
  nConnect ( Stack , SIGNAL ( currentChanged(int) )              ,
             this  , SIGNAL ( currentChanged(int) )            ) ;
  nConnect ( Stack , SIGNAL ( widgetRemoved (int) )              ,
             this  , SIGNAL ( widgetRemoved (int) )            ) ;
  ////////////////////////////////////////////////////////////////
  nConnect ( Left  , SIGNAL ( clicked  ( ) )                     ,
             this  , SLOT   ( Previous ( ) )                   ) ;
  nConnect ( Right , SIGNAL ( clicked  ( ) )                     ,
             this  , SLOT   ( Next     ( ) )                   ) ;
}

bool N::PanWidget::FocusIn(void)
{
  AssignAction ( Label , windowTitle() ) ;
  CheckIndex   (                       ) ;
  return true                            ;
}

void N::PanWidget::setHandleSize(int width)
{
  Left  -> setMinimumWidth ( width ) ;
  Left  -> setMaximumWidth ( width ) ;
  Right -> setMinimumWidth ( width ) ;
  Right -> setMaximumWidth ( width ) ;
}

void N::PanWidget::CheckIndex(void)
{
  setEnabled            ( count               () >  0 ) ;
  nDropOut              ( count               () <= 0 ) ;
  nDropOut              ( IsNull(Left )               ) ;
  nDropOut              ( IsNull(Right)               ) ;
  Left  -> setEnabled   ( currentIndex        () >  0 ) ;
  Right -> setEnabled   ( count()-currentIndex() >  1 ) ;
  if (Hidden)                                           {
    Left  -> setVisible ( currentIndex() > 0          ) ;
    Right -> setVisible ( count()-currentIndex() >  1 ) ;
  }                                                     ;
}

void N::PanWidget::Previous(void)
{
  int index = currentIndex() ;
  index--                    ;
  nDropOut ( index < 0 )     ;
  setCurrentIndex ( index )  ;
}

void N::PanWidget::Next(void)
{
  int index = currentIndex()    ;
  index++                       ;
  nDropOut ( index >= count() ) ;
  setCurrentIndex ( index )     ;
}
