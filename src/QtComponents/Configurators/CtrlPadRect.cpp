#include <qtcomponents.h>
#include "ui_CtrlPadRect.h"

N::CtrlPadRect:: CtrlPadRect ( QWidget * parent , Plan * p )
               : Widget      (           parent ,        p )
               , ui          ( new Ui::CtrlPadRect         )
               , rect        ( NULL                        )
               , identifier  ( 0                           )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::CtrlPadRect::~CtrlPadRect(void)
{
  delete ui ;
}

void N::CtrlPadRect::closeEvent(QCloseEvent * event)
{
  emit Closed           ( identifier , this  ) ;
  QWidget :: closeEvent ( event              ) ;
}

void N::CtrlPadRect::Configure (void)
{
  ui   -> setupUi ( this ) ;
  plan -> setFont ( this ) ;
}

void N::CtrlPadRect::setIdentifier(int id)
{
  identifier = id ;
}

void N::CtrlPadRect::ValueChanged(int)
{
  if ( IsNull(rect) ) return              ;
  rect -> setX      ( ui->X->value()    ) ;
  rect -> setY      ( ui->Y->value()    ) ;
  rect -> setWidth  ( ui->W->value()    ) ;
  rect -> setHeight ( ui->H->value()    ) ;
  emit Changed      ( identifier , this ) ;
}

QRect & N::CtrlPadRect::Create(void)
{
  rect  = new QRect (       ) ;
  rect -> setX      ( 0     ) ;
  rect -> setY      ( 0     ) ;
  rect -> setWidth  ( 0     ) ;
  rect -> setHeight ( 0     ) ;
  return            ( *rect ) ;
}

QRect & N::CtrlPadRect::Value(void)
{
  return ( *rect ) ;
}

QRect & N::CtrlPadRect::setValue(QRect & p)
{
  rect = &p                              ;
  ui -> X -> blockSignals ( true       ) ;
  ui -> Y -> blockSignals ( true       ) ;
  ui -> W -> blockSignals ( true       ) ;
  ui -> H -> blockSignals ( true       ) ;
  ui -> X -> setValue     ( p.x     () ) ;
  ui -> Y -> setValue     ( p.y     () ) ;
  ui -> W -> setValue     ( p.width () ) ;
  ui -> H -> setValue     ( p.height() ) ;
  ui -> X -> blockSignals ( false      ) ;
  ui -> Y -> blockSignals ( false      ) ;
  ui -> W -> blockSignals ( false      ) ;
  ui -> H -> blockSignals ( false      ) ;
  return                  ( *rect      ) ;
}

QSpinBox * N::CtrlPadRect::SpinBox(int index)
{
  switch ( index ) {
    case 0         :
    return ui -> X ;
    case 1         :
    return ui -> Y ;
    case 2         :
    return ui -> W ;
    case 3         :
    return ui -> H ;
  }                ;
  return NULL      ;
}
