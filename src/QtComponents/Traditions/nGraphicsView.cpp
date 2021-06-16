#include <qtcomponents.h>

N::GraphicsView:: GraphicsView    (QWidget * parent,Plan * p)
                : QGraphicsView   (          parent         )
                , VirtualGui      (          this  ,       p)
                , VcfDisplay      (                         )
                , VcfManager      (                         )
                , VcfPaperManager (                        p)
                , Thread          (0,false                  )
                , RelocationMode  (PerfectRegion            )
                , mode            (0                        )
                , method          (0                        )
                , group           (0                        )
                , uuid            (0                        )
{
  WidgetClass                                                        ;
  addIntoWidget                ( parent                     , this ) ;
  setAttribute                 ( Qt::WA_InputMethodEnabled         ) ;
  setOptimizationFlag          ( DontAdjustForAntialiasing  , true ) ;
  setRenderHint                ( QPainter::Antialiasing     , true ) ;
  setRenderHint                ( QPainter::TextAntialiasing , true ) ;
  setAttribute                 ( Qt::WA_InputMethodEnabled         ) ;
  viewport ( ) -> setAttribute ( Qt::WA_InputMethodEnabled         ) ;
  if ( NotNull(plan) )  screen = plan -> screen                      ;
  ////////////////////////////////////////////////////////////////////
  if ( NotNull ( plan ) )                                            {
    Data . Controller = & ( plan->canContinue )                      ;
  }                                                                  ;
}

N::GraphicsView::~GraphicsView(void)
{
}

bool N::GraphicsView::event(QEvent * event)
{
  if (permitGesture() && gestureEvent(event)) return true ;
  return QGraphicsView::event(event)                      ;
}

void N::GraphicsView::closeEvent(QCloseEvent * event)
{
  if (Shutdown()) event->accept();
  else QGraphicsView::closeEvent(event);
}

void N::GraphicsView::ConnectScrolls(void)
{
  QScrollBar * sv = verticalScrollBar   () ;
  QScrollBar * sh = horizontalScrollBar () ;
  if (NotNull(sv))                         {
    connect(sv  ,SIGNAL(sliderMoved(int))  ,
            this,SLOT  (ScrollMoved(int))) ;
  }                                        ;
  if (NotNull(sh))                         {
    connect(sh  ,SIGNAL(sliderMoved(int))  ,
            this,SLOT  (ScrollMoved(int))) ;
  }                                        ;
}

void N::GraphicsView::ScrollMoved (int)
{
  update ( ) ;
}

void N::GraphicsView::setRelocation(ResizeViewMode mode)
{
  RelocationMode = mode ;
}

void N::GraphicsView::setScrollBarPolicy(enum Qt::ScrollBarPolicy policy)
{
  setHorizontalScrollBarPolicy ( policy ) ;
  setVerticalScrollBarPolicy   ( policy ) ;
}

bool N::GraphicsView::Shutdown(void)
{
  return true ;
}

void N::GraphicsView::Remove(VcfItem * item)
{
  takeItem ( item ) ;
}

void N::GraphicsView::Append(VcfItem * item,VcfItem * parent)
{
  addItem ( item , parent ) ;
}

void N::GraphicsView::connectItem(VcfItem * item)
{
  nConnect ( item , SIGNAL ( Append (VcfItem*,VcfItem*) )   ,
             this , SLOT   ( Append (VcfItem*,VcfItem*) ) ) ;
  nConnect ( item , SIGNAL ( Remove (VcfItem*         ) )   ,
             this , SLOT   ( Remove (VcfItem*         ) ) ) ;
}
