#include <qtcomponents.h>

N::EditToolBar:: EditToolBar ( QWidget * parent , Plan * p )
               : ToolBar     (           parent ,        p )
               , action      ( NULL                        )
               , line        ( NULL                        )
               , combo       ( NULL                        )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::EditToolBar::~EditToolBar (void)
{
}

void N::EditToolBar::Configure(void)
{
  QString title = tr       ( "Edit Tool Bar"                ) ;
  setAttribute             ( Qt::WA_InputMethodEnabled      ) ;
  setWindowTitle           ( title                          ) ;
  setToolTip               ( title                          ) ;
  setAllowedAreas          ( Qt::TopToolBarArea               |
                             Qt::BottomToolBarArea          ) ;
  action = addAction       ( QIcon(":/images/yes.png") , "" ) ;
  line   = new LineEdit    ( NULL    , plan                 ) ;
  combo  = new ComboBox    ( NULL    , plan                 ) ;
  combo -> setInsertPolicy ( QComboBox::NoInsert            ) ;
  combo -> setEditable     ( true                           ) ;
  combo -> setLineEdit     ( line                           ) ;
  widget = addWidget       ( combo                          ) ;
  plan  -> setFont         ( this                           ) ;
  plan  -> addWidget       ( AttacheId + 1 , this           ) ;
  plan  -> addWidget       ( AttacheId + 2 , line           ) ;
  plan  -> addWidget       ( AttacheId + 3 , combo          ) ;
  plan  -> addAction       ( AttacheId + 4 , action         ) ;
  plan  -> addAction       ( AttacheId + 5 , widget         ) ;
}

bool N::EditToolBar::Relocation(void)
{
  if ( NotNull ( combo ) )           {
    QRect g = combo -> geometry ( )  ;
    QSize s                          ;
    g . setTop    ( 3              ) ;
    g . setBottom ( height ( ) - 3 ) ;
    g . setRight  ( width  ( ) - 2 ) ;
    combo -> setGeometry ( g )       ;
    s . setWidth  ( 320            ) ;
    s . setHeight ( 24             ) ;
    combo -> setMinimumSize ( s    ) ;
  }                                  ;
  return false                       ;
}

N::ComboBox * N::EditToolBar::Listing(void)
{
  return combo ;
}

void N::EditToolBar::setIcon(QIcon icon)
{
  if ( IsNull ( action ) ) return ;
  action -> setIcon ( icon )      ;
}

void N::EditToolBar::LinkToLine(QObject * w,const char * Receiver,const char * Member)
{
  if ( IsNull ( line ) ) return                                                ;
  QObject::disconnect ( line , SIGNAL(cursorPositionChanged(int,int)) , NULL , NULL ) ;
  QObject::disconnect ( line , SIGNAL(editingFinished())              , NULL , NULL ) ;
  QObject::disconnect ( line , SIGNAL(returnPressed())                , NULL , NULL ) ;
  QObject::disconnect ( line , SIGNAL(selectionChanged())             , NULL , NULL ) ;
  QObject::disconnect ( line , SIGNAL(textChanged(QString))           , NULL , NULL ) ;
  QObject::disconnect ( line , SIGNAL(textEdited(QString))            , NULL , NULL ) ;
  QObject::disconnect ( line , Member                                 , NULL , NULL ) ;
  QObject::connect    ( line , Member , w , Receiver                                ) ;
}

void N::EditToolBar::ClearCombo(void)
{
  combo -> blockSignals ( true  ) ;
  combo -> clear        (       ) ;
  combo -> blockSignals ( false ) ;
}

void N::EditToolBar::LinkToList(QObject * w,const char * Receiver,const char * Member)
{
  if ( IsNull ( combo ) ) return                                                     ;
  QObject::disconnect ( combo , SIGNAL(activated(int))               , NULL , NULL ) ;
  QObject::disconnect ( combo , SIGNAL(activated(QString))           , NULL , NULL ) ;
  QObject::disconnect ( combo , SIGNAL(currentIndexChanged(int))     , NULL , NULL ) ;
  QObject::disconnect ( combo , SIGNAL(currentIndexChanged(QString)) , NULL , NULL ) ;
  QObject::disconnect ( combo , SIGNAL(currentTextChanged(QString))  , NULL , NULL ) ;
  QObject::disconnect ( combo , SIGNAL(editTextChanged(QString))     , NULL , NULL ) ;
  QObject::disconnect ( combo , SIGNAL(highlighted(int))             , NULL , NULL ) ;
  QObject::disconnect ( combo , SIGNAL(highlighted(QString))         , NULL , NULL ) ;
  QObject::disconnect ( combo , Member                               , NULL , NULL ) ;
  QObject::connect    ( combo , Member , w , Receiver                              ) ;
}
