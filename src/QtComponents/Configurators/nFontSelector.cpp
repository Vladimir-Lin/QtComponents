#include <qtcomponents.h>
#include "ui_nFontSelector.h"

N::FontSelector:: FontSelector (QWidget * parent,Plan * p)
                : Widget       (          parent,       p)
{
  WidgetClass   ;
  Configure ( ) ;
}

N::FontSelector::~FontSelector (void)
{
  delete ui ;
}

void N::FontSelector::Configure(void)
{
  ui   -> setupUi  ( this                           ) ;
  plan -> setFont  ( this                           ) ;
  font =  Font     ( plan->fonts[N::Fonts::Default] ) ;
  setFontParaments (                                ) ;
}

void N::FontSelector::setFontParaments(void)
{
  ui -> Fonts       -> blockSignals   ( true               ) ;
  ui -> Size        -> blockSignals   ( true               ) ;
  ui -> Stretch     -> blockSignals   ( true               ) ;
  ui -> Weight      -> blockSignals   ( true               ) ;
  ui -> WordSpacing -> blockSignals   ( true               ) ;
  ui -> FixedPitch  -> blockSignals   ( true               ) ;
  ui -> Bold        -> blockSignals   ( true               ) ;
  ui -> Italic      -> blockSignals   ( true               ) ;
  ui -> Kerning     -> blockSignals   ( true               ) ;
  ui -> Overline    -> blockSignals   ( true               ) ;
  ui -> StrikeOut   -> blockSignals   ( true               ) ;
  ui -> Underline   -> blockSignals   ( true               ) ;
  ui -> Fonts       -> setCurrentFont ( font               ) ;
  ui -> Size        -> setValue       ( font.cm            ) ;
  ui -> Stretch     -> setValue       ( font.stretch    () ) ;
  ui -> Weight      -> setValue       ( font.weight     () ) ;
  ui -> WordSpacing -> setValue       ( font.wordSpacing() ) ;
  ui -> FixedPitch  -> setChecked     ( font.fixedPitch () ) ;
  ui -> Bold        -> setChecked     ( font.bold       () ) ;
  ui -> Italic      -> setChecked     ( font.italic     () ) ;
  ui -> Kerning     -> setChecked     ( font.kerning    () ) ;
  ui -> Overline    -> setChecked     ( font.overline   () ) ;
  ui -> StrikeOut   -> setChecked     ( font.strikeOut  () ) ;
  ui -> Underline   -> setChecked     ( font.underline  () ) ;
  ui -> Fonts       -> blockSignals   ( false              ) ;
  ui -> Size        -> blockSignals   ( false              ) ;
  ui -> Stretch     -> blockSignals   ( false              ) ;
  ui -> Weight      -> blockSignals   ( false              ) ;
  ui -> WordSpacing -> blockSignals   ( false              ) ;
  ui -> FixedPitch  -> blockSignals   ( false              ) ;
  ui -> Bold        -> blockSignals   ( false              ) ;
  ui -> Italic      -> blockSignals   ( false              ) ;
  ui -> Kerning     -> blockSignals   ( false              ) ;
  ui -> Overline    -> blockSignals   ( false              ) ;
  ui -> StrikeOut   -> blockSignals   ( false              ) ;
  ui -> Underline   -> blockSignals   ( false              ) ;
  font . setScreen                    ( plan->screen       ) ;
  ui -> Text        -> setCurrentFont ( font               ) ;
  ui -> Text -> setPlainText   ( ui ->Text->toPlainText () ) ;
}

void N::FontSelector::Fetch(void)
{
  QFont  f  = ui -> Fonts -> currentFont ( )                 ;
  font . cm = ui -> Size  -> value       ( )                 ;
  font . setFamily      ( f   . family ()                  ) ;
  font . setStretch     ( ui -> Stretch     -> value    () ) ;
  font . setWeight      ( ui -> Weight      -> value    () ) ;
  font . setWordSpacing ( ui -> WordSpacing -> value    () ) ;
  font . setFixedPitch  ( ui -> FixedPitch  -> isChecked() ) ;
  font . setBold        ( ui -> Bold        -> isChecked() ) ;
  font . setItalic      ( ui -> Italic      -> isChecked() ) ;
  font . setKerning     ( ui -> Kerning     -> isChecked() ) ;
  font . setOverline    ( ui -> Overline    -> isChecked() ) ;
  font . setStrikeOut   ( ui -> StrikeOut   -> isChecked() ) ;
  font . setUnderline   ( ui -> Underline   -> isChecked() ) ;
  font . setScreen      ( plan->screen                     ) ;
  ui -> Text -> setCurrentFont ( font                      ) ;
  ui -> Text -> setPlainText   ( ui ->Text->toPlainText () ) ;
}

void N::FontSelector::setFont(QString name,Font & f)
{
  font = f                    ;
  setFontParaments ()         ;
  ui -> Name -> setText(name) ;
}

void N::FontSelector::NameChanged(QString text)
{
  ui -> Done -> setEnabled ( text.length()>0 ) ;
}

void N::FontSelector::doubleChanged(double)
{
  Fetch ( ) ;
}

void N::FontSelector::valueChanged(int)
{
  Fetch ( ) ;
}

void N::FontSelector::FontChanged(QFont font)
{
  Fetch ( ) ;
}

void N::FontSelector::Done(void)
{
  QMdiSubWindow * msw = qobject_cast<QMdiSubWindow *>(parent()) ;
  QString name = ui->Name->text()                               ;
  Fetch       (              )                                  ;
  emit Update ( name , &font )                                  ;
  deleteLater (              )                                  ;
  if (NotNull(msw)) msw -> deleteLater ( )                      ;
}
