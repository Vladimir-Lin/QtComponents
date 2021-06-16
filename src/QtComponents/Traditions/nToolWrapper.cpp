#include <qtcomponents.h>

N::ToolWrapper :: ToolWrapper ( QWidget * parent , Plan * p  , Qt::WindowFlags f )
                : QWidget     (           parent ,                             f )
                , VirtualGui  (           this   ,        p                      )
                , Thread      (           0      , false                         )
                , LocalWidget ( NULL                                             )
                , Abstract    ( NULL                                             )
{
  WidgetClass                                         ;
  setAttribute          ( Qt::WA_InputMethodEnabled ) ;
  Commando -> setParent ( this                      ) ;
  /////////////////////////////////////////////////////
  if ( NotNull ( plan ) )                             {
    Data . Controller = & ( plan -> canContinue )     ;
  }                                                   ;
}

N::ToolWrapper ::~ToolWrapper(void)
{
}

QSize N::ToolWrapper::sizeHint(void) const
{
  return SizeSuggestion ( QSize ( 240 , 120 ) ) ;
}

void N::ToolWrapper::closeEvent(QCloseEvent * e)
{
  emit Leave          ( this ) ;
  QWidget::closeEvent ( e    ) ;
}

void N::ToolWrapper::resizeEvent(QResizeEvent * e)
{
  QWidget::resizeEvent ( e ) ;
  Relocation           (   ) ;
}

void N::ToolWrapper::showEvent(QShowEvent * e)
{
  QWidget::showEvent ( e ) ;
  Relocation         (   ) ;
}

void N::ToolWrapper::focusInEvent(QFocusEvent * e)
{
  emit GainFocus         ( this ) ;
  QWidget::focusInEvent  ( e    ) ;
}

void N::ToolWrapper::focusOutEvent(QFocusEvent * e)
{
  emit LostFocus         ( this ) ;
  QWidget::focusOutEvent ( e    ) ;
}

bool N::ToolWrapper::Relocation(void)
{
  if ( IsNull ( LocalWidget ) ) return false ;
  QRect G ( 0 , 0 , width ( ) , height ( ) ) ;
  LocalWidget -> setGeometry ( G )           ;
  return true                                ;
}

void N::ToolWrapper::setWidget(QWidget * widget)
{
  QWidget * w = LocalWidget         ;
  LocalWidget  = widget             ;
  LocalWidget -> setParent ( this ) ;
  if ( NotNull ( w ) )              {
    w -> deleteLater       (      ) ;
  }                                 ;
  Relocation               (      ) ;
}

void N::ToolWrapper::setAbstract(AbstractGui * abstract)
{
  Abstract = abstract                ;
  if ( NULL == Abstract    ) return  ;
  if ( NULL == LocalWidget ) return  ;
  Abstract -> setGui ( LocalWidget ) ;
}

void N::ToolWrapper::setDisappear(int msec)
{
  QTimer::singleShot ( msec , this , SLOT ( DelayedClose ( ) ) ) ;
}

void N::ToolWrapper::DelayedClose(void)
{
  emit Leave  ( this ) ;
  deleteLater (      ) ;
}
