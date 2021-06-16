#include <qtcomponents.h>

N::PaperArrangement:: PaperArrangement (QWidget * parent,Plan * p)
                    : Dialog           (          parent,       p)
{
  paper      = "A4"           ;
  borders[1] = 1.00           ;
  borders[2] = 1.00           ;
  borders[3] = 1.00           ;
  borders[4] = 1.00           ;
  paperX     = 1              ;
  paperY     = 1              ;
  dpi        = 300            ;
  direction  = Qt::Vertical   ;
  arrange    = Qt::Horizontal ;
  rulers     = true           ;
}

N::PaperArrangement::~PaperArrangement (void)
{
}
