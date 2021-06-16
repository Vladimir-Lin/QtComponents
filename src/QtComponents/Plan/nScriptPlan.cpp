#include <qtcomponents.h>

typedef struct       {
  N::ScriptPlan * pp ;
} ScriptPlanPacket   ;

N::ScriptPlan:: ScriptPlan  ( QObject * parent )
              : QObject     (           parent )
              , QScriptable (                  )
              , Plan        (                  )
{
  ScriptPlanPacket * pp = new ScriptPlanPacket ( ) ;
  pp -> pp  = this                                 ;
  Variables [ "ScriptPlan" ] = VoidVariant ( pp )  ;
  //////////////////////////////////////////////////
  ProgressReporter::setVirtual ( this )            ;
}

N::ScriptPlan::~ScriptPlan(void)
{
}

void N::ScriptPlan::setObject(QObject * parent)
{
  QObject::setParent ( parent                           ) ;
  QObject::connect   ( this , SIGNAL ( EmitStart  ( ) )   ,
                       this , SLOT   ( AlertStart ( ) ) ) ;
  QObject::connect   ( this , SIGNAL ( EmitStop   ( ) )   ,
                       this , SLOT   ( AlertStop  ( ) ) ) ;
  QObject::connect   ( this , SIGNAL ( EmitStatus ( ) )   ,
                       this , SLOT   ( SendStatus ( ) ) ) ;
}

void N::ScriptPlan::StartBusy(void)
{
  emit EmitStart ( ) ;
}

void N::ScriptPlan::StopBusy(void)
{
  emit EmitStop ( ) ;
}

void N::ScriptPlan::AlertStart(void)
{
  RealStart ( ) ;
}

void N::ScriptPlan::AlertStop(void)
{
  RealStop ( ) ;
}

void N::ScriptPlan::showMessage(QString message)
{
  if ( IsNull ( status ) ) return ;
  statusMessage = message         ;
  emit EmitStatus ( )             ;
}

void N::ScriptPlan::SendStatus(void)
{
  if ( IsNull ( status ) ) return         ;
  status -> showMessage ( statusMessage ) ;
}
