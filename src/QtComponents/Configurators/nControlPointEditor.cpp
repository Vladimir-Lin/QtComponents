#include <qtcomponents.h>

N::ControlPointEditor:: ControlPointEditor ( QWidget * parent , Plan * p )
                      : Widget             (           parent ,        p )
                      , point              ( NULL                        )
{
  WidgetClass                                   ;
  setWindowTitle ( tr("Control point editor") ) ;
  setFunction    ( 800001 , true              ) ;
  setFunction    ( 800002 , true              ) ;
  setFunction    ( 800003 , true              ) ;
  setFunction    ( 800004 , false             ) ;
  setFunction    ( 800005 , false             ) ;
  setFunction    ( 800006 , false             ) ;
}

N::ControlPointEditor::~ControlPointEditor (void)
{
}

void N::ControlPointEditor::prepare(void)
{
  if ( IsNull ( point ) ) return               ;
  //////////////////////////////////////////////
  int    P = 0                                 ;
  double m = 10000000000000000000.0f           ;
  for (int i=800001;i<=800006;i++)             {
    if ( isFunction ( i ) )                    {
      QRect R ( 0 , ( P * 30 ) , 240 , 28 )    ;
      DoubleSpinBox * dsb                      ;
      dsb  = new DoubleSpinBox ( this , plan ) ;
      dsb -> setRange          ( -m   , m    ) ;
      switch ( i )                             {
        case 800001                            :
          dsb -> setValue     ( point -> x )   ;
          dsb -> External = & ( point -> x )   ;
        break                                  ;
        case 800002                            :
          dsb -> setValue     ( point -> y )   ;
          dsb -> External = & ( point -> y )   ;
        break                                  ;
        case 800003                            :
          dsb -> setValue     ( point -> z )   ;
          dsb -> External = & ( point -> z )   ;
        break                                  ;
        case 800004                            :
          dsb -> setValue     ( point -> r )   ;
          dsb -> External = & ( point -> r )   ;
        break                                  ;
        case 800005                            :
          dsb -> setValue     ( point -> t )   ;
          dsb -> External = & ( point -> t )   ;
        break                                  ;
        case 800006                            :
          dsb -> setValue     ( point -> f )   ;
          dsb -> External = & ( point -> f )   ;
        break                                  ;
      }                                        ;
      dsb -> setGeometry ( R )                 ;
      P++                                      ;
    }                                          ;
  }                                            ;
  //////////////////////////////////////////////
  resize ( QSize ( 240 , ( P * 30 ) ) )        ;
}
