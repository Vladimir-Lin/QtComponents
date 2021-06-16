#include <qtcomponents.h>
#include "ui_nFontConfigurator.h"

N::FontConfigurator:: FontConfigurator (QWidget * parent,Plan * p)
                    : Widget           (          parent,       p)
                    , ui               (new Ui::nFontConfigurator)
{
  WidgetClass   ;
  Configure ( ) ;
}

N::FontConfigurator::~FontConfigurator(void)
{
  delete ui;
}

void N::FontConfigurator::Configure(void)
{
  ui   -> setupUi ( this ) ;
  plan -> setFont ( this ) ;
}

void N::FontConfigurator::addItem(int Id,QString name)
{
  ui -> FontItems -> blockSignals ( true      ) ;
  ui -> FontItems -> addItem      ( name , Id ) ;
  ui -> FontItems -> blockSignals ( false     ) ;
}

void N::FontConfigurator::startup(void)
{
  ui -> FontItems -> setCurrentIndex ( 0 ) ;
}

void N::FontConfigurator::FontChanged(int state)
{ Q_UNUSED ( state ) ;
  Font f             ;
  Obtain   ( f )     ;
  showText ( f )     ;
}

void N::FontConfigurator::FontChanged(double state)
{ Q_UNUSED ( state ) ;
  Font f             ;
  Obtain   ( f )     ;
  showText ( f )     ;
}

bool N::FontConfigurator::Obtain(Font & font)
{
  QFont F = ui->Fonts->currentFont()            ;
  font = Font(F)                                ;
  font.cm  = ui->Height->value()                ;
  font.setBold     (ui->Bold     ->isChecked()) ;
  font.setKerning  (ui->Kerning  ->isChecked()) ;
  font.setItalic   (ui->Italic   ->isChecked()) ;
  font.setOverline (ui->Overline ->isChecked()) ;
  font.setStrikeOut(ui->Strikeout->isChecked()) ;
  font.setUnderline(ui->Underline->isChecked()) ;
  font.setScreen(plan->screen)                  ;
  return true                                   ;
}

void N::FontConfigurator::showText(Font & font)
{
  QString T = ui->Test->toPlainText() ;
  ui->Test->clear()                   ;
  ui->Test->setCurrentFont(font)      ;
  ui->Test->append(T)                 ;
}

void N::FontConfigurator::Update(void)
{
  Font    f                                                   ;
  QString FID                                                 ;
  int     index = ui->FontItems->currentIndex()               ;
  Obtain(f)                                                   ;
  index = ui->FontItems->itemData(index,Qt::UserRole).toInt() ;
  FID = QString("Font %1").arg(index)                         ;
  plan->fonts[index] = f                                      ;
  plan->settings.SaveFont(FID,f)                              ;
}

void N::FontConfigurator::ItemChanged(int index)
{
  index = ui->FontItems->itemData(index,Qt::UserRole).toInt() ;
  Font f                                                      ;
  if (plan->fonts.contains(index)) f = plan->fonts[index]     ;
  ui -> Fonts     -> blockSignals   (true )                   ;
  ui -> Height    -> blockSignals   (true )                   ;
  ui -> Bold      -> blockSignals   (true )                   ;
  ui -> Kerning   -> blockSignals   (true )                   ;
  ui -> Italic    -> blockSignals   (true )                   ;
  ui -> Overline  -> blockSignals   (true )                   ;
  ui -> Strikeout -> blockSignals   (true )                   ;
  ui -> Underline -> blockSignals   (true )                   ;
  ui -> Fonts     -> setCurrentFont ( f   )                   ;
  ui -> Height    -> setValue       (f.cm )                   ;
  ui -> Bold      -> setChecked     (f.bold     ())           ;
  ui -> Kerning   -> setChecked     (f.kerning  ())           ;
  ui -> Italic    -> setChecked     (f.italic   ())           ;
  ui -> Overline  -> setChecked     (f.overline ())           ;
  ui -> Strikeout -> setChecked     (f.strikeOut())           ;
  ui -> Underline -> setChecked     (f.underline())           ;
  ui -> Fonts     -> blockSignals   (false)                   ;
  ui -> Height    -> blockSignals   (false)                   ;
  ui -> Bold      -> blockSignals   (false)                   ;
  ui -> Kerning   -> blockSignals   (false)                   ;
  ui -> Italic    -> blockSignals   (false)                   ;
  ui -> Overline  -> blockSignals   (false)                   ;
  ui -> Strikeout -> blockSignals   (false)                   ;
  ui -> Underline -> blockSignals   (false)                   ;
}
