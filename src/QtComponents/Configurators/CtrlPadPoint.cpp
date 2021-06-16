#include <qtcomponents.h>
#include "ui_CtrlPadPoint.h"

N::CtrlPadPoint:: CtrlPadPoint ( QWidget * parent , Plan * p )
                : Widget       (           parent ,        p )
                , ui           ( new Ui::CtrlPadPoint        )
                , point        ( NULL                        )
                , identifier   ( 0                           )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::CtrlPadPoint::~CtrlPadPoint(void)
{
  delete ui ;
}

void N::CtrlPadPoint::closeEvent(QCloseEvent * event)
{
  emit Closed           ( identifier , this  ) ;
  QWidget :: closeEvent ( event              ) ;
}

void N::CtrlPadPoint::Configure (void)
{
  ui   -> setupUi ( this ) ;
  plan -> setFont ( this ) ;
}

void N::CtrlPadPoint::setIdentifier(int id)
{
  identifier = id ;
}

void N::CtrlPadPoint::ValueChanged(int)
{
  if ( IsNull(point) ) return         ;
  point -> setX ( ui->X->value()    ) ;
  point -> setY ( ui->Y->value()    ) ;
  emit Changed  ( identifier , this ) ;
}

QPoint & N::CtrlPadPoint::Create(void)
{
  point  = new QPoint (        ) ;
  point -> setX       ( 0      ) ;
  point -> setY       ( 0      ) ;
  return              ( *point ) ;
}

QPoint & N::CtrlPadPoint::Value(void)
{
  return ( *point ) ;
}

QPoint & N::CtrlPadPoint::setValue(QPoint & p)
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

QSpinBox * N::CtrlPadPoint::SpinBox(int index)
{
  switch ( index ) {
    case 0         :
    return ui -> X ;
    case 1         :
    return ui -> Y ;
  }                ;
  return NULL      ;
}
