#include <qtcomponents.h>

static N::BalloonTip * theSolitaryBalloonTip = NULL ;

N::BalloonTip::BalloonTip (const QString & title   ,
                           const QString & message ,
                           QWidget * parent        )
              : QWidget   (parent, Qt::ToolTip     )
              , timerId   (-1                      )
{
  Configure ( title , message ) ;
}

N::BalloonTip::~BalloonTip(void)
{
  theSolitaryBalloonTip = NULL ;
}

QWidget * N::BalloonTip::showBalloon  (
            const QString & title     ,
            const QString & message   ,
            int             timeout   ,
            bool            showArrow )
{
  hideBalloon ( )                                        ;
  theSolitaryBalloonTip = new BalloonTip(title, message) ;
  if (timeout < 0) timeout = 10000                       ;
  theSolitaryBalloonTip->balloon(timeout, showArrow)     ;
  return theSolitaryBalloonTip                           ;
}

void N::BalloonTip::hideBalloon(void)
{
  if (IsNull(theSolitaryBalloonTip)) return ;
  theSolitaryBalloonTip->hide()             ;
  delete theSolitaryBalloonTip              ;
  theSolitaryBalloonTip = NULL              ;
}

void N::BalloonTip::paintEvent(QPaintEvent *)
{
  QPainter painter   ( this            ) ;
  painter.drawPixmap ( rect() , pixmap ) ;
}

void N::BalloonTip::resizeEvent(QResizeEvent * event)
{
  QWidget::resizeEvent(event) ;
}

void N::BalloonTip::mousePressEvent(QMouseEvent *)
{
  close ( ) ;
}

void N::BalloonTip::timerEvent(QTimerEvent * event)
{
  if (event->timerId() == timerId) {
    killTimer(timerId)             ;
    timerId = -1                   ;
    if (!underMouse()) close()     ;
    return                         ;
  }                                ;
  QWidget::timerEvent(event)       ;
}

void N::BalloonTip::Configure(const QString & title,const QString & message)
{
  setAttribute  ( Qt::WA_DeleteOnClose )   ;
  setObjectName ( "nBalloonTip"        )   ;
  //////////////////////////////////////////
  QLabel * titleLabel = new QLabel         ;
  titleLabel->installEventFilter(this)     ;
  titleLabel->setText(title)               ;
  //////////////////////////////////////////
  QFont f = titleLabel->font()                ;
  f.setBold(true)                             ;
  titleLabel->setFont(f)                      ;
  titleLabel->setTextFormat(Qt::PlainText)    ;
  /////////////////////////////////////////////
  QPushButton * closeButton = new QPushButton ;
  closeButton->setIcon(style()->standardIcon(QStyle::SP_DockWidgetCloseButton));
  closeButton->setIconSize(QSize(18, 18));
  closeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  closeButton->setFixedSize(18, 18);
  QObject::connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
  ////////////////////////////////////////////////////////////////////////////
  QLabel *msgLabel = new QLabel;
  msgLabel->installEventFilter(this);
  msgLabel->setText(message);
  msgLabel->setTextFormat(Qt::PlainText);
  msgLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  ////////////////////////////////////////////////////////////////////////////
  int limit = QApplication::desktop()->availableGeometry(msgLabel).size().width() / 3;
  if (msgLabel->sizeHint().width() > limit) {
    msgLabel->setWordWrap(true);
    msgLabel->setFixedSize(limit, msgLabel->heightForWidth(limit));
  } ;
  ////////////////////////////////////////////////////////////////////////////
  QGridLayout *layout = new QGridLayout;
  layout->addWidget(titleLabel, 0, 0, 1, 2);
  layout->addWidget(closeButton, 0, 2);
  layout->addWidget(msgLabel, 1, 0, 1, 3);
  layout->setSizeConstraint(QLayout::SetFixedSize);
  layout->setMargin(3);
  setLayout(layout);
  ////////////////////////////////////////////////////////////////////////////
  QPalette pal = palette();
  pal.setColor(QPalette::Window, QColor(0xff, 0xff, 0xe1));
  setPalette(pal);
}

void N::BalloonTip::balloon(int msecs, bool showArrow)
{
  QSize sh = sizeHint();
  QRect desktopRect = qApp->desktop()->availableGeometry();
  QPoint bottomRight=desktopRect.bottomRight();
  const QPoint& pos=mapToGlobal(QPoint(bottomRight.x(),bottomRight.y()/*-sh.height()*/));
  const QPoint& localpos=QPoint(pos);
  const QRect& prect=desktopRect;
  QRect scr = prect;
  const int border = 1;
  const int ah = 18, ao = 18, aw = 18, rc = 7;
  /////////////////////////////////////////////////////////////////////////////
  bool arrowAtTop = (localpos.y() - sh.height() - ah < 0);//scr.height());
  bool arrowAtLeft = (localpos.x() + sh.width() - ao < scr.width());
  setContentsMargins(border + 3, border + (arrowAtTop ? ah : 0) + 2, border + 3, border + (arrowAtTop ? 0 : ah) + 2);
  updateGeometry();
  sh = sizeHint();
  /////////////////////////////////////////////////////////////////////////////
  int ml, mr, mt, mb;
  QSize sz = sizeHint();
  if (!arrowAtTop) {
    ml = mt = 0;
    mr = sz.width() - 1;
    mb = sz.height() - ah - 1;
  } else {
    ml = 0;
    mt = ah;
    mr = sz.width() - 1;
    mb = sz.height() - 1;
  }
  /////////////////////////////////////////////////////////////////////////////
  QPainterPath path;
  path.moveTo(ml + rc, mt);
  if (arrowAtTop && arrowAtLeft) {
    if (showArrow) {
      path.lineTo(ml + ao, mt);
      path.lineTo(ml + ao, mt - ah);
      path.lineTo(ml + ao + aw, mt);
    }
    move(qMax(pos.x() - ao, scr.left() + 2), pos.y());
  } else
  if (arrowAtTop && !arrowAtLeft) {
    if (showArrow) {
      path.lineTo(mr - ao - aw, mt);
      path.lineTo(mr - ao, mt - ah);
      path.lineTo(mr - ao, mt);
    }
    move(qMin(pos.x() - sh.width() + ao, scr.right() - sh.width() - 2), pos.y());
  }
  path.lineTo(mr - rc, mt);
  path.arcTo(QRect(mr - rc*2, mt, rc*2, rc*2), 90, -90);
  path.lineTo(mr, mb - rc);
  path.arcTo(QRect(mr - rc*2, mb - rc*2, rc*2, rc*2), 0, -90);
  if (!arrowAtTop && !arrowAtLeft) {
    if (showArrow) {
      path.lineTo(mr - ao, mb);
      path.lineTo(mr - ao, mb + ah);
      path.lineTo(mr - ao - aw, mb);
    }
    move(qMin(pos.x() - sh.width() + ao, scr.right() - sh.width() - 2),
         pos.y() - sh.height());
  } else
  if (!arrowAtTop && arrowAtLeft) {
    if (showArrow) {
      path.lineTo(ao + aw, mb);
      path.lineTo(ao, mb + ah);
      path.lineTo(ao, mb);
    }
    move(qMax(pos.x() - ao, scr.x() + 2), pos.y() - sh.height());
  }
  path.lineTo(ml + rc, mb);
  path.arcTo(QRect(ml, mb - rc*2, rc*2, rc*2), -90, -90);
  path.lineTo(ml, mt + rc);
  path.arcTo(QRect(ml, mt, rc*2, rc*2), 180, -90);
  /////////////////////////////////////////////////////////////////////////////
  if (msecs > 0) timerId = startTimer(msecs) ;
  show();
}
