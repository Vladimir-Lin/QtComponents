#include <qtcomponents.h>

N::ContainEditor:: ContainEditor ( QWidget * parent , Plan * p )
                 : Widget        (           parent ,        p )
                 , vcf           ( NULL                        )
                 , stacked       ( NULL                        )
                 , tab           ( NULL                        )
                 , complete      ( NULL                        )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::ContainEditor::~ContainEditor (void)
{
}

void N::ContainEditor::Configure(void)
{
  range     = QSize             ( 32      , 32   ) ;
  stacked   = new StackedWidget ( this    , plan ) ;
  tab       = new TabWidget     ( stacked , plan ) ;
  complete  = new QPushButton   ( this           ) ;
  stacked  -> addWidget         ( tab            ) ;
  complete -> setText           ( tr("Complete") ) ;
  complete -> resize            ( QSize(100, 28) ) ;
  nConnect ( complete , SIGNAL  ( clicked ( ) )    ,
             this     , SLOT    ( Close   ( ) )  ) ;
}

void N::ContainEditor::Close(void)
{
  emit Close ( this ) ;
}

void N::ContainEditor::addStacked(QWidget * widget)
{
  stacked -> addWidget ( widget ) ;
}

void N::ContainEditor::setStacked(QWidget * widget)
{
  range    = widget -> size   (         )   ;
  stacked -> setCurrentWidget ( widget  )   ;
  stacked -> move             ( 10 , 10 )   ;
  stacked -> resize           ( range   )   ;
  ///////////////////////////////////////////
  QSize w                                   ;
  w . setWidth  ( range . width  ( ) + 20 ) ;
  w . setHeight ( range . height ( ) + 50 ) ;
  resize ( w )                              ;
  ///////////////////////////////////////////
  QPoint p                                  ;
  p . setX ( range . width  ( ) - 90 )      ;
  p . setY ( range . height ( ) + 20 )      ;
  complete -> move ( p )                    ;
}

void N::ContainEditor::addTab(QWidget * widget,QString title)
{
  QSize s = widget -> size ( )               ;
  tab -> addTab ( widget , title )           ;
  if ( s . width  ( ) > range . width  ( ) ) {
    range . setWidth  ( s . width  ( ) )     ;
  }                                          ;
  if ( s . height ( ) > range . height ( ) ) {
    range . setHeight ( s . height ( ) )     ;
  }                                          ;
  ////////////////////////////////////////////
  QSize r = range                            ;
  r . setHeight ( range . height ( ) + 28 )  ;
  stacked -> move             ( 10 , 10 )    ;
  stacked -> resize           ( r       )    ;
  ////////////////////////////////////////////
  QSize w                                    ;
  w . setWidth  ( r . width  ( ) + 20 )      ;
  w . setHeight ( r . height ( ) + 50 )      ;
  resize ( w )                               ;
  ////////////////////////////////////////////
  QPoint p                                   ;
  p . setX      ( r . width  ( ) - 90 )      ;
  p . setY      ( r . height ( ) + 20 )      ;
  complete -> move ( p )                     ;
}
