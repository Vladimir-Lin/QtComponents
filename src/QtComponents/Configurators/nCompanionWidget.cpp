#include <qtcomponents.h>

N::CompanionWidget:: CompanionWidget ( QWidget * w , Plan * p )
                   : IconDock        (           w ,        p )
                   , wrapper         ( NULL                   )
                   , cpu             ( NULL                   )
                   , bgimg           ( NULL                   )
                   , desktop         ( NULL                   )
                   , monitors        ( NULL                   )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::CompanionWidget::~CompanionWidget (void)
{
  Stop ( )                         ;
  mutex [ "Listing" ] . lock   ( ) ;
  if ( NULL != bgimg    )          {
    delete bgimg                   ;
  }                                ;
  if ( NULL != desktop  )          {
    delete desktop                 ;
  }                                ;
  if ( NULL != monitors )          {
    delete monitors                ;
  }                                ;
  mutex [ "Listing" ] . unlock ( ) ;
}

void N::CompanionWidget::Configure(void)
{
  setWindowTitle               ( tr("Companions")              ) ;
  setAccessibleName            ( "N::CompanionWidget"          ) ;
  setObjectName                ( "N::CompanionWidget"          ) ;
  setDragDropMode              ( DragDrop                      ) ;
  setViewMode                  ( IconMode                      ) ;
  setIconSize                  ( QSize (  64 ,  64 )           ) ;
  setGridSize                  ( QSize (  72 ,  96 )           ) ;
  setMinimumSize               ( QSize ( 144 , 108 )           ) ;
  setMovement                  ( Snap                          ) ;
  setResizeMode                ( Adjust                        ) ;
  setSelectionMode             ( ExtendedSelection             ) ;
  setWordWrap                  ( true                          ) ;
  setMouseTracking             ( true                          ) ;
  setWrapping                  ( true                          ) ;
  setTextElideMode             ( Qt::ElideNone                 ) ;
  setHorizontalScrollBarPolicy ( Qt::ScrollBarAsNeeded         ) ;
  setVerticalScrollBarPolicy   ( Qt::ScrollBarAsNeeded         ) ;
  setDropFlag                  ( DropText     , false          ) ;
  setDropFlag                  ( DropUrls     , false          ) ;
  setDropFlag                  ( DropImage    , false          ) ;
  setDropFlag                  ( DropHtml     , false          ) ;
  setDropFlag                  ( DropColor    , false          ) ;
  setDropFlag                  ( DropTag      , false          ) ;
  setDropFlag                  ( DropPicture  , false          ) ;
  setDropFlag                  ( DropPeople   , false          ) ;
  setDropFlag                  ( DropVideo    , false          ) ;
  setDropFlag                  ( DropAlbum    , false          ) ;
  setDropFlag                  ( DropGender   , false          ) ;
  setDropFlag                  ( DropDivision , false          ) ;
  MountCommands                (                               ) ;
  ////////////////////////////////////////////////////////////////
  setLimitValue                ( 170001       , 1000           ) ;
  setLimitValue                ( 170002       , 0              ) ;
  plan   -> setFont            ( this                          ) ;
  ////////////////////////////////////////////////////////////////
  QImage r                                                       ;
  QImage b                                                       ;
  r = QImage ( ":/images/server.png" )                           ;
  b = r . scaled ( QSize(64,64)                                  ,
                   Qt::KeepAspectRatio                           ,
                   Qt::SmoothTransformation                    ) ;
  bgimg    = new QImage ( b )                                    ;
  r = QImage ( ":/images/desktop.png" )                          ;
  b = r . scaled ( QSize(16,16)                                  ,
                   Qt::KeepAspectRatio                           ,
                   Qt::SmoothTransformation                    ) ;
  desktop  = new QImage ( b )                                    ;
  r = QImage ( ":/images/monitors.png" )                         ;
  b = r . scaled ( QSize(24,24)                                  ,
                   Qt::KeepAspectRatio                           ,
                   Qt::SmoothTransformation                    ) ;
  monitors = new QImage ( b )                                    ;
  nConnect                     ( this , SIGNAL ( Changes ( ) )   ,
                                 this , SLOT   ( Listing ( ) ) ) ;
}

void N::CompanionWidget::setWrapper(N::ToolWrapper * w)
{
  wrapper = w ;
}

void N::CompanionWidget::Appear(void)
{
  QWidget * w = this                 ;
  if ( NULL != wrapper ) w = wrapper ;
  nDropOut ( w -> isVisible ( ) )    ;
  FadeIn   ( w , 10             )    ;
}

void N::CompanionWidget::Disappear(void)
{
  QWidget * w = this                 ;
  if ( NULL != wrapper ) w = wrapper ;
  nDropOut ( ! w -> isVisible ( ) )  ;
  FadeOut  ( w , 10               )  ;
}

void N::CompanionWidget::Vanish(void)
{
  QWidget * w = this     ;
  if ( NULL != wrapper ) {
    w = wrapper          ;
  }                      ;
  w -> hide ( )          ;
}

void N::CompanionWidget::Eradicate(void)
{
  QWidget * w = this     ;
  if ( NULL != wrapper ) {
    w = wrapper          ;
  }                      ;
  w -> deleteLater ( )   ;
}

void N::CompanionWidget::run(int T,ThreadData * d)
{
  ItemRunner ( T , d ) ;
}

bool N::CompanionWidget::ItemRunner(int T,ThreadData * d)
{
  return false ;
}

void N::CompanionWidget::singleClicked (QListWidgetItem * item)
{
  if ( IsNull ( item ) ) return ;
  alert ( "Action" , "" )       ;
}

void N::CompanionWidget::doubleClicked (QListWidgetItem * item)
{
  if ( IsNull ( item ) ) return ;
  QString n = item -> text ( )  ;
  emit Chat ( n )               ;
}

void N::CompanionWidget::setMachineIcon(QImage & img)
{
  mutex [ "Listing" ] . lock   ( )                   ;
  if ( bgimg != NULL ) delete bgimg                  ;
  QImage r = img                                     ;
  QImage b = r . scaled ( QSize(64,64)               ,
                          Qt::KeepAspectRatio        ,
                          Qt::SmoothTransformation ) ;
  bgimg = new QImage ( b )                           ;
  mutex [ "Listing" ] . unlock ( )                   ;
}

void N::CompanionWidget::Visit(void)
{
  QListWidgetItem * item = currentItem ( ) ;
  if ( IsNull ( item ) ) return            ;
  doubleClicked ( item )                   ;
}

void N::CompanionWidget::Close(void)
{
  emit Complete ( ) ;
}

void N::CompanionWidget::Start(void)
{
  if ( NULL != cpu ) return                    ;
  cpu = new QTimer ( this )                    ;
  nConnect ( cpu  , SIGNAL ( timeout ( ) )     ,
             this , SLOT   ( Reflush ( ) )   ) ;
  cpu -> setInterval ( LimitValue ( 170001 ) ) ;
  cpu -> start       ( LimitValue ( 170001 ) ) ;
}

void N::CompanionWidget::Stop(void)
{
  if ( NULL == cpu ) return ;
  cpu -> stop        ( )    ;
  cpu -> deleteLater ( )    ;
  cpu  = NULL               ;
}

void N::CompanionWidget::Reflush(void)
{
  if ( ! isVisible ( )            ) return                              ;
  if ( LimitValues [ 170002 ] > 0 ) return                              ;
  qint32 * m = plan -> profiler -> IntPointer ( "process" , "machine" ) ;
  if ( NULL == m                  ) return                              ;
  ///////////////////////////////////////////////////////////////////////
  if ( plan -> profiler -> isReadable ( ) )                             {
    int mav      = (*m)                                                 ;
    int interval = cpu -> interval ( )                                  ;
    int stdv     = LimitValues [ 170001 ]                               ;
    if ( mav > 9750 ) stdv *= 8                                    ; else
    if ( mav > 9500 ) stdv *= 5                                    ; else
    if ( mav > 9000 ) stdv *= 4                                    ; else
    if ( mav > 8500 ) stdv *= 3                                    ; else
    if ( mav > 8000 ) stdv *= 2                                         ;
    if ( interval != stdv ) cpu -> setInterval ( stdv )                 ;
  } else return                                                         ;
  ///////////////////////////////////////////////////////////////////////
  emit Changes ( )                                                      ;
}

void N::CompanionWidget::DrawMachine(QListWidgetItem * item,QString host)
{
  if ( ! plan -> parallel -> hasCompanion ( host ) ) return                  ;
  QtParallel::Companion * nf = plan -> parallel -> FindCompanion ( host )    ;
  if ( NULL == nf ) return                                                   ;
  nf -> lock   ( )                                                           ;
  ////////////////////////////////////////////////////////////////////////////
  QImage   imgs = (*bgimg)                                                   ;
  QSize    ims  = imgs . size  ( )                                           ;
  QFont    fnt  = font         ( )                                           ;
  bool     self = nf -> isSelf ( )                                           ;
  qint64   mll  = nf -> Information [ "MachineCpu"  ] . toLongLong ( )       ;
  qint64   pll  = nf -> Information [ "ProcessCpu"  ] . toLongLong ( )       ;
  qint64   mtl  = nf -> Information [ "MemoryLoad"  ] . toLongLong ( )       ;
  QString  ip   = nf -> IpAddress ( )                                        ;
  QString  pss  = QString ( "%1%" ) . arg ( mll/100 )                        ;
  int      mts  = 0                                                          ;
  QPen     fpen       ( QColor ( 168 ,  88 , 168 )                         ) ; /*! light Lilac */
  QBrush   fbbb       ( QColor ( 168 ,  88 , 168 )                         ) ;
  QPen     vpen       ( QColor ( 153 , 204 ,  51 )                         ) ; /*! light green */
  QBrush   vbbb       ( QColor ( 153 , 204 ,  51 )                         ) ;
  QPen     ppen       ( QColor ( 255 , 215 ,  51 )                         ) ; /*! golden yellow */
  QBrush   pbbb       ( QColor ( 255 , 215 ,  51 )                         ) ;
  QRect    T          ( 0 , 0 , ims . width ( ) , 8                        ) ;
  QIcon    icns                                                              ;
  QPainter p                                                                 ;
  ////////////////////////////////////////////////////////////////////////////
  if ( nf -> Information . contains ( "Monitors" ) )                         {
    mts = nf -> Information [ "Monitors" ] . toInt ( )                       ;
  }                                                                          ;
  nf -> unlock ( )                                                           ;
  ////////////////////////////////////////////////////////////////////////////
  mll *= ims . width  (                                                    ) ;
  mll /= 10000                                                               ;
  pll *= ims . width  (                                                    ) ;
  pll /= 10000                                                               ;
  ////////////////////////////////////////////////////////////////////////////
  p   . begin         ( &imgs                                              ) ;
  ////////////////////////////////////////////////////////////////////////////
  if ( self && ( NULL != desktop ) )                                         { /*! Draw desktop icon if this is myself */
    QSize pc ( imgs . width ( ) / 4 , imgs . height ( ) / 4 )                ;
    QRect rc ( imgs . width ( ) - pc . width  ( )                            ,
               imgs . height( ) - pc . height ( )                            ,
                                  pc . width  ( )                            ,
                                  pc . height ( )                          ) ;
    p . drawImage     ( rc , *desktop                                      ) ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( ( mts > 1 ) && ( NULL != monitors ) )                                 { /*! Draw multiple head monitors icon */
    QSize pc ( imgs . width ( ) * 3 / 8 , imgs . height ( ) * 3 / 8 )        ;
    QRect rc ( 0                                                             ,
               imgs . height( ) - pc . height ( )                            ,
                                  pc . width  ( )                            ,
                                  pc . height ( )                          ) ;
    p . drawImage     ( rc , *monitors                                     ) ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if                  ( mll > 0                                            ) { /*! Draw machine usage */
    QRect R           ( 0 , ims . height ( ) - 9 , mll , 8                 ) ;
    p . setOpacity    ( 0.50                                               ) ;
    p . setPen        ( ppen                                               ) ;
    p . fillRect      ( R , vbbb                                           ) ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if                  ( pll > 0                                            ) { /*! Draw process usage */
    QRect R           ( 0 , 0                    , pll , 8                 ) ;
    p . setOpacity    ( 0.50                                               ) ;
    p . setPen        ( vpen                                               ) ;
    p . fillRect      ( R , pbbb                                           ) ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( mtl > 0 )                                                             { /*! Draw memory load */
    mtl *= imgs . height ( )                                                 ;
    mtl /= 100                                                               ;
    QRect MV          ( ims . width  ( ) - 10 , ims . height ( ) - mtl       ,
                                            8 ,                    mtl     ) ;
    p . setOpacity    ( 0.50                                               ) ;
    p . setPen        ( vpen                                               ) ;
    p . fillRect      ( MV , fbbb                                          ) ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  fnt . setPixelSize  ( 8                                                  ) ;
  p   . setOpacity    ( 1.0                                                ) ;
  p   . setFont       ( fnt                                                ) ; /*! Draw machine usage text */
  p   . setPen        ( fpen                                               ) ;
  p   . setBrush      ( fbbb                                               ) ;
  p   . drawText      ( T , Qt::AlignRight | Qt::AlignVCenter , pss        ) ;
  ////////////////////////////////////////////////////////////////////////////
  p   . end           (                                                    ) ;
  ////////////////////////////////////////////////////////////////////////////
  icns  = QIcon       ( QPixmap::fromImage ( imgs )                        ) ; /*! Assign into ICON */
  item -> setIcon     ( icns                                               ) ;
  item -> setText     ( host                                               ) ;
  item -> setToolTip  ( ip                                                 ) ;
}

void N::CompanionWidget::Listing(void)
{
  if ( NULL == plan -> parallel   ) return              ;
  if ( LimitValues [ 170002 ] > 0 ) return              ;
  bool changed = false                                  ;
  if ( ! mutex [ "Listing" ] . tryLock ( 100 ) ) return ;
  LimitValues [ 170002 ] = 1                            ;
  ///////////////////////////////////////////////////////
  QStringList H = plan -> parallel  -> Others ( )       ;
  QStringList L = HostItems          . keys   ( )       ;
  QString     host                                      ;
  if ( ! H . contains ( plan -> Hostname ) )            {
    H . prepend ( plan -> Hostname )                    ;
  }                                                     ;
  ///////////////////////////////////////////////////////
  foreach ( host , L ) if ( ! H . contains ( host ) )   { /*! Remove aparted companions */
    QListWidgetItem * lwi = HostItems [ host ]          ;
    if ( NULL != lwi )                                  {
      int index = row ( lwi )                           ;
      if ( index >= 0 )                                 {
        HostItems . remove ( host  )                    ;
        takeItem           ( index )                    ;
        changed = true                                  ;
      }                                                 ;
    }                                                   ;
  }                                                     ;
  ///////////////////////////////////////////////////////
  foreach ( host , H )                                  {
    QListWidgetItem * lwi                               ; /*! Ensure host exists in the list */
    if ( HostItems . contains ( host ) )                {
      lwi = HostItems [ host ]                          ;
    } else                                              {
      lwi     = new QListWidgetItem ( )                 ;
      changed = true                                    ;
    }                                                   ;
    DrawMachine ( lwi , host )                          ;
    if ( ! HostItems . contains ( host ) )              {
      QListWidget::addItem ( lwi )                      ;
      HostItems [ host ] = lwi                          ;
    }                                                   ;
  }                                                     ;
  ///////////////////////////////////////////////////////
  LimitValues [ 170002 ] = 0                            ;
  mutex [ "Listing" ] . unlock ( )                      ;
  if ( changed ) CompanionsChanged ( )                  ;
}

bool N::CompanionWidget::Menu(QPoint pos)
{
  nScopedMenu ( mm , this )                                        ;
  QListWidgetItem       * lwi  = itemAt ( pos )                    ;
  QAction               * aa                                       ;
  QString                 name = ""                                ;
  QtParallel::Companion * pc   = NULL                              ;
  bool                    self = false                             ;
  //////////////////////////////////////////////////////////////////
  mm   . add ( 101 , tr("Parallel computing")                    ) ;
  if ( NULL != lwi )                                               {
    name = lwi -> text ( )                                         ;
    mm . addSeparator ( )                                          ;
    mm . add ( 401 , tr("%1 details").arg(name)                  ) ;
    mm . add ( 402 , tr("Chat to %1").arg(name)                  ) ;
    mm . add ( 403 , tr("Command to %1").arg(name)               ) ;
    mm . addSeparator ( )                                          ;
    mm . add ( 404 , tr("Quit %1").arg(name)                     ) ;
    if ( NULL != plan -> parallel )                                {
      if ( plan -> parallel -> hasCompanion ( name ) )             {
        pc = plan -> parallel -> FindCompanion ( name )            ;
        if ( NULL != pc ) self = pc -> isSelf ( )                  ;
      }                                                            ;
    }                                                              ;
  }                                                                ;
  //////////////////////////////////////////////////////////////////
  if ( self && ( NULL != pc ) )                                    {
    bool sendAudio = false                                         ;
    bool recvAudio = false                                         ;
    if ( pc -> Information . contains ( "SendAudio"   ) )          {
      sendAudio = pc -> Information [ "SendAudio"   ] . toBool ( ) ;
    }                                                              ;
    if ( pc -> Information . contains ( "AcceptAudio" ) )          {
      recvAudio = pc -> Information [ "AcceptAudio" ] . toBool ( ) ;
    }                                                              ;
    mm . addSeparator ( )                                          ;
    if ( sendAudio )                                               {
      mm . add ( 511 , tr("Disable audio transmitting")          ) ;
    } else                                                         {
      mm . add ( 501 , tr("Enable audio transmitting")           ) ;
    }                                                              ;
    if ( recvAudio )                                               {
      mm . add ( 512 , tr("Disable audio receiving")             ) ;
    } else                                                         {
      mm . add ( 502 , tr("Enable audio receiving")              ) ;
    }                                                              ;
  }                                                                ;
  //////////////////////////////////////////////////////////////////
  mm . setFont   ( plan )                                          ;
  aa = mm . exec (      )                                          ;
  if ( NULL == aa )                                                {
    return true                                                    ;
  }                                                                ;
  //////////////////////////////////////////////////////////////////
  switch ( mm [ aa ] )                                             {
    case 101                                                       :
      emit ParallelComputing ( )                                   ;
    break                                                          ;
    case 401                                                       :
      if ( name . length ( ) > 0 ) emit Details   ( name )         ;
    break                                                          ;
    case 402                                                       :
      if ( name . length ( ) > 0 ) emit Chat      ( name )         ;
    break                                                          ;
    case 403                                                       :
      if ( name . length ( ) > 0 ) emit CommandTo ( name )         ;
    break                                                          ;
    case 404                                                       :
      if ( name . length ( ) > 0 ) emit Quit      ( name )         ;
    break                                                          ;
    case 501                                                       :
      if ( NULL != pc )                                            {
        pc -> Information [ "SendAudio"   ] = true                 ;
      }                                                            ;
    break                                                          ;
    case 502                                                       :
      if ( NULL != pc )                                            {
        pc -> Information [ "AcceptAudio" ] = true                 ;
      }                                                            ;
    break                                                          ;
    case 511                                                       :
      if ( NULL != pc )                                            {
        pc -> Information [ "SendAudio"   ] = false                ;
      }                                                            ;
    break                                                          ;
    case 512                                                       :
      if ( NULL != pc )                                            {
        pc -> Information [ "AcceptAudio" ] = false                ;
      }                                                            ;
    break                                                          ;
  }                                                                ;
  //////////////////////////////////////////////////////////////////
  return true                                                      ;
}
