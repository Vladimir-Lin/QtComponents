#include <qtcomponents.h>

N::TextBrowser:: TextBrowser  ( QWidget * parent,Plan * p     )
               : QTextBrowser (           parent              )
               , VirtualGui   (           this  ,       p     )
               , Thread       (           0     ,       false )
{
  WidgetClass                                   ;
  addIntoWidget ( parent , this               ) ;
  setAttribute  ( Qt::WA_InputMethodEnabled   ) ;
  addConnector  ( "Commando"                    ,
                  Commando                      ,
                  SIGNAL ( timeout      ( ) )   ,
                  this                          ,
                  SLOT   ( DropCommands ( ) ) ) ;
  onlyConnector ( "Commando"                  ) ;
  ///////////////////////////////////////////////
  if ( NotNull ( plan ) )                       {
    Data . Controller = & ( plan->canContinue ) ;
  }                                             ;
}

N::TextBrowser::~TextBrowser (void)
{
}

void N::TextBrowser::paintEvent(QPaintEvent * event)
{
  nIsolatePainter(QTextBrowser) ;
}

void N::TextBrowser::focusInEvent(QFocusEvent * event)
{
  if (!focusIn (event)) QTextBrowser::focusInEvent (event) ;
}

void N::TextBrowser::focusOutEvent(QFocusEvent * event)
{
  if (!focusOut(event)) QTextBrowser::focusOutEvent(event) ;
}

void N::TextBrowser::resizeEvent(QResizeEvent * event)
{
  if (Relocation()) event->accept();
  else QTextBrowser::resizeEvent(event);
}

void N::TextBrowser::contextMenuEvent(QContextMenuEvent * event)
{
  QTextBrowser::contextMenuEvent(event);
}

void N::TextBrowser::dragEnterEvent(QDragEnterEvent * event)
{
  if (dragEnter(event)) event->acceptProposedAction() ;
  else QTextBrowser::dragEnterEvent(event);
}

void N::TextBrowser::dragLeaveEvent(QDragLeaveEvent * event)
{
  if (removeDrop()) event->accept() ;
  else QTextBrowser::dragLeaveEvent(event);
}

void N::TextBrowser::dragMoveEvent(QDragMoveEvent * event)
{
  if (dragMove(event)) event->acceptProposedAction() ;
  else QTextBrowser::dragMoveEvent(event);
}

void N::TextBrowser::dropEvent(QDropEvent * event)
{
  if (drop(event)) event->acceptProposedAction() ;
  else QTextBrowser::dropEvent(event);
}

void N::TextBrowser::closeEvent(QCloseEvent * event)
{
  if (Shutdown()) event->accept();
  else QTextBrowser::closeEvent(event);
}

bool N::TextBrowser::Shutdown(void)
{
  emit Leave(this) ;
  return true ;
}

bool N::TextBrowser::Relocation(void)
{
  return false ;
}

void N::TextBrowser::setFont(void)
{
  changeFont ( ) ;
}

void N::TextBrowser::DropCommands(void)
{
  LaunchCommands ( ) ;
}
