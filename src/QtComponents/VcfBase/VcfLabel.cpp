#include <qtcomponents.h>

#define EDITID  10001

N::VcfLabel:: VcfLabel      (QObject * parent,QGraphicsItem * item,Plan * p)
            : VcfCanvas     (          parent,                item,       p)
            , TextAlignment (Qt::AlignVCenter | Qt::AlignHCenter           )
            , Content       (""                                            )
{
  Printable = true                                      ;
  Scaling   = false                                     ;
  Editable  = true                                      ;
  setFlag(ItemIsMovable           ,true )               ;
  setFlag(ItemIsSelectable        ,true )               ;
  setFlag(ItemIsFocusable         ,true )               ;
  setFlag(ItemClipsToShape        ,false)               ;
  setFlag(ItemClipsChildrenToShape,false)               ;
  Painter . addMap   ( "Default" , 0                  ) ;
  Painter . addPen   ( 0 , QColor ( 192 , 192 , 192 ) ) ;
  Painter . addPen   ( 1 , QColor (   0 ,   0 ,   0 ) ) ;
  Painter . addBrush ( 0 , QColor ( 240 , 240 , 240 ) ) ;
}

N::VcfLabel::~VcfLabel(void)
{
}

void N::VcfLabel::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event)
{
  if (Editable)                                      {
    MountEditor     ( )                              ;
    event -> accept ( )                              ;
  } else QGraphicsItem::mouseDoubleClickEvent(event) ;
}

void N::VcfLabel::Paint(QPainter * painter,QRectF Region,bool clip,bool color)
{
  VcfCanvas::Paint ( painter , Region , clip , color ) ;
  PaintText        ( painter , Region , clip , color ) ;
}

void N::VcfLabel::PaintText(QPainter * p,QRectF Region,bool clip,bool color)
{
  if (IsNull(plan)) return                ;
  QRectF R = ContentRect ( )              ;
  pushPainters  (p                   )    ;
  Painter.fonts[0].setDPI(Options->DPI)   ;
  p->setFont(Painter.fonts[0])            ;
  if (clip)                               {
    p->drawText (R,TextAlignment,Content) ;
  } else                                  {
    p->drawText (R,TextAlignment,Content) ;
  }                                       ;
  popPainters   (p                      ) ;
}

void N::VcfLabel::setText(QString text)
{
  Content = text            ;
  QGraphicsItem::update ( ) ;
}

QRectF N::VcfLabel::ContentRect(void)
{
  double ls = Options->LineSpace                      ;
  QPointF G(ls,ls)                                    ;
  G = Options->position(G)                            ;
  return QRectF(ScreenRect . left   ( ) +  G.x()      ,
                ScreenRect . top    ( ) +  G.y()      ,
                ScreenRect . width  ( ) - (G.x()*2)   ,
                ScreenRect . height ( ) - (G.y()*2) ) ;
}

QRectF N::VcfLabel::EditorRect(void)
{
  double ls = Options->LineSpace                      ;
  QPointF G(ls,ls)                                    ;
  G = Options->position(G)                            ;
  return QRectF(ScreenRect . left   ( ) +  G.x()      ,
                ScreenRect . top    ( ) +  G.y()      ,
                ScreenRect . width  ( ) - (G.x()*2)   ,
                ScreenRect . height ( ) - (G.y()*2) ) ;
}

QSizeF N::VcfLabel::FitSize(void)
{
  Painter.fonts[0].setDPI(Options->DPI) ;
  QFontMetricsF FMF(Painter.fonts[0])   ;
  QRectF  R = FMF.boundingRect(Content) ;
  QPointF S (R.width(),R.height())      ;
  S = Options -> Standard ( S )         ;
  return QSizeF ( S . x () , S . y () ) ;
}

void N::VcfLabel::MountEditor(void)
{
  QLineEdit * LE = NewLineEdit ( EDITID )    ;
  QRectF      ER = EditorRect  (        )    ;
  Proxys[EDITID]->setGeometry  ( ER     )    ;
  Painter.fonts[0].setDPI(Options->DPI  )    ;
  LE -> setFont ( Painter.fonts[0]      )    ;
  LE -> setText ( Content               )    ;
  connect(LE  ,SIGNAL(editingFinished() )    ,
          this,SLOT  (NameFinished   () )  ) ;
  Alert ( Click )                            ;
  LE -> setFocus ( Qt::TabFocusReason      ) ;
}

void N::VcfLabel::NameFinished(void)
{
  QLineEdit * LE = qobject_cast<QLineEdit *>(Widgets[EDITID]) ;
  if (NotNull(LE))                                            {
    Content = LE -> text ( )                                  ;
    emit Changed ( this )                                     ;
  }                                                           ;
  DeleteGadgets ( )                                           ;
  update        ( )                                           ;
}
