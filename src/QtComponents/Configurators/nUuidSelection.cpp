#include <qtcomponents.h>
#include "ui_nUuidSelection.h"

N::UuidSelection:: UuidSelection ( QWidget * parent , Plan * p )
                 : Dialog        (           parent ,        p )
                 , GroupItems    (                           p )
                 , ui            ( new Ui::nUuidSelection      )
{
  WidgetClass              ;
  ui   -> setupUi ( this ) ;
  plan -> setFont ( this ) ;
}

N::UuidSelection::~UuidSelection(void)
{
  delete ui ;
}

SUID N::UuidSelection::currentUuid(void)
{
  return N::GetUuid ( ui->UUIDs ) ;
}

void N::UuidSelection::setUuids(UUIDs & Uuids,int language)
{
  NAMEs NS                            ;
  ui->UUIDs->clear()                  ;
  if (language==0)                    {
    language = plan->LanguageId       ;
                                      }
  EnterSQL(SC,plan->sql)              ;
    NS = UuidNames(SC,Uuids,language) ;
  LeaveSQL(SC,plan->sql)              ;
  AddItems(*(ui->UUIDs),Uuids,NS)     ;
}

void N::UuidSelection::setNames(UUIDs & Uuids,NAMEs & Names)
{
  SUID u ;
  foreach (u,Uuids)                            {
    ui -> UUIDs -> addItem ( Names [ u ] , u ) ;
  }                                            ;
}
