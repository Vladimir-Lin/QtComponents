#include <qtcomponents.h>
#include "ui_CtrlPadSizeF.h"

N::CtrlPadSizeF:: CtrlPadSizeF ( QWidget * parent , Plan * p )
                : Widget       (           parent ,        p )
                , ui           ( new Ui::CtrlPadSizeF        )
                , size         ( NULL                        )
                , identifier   ( 0                           )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::CtrlPadSizeF::~CtrlPadSizeF(void)
{
  delete ui ;
}

void N::CtrlPadSizeF::closeEvent(QCloseEvent * event)
{
  emit Closed           ( identifier , this  ) ;
  QWidget :: closeEvent ( event              ) ;
}

void N::CtrlPadSizeF::Configure (void)
{
  ui   -> setupUi ( this ) ;
  plan -> setFont ( this ) ;
}

void N::CtrlPadSizeF::setIdentifier(int id)
{
  identifier = id ;
}

void N::CtrlPadSizeF::ValueChanged(double)
{
  if ( IsNull(size) ) return              ;
  size -> setWidth  ( ui->W->value()    ) ;
  size -> setHeight ( ui->H->value()    ) ;
  emit Changed      ( identifier , this ) ;
}

QSizeF & N::CtrlPadSizeF::Create(void)
{
  size  = new QSizeF (       ) ;
  size -> setWidth   ( 0     ) ;
  size -> setHeight  ( 0     ) ;
  return             ( *size ) ;
}

QSizeF & N::CtrlPadSizeF::Value(void)
{
  return ( *size ) ;
}

QSizeF & N::CtrlPadSizeF::setValue(QSizeF & p)
{
  size = &p                              ;
  ui -> W -> blockSignals ( true       ) ;
  ui -> H -> blockSignals ( true       ) ;
  ui -> W -> setValue     ( p.width () ) ;
  ui -> H -> setValue     ( p.height() ) ;
  ui -> W -> blockSignals ( false      ) ;
  ui -> H -> blockSignals ( false      ) ;
  return                  ( *size      ) ;
}

QDoubleSpinBox * N::CtrlPadSizeF::SpinBox(int index)
{
  switch ( index ) {
    case 0         :
    return ui -> W ;
    case 1         :
    return ui -> H ;
  }                ;
  return NULL      ;
}
