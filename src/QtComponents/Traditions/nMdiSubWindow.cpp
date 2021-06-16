#include <qtcomponents.h>

N::MdiSubWindow:: MdiSubWindow  ( QWidget * parent , Qt::WindowFlags flags )
                : QMdiSubWindow (           parent ,                 flags )
                , abstract      ( NULL                                     )
{
  setAccessibleName ( "N::MdiSubWindow"         ) ;
  setAttribute      ( Qt::WA_InputMethodEnabled ) ;
}

N::MdiSubWindow::~MdiSubWindow (void)
{
}

void N::MdiSubWindow::closeEvent(QCloseEvent * e)
{
  if ( NULL != abstract )                                         {
    if ( ! abstract -> canStop ( ) )                              {
      e -> ignore ( )                                             ;
      return                                                      ;
    }                                                             ;
  } else                                                          {
    QWidget * w = widget ( )                                      ;
    if ( NULL != w )                                              {
      QVariant v = w -> property ( "AbstractGui" )                ;
      if ( v . isValid ( ) && v . toBool ( ) )                    {
        QVariant z = w -> property ( "CanStop" )                  ;
        if ( z . isValid ( ) && ( ! getAbstractStopable ( z ) ) ) {
          e -> ignore ( )                                         ;
          return                                                  ;
        }                                                         ;
      }                                                           ;
    }                                                             ;
  }                                                               ;
  QMdiSubWindow::closeEvent ( e )                                 ;
}
