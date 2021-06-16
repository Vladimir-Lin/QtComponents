#include <qtcomponents.h>
#include "ui_ContainerDialog.h"

N::ContainerDialog:: ContainerDialog ( QWidget * parent , Plan * p )
                   : Dialog          (           parent ,        p )
                   , ui              ( new Ui::ContainerDialog     )
{
  WidgetClass              ;
  ui   -> setupUi ( this ) ;
  plan -> setFont ( this ) ;
}

N::ContainerDialog::~ContainerDialog(void)
{
  delete ui;
}

void N::ContainerDialog::setWidget(QWidget * widget)
{
  QSize  w = widget->size()                             ;
  QSize  s ( w.width() + 40 , w.height() + 100        ) ;
  QSize  b ( s.width() - 60 , ui->buttonBox->height() ) ;
  QPoint p ( 30             , w.height() +  40        ) ;
  resize   ( s                                        ) ;
  ui -> buttonBox -> move             ( p      )        ;
  ui -> buttonBox -> resize           ( b      )        ;
  ///////////////////////////////////////////////////////
  ui -> Stacked   -> resize           ( w      )        ;
  ui -> Stacked   -> addWidget        ( widget )        ;
  ui -> Stacked   -> setCurrentWidget ( widget )        ;
  ///////////////////////////////////////////////////////
  setWindowTitle   ( widget -> windowTitle ( ) )        ;
  setWindowIcon    ( widget -> windowIcon  ( ) )        ;
  ///////////////////////////////////////////////////////
  plan -> setFont  ( this                      )        ;
}
