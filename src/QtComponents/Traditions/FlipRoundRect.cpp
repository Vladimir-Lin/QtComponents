#include <qtcomponents.h>

N::FlipRoundRect:: FlipRoundRect     ( const QRectF & rect           ,
                                       const QBrush & brush          ,
                                       QWidget      * embeddedWidget )
                 : QGraphicsRectItem ( rect                          )
                 , m_brush           ( brush                         )
                 , m_opacity         ( 1                             )
                 , m_proxyWidget     ( 0                             )
                 , m_borderWidth     ( 0                             )
                 , m_roundBorder     ( false                         )
{ 
  if ( IsNull(embeddedWidget) ) return ;
  m_proxyWidget = new QGraphicsProxyWidget( this );
  m_proxyWidget->setFocusPolicy( Qt::StrongFocus );
  m_proxyWidget->setWidget( embeddedWidget );
  m_proxyWidget->setGeometry( boundingRect().adjusted( m_borderWidth, m_borderWidth, -m_borderWidth, -m_borderWidth ) );
}

N::FlipRoundRect::~FlipRoundRect (void)
{
}

void N::FlipRoundRect::paint( QPainter * painter, const QStyleOptionGraphicsItem * , QWidget * )
{
  QTransform x = painter->worldTransform() ;

  QLineF unit = x.map( QLineF( 0, 0, 1, 1 ) );
  if ( unit.p1().x() > unit.p2().x() || unit.p1().y() > unit.p2().y() ) {
    if ( m_proxyWidget && m_proxyWidget->isVisible() ) {
      m_proxyWidget->hide();
      m_proxyWidget->setGeometry( rect() );
    }
    return;
  }

  if ( m_proxyWidget && !m_proxyWidget->isVisible() ) {
    m_proxyWidget->show();
    m_proxyWidget->setFocus();
  }

  if ( m_proxyWidget && m_proxyWidget->pos() != QPoint() ) {
    m_proxyWidget->setGeometry( boundingRect().adjusted( m_borderWidth, m_borderWidth, -m_borderWidth, -m_borderWidth ) );
  }

  painter->setOpacity( opacity() );
  painter->setPen( Qt::NoPen );
  painter->setBrush( QColor(0, 0, 0, 64 ) );

  if ( m_roundBorder ) {
    painter->drawRoundRect( rect().translated( 2, 2 ) );
  } else {
    painter->drawRect( rect().translated( 2, 2 ) );
  }

  painter->setBrush( m_brush );
  painter->setPen( QPen( Qt::black, 1 ) );

  if ( m_roundBorder ) {
    painter->drawRoundRect( rect() );
  } else {
    painter->drawRect( rect() );
  }

  if ( !m_pixmap.isNull() ) {
    painter->scale( 1.95, 1.95 );
    painter->drawPixmap( -m_pixmap.width() / 2, -m_pixmap.height() / 2, m_pixmap );
  }

}

void N::FlipRoundRect::setBorderBrush( const QBrush & brush )
{
  m_brush = brush ;
}

void N::FlipRoundRect::setBorderWidth( qreal width )
{
  m_borderWidth = width ;
}

void N::FlipRoundRect::setRoundBorder( bool round )
{
  m_roundBorder = round ;
}

QRectF N::FlipRoundRect::boundingRect(void) const
{
  qreal penW    = 0.5                                                    ;
  qreal shadowW = 2.0                                                    ;
  return rect().adjusted( -penW, -penW, penW + shadowW, penW + shadowW ) ;
}

void N::FlipRoundRect::setPixmap( const QPixmap & pixmap )
{
  m_pixmap = pixmap                      ;
  if ( scene() && isVisible() ) update() ;
}

qreal N::FlipRoundRect::opacity() const
{
  FlipRoundRect * parent = parentItem() ? (FlipRoundRect*)parentItem() : 0 ;
  return m_opacity + ( parent ? parent->opacity() : 0 )                    ;
}

void N::FlipRoundRect::setOpacity( qreal opacity )
{
  m_opacity = opacity ;
  update ( )          ;
}
