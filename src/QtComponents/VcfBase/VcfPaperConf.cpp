#include <qtcomponents.h>

N::VcfPaperConf:: VcfPaperConf (void)
{
  direction = Qt::Vertical              ;
  arrange   = Texts::TopLeftToTopRight  ;
  paperX    = 1                         ;
  paperY    = 1                         ;
  dpi       = 300                       ;
  paper     = "A4"                      ;
  borders [ VcfPaper :: Left   ] = 1.00 ;
  borders [ VcfPaper :: Top    ] = 1.00 ;
  borders [ VcfPaper :: Right  ] = 1.00 ;
  borders [ VcfPaper :: Bottom ] = 1.00 ;
}

N::VcfPaperConf:: VcfPaperConf (const VcfPaperConf & conf)
{
  ME = conf ;
}

N::VcfPaperConf::~VcfPaperConf(void)
{
}

N::VcfPaperConf & N::VcfPaperConf::operator = (const VcfPaperConf & conf)
{
  nMemberCopy ( conf , paper     ) ;
  nMemberCopy ( conf , borders   ) ;
  nMemberCopy ( conf , paperX    ) ;
  nMemberCopy ( conf , paperY    ) ;
  nMemberCopy ( conf , dpi       ) ;
  nMemberCopy ( conf , direction ) ;
  nMemberCopy ( conf , arrange   ) ;
  return ME                        ;
}

int N::VcfPaperConf::X(int page)
{
  switch (arrange)                   {
    case Texts::TopLeftToTopRight    :
    return   page % paperX           ;
    case Texts::TopLeftToBottomRight :
    return   page / paperY           ;
    case Texts::TopRightToTopLeft    :
    return -(page % paperX)          ;
    case Texts::TopRightToBottomLeft :
    return -(page / paperY)          ;
  }                                  ;
  return 0                           ;
}

int N::VcfPaperConf::Y(int page)
{
  switch (arrange)                   {
    case Texts::TopLeftToTopRight    :
    return   page / paperX           ;
    case Texts::TopLeftToBottomRight :
    return   page % paperY           ;
    case Texts::TopRightToTopLeft    :
    return -(page / paperX)          ;
    case Texts::TopRightToBottomLeft :
    return -(page % paperY)          ;
  }                                  ;
  return 0                           ;
}

QRectF N::VcfPaperConf::PaperAt(int page,QRectF PaperSize)
{
  QRectF  At                      ;
  int     x = X(page)             ;
  int     y = Y(page)             ;
  qreal   w = PaperSize.width  () ;
  qreal   h = PaperSize.height () ;
  QPointF p = PaperSize.topLeft() ;
  QPointF d ( w * x , h * y )     ;
  p += d                          ;
  At . setTopLeft ( p )           ;
  At . setWidth   ( w )           ;
  At . setHeight  ( h )           ;
  return At                       ;
}
