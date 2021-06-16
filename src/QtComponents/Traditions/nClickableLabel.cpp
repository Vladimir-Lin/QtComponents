#include <qtcomponents.h>

N::ClickableLabel:: ClickableLabel (QWidget * parent,Plan * p)
                  : QLabel         (          parent         )
                  , VirtualGui     (          this  ,       p)
{
}

N::ClickableLabel::~ClickableLabel(void)
{
}

void N::ClickableLabel::mousePressEvent(QMouseEvent * event)
{
  emit clicked(event->buttons()) ;
}
