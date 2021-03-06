#include <qtcomponents.h>

typedef struct                     {
  const QObject         * sender   ;
  const char            * signal   ;
  const QObject         * receiver ;
  const char            * method   ;
  enum Qt::ConnectionType type     ;
} SignalConnections                ;

N::VirtualGui:: VirtualGui  (QWidget * widget,Plan * p)
              : AbstractGui (          widget,       p)
{
}

N::VirtualGui::~VirtualGui(void)
{
  QStringList k = SignalConnectors . keys ( )         ;
  QString     s                                       ;
  foreach ( s , k )                                   {
    SignalConnections * sc                            ;
    sc = (SignalConnections *) SignalConnectors [ s ] ;
    SignalConnectors . remove ( s )                   ;
    if ( NotNull(sc) )                                {
      delete sc                                       ;
    }                                                 ;
  }                                                   ;
  SignalConnectors . clear ( )                        ;
}

void N::VirtualGui::addIntoWidget(QWidget * parent,QWidget * widget)
{
  QStackedWidget * stacked = Casting(QStackedWidget,parent) ;
  if (NotNull(stacked)) stacked->addWidget(widget)          ;
}

Qt::WindowFlags N::VirtualGui::Frameless(QWidget * widget)
{
  Qt::WindowFlags wflags = widget->windowFlags()                              ;
//  wflags  =  Qt::WindowStaysOnTopHint                                         ;
  wflags  =  Qt::FramelessWindowHint                                          ;
  wflags |=  Qt::CustomizeWindowHint                                          ;
  wflags &= (Qt::WindowFlags)(0xFFFFFFFF ^ (unsigned int)Qt::WindowTitleHint) ;
  widget->setWindowFlags(wflags)                                              ;
  return wflags                                                               ;
}

bool N::VirtualGui::allowDrag(QAbstractItemView::DragDropMode dragDrop)
{
  switch (dragDrop)                                     {
    case QAbstractItemView::NoDragDrop   : return false ;
    case QAbstractItemView::DragOnly     : return true  ;
    case QAbstractItemView::DropOnly     : return false ;
    case QAbstractItemView::DragDrop     : return true  ;
    case QAbstractItemView::InternalMove : return false ;
  }                                                     ;
  return false                                          ;
}

bool N::VirtualGui::allowDrop(QAbstractItemView::DragDropMode dragDrop)
{
  switch (dragDrop)                                     {
    case QAbstractItemView::NoDragDrop   : return false ;
    case QAbstractItemView::DragOnly     : return false ;
    case QAbstractItemView::DropOnly     : return true  ;
    case QAbstractItemView::DragDrop     : return true  ;
    case QAbstractItemView::InternalMove : return false ;
  }                                                     ;
  return false                                          ;
}

void N::VirtualGui::addConnector         (
        QString                 name     ,
        const QObject         * sender   ,
        const char            * signal   ,
        const QObject         * receiver ,
        const char            * method   ,
        enum Qt::ConnectionType type     )
{
  SignalConnections * sc            ;
  removeConnector ( name )          ;
  sc  = new SignalConnections ( )   ;
  sc -> sender   = sender           ;
  sc -> signal   = signal           ;
  sc -> receiver = receiver         ;
  sc -> method   = method           ;
  sc -> type     = type             ;
  SignalConnectors [ name ] = sc    ;
}

void N::VirtualGui::addConnector         (
        QString                 name     ,
        const QObject         * sender   ,
        const char            * signal   ,
        const QObject         * receiver ,
        const char            * method   )
{
  addConnector ( name                 ,
                 sender               ,
                 signal               ,
                 receiver             ,
                 method               ,
                 Qt::AutoConnection ) ;
}

void N::VirtualGui::addConnector (
        QString         name     ,
        const QObject * receiver ,
        const char    * signal   ,
        const char    * method   )
{
  addConnector ( name                 ,
                 Gui                  ,
                 signal               ,
                 receiver             ,
                 method               ,
                 Qt::AutoConnection ) ;
}

// Qt::AutoConnection
void N::VirtualGui::addConnector (
        QString      name        ,
        const char * signal      ,
        const char * method      )
{
  addConnector ( name                 ,
                 Gui                  ,
                 signal               ,
                 Gui                  ,
                 method               ,
                 Qt::AutoConnection ) ;
}

void N::VirtualGui::onlyConnector(QString name)
{
  if ( ! SignalConnectors .contains ( name ) ) return  ;
  SignalConnections * sc                               ;
  sc = (SignalConnections *) SignalConnectors [ name ] ;
  QObject::disconnect ( sc -> sender                   ,
                        sc -> signal                   ,
                        NULL                           ,
                        NULL                         ) ;
  QObject::connect    ( sc -> sender                   ,
                        sc -> signal                   ,
                        sc -> receiver                 ,
                        sc -> method                   ,
                        sc -> type                   ) ;
}

void N::VirtualGui::doConnector(QString name)
{
  if ( ! SignalConnectors .contains ( name ) ) return  ;
  SignalConnections * sc                               ;
  sc = (SignalConnections *) SignalConnectors [ name ] ;
  QObject::connect    ( sc -> sender                   ,
                        sc -> signal                   ,
                        sc -> receiver                 ,
                        sc -> method                   ,
                        sc -> type                   ) ;
}

void N::VirtualGui::undoConnector(QString name)
{
  if ( ! SignalConnectors .contains ( name ) ) return  ;
  SignalConnections * sc                               ;
  sc = (SignalConnections *) SignalConnectors [ name ] ;
  QObject::disconnect ( sc -> sender                   ,
                        sc -> signal                   ,
                        sc -> receiver                 ,
                        sc -> method                 ) ;
}

void N::VirtualGui::removeConnector(QString name)
{
  if ( ! SignalConnectors .contains ( name ) ) return  ;
  SignalConnections * sc                               ;
  sc = (SignalConnections *) SignalConnectors [ name ] ;
  SignalConnectors . remove ( name )                   ;
  if ( NotNull(sc) )                                   {
    delete sc                                          ;
  }                                                    ;
}

bool N::VirtualGui::CopyToFile (
       QString filename        ,
       QString ToFile          ,
       QString progressName    ,
       QString progressFormat  )
{
  bool      success = false                                                  ;
  QFileInfo SFI ( filename )                                                 ;
  QString   dFile      = QString("%1.part").arg(ToFile)                      ;
  int       dlen       = 1024 * 256                                          ;
  char      BUFF       [ 1024 * 256 ]                                        ;
  qint64    sourceSize = SFI . size ( )                                      ;
  qint64    destSize   = 0                                                   ;
  QFile     SF ( filename )                                                  ;
  QFile     TF ( dFile    )                                                  ;
  QDateTime StartT                                                           ;
  ////////////////////////////////////////////////////////////////////////////
  if ( SF . open ( QIODevice::ReadOnly ) )                                   {
    if ( TF . open ( QIODevice::WriteOnly ) )                                {
      bool      keepReading = true                                           ;
      int       pid                                                          ;
      qint64    value = 0                                                    ;
      bool      go    = true                                                 ;
      QDateTime T = nTimeNow                                                 ;
      pid   = plan -> Progress ( progressName , progressFormat )             ;
      plan -> Start ( pid , &value , &go )                                   ;
      qint64 ds = 0                                                          ;
      plan -> setRange ( pid , 0 , (int)(sourceSize/1024) )                  ;
      StartT = nTimeNow                                                      ;
      while ( keepReading && go )                                            {
        ds = SF . read ( BUFF , dlen )                                       ;
        if ( ds > 0 )                                                        {
          TF . write ( BUFF , ds )                                           ;
          destSize += ds                                                     ;
        } else keepReading = false                                           ;
        if ( sourceSize == destSize ) keepReading = false                    ;
        value = (int) ( destSize / 1024 )                                    ;
      }                                                                      ;
      if ( T.msecsTo(nTimeNow) < 1500 ) Time::skip(1500)                     ;
      plan -> Finish ( pid )                                                 ;
      TF . close ( )                                                         ;
    }                                                                        ;
    SF . close ( )                                                           ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  success = ( sourceSize == destSize )                                       ;
  if ( success ) success = QFile::rename(dFile,ToFile)                       ;
  return success                                                             ;
}
