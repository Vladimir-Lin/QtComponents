#include <qtcomponents.h>

N::IconDock:: IconDock (QWidget * parent,Plan * p)
            : ListDock (          parent,       p)
{
  WidgetClass   ;
  Configure ( ) ;
}

N::IconDock::~IconDock (void)
{
}

void N::IconDock::Configure(void)
{
  setViewMode                  (IconMode             ) ;
  setIconSize                  (QSize(128,128)       ) ;
  setGridSize                  (QSize(140,192)       ) ;
  setDragDropMode              (DropOnly             ) ;
  setResizeMode                (QListView::Adjust    ) ;
  setWordWrap                  (true                 ) ;
  setHorizontalScrollBarPolicy (Qt::ScrollBarAsNeeded) ;
  setVerticalScrollBarPolicy   (Qt::ScrollBarAsNeeded) ;
  setMinimumSize               (QSize(144,200)       ) ;
}

bool N::IconDock::startup(void)
{
  if (IsNull(plan)) return false ;
  return true                    ;
}

bool N::IconDock::Menu(QPoint pos)
{ Q_UNUSED ( pos ) ;
  return false     ;
}
