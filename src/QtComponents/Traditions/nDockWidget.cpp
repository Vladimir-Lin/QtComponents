#include <qtcomponents.h>

QString dockStyleSheet = "QDockWidget::title "
                         "{ background-color:"
                         "qlineargradient"
                         "(spread:reflect, x1:0.5, y1:0.5, x2:0.5, y2:0.0,"
                         " stop:0 rgba(216,216,216,255),"
                         " stop:1 rgba(240,240,240,255)) ;"
                         " text-align: center center }"                   ;

N::DockWidget:: DockWidget  (const QString & title,QWidget * parent,Qt::WindowFlags flags)
              : QDockWidget (                title,          parent,                flags)
              , Regular     (true                                                        )
{
  setStyleSheet ( dockStyleSheet            ) ;
  setAttribute  ( Qt::WA_InputMethodEnabled ) ;
}

N::DockWidget:: DockWidget  (QWidget * parent,Qt::WindowFlags flags)
              : QDockWidget (          parent,                flags)
              , Regular     (true                                  )
{
  setStyleSheet ( dockStyleSheet            ) ;
  setAttribute  ( Qt::WA_InputMethodEnabled ) ;
}

N::DockWidget::~DockWidget(void)
{
}

bool N::DockWidget::event(QEvent * e)
{
  return QDockWidget::event ( e ) ;
}

QSize N::DockWidget::sizeHint(void) const
{
  if ( ! Regular )                 {
    return DockGeometry . size ( ) ;
  }                                ;
  return QDockWidget::sizeHint ( ) ;
}
