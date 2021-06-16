#include <qtcomponents.h>

N::VcfLines:: VcfLines (QObject * parent,QGraphicsItem * item,Plan * p)
            : VcfPath  (          parent,                item,       p)
{
  setBrushColor ( 1 , QColor ( 224 , 224 , 224 ) ) ;
  setBrushColor ( 2 , QColor ( 255 , 144 , 144 ) ) ;
}

N::VcfLines::~VcfLines (void)
{
}

void N::VcfLines::Paint(QPainter * p,QRectF Region,bool,bool)
{
  PaintPath  ( p , 1        ) ;
  PaintLines ( p , 3 ,lines ) ;
  PaintPath  ( p , 2        ) ;
}

void N::VcfLines::Prepare(bool line,bool dot)
{
  setLines     ( 1 , contour ) ;
  EnablePath   ( 1 , true    ) ;
  ShowLines    ( line        ) ;
  if (dot )                    {
    setPoints  ( 2 , contour ) ;
    EnablePath ( 2 , true    ) ;
  } else                       {
    EnablePath ( 2 , false   ) ;
  }                            ;
  MergePathes  ( 0           ) ;
}

void N::VcfLines::ShowLines(bool line)
{
  lines . clear              (                          ) ;
  if (line) lines = Polyline ( contour , contour.closed ) ;
  update                     (                          ) ;
}
