#include <qtcomponents.h>

N::ClipboardView:: ClipboardView ( QWidget * parent , Plan * p )
                 : TextBrowser   (           parent ,        p )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::ClipboardView::~ClipboardView(void)
{
}

QSize N::ClipboardView::sizeHint(void) const
{
  if ( plan  -> Booleans [ "Desktop" ] ) {
    return QSize ( 640 ,  480 )          ;
  } else
  if ( plan  -> Booleans [ "Pad"     ] ) {
    return QSize ( 640 ,  480 )          ;
  } else
  if ( plan  -> Booleans [ "Phone"   ] ) {
    return QSize (  320 ,  480 )         ;
  }                                      ;
  return QSize ( 640 , 480 ) ;
}

void N::ClipboardView::contextMenuEvent(QContextMenuEvent * e)
{
  if ( Menu ( e -> pos ( ) ) ) e -> accept ( ) ; else
  QTextBrowser :: contextMenuEvent ( e )            ;
}

void N::ClipboardView::Configure(void)
{
  setWindowTitle ( tr("Clipboard contents") ) ;
}

bool N::ClipboardView::FocusIn(void)
{
  DisableAllActions (                           ) ;
  AssignAction      ( Label   , windowTitle ( ) ) ;
  LinkAction        ( Copy    , copy        ( ) ) ;
  LinkAction        ( Refresh , startup     ( ) ) ;
  return true                                     ;
}

bool N::ClipboardView::startup (void)
{
  QClipboard * clip = qApp->clipboard()                                      ;
  clear        ( )                                                           ;
  clearHistory ( )                                                           ;
  if ( IsNull(clip) ) return false                                           ;
  ////////////////////////////////////////////////////////////////////////////
  const QMimeData * mime                                                     ;
  QPixmap           pix = clip -> pixmap ( )                                 ;
  QString           txt = clip -> text   ( )                                 ;
  mime = clip -> mimeData ( )                                                ;
  if ( clip->ownsClipboard () )                                              {
    append ( tr("Application owns clipboard.")                             ) ;
  }                                                                          ;
  if ( clip->ownsFindBuffer() )                                              {
    append ( tr("Application has 'find buffer' functionality.")            ) ;
  }                                                                          ;
  if ( clip->ownsSelection () )                                              {
    append ( tr("Application has selections.")                             ) ;
  }                                                                          ;
  if ( txt . length ( ) > 0 )                                                {
    append ( tr("Clipboard text : ")                                       ) ;
    append ( "========================================================="   ) ;
    append ( txt                                                           ) ;
    append ( "========================================================="   ) ;
  }                                                                          ;
  if ( ! pix . isNull ( ) )                                                  {
    QImage image = pix.toImage()                                             ;
    QUrl Uri(QString("file://%1.png").arg(QtUUID::createUuidString()))         ;
    document() -> addResource                                                (
                      QTextDocument::ImageResource                           ,
                      Uri                                                    ,
                      QVariant ( image )                                   ) ;
    append ( tr("Pixmap : ")                                               ) ;
    append ( "========================================================="   ) ;
    append ( QString("<img src=\"%1\">").arg(Uri.toString())               ) ;
    append ( "========================================================="   ) ;
  }                                                                          ;
  if ( IsNull(mime) ) return true                                            ;
  QStringList formats = mime->formats()                                      ;
  QString     format                                                         ;
  append ( tr("Application has mime data.")                                ) ;
  if ( mime->hasText () )                                                    {
    append ( tr("Mime text : ")                                            ) ;
    append ( "========================================================="   ) ;
    append ( mime -> text ( )                                              ) ;
    append ( "========================================================="   ) ;
  }                                                                          ;
  if ( mime->hasHtml () )                                                    {
    append ( tr("Mime HTML : ")                                            ) ;
    append ( "========================================================="   ) ;
    append ( mime -> html ( )                                              ) ;
    append ( "========================================================="   ) ;
  }                                                                          ;
  if ( mime->hasUrls () )                                                    {
    QList<QUrl> urls = mime->urls()                                          ;
    QUrl        url                                                          ;
    append ( tr("Mime URLs : ")                                            ) ;
    append ( "<hr>"                                                        ) ;
    append ( "========================================================="   ) ;
    foreach (url,urls) append ( url . toString ( ) )                         ;
    append ( "========================================================="   ) ;
  }                                                                          ;
  if ( mime->hasColor() )                                                    {
    QColor color = qvariant_cast<QColor>(mime->colorData())                  ;
    append ( tr("Mime Color : ")                                           ) ;
    append ( "========================================================="   ) ;
    append ( tr("[R,G,B,A] = [%1,%2,%3,%4]"                                  )
             . arg ( color . red   ( )                                       )
             . arg ( color . green ( )                                       )
             . arg ( color . blue  ( )                                       )
             . arg ( color . alpha ( )                                   ) ) ;
    append ( "========================================================="   ) ;
  }                                                                          ;
  if ( mime->hasImage() )                                                    {
    QImage image = qvariant_cast<QImage>(mime->imageData())                  ;
    QUrl Uri(QString("file://%1.png").arg(QtUUID::createUuidString()))         ;
    document() -> addResource                                                (
                      QTextDocument::ImageResource                           ,
                      Uri                                                    ,
                      QVariant ( image )                                   ) ;
    append ( tr("Mime Image : ")                                           ) ;
    append ( "========================================================="   ) ;
    append ( QString("<img src=\"%1\">").arg(Uri.toString())               ) ;
    append ( "========================================================="   ) ;
  }                                                                          ;
  foreach ( format , formats ) if ( mime->hasFormat(format) )                {
    QByteArray D = mime -> data ( format )                                   ;
    if ( D . size ( ) > 0 )                                                  {
      append ( tr("Data : %1") . arg ( format       )                      ) ;
      append ( tr("Size : %1") . arg ( D . size ( ) )                      ) ;
      append ( "=========================================================" ) ;
      append ( QString::fromUtf8(D.toHex()).toUpper()                      ) ;
      append ( "=========================================================" ) ;
    }                                                                        ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  return true                                                                ;
}

bool N::ClipboardView::Menu(QPoint)
{
  nScopedMenu ( mm , this )                         ;
  ///////////////////////////////////////////////////
  QAction * aa = NULL                               ;
  mm . add ( 101 , tr("Refresh"        ) )          ;
  mm . add ( 102 , tr("Copy"           ) )          ;
  mm . add ( 103 , tr("Clear clipboard") )          ;
  mm . setFont ( plan )                             ;
  aa = mm . exec ( )                                ;
  if ( ! mm . contains ( aa ) ) return true         ;
  ///////////////////////////////////////////////////
  int Id = mm [ aa ]                                ;
  switch (Id)                                       {
    case 101                                        :
      startup ( )                                   ;
    return true                                     ;
    case 102                                        :
      copy    ( )                                   ;
    return true                                     ;
    case 103                                        :
      if ( NotNull(qApp->clipboard()) )             {
        qApp->clipboard()->clear()                  ;
      }                                             ;
    return true                                     ;
    default                                         :
    return true                                     ;
  }                                                 ;
  return true                                       ;
}
