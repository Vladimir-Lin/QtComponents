#include <qtcomponents.h>
#include "ui_nLanguageSelections.h"

N::LanguageSelections:: LanguageSelections ( QWidget * parent , Plan * p )
                      : Dialog             (           parent ,        p )
                      , ui                 ( new Ui::nLanguageSelections )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::LanguageSelections::~LanguageSelections(void)
{
  delete ui ;
}

void N::LanguageSelections::Configure(void)
{
  ui   -> setupUi ( this ) ;
  plan -> setFont ( this ) ;
}

void N::LanguageSelections::doubleClicked(QTreeWidgetItem * item,int column)
{
  QDialog::accept() ;
}

int N::LanguageSelections::Language(void)
{
  QTreeWidgetItem * it = ui->Languages->currentItem() ;
  if (IsNull(it)) return plan->LanguageId             ;
  return nTreeInt(it,0)                               ;
}

CUIDs N::LanguageSelections::AllLanguages(void)
{
  CUIDs IDs                                               ;
  for (int i=0;i<ui->Languages->topLevelItemCount();i++)  {
    QTreeWidgetItem * it = ui->Languages->topLevelItem(i) ;
    int id               = nTreeInt(it,0)                 ;
    if (it->checkState(0)==Qt::Checked)                   {
      IDs << id                                           ;
    }                                                     ;
  }                                                       ;
  return IDs                                              ;
}

void N::LanguageSelections::List(int language)
{
  ui->Languages << plan->languages                        ;
  if (language==0) language = plan->LanguageId            ;
  for (int i=0;i<ui->Languages->topLevelItemCount();i++)  {
    QTreeWidgetItem * it = ui->Languages->topLevelItem(i) ;
    int id               = nTreeInt(it,0)                 ;
    if (id==language)                                     {
      ui->Languages->scrollToItem  (it)                   ;
      ui->Languages->setCurrentItem(it)                   ;
      return                                              ;
    }                                                     ;
  }                                                       ;
}

void N::LanguageSelections::List(CUIDs IDs)
{
  ui->Languages << plan->languages                        ;
  for (int i=0;i<ui->Languages->topLevelItemCount();i++)  {
    QTreeWidgetItem * it = ui->Languages->topLevelItem(i) ;
    int checkState       = Qt::Unchecked                  ;
    int id               = nTreeInt(it,0)                 ;
    if (IDs.contains(id)) checkState = Qt::Checked        ;
    it->setCheckState(0,(Qt::CheckState)checkState)       ;
  }                                                       ;
}
