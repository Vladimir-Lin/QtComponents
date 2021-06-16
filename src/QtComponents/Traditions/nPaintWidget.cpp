#include <qtcomponents.h>

N::PaintWidget:: PaintWidget (QWidget * parent,Plan * p)
               : Widget      (          parent,       p)
{
  WidgetClass   ;
  Configure ( ) ;
}

N::PaintWidget::~PaintWidget (void)
{
}

void N::PaintWidget::showEvent(QShowEvent * event)
{
  QWidget :: showEvent   ( event ) ;
  relocation             (       ) ;
}

void N::PaintWidget::resizeEvent (QResizeEvent * event)
{
  QWidget :: resizeEvent ( event ) ;
  relocation             (       ) ;
}

void N::PaintWidget::paintEvent(QPaintEvent * event)
{ Q_UNUSED       ( event            ) ;
  QMutexLocker L ( & Mutex          ) ;
  QPainter     p ( this             ) ;
  p . drawImage  ( 0 , 0 , Painting ) ;
}

void N::PaintWidget::Configure(void)
{
  Painting   = QImage(64,64,QImage::Format_ARGB32) ;
  Background = QImage(64,64,QImage::Format_ARGB32) ;
  Drawing    = QImage(64,64,QImage::Format_ARGB32) ;
  disconnect ( this , SIGNAL ( reflush ( ) )       ,
               NULL , NULL                       ) ;
  nConnect   ( this , SIGNAL ( reflush ( ) )       ,
               this , SLOT   ( update  ( ) )     ) ;
}

void N::PaintWidget::relocation(void)
{
  QMutexLocker Locker ( & Mutex                   ) ;
  QColor   w = QColor ( 255 , 255 , 255           ) ;
  QSize    s = size   (                           ) ;
  Painting   = QImage ( s , QImage::Format_ARGB32 ) ;
  Background = QImage ( s , QImage::Format_ARGB32 ) ;
  Drawing    = QImage ( s , QImage::Format_ARGB32 ) ;
  Painting   . fill   ( w                         ) ;
  Background . fill   ( w                         ) ;
  Drawing    . fill   ( w                         ) ;
}

void N::PaintWidget::LockImage(void)
{
  LockGui   ( ) ;
}

void N::PaintWidget::UnlockImage(void)
{
  UnlockGui ( ) ;
}
