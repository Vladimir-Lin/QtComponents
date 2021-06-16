#include <qtcomponents.h>

N::HeaderView:: HeaderView  ( Qt::Orientation orientation ,
                              QWidget       * parent      ,
                              Plan          * p           )
              : QHeaderView ( orientation   , parent      )
              , VirtualGui  ( this          , p           )
{
  setStretchLastSection ( true ) ;
}

N::HeaderView::~HeaderView(void)
{
}

void N::HeaderView::contextMenuEvent(QContextMenuEvent * event)
{
  QHeaderView::contextMenuEvent(event) ;
  emit HeaderMenu ( this,event->pos())  ;
}
