#include <qtcomponents.h>
#include "ui_nScreenConfigurator.h"

N::ScreenConfigurator:: ScreenConfigurator (QWidget * parent,Plan * p  )
                      : Widget             (          parent,       p  )
                      , ui                 (new Ui::nScreenConfigurator)
{
  WidgetClass        ;
  ui->setupUi(this)  ;
  Pad = plan->screen ;
  Refresh ( )        ;
}

N::ScreenConfigurator::~ScreenConfigurator(void)
{
  delete ui;
}

void N::ScreenConfigurator::resizeEvent (QResizeEvent * event)
{
  QWidget::resizeEvent(event) ;
  Refresh ( )                 ;
}

void N::ScreenConfigurator::Refresh(void)
{
  Pad . Detect                      (                ) ;
  ui -> WidthMM     -> blockSignals (true            ) ;
  ui -> WidthPixel  -> blockSignals (true            ) ;
  ui -> HeightMM    -> blockSignals (true            ) ;
  ui -> HeightPixel -> blockSignals (true            ) ;
  ui -> WidthMM     -> setValue     (Pad.WidthLength ) ;
  ui -> WidthPixel  -> setValue     (Pad.WidthPixels ) ;
  ui -> HeightMM    -> setValue     (Pad.HeightLength) ;
  ui -> HeightPixel -> setValue     (Pad.HeightPixels) ;
  ui -> WidthMM     -> blockSignals (false           ) ;
  ui -> WidthPixel  -> blockSignals (false           ) ;
  ui -> HeightMM    -> blockSignals (false           ) ;
  ui -> HeightPixel -> blockSignals (false           ) ;
}

void N::ScreenConfigurator::Changed(int)
{
  Pad.WidthLength  = ui -> WidthMM     -> value ( ) ;
  Pad.WidthPixels  = ui -> WidthPixel  -> value ( ) ;
  Pad.HeightLength = ui -> HeightMM    -> value ( ) ;
  Pad.HeightPixels = ui -> HeightPixel -> value ( ) ;
}

void N::ScreenConfigurator::Measure(void)
{
  emit Details ( ) ;
}

void N::ScreenConfigurator::Apply(void)
{
  Pad.MonitorSize.setWidth (Pad.WidthPixels ) ;
  Pad.MonitorSize.setHeight(Pad.HeightPixels) ;
  Pad.WidthInCentimeter   = Pad.WidthLength   ;
  Pad.WidthInCentimeter  /= 10                ;
  Pad.HeightInCentimeter  = Pad.HeightLength  ;
  Pad.HeightInCentimeter /= 10                ;
  plan->screen            = Pad               ;
  plan->saveScreen("Monitor")                 ;
  plan->showMessage(tr("Display size saved")) ;
}

void N::ScreenConfigurator::setMeasure(bool visible)
{
  ui -> Measure -> setVisible ( visible ) ;
}
