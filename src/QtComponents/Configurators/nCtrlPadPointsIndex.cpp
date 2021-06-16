#include <qtcomponents.h>

N::CtrlPadPointsIndex:: CtrlPadPointsIndex ( QWidget * parent , Plan * p )
                      : TreeWidget         (           parent ,        p )
                      , identifier         ( 0                           )
                      , digits             ( 3                           )
                      , Points             ( NULL                        )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::CtrlPadPointsIndex::~CtrlPadPointsIndex(void)
{
}

void N::CtrlPadPointsIndex::closeEvent(QCloseEvent * event)
{
  emit Closed           ( identifier , this  ) ;
  QWidget :: closeEvent ( event              ) ;
}

void N::CtrlPadPointsIndex::Configure(void)
{
  PassDragDrop = false                             ;
  //////////////////////////////////////////////////
  NewTreeWidgetItem       ( head                 ) ;
  head -> setText         ( 0 , tr("Id")         ) ;
  head -> setText         ( 1 , tr("X" )         ) ;
  head -> setText         ( 2 , tr("Y" )         ) ;
  head -> setText         ( 3 , ""               ) ;
  setWindowTitle          ( tr("Points")         ) ;
  setFocusPolicy          ( Qt::WheelFocus       ) ;
  setDragDropMode         ( DragDrop             ) ;
  setAlternatingRowColors ( true                 ) ;
  setRootIsDecorated      ( false                ) ;
  setSelectionMode        ( ExtendedSelection    ) ;
  setColumnCount          ( 4                    ) ;
  setAlignment            ( 0 , Qt::AlignRight     |
                                Qt::AlignVCenter ) ;
  setAlignment            ( 1 , Qt::AlignRight     |
                                Qt::AlignVCenter ) ;
  setAlignment            ( 2 , Qt::AlignRight     |
                                Qt::AlignVCenter ) ;
  assignHeaderItems       ( head                 ) ;
  MountClicked            ( 1                    ) ;
  MountClicked            ( 2                    ) ;
  plan->setFont           ( this                 ) ;
  //////////////////////////////////////////////////
  if (!plan->Booleans["Desktop"])                  {
    allowGesture = true                            ;
    grabGesture ( Qt::TapAndHoldGesture )          ;
    grabGesture ( Qt::PanGesture        )          ;
  }                                                ;
}

bool N::CtrlPadPointsIndex::FocusIn(void)
{
  DisableAllActions (                           ) ;
  AssignAction      ( Label   , windowTitle ( ) ) ;
  LinkAction        ( Refresh , startup     ( ) ) ;
  LinkAction        ( Insert  , New         ( ) ) ;
  LinkAction        ( Delete  , Delete      ( ) ) ;
  LinkAction        ( Paste   , Paste       ( ) ) ;
  LinkAction        ( Copy    , Copy        ( ) ) ;
  LinkAction        ( Export  , Export      ( ) ) ;
  return true                                     ;
}

void N::CtrlPadPointsIndex::setDigits(int D)
{
  digits = D ;
}

QString N::CtrlPadPointsIndex::DoubleString(double v)
{
  QString R                    ;
  if (v<0)                     {
    R.prepend("-")             ;
    v = -v                     ;
  }                            ;
  int     V = (int)v           ;
  QString S                    ;
  S = QString::number(V)       ;
  R.append(S)                  ;
  if ( digits > 0 )            {
    R.append(".")              ;
    v -= V                     ;
    for (int i=0;i<digits;i++) {
      v *= 10                  ;
      V  = (int)v              ;
      v -= V                   ;
      S = QString::number(V)   ;
      R.append(S)              ;
    }                          ;
  }                            ;
  return  R                    ;
}

void N::CtrlPadPointsIndex::assignItem(QTreeWidgetItem * item,int id,QPointF p)
{
  item -> setText ( 0 , QString::number ( id   ) ) ;
  item -> setText ( 1 , DoubleString    ( p.x()) ) ;
  item -> setText ( 2 , DoubleString    ( p.y()) ) ;
  setAlignments   ( item                         ) ;
}

bool N::CtrlPadPointsIndex::startup(void)
{
  clear ( )                                     ;
  if ( IsNull(Points) ) return false            ;
  CUIDs I = Points->keys()                      ;
  int   i                                       ;
  if (I.count()>1)                              {
    qSort             ( I.begin() , I.end()   ) ;
  }                                             ;
  foreach             ( i , I                 ) {
    NewTreeWidgetItem ( IT                    ) ;
    assignItem        ( IT , i , (*Points)[i] ) ;
    addTopLevelItem   ( IT                    ) ;
  }                                             ;
  emit AutoFit ( )                              ;
  return true                                   ;
}

QMap<int,QPointF> & N::CtrlPadPointsIndex::Create(void)
{
  Points = new QMap<int,QPointF>() ;
  return ( *Points )               ;
}

QMap<int,QPointF> & N::CtrlPadPointsIndex::Value(void)
{
  return ( *Points ) ;
}

QMap<int,QPointF> & N::CtrlPadPointsIndex::setPoints(QMap<int,QPointF> & points)
{
  Points = &points   ;
  return ( *Points ) ;
}

void N::CtrlPadPointsIndex::setIdentifier(int id)
{
  identifier = id ;
}

void N::CtrlPadPointsIndex::singleClicked(QTreeWidgetItem * item,int column)
{ Q_UNUSED ( item   ) ;
  Q_UNUSED ( column ) ;
  Alert    ( Click  ) ;
}

void N::CtrlPadPointsIndex::doubleClicked(QTreeWidgetItem * item,int column)
{
  QLineEdit * le = NULL                  ;
  switch (column)                        {
    case 0                               :
    case 1                               :
    case 2                               :
      le = setLineEdit                   (
             item                        ,
             column                      ,
             SIGNAL(returnPressed  ())   ,
             SLOT  (editingFinished()) ) ;
      le -> setFocus(Qt::TabFocusReason) ;
    break                                ;
  }                                      ;
}

void N::CtrlPadPointsIndex::editingFinished(void)
{
  QLineEdit * name = Casting(QLineEdit,ItemWidget)  ;
  bool        redo = false                          ;
  bool        look = false                          ;
  if (NotNull(name))                                {
    QString v = name->text()                        ;
    if (v.length()>0)                               {
      int     id = ItemEditing->text(0).toInt()     ;
      int     vt                                    ;
      double  vp                                    ;
      QPointF pt                                    ;
      switch ( ItemColumn )                         {
        case 0                                      :
          vt = v . toInt    ( )                     ;
          pt = (*Points)[id]                        ;
          Points->take(id)                          ;
          (*Points)[vt] = pt                        ;
          redo = true                               ;
          look = true                               ;
        break                                       ;
        case 1                                      :
          vp = v . toDouble ( )                     ;
          (*Points)[id].setX(vp)                    ;
          ItemEditing -> setText                    (
            1                                       ,
            DoubleString ( (*Points)[id].x())     ) ;
          look = true                               ;
        break                                       ;
        case 2                                      :
          vp = v . toDouble ( )                     ;
          (*Points)[id].setY(vp)                    ;
          ItemEditing -> setText                    (
            2                                       ,
            DoubleString ( (*Points)[id].y())     ) ;
          look = true                               ;
        break                                       ;
      }                                             ;
    }                                               ;
  }                                                 ;
  removeOldItem ( 0 , false )                       ;
  if (redo) startup ( )                             ;
  if (look) emit Changed ( identifier , this )      ;
}

void N::CtrlPadPointsIndex::New(void)
{
  CUIDs K = Points->keys()                    ;
  int   L = 0                                 ;
  /////////////////////////////////////////////
  if (K.count()>0)                            {
    qSort(K.begin(),K.end())                  ;
    L = K.last()                              ;
  }                                           ;
  L++                                         ;
  /////////////////////////////////////////////
  QPointF E(0,0)                              ;
  (*Points)[L] = E                            ;
  NewTreeWidgetItem ( IT                    ) ;
  assignItem        ( IT , L , (*Points)[L] ) ;
  addTopLevelItem   ( IT                    ) ;
  scrollToItem      ( IT                    ) ;
  /////////////////////////////////////////////
  emit Changed      ( identifier , this     ) ;
  Alert             ( Click                 ) ;
}

void N::CtrlPadPointsIndex::Delete(void)
{
  QTreeWidgetItem * it = currentItem ( )      ;
  if (IsNull(it)) return                      ;
  /////////////////////////////////////////////
  int id = it->text(0).toInt()                ;
  if (Points->contains(id))                   {
    Points -> take ( id )                     ;
  }                                           ;
  takeItem          ( it                    ) ;
  /////////////////////////////////////////////
  emit Changed      ( identifier , this     ) ;
  Alert             ( Click                 ) ;
}

void N::CtrlPadPointsIndex::Paste(void)
{
  QString text = qApp->clipboard()->text() ;
  if (text.length()<=0) return             ;
  bool okay = false                        ;
  switch ( currentColumn ( ) )             {
    case 0                                 :
      text . toInt    ( &okay )            ;
    break                                  ;
    case 1                                 :
    case 2                                 :
      text . toDouble ( &okay )            ;
    break                                  ;
  }                                        ;
  if ( !okay ) return                      ;
  Paste ( text )                           ;
}

void N::CtrlPadPointsIndex::Paste(QString text)
{
  QTreeWidgetItem * it = currentItem ( )       ;
  if (IsNull(it)) return                       ;
  bool    redo = false                         ;
  bool    look = false                         ;
  QString v    = text                          ;
  if (v.length()>0)                            {
    int     id = it->text(0).toInt()           ;
    int     vt                                 ;
    double  vp                                 ;
    QPointF pt                                 ;
    switch ( currentColumn() )                 {
      case 0                                   :
        vt = v . toInt    ( )                  ;
        pt = (*Points)[id]                     ;
        Points->take(id)                       ;
        (*Points)[vt] = pt                     ;
        redo = true                            ;
        look = true                            ;
      break                                    ;
      case 1                                   :
        vp = v . toDouble ( )                  ;
        (*Points)[id].setX(vp)                 ;
        it -> setText                          (
          1                                    ,
          DoubleString ( (*Points)[id].x())  ) ;
        look = true                            ;
      break                                    ;
      case 2                                   :
        vp = v . toDouble ( )                  ;
        (*Points)[id].setY(vp)                 ;
        it -> setText                          (
          2                                    ,
          DoubleString ( (*Points)[id].y())  ) ;
        look = true                            ;
      break                                    ;
    }                                          ;
  }                                            ;
  if (redo) startup ( )                        ;
  if (look) emit Changed ( identifier , this ) ;
  Alert                  ( Click             ) ;
}

void N::CtrlPadPointsIndex::Copy(void)
{
  QTreeWidgetItem * it = currentItem ( ) ;
  if (IsNull(it)) return                 ;
  QString v = it->text(currentColumn())  ;
  qApp->clipboard()->setText(v)          ;
}

bool N::CtrlPadPointsIndex::toPlainText(QByteArray & text)
{
  QString T                               ;
  for (int i=0;i<topLevelItemCount();i++) {
    QTreeWidgetItem * it                  ;
    QStringList       L                   ;
    it = topLevelItem ( i )               ;
    L  . clear        (   )               ;
    for (int j=0;j<(columnCount()-1);j++) {
      L << it->text(j)                    ;
    }                                     ;
    T . append ( L . join ( "\t" ) )      ;
    T . append ( "\n"              )      ;
  }                                       ;
  text = T.toUtf8()                       ;
  return true                             ;
}

bool N::CtrlPadPointsIndex::toHtml(QByteArray & text)
{
  setColumnCount ( 3 )                       ;
  QString HTML = TreeWidget::toHtml ( true ) ;
  HTML.prepend("<table>\n")                  ;
  HTML.append("</table>\n")                  ;
  setColumnCount ( 4 )                       ;
  emit AutoFit ( )                           ;
  text = HTML . toUtf8 ( )                   ;
  return true                                ;
}

bool N::CtrlPadPointsIndex::toTeX(QByteArray & text)
{
  setColumnCount ( 3 )                     ;
  QString T                                ;
  QString TeX = TreeWidget::toTeX ( true ) ;
  T . append ( "\\begin{table}\n" )        ;
  T . append ( TeX                )        ;
  T . append ( "\\end{table}\n"   )        ;
  setColumnCount ( 4 )                     ;
  emit AutoFit ( )                         ;
  text = T.toUtf8()                        ;
  return true                              ;
}

void N::CtrlPadPointsIndex::Export(void)
{
  QString filename = QFileDialog :: getSaveFileName            (
                       this                                    ,
                       tr("Export points list")                ,
                       plan->Temporary("")                     ,
                       tr("Plain text (*.txt);;"
                          "TeX (*.tex);;"
                          "HTML (*.html *.htm)"            ) ) ;
  if (filename.length()<=0) return                             ;
  QFileInfo F ( filename )                                     ;
  QString   S = F.suffix()                                     ;
  S = S.toLower()                                              ;
  QByteArray Text                                              ;
  if ( "htm"  == S ) toHtml      ( Text )                 ; else
  if ( "html" == S ) toHtml      ( Text )                 ; else
  if ( "tex"  == S ) toTeX       ( Text )                 ; else
  if ( "txt"  == S ) toPlainText ( Text )        ; else return ;
  File :: toFile ( filename , Text )                           ;
}

bool N::CtrlPadPointsIndex::Menu(QPoint pos)
{ Q_UNUSED       ( pos  )           ;
  MenuManager mm ( this )           ;
  QAction  *  aa                    ;
  ///////////////////////////////////
  mm . add ( 101 , tr("Refresh") )  ;
  mm . add ( 102 , tr("Insert" ) )  ;
  mm . add ( 103 , tr("Delete" ) )  ;
  mm . addSeparator (            )  ;
  mm . add ( 104 , tr("Paste"  ) )  ;
  mm . add ( 105 , tr("Copy"   ) )  ;
  mm . addSeparator (            )  ;
  mm . add ( 106 , tr("Export" ) )  ;
  ///////////////////////////////////
  mm . setFont ( plan )             ;
  aa = mm.exec()                    ;
  if (IsNull(aa)) return true       ;
  ///////////////////////////////////
  switch (mm[aa])                   {
    nFastCast ( 101 , startup ( ) ) ;
    nFastCast ( 102 , New     ( ) ) ;
    nFastCast ( 103 , Delete  ( ) ) ;
    nFastCast ( 104 , Paste   ( ) ) ;
    nFastCast ( 105 , Copy    ( ) ) ;
    nFastCast ( 106 , Export  ( ) ) ;
  }                                 ;
  ///////////////////////////////////
  return true                       ;
}
