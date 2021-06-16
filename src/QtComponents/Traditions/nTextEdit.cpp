#include <qtcomponents.h>

N::TextEdit:: TextEdit   ( QWidget * parent,Plan * p     )
            : QTextEdit  (           parent              )
            , VirtualGui (           this  ,       p     )
            , Thread     (           0     ,       false )
{
  WidgetClass                                   ;
  addIntoWidget ( parent , this )               ;
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

N::TextEdit::~TextEdit (void)
{
}

void N::TextEdit::paintEvent(QPaintEvent * event)
{
  nIsolatePainter(QTextEdit) ;
}

void N::TextEdit::focusInEvent(QFocusEvent * event)
{
  if (!focusIn (event)) QTextEdit::focusInEvent (event) ;
}

void N::TextEdit::focusOutEvent(QFocusEvent * event)
{
  if (!focusOut(event)) QTextEdit::focusOutEvent(event) ;
}

void N::TextEdit::resizeEvent(QResizeEvent * event)
{
  if (Relocation()) event->accept();
  else QTextEdit::resizeEvent(event);
}

void N::TextEdit::contextMenuEvent(QContextMenuEvent * event)
{
  QTextEdit::contextMenuEvent(event);
}

void N::TextEdit::closeEvent(QCloseEvent * event)
{
  if (Shutdown()) event->accept();
  else QTextEdit::closeEvent(event);
}

bool N::TextEdit::Shutdown(void)
{
  emit Leave(this) ;
  return true ;
}

bool N::TextEdit::Relocation(void)
{
  return false ;
}

void N::TextEdit::setFont(void)
{
  changeFont ( ) ;
}

void N::TextEdit::DropCommands(void)
{
  LaunchCommands ( ) ;
}
