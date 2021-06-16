#include <qtcomponents.h>

N::VcfPainter:: VcfPainter (void)
{
}

N::VcfPainter::~VcfPainter (void)
{
}

int N::VcfPainter::addPen(int Id,QColor color)
{
  pens [ Id ] = Pen   ( color ) ;
  return pens . count (       ) ;
}

int N::VcfPainter::addBrush(int Id,QColor color)
{
  brushes [ Id ] = Brush ( color ) ;
  return brushes . count (       ) ;
}

void N::VcfPainter::addMap(QString name,int Id)
{
  Names[name] = Id ;
}

void N::VcfPainter::setPainter(QPainter * p,QString name)
{
  if (!Names.contains(name)) return                     ;
  int Id = Names[name]                                  ;
  if (pens   .contains(Id)) p -> setPen   (pens   [Id]) ;
  if (brushes.contains(Id)) p -> setBrush (brushes[Id]) ;
}

void N::VcfPainter::drawRect(QPainter * p,QString name,QRectF Rect)
{
  if (!Names.contains(name)) return                     ;
  int Id = Names[name]                                  ;
  if (pens   .contains(Id)) p -> setPen   (pens   [Id]) ;
  if (brushes.contains(Id)) p -> setBrush (brushes[Id]) ;
  p -> drawRect ( Rect )                                ;
}

void N::VcfPainter::drawBorder(QPainter * p,QString name,QRectF Rect)
{
  if (!Names.contains(name)) return ;
  int Id = Names[name]              ;
  if (pens   .contains(Id))         {
    p -> setPen ( pens [ Id ] )     ;
  }                                 ;
  QPolygonF P                       ;
  P << Rect . topLeft     (   )     ;
  P << Rect . topRight    (   )     ;
  P << Rect . bottomRight (   )     ;
  P << Rect . bottomLeft  (   )     ;
  P << Rect . topLeft     (   )     ;
  p -> drawPolyline       ( P )     ;
}

QFontMetricsF N::VcfPainter::FontMetrics (int Id)
{
  return QFontMetricsF(fonts[Id]) ;
}

QRectF N::VcfPainter::boundingRect(int Id,QString text)
{
  return FontMetrics(Id).boundingRect(text) ;
}
