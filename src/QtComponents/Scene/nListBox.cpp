#include <qtcomponents.h>

#ifdef QT_OPENGL_LIB

N::ListBox:: ListBox ( QObject * parent , Plan * p )
           : PickBox (           parent ,        p )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::ListBox:: ListBox ( QObject * parent , Plan * p , SceneDestructor * des )
           : PickBox (           parent ,        p ,                   des )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::ListBox::~ListBox (void)
{
}

void N::ListBox::Configure(void)
{
  QObject::setProperty ( "Type" , "ListBox" ) ;
  setVariable          ( "Type" , "ListBox" ) ;
}

void N::ListBox::addItem(SUID uuid,QString text)
{
  ControlPoint base ( 0 ,   0 ,  0 , 1 )                         ;
  ControlPoint gap  ( 0 , -48 ,  0 , 1 )                         ;
  SelectItem * si   = New ( )                                    ;
  int          cnt  = CurrentItems . count ( )                   ;
  ////////////////////////////////////////////////////////////////
  if ( Variables . contains ( "BasePoint" ) )                    {
    int basi = Value ( "BasePoint" ) . toInt ( )                 ;
    base = points [ basi ]                                       ;
  }                                                              ;
  ////////////////////////////////////////////////////////////////
  if ( Variables . contains ( "GapPoint" ) )                     {
    int gapi = Value ( "GapPoint" ) . toInt ( )                  ;
    gap  = points [ gapi ]                                       ;
  }                                                              ;
  ////////////////////////////////////////////////////////////////
  gap       *= cnt                                               ;
  gap       += base                                              ;
  gap . t    = 1                                                 ;
  gap . DOF  = ControlPoint::DofTranslate                        ;
  si        -> addDof      (  0 , gap                          ) ;
  si        -> setVariable ( "Shell" , "Never"                 ) ;
  si        -> Finish      (                                   ) ;
  si        -> Dual        (                                   ) ;
  si        -> addSequence (  9 , SceneObject::RenderChildren  ) ;
  ////////////////////////////////////////////////////////////////
  PickItem::addItem  ( si            )                           ;
  ////////////////////////////////////////////////////////////////
  TextObject * tox = new TextObject ( NULL , plan , destructor ) ;
  ControlPoint at     (  10 , 4 ,  4 , 1 )                       ;
  ControlPoint zp     (   0 , 0 ,  0 , 1 )                       ;
  ControlPoint scale  (   1 , 1 ,  1 , 1 )                       ;
  ControlPoint rotate (   0 , 0 ,  1 , 0 )                       ;
  ////////////////////////////////////////////////////////////////
  at      . DOF = ControlPoint::DofTranslate                     ;
  zp      . DOF = ControlPoint::DofTranslate                     ;
  scale   . DOF = ControlPoint::DofScale                         ;
  rotate  . DOF = ControlPoint::DofRotate                        ;
  ////////////////////////////////////////////////////////////////
  tox    -> gui     = gui                                        ;
  tox    -> minimum = ControlPoint (   0 ,  0 ,   0 )            ;
  tox    -> maximum = ControlPoint ( 760 , 32 ,  24 )            ;
  tox    -> DynamicFunctions = DynamicFunctions                  ;
  ////////////////////////////////////////////////////////////////
  tox    -> addDof       ( 0 , at                              ) ;
  tox    -> addDof       ( 1 , zp                              ) ;
  tox    -> addDof       ( 2 , scale                           ) ;
  tox    -> addDof       ( 3 , rotate                          ) ;
  ////////////////////////////////////////////////////////////////
  tox    -> setTextFlags ( Qt::AlignLeft | Qt::AlignVCenter    ) ;
  tox    -> setFont      ( plan->fonts[Fonts::Editor].toQFont()) ;
  tox    -> setPixelSize ( 24                                  ) ;
  tox    -> setTextRange ( uuid , QSize ( 512 , 32 )           ) ;
  tox    -> setTextColor ( QColor ( 0 , 0 , 0 , 255 )          ) ;
  tox    -> setText      ( text                                ) ;
  tox    -> setVariable  ( "UUID" , uuid                       ) ;
  ////////////////////////////////////////////////////////////////
  tox    -> Finish       (                             )         ;
  tox    -> Dual         (                             )         ;
  tox    -> addSequence  ( 7 , SceneObject::RenderUser )         ;
  ////////////////////////////////////////////////////////////////
  si     -> addItem      ( tox                         )         ;
  si     -> setVariable  ( "UUID" , uuid               )         ;
  si     -> setCheckable ( true                        )         ;
}

#endif
