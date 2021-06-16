#include <qtcomponents.h>

N::TabBar:: TabBar     (QWidget * parent,Plan * p)
          : QTabBar    (          parent         )
          , VirtualGui (          this  ,       p)
{
  Configure ( ) ;
}

N::TabBar::~TabBar (void)
{
}

void N::TabBar::paintEvent(QPaintEvent * event)
{
  nIsolatePainter(QTabBar) ;
}

void N::TabBar::focusInEvent(QFocusEvent * event)
{
  if (!focusIn (event)) QTabBar::focusInEvent (event) ;
}

void N::TabBar::focusOutEvent(QFocusEvent * event)
{
  if (!focusOut(event)) QTabBar::focusOutEvent(event) ;
}

void N::TabBar::closeEvent(QCloseEvent * event)
{
  if (Shutdown()) event->accept() ; else {
    QTabBar::closeEvent(event)           ;
  }                                      ;
}

void N::TabBar::resizeEvent(QResizeEvent * event)
{
  if (Relocation()) event->accept() ; else {
    QTabBar::resizeEvent(event)            ;
  }                                        ;
}

void N::TabBar::contextMenuEvent(QContextMenuEvent * event)
{
  if (Menu(event->pos())) event->accept(); else {
    QTabBar::contextMenuEvent(event)            ;
  }                                             ;
}

bool N::TabBar::Shutdown(void)
{
  return true ;
}

void N::TabBar::Configure(void)
{
  setAcceptDrops ( true                      ) ;
  setAttribute   ( Qt::WA_InputMethodEnabled ) ;
}

bool N::TabBar::Relocation(void)
{
  return false ;
}

bool N::TabBar::Menu(QPoint pos)
{ Q_UNUSED ( pos ) ;
  return false     ;
}
