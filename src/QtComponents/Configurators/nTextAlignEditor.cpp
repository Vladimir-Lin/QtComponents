#include <qtcomponents.h>
#include "ui_nTextAlignEditor.h"

N::TextAlignEditor:: TextAlignEditor ( QWidget *         parent )
                   : QDialog         (                   parent )
                   , ui              ( new Ui::nTextAlignEditor )
{
  Configure ( ) ;
}

N::TextAlignEditor::~TextAlignEditor(void)
{
  delete ui ;
}

void N::TextAlignEditor::Configure(void)
{
  ui -> setupUi ( this )                                                    ;
  ui -> Horizontal -> addItem(tr("Qt::AlignLeft"   ),(int)Qt::AlignLeft   ) ;
  ui -> Horizontal -> addItem(tr("Qt::AlignRight"  ),(int)Qt::AlignRight  ) ;
  ui -> Horizontal -> addItem(tr("Qt::AlignHCenter"),(int)Qt::AlignHCenter) ;
  ui -> Horizontal -> addItem(tr("Qt::AlignJustify"),(int)Qt::AlignJustify) ;
  ui -> Vertical   -> addItem(tr("Qt::AlignTop"    ),(int)Qt::AlignTop    ) ;
  ui -> Vertical   -> addItem(tr("Qt::AlignBottom" ),(int)Qt::AlignBottom ) ;
  ui -> Vertical   -> addItem(tr("Qt::AlignVCenter"),(int)Qt::AlignVCenter) ;
  ui -> Vertical   -> setCurrentIndex ( 2 )                                 ;
}

int N::TextAlignEditor::Alignment(void)
{
  int hv = ui->Horizontal->currentIndex() ;
  int vv = ui->Vertical  ->currentIndex() ;
  if (hv==0) hv = Qt::AlignLeft    ; else
  if (hv==1) hv = Qt::AlignRight   ; else
  if (hv==2) hv = Qt::AlignHCenter ; else
  if (hv==3) hv = Qt::AlignJustify ;
  if (vv==0) hv = Qt::AlignTop     ; else
  if (vv==1) hv = Qt::AlignBottom  ; else
  if (vv==2) hv = Qt::AlignVCenter ;
  return hv | vv                          ;
}

void N::TextAlignEditor::setAlignment(int alignment)
{
  int hv = 0                                          ;
  int vv = 0                                          ;
  if (IsMask(alignment,(int)Qt::AlignLeft   )) hv = 0 ; else
  if (IsMask(alignment,(int)Qt::AlignRight  )) hv = 1 ; else
  if (IsMask(alignment,(int)Qt::AlignHCenter)) hv = 2 ; else
  if (IsMask(alignment,(int)Qt::AlignJustify)) hv = 3 ;
  if (IsMask(alignment,(int)Qt::AlignTop    )) vv = 0 ; else
  if (IsMask(alignment,(int)Qt::AlignBottom )) vv = 1 ; else
  if (IsMask(alignment,(int)Qt::AlignVCenter)) vv = 2 ;
  ui -> Horizontal -> setCurrentIndex ( hv )          ;
  ui -> Vertical   -> setCurrentIndex ( vv )          ;
}
