#include <qtcomponents.h>
#include "ui_nGetSize.h"

N::GetSize:: GetSize (QWidget * parent,Plan * p)
           : Dialog  (          parent,       p)
           , ui      (new Ui::nGetSize         )
{
  WidgetClass            ;
  ui   -> setupUi (this) ;
  plan -> setFont (this) ;
}

N::GetSize::~GetSize(void)
{
  delete ui ;
}

QSize N::GetSize::Size(void)
{
  return QSize(value(0),value(1)) ;
}

int N::GetSize::value(int index)
{
  int v = 0              ;
  switch (index)         {
    case 0               :
      v = ui->A->value() ;
    break                ;
    case 1               :
      v = ui->B->value() ;
    break                ;
  }                      ;
  return v               ;
}

void N::GetSize::setSize(QSize s)
{
  setValue ( 0 , s . width  () ) ;
  setValue ( 1 , s . height () ) ;
}

void N::GetSize::setValue(int index,int v)
{
  switch (index)         {
    case 0               :
      ui->A->setValue(v) ;
    break                ;
    case 1               :
      ui->B->setValue(v) ;
     break               ;
  }                      ;
}

void N::GetSize::setRange(int index,int MinV,int MaxV)
{
  switch (index)                 {
    case 0                       :
      ui->A->setRange(MinV,MaxV) ;
    break                        ;
    case 1                       :
      ui->B->setRange(MinV,MaxV) ;
     break                       ;
  }                              ;
}

void N::GetSize::setSingleStep(int index,int v)
{
  switch (index)              {
    case 0                    :
      ui->A->setSingleStep(v) ;
    break                     ;
    case 1                    :
      ui->B->setSingleStep(v) ;
     break                    ;
  }                           ;
}

void N::GetSize::setPrefix(int index,QString name)
{
  switch (index)             {
    case 0                   :
      ui->A->setPrefix(name) ;
    break                    ;
    case 1                   :
      ui->B->setPrefix(name) ;
     break                   ;
  }                          ;
}

void N::GetSize::setSuffix(int index,QString name)
{
  switch (index)             {
    case 0                   :
      ui->A->setSuffix(name) ;
    break                    ;
    case 1                   :
      ui->B->setSuffix(name) ;
     break                   ;
  }                          ;
}
