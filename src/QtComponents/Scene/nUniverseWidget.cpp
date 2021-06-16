#include <qtcomponents.h>

typedef struct               {
  N::MenuManager    * menu   ;
  QAction           * action ;
  N::UniverseWidget * editor ;
  N::UniverseWidget * extra  ;
} PrivateMenuBinder          ;

N::UniverseWidget:: UniverseWidget ( QObject * parent , Plan * p )
                  : QObject        (           parent            )
                  , QScriptable    (                             )
                  , Universe       (                             )
                  , Thread         (                0 , false    )
                  , plan           (                           p )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::UniverseWidget:: UniverseWidget ( QObject * parent , Plan * p ,SceneDestructor * des )
                  : QObject        (           parent                                   )
                  , QScriptable    (                                                    )
                  , Universe       (                                                    )
                  , Thread         (                0 , false                           )
                  , plan           (                           p                        )
{
  WidgetClass        ;
  destructor = des   ;
  JoinDestructor ( ) ;
  Configure      ( ) ;
}

N::UniverseWidget::~UniverseWidget (void)
{
}

void N::UniverseWidget::Configure (void)
{
  setVariable ( "AllowDrag"  , true )               ;
  setVariable ( "AcceptDrop" , true )               ;
  ///////////////////////////////////////////////////
  nConnect ( this , SIGNAL ( assignCursor (int) )   ,
             this , SLOT   ( localCursor  (int) ) ) ;
}

QScriptValue N::UniverseWidget::UniverseAttachment(QScriptContext * context,QScriptEngine * engine)
{
  N::UniverseWidget * nuw = new N::UniverseWidget ( engine , (Plan *) qPlan ) ;
  return engine -> newQObject                     ( nuw                     ) ;
}

int N::UniverseWidget::MenuBindings(void * data,void * dispatcher,QVariants & v)
{
  PrivateMenuBinder * pmb = (PrivateMenuBinder *) dispatcher ;
  return pmb -> editor -> MenuBinder ( * ( pmb -> menu )     ,
                                           pmb -> action     ,
                                           v                 ,
                                           dispatcher      ) ;
}

int N::UniverseWidget::MenuBinder  (
      MenuManager & mm         ,
      QAction     * action     ,
      QVariants   & v          ,
      void        * dispatcher )
{
  bool completed = v [ 0 ] . toBool ( )    ;
  if ( ! completed )                       {
    CallToMenu ( mm , action , false )     ;
    return 1                               ;
  }                                        ;
  return CallToMenu ( mm , action , true ) ;
}

void N::UniverseWidget::BindingMenu(SceneObject * s)
{
  PrivateMenuBinder * pmb = new PrivateMenuBinder ( )                        ;
  ::memset(pmb,0,sizeof(PrivateMenuBinder))                                  ;
  pmb -> editor = this                                                       ;
  s   -> userobjs         [ "MenuBinder" ] = pmb                             ;
  s   -> DynamicFunctions [ "MenuBinder" ] = N::UniverseWidget::MenuBindings ;
}

int N::UniverseWidget::CallToMenu (
      MenuManager & mm            ,
      QAction     * aa            ,
      bool          executed      )
{
  if ( ! userobjs . contains ( "MenuBinder" ) ) return 0      ;
  void              * Handler = userobjs [ "MenuBinder" ]     ;
  PrivateMenuBinder * pmb     = (PrivateMenuBinder *) Handler ;
  QVariants V                                                 ;
  V << executed                                               ;
  pmb -> menu   = &mm                                         ;
  pmb -> action = aa                                          ;
  pmb -> extra  = this                                        ;
  return CallDynamic ( "MenuBinder" , this , Handler , V )    ;
}

int N::UniverseWidget::CallTapping(QString tapping,QVariants & args)
{
  if ( ! userobjs . contains ( tapping ) ) return 0 ;
  return CallDynamic ( tapping                      ,
                        this                        ,
                        userobjs [ tapping ]        ,
                        args                      ) ;
}

int N::UniverseWidget::CallBinding(QVariants & args)
{
  return CallTapping ( "BindFunctions" , args ) ;
}

void N::UniverseWidget::localCursor(int cursorType)
{
  setCursor( (Qt::CursorShape) cursorType ) ;
}
