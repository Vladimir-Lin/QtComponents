#include <qtcomponents.h>

int N::AddItems(QComboBox & Combo,NAMEs & Names)
{
  UUIDs Uuids = Names.keys()                           ;
  SUID  uuid                                           ;
  Combo . clear()                                      ;
  foreach (uuid,Uuids) Combo.addItem(Names[uuid],uuid) ;
  return Uuids.count()                                 ;
}

int N::AddItems(QComboBox & Combo,UUIDs & Uuids,NAMEs & Names)
{
  SUID  uuid                                           ;
  Combo . clear()                                      ;
  foreach (uuid,Uuids) Combo.addItem(Names[uuid],uuid) ;
  return Uuids.count()                                 ;
}

SUID N::RetrieveUuid(QTreeWidgetItem * item,int column)
{
  return item->data(column,Qt::UserRole).toULongLong() ;
}

SUID N::GetUuid(QComboBox * combo)
{
  SUID uuid = 0 ;
  int  index = combo->currentIndex() ;
  if (index>=0) uuid = combo->itemData(index,Qt::UserRole).toULongLong() ;
  return uuid ;
}

void operator << (QComboBox * Combo,NAMEs & Names)
{
  N::AddItems(*Combo,Names);
}

void operator <= (QComboBox & Combo,QString name)
{
  int index = -1                             ;
  for (int i=0;index<0 && i<Combo.count();i++)
    if (Combo.itemText(i)==name) index = i   ;
  if (index>=0) Combo.setCurrentIndex(index) ;
}

void operator <= (QComboBox & Combo,int Id)
{
  for (int i=0;i<Combo.count();i++)                {
    int v = Combo.itemData(i,Qt::UserRole).toInt() ;
    if (v==Id)                                     {
      Combo.setCurrentIndex(i)                     ;
      return                                       ;
    }                                              ;
  }                                                ;
}

void operator <= (QComboBox & Combo,SUID uuid)
{
  for (int i=0;i<Combo.count();i++)                       {
    SUID v = Combo.itemData(i,Qt::UserRole).toULongLong() ;
    if (v==uuid)                                          {
      Combo.setCurrentIndex(i)                            ;
      return                                              ;
    }                                                     ;
  }                                                       ;
}

void operator <= (QLineEdit & lineEdit,QString name)
{
  lineEdit . setText ( name ) ;
}

void operator , (QComboBox & Combo,N::Plan & plan)
{
  if (plan.fonts.contains(N::Fonts::ComboBox))    {
    Combo.setFont(plan.fonts[N::Fonts::ComboBox]) ;
  }                                               ;
}

void operator , (QTreeWidget & Tree ,N::Plan & plan)
{
  if (plan.fonts.contains(N::Fonts::Tree))   {
    Tree.setFont(plan.fonts[N::Fonts::Tree]) ;
  }                                          ;
}

void operator << (QComboBox * Combo,N::Languages & languages)
{
  CUIDs LIDs                                              ;
  Combo->blockSignals(true)                               ;
  Combo->clear()                                          ;
  ForLanguage(LID,languages.languages)                    ;
    SUID Uuid = languages.Uuids[LID]                      ;
    if (languages.Names.contains(Uuid))                   {
      Combo->addItem(languages.Names[Uuid],LID)           ;
      LIDs << LID                                         ;
    }                                                     ;
  EndLanguage(LID,languages.languages)                    ;
  Combo->setCurrentIndex(LIDs.indexOf(languages.Default)) ;
  Combo->blockSignals(false)                              ;
}

void operator << (QTreeWidget * Tree,N::Languages & languages)
{
  Tree->blockSignals(true)                 ;
  Tree->clear()                            ;
  ForLanguage(LID,languages.languages)     ;
    SUID Uuid = languages.Uuids[LID]       ;
    if (languages.Names.contains(Uuid))    {
      NewTreeWidgetItem(it)                ;
      it->setText(0,languages.Names[Uuid]) ;
      it->setData(0,Qt::UserRole,LID)      ;
      Tree->addTopLevelItem(it)            ;
    }                                      ;
  EndLanguage(LID,languages.languages)     ;
  Tree->blockSignals(false)                ;
}

