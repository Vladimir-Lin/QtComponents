#include <qtcomponents.h>
#include "ui_CtrlPadPointF.h"

N::CtrlPadPointF:: CtrlPadPointF ( QWidget * parent , Plan * p )
                 : Widget        (           parent ,        p )
                 , ui            ( new Ui::CtrlPadPointF       )
                 , point         ( NULL                        )
                 , identifier    ( 0                           )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::CtrlPadPointF::~CtrlPadPointF(void)
{
  delete ui ;
}

void N::CtrlPadPointF::closeEvent(QCloseEvent * event)
{
  emit Closed           ( identifier , this  ) ;
  QWidget :: closeEvent ( event              ) ;
}

void N::CtrlPadPointF::Configure (void)
{
  ui   -> setupUi ( this ) ;
  plan -> setFont ( this ) ;
}

void N::CtrlPadPointF::setIdentifier(int id)
{
  identifier = id ;
}

void N::CtrlPadPointF::ValueChanged(double)
{
  if ( IsNull(point) ) return         ;
  point -> setX ( ui->X->value()    ) ;
  point -> setY ( ui->Y->value()    ) ;
  emit Changed  ( identifier , this ) ;
}

QPointF & N::CtrlPadPointF::Create(void)
{
  point  = new QPointF (        ) ;
  point -> setX        ( 0      ) ;
  point -> setY        ( 0      ) ;
  return               ( *point ) ;
}

QPointF & N::CtrlPadPointF::Value(void)
{
  return ( *point ) ;
}

QPointF & N::CtrlPadPointF::setValue(QPointF & p)
{
  point = &p                         ;
  ui -> X -> blockSignals ( true   ) ;
  ui -> Y -> blockSignals ( true   ) ;
  ui -> X -> setValue     ( p.x()  ) ;
  ui -> Y -> setValue     ( p.y()  ) ;
  ui -> X -> blockSignals ( false  ) ;
  ui -> Y -> blockSignals ( false  ) ;
  return                  ( *point ) ;
}

QDoubleSpinBox * N::CtrlPadPointF::SpinBox(int index)
{
  switch ( index ) {
    case 0         :
    return ui -> X ;
    case 1         :
    return ui -> Y ;
  }                ;
  return NULL      ;
}
