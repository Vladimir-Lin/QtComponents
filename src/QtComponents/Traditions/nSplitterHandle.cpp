#include <qtcomponents.h>

N::SplitterHandle:: SplitterHandle  (Qt::Orientation orientation ,
                                     Splitter      * parent      ,
                                     Plan          * p           )
                  : QSplitterHandle (orientation , parent        )
                  , VirtualGui      (this        , p             )
{
}

N::SplitterHandle::~SplitterHandle (void)
{
}

void N::SplitterHandle::contextMenuEvent(QContextMenuEvent * event)
{
  if (Menu(event->pos())) event->accept(); else
    QSplitterHandle::contextMenuEvent(event)  ;
}

bool N::SplitterHandle::Menu(QPoint pos)
{ Q_UNUSED    ( pos       )                  ;
  nScopedMenu ( mm , this )                  ;
  QAction    * aa                            ;
  switch (orientation())                     {
    case Qt::Vertical                        :
      mm.add(302,tr("Change to Horizontal")) ;
    break                                    ;
    case Qt::Horizontal                      :
      mm.add(301,tr("Change to Vertical"  )) ;
    break                                    ;
    default                                  :
    return true                              ;
  }                                          ;
  mm . setFont ( plan )                      ;
  aa = mm.exec (      )                      ;
  nKickOut ( IsNull(aa) , true )             ;
  switch (mm[aa])                            {
    case 301                                 :
      emit assignOrientation(Qt::Vertical  ) ;
    break                                    ;
    case 302                                 :
      emit assignOrientation(Qt::Horizontal) ;
    break                                    ;
  }                                          ;
  return true                                ;
}
