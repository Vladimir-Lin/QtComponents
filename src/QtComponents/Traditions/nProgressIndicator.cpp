#include <qtcomponents.h>

N::ProgressIndicator:: ProgressIndicator      ( QWidget * parent , Plan * p )
                     : Widget                 (           parent ,        p )
                     , m_angle                ( 0                           )
                     , m_timerId              ( -1                          )
                     , m_delay                ( 40                          )
                     , m_entry                ( 0                           )
                     , m_count                ( 15                          )
                     , m_factor               ( 0.50                        )
                     , m_displayedWhenStopped ( false                       )
                     , m_color                ( Qt::black                   )
{
  WidgetClass                                              ;
  setSizePolicy  ( QSizePolicy::Fixed,QSizePolicy::Fixed ) ;
  setFocusPolicy ( Qt::NoFocus                           ) ;
  hint = QSize   ( 20 , 20                               ) ;
}

N::ProgressIndicator:: ProgressIndicator      ( QWidget * parent , Plan * p , QSize h)
                     : Widget                 (           parent ,        p          )
                     , m_angle                ( 0                                    )
                     , m_timerId              ( -1                                   )
                     , m_delay                ( 40                                   )
                     , m_entry                ( 0                                    )
                     , m_count                ( 15                                   )
                     , m_factor               ( 0.50                                 )
                     , m_displayedWhenStopped ( false                                )
                     , m_color                ( Qt::black                            )
{
  WidgetClass                                              ;
  setSizePolicy  ( QSizePolicy::Fixed,QSizePolicy::Fixed ) ;
  setFocusPolicy ( Qt::NoFocus                           ) ;
  hint = h                                                 ;
}

N::ProgressIndicator::~ProgressIndicator(void)
{
}

int N::ProgressIndicator::animationDelay(void) const
{
  return m_delay ;
}

const QColor & N::ProgressIndicator::color(void) const
{
  return m_color ;
}

int N::ProgressIndicator::TickCount(void) const
{
  return m_count ;
}

double N::ProgressIndicator::RadiusFactor(void) const
{
  return m_factor ;
}

bool N::ProgressIndicator::isAnimated(void) const
{
  return ( m_timerId != -1 ) ;
}

void N::ProgressIndicator::setDisplayedWhenStopped(bool state)
{
  m_displayedWhenStopped = state ;
  update ( )                     ;
}

bool N::ProgressIndicator::isDisplayedWhenStopped(void) const
{
  return m_displayedWhenStopped ;
}

void N::ProgressIndicator::startAnimation(void)
{
  m_entry++                            ;
  if ( m_entry > 1 ) return            ;
  m_angle = 0                          ;
  if ( m_timerId == -1)                {
    m_timerId = startTimer ( m_delay ) ;
  }                                    ;
}

int N::ProgressIndicator::stopAnimation(void)
{
  m_entry--                                      ;
  if ( m_entry > 0 ) return m_entry              ;
  if ( m_timerId != -1 ) killTimer ( m_timerId ) ;
  m_timerId = -1                                 ;
  update ( )                                     ;
  return 0                                       ;
}

void N::ProgressIndicator::setAnimationDelay(int delay)
{
  if ( m_timerId != -1 ) killTimer ( m_timerId ) ;
  m_delay = delay                                ;
  if ( m_timerId != -1 )                         {
    m_timerId = startTimer ( m_delay )           ;
  }                                              ;
}

void N::ProgressIndicator::setColor(const QColor & color)
{
  m_color = color ;
  update ( )      ;
}

void N::ProgressIndicator::setTicks(int count)
{
  m_count = count ;
}

void N::ProgressIndicator::setRadiusFactor(double factor)
{
  m_factor = factor ;
}

QSize N::ProgressIndicator::sizeHint(void) const
{
  return hint ;
}

int N::ProgressIndicator::heightForWidth(int w) const
{
  return w ;
}

void N::ProgressIndicator::timerEvent(QTimerEvent * ee)
{ Q_UNUSED ( ee )                                 ;
  m_angle = ( m_angle + ( 360 / m_count ) ) % 360 ;
  update ( )                                      ;
}

void N::ProgressIndicator::paintEvent(QPaintEvent * ep)
{ Q_UNUSED ( ep ) ;
  if ( ( ! m_displayedWhenStopped ) && ( ! isAnimated ( ) ) ) return          ;
  int width = qMin(this->width(), this->height())                             ;
  QPainter p(this)                                                            ;
  p.setRenderHint(QPainter::Antialiasing)                                     ;
  /////////////////////////////////////////////////////////////////////////////
  int outerRadius   = (width-1)*0.50                                          ;
  int innerRadius   = (width-1)*0.50*m_factor                                 ;
  int capsuleHeight = outerRadius - innerRadius                               ;
  int capsuleWidth  = (width > 32 ) ? capsuleHeight *.23 : capsuleHeight *.35 ;
  int capsuleRadius = capsuleWidth/2                                          ;
  /////////////////////////////////////////////////////////////////////////////
  int    gap   = m_count                                                      ;
  double angle = 360.0 / gap                                                  ;
  for (int i=0; i<gap; i++)                                                   {
     QColor color = m_color                                                   ;
     color . setAlphaF       ( 1.0f - ( ( (double ) i ) / ( (double) gap ) )) ;
     p     . setPen          ( Qt::NoPen                                    ) ;
     p     . setBrush        ( color                                        ) ;
     p     . save            (                                              ) ;
     p     . translate       ( rect().center()                              ) ;
     p     . rotate          ( m_angle - i * angle                          ) ;
     p     . drawRoundedRect ( -capsuleWidth*0.5                              ,
                               -( innerRadius + capsuleHeight )               ,
                                capsuleWidth                                  ,
                                capsuleHeight                                 ,
                                capsuleRadius                                 ,
                                capsuleRadius                               ) ;
     p     . restore         (                                              ) ;
  }                                                                           ;
}
