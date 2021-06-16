#include <qtcomponents.h>
#include "ui_CtrlPadSize.h"

N::CtrlPadSize:: CtrlPadSize ( QWidget * parent , Plan * p )
               : Widget      (           parent ,        p )
               , ui          ( new Ui::CtrlPadSize         )
               , size        ( NULL                        )
               , identifier  ( 0                           )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::CtrlPadSize::~CtrlPadSize(void)
{
  delete ui ;
}

void N::CtrlPadSize::closeEvent(QCloseEvent * event)
{
  emit Closed           ( identifier , this  ) ;
  QWidget :: closeEvent ( event              ) ;
}

void N::CtrlPadSize::Configure (void)
{
  ui   -> setupUi ( this ) ;
  plan -> setFont ( this ) ;
}

void N::CtrlPadSize::setIdentifier(int id)
{
  identifier = id ;
}

void N::CtrlPadSize::ValueChanged(int)
{
  if ( IsNull(size) ) return              ;
  size -> setWidth  ( ui->W->value()    ) ;
  size -> setHeight ( ui->H->value()    ) ;
  emit Changed      ( identifier , this ) ;
}

QSize & N::CtrlPadSize::Create(void)
{
  size  = new QSize (       ) ;
  size -> setWidth  ( 0     ) ;
  size -> setHeight ( 0     ) ;
  return            ( *size ) ;
}

QSize & N::CtrlPadSize::Value(void)
{
  return ( *size ) ;
}

QSize & N::CtrlPadSize::setValue(QSize & p)
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

QSpinBox * N::CtrlPadSize::SpinBox(int index)
{
  switch ( index ) {
    case 0         :
    return ui -> W ;
    case 1         :
    return ui -> H ;
  }                ;
  return NULL      ;
}
