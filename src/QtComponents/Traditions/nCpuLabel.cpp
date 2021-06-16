#include <qtcomponents.h>

N::CpuLabel:: CpuLabel       ( QWidget * parent , Plan * p , bool flags )
            : ClickableLabel (           parent ,        p              )
            , Timer          ( NULL                                     )
            , CPU::Usage     (                                          )
            , Flag           ( flags                                    )
{
}

N::CpuLabel::~CpuLabel (void)
{
  Stop ( ) ;
}

void N::CpuLabel::Start(void)
{
  if ( IsNull ( Timer ) )                            {
    Timer  = new QTimer ( this )                     ;
    Timer -> setParent  ( this )                     ;
    addConnector  ( "Timer"                          ,
                    Timer , SIGNAL ( timeout ( ) )   ,
                    this  , SLOT   ( Update  ( ) ) ) ;
    onlyConnector ( "Timer"                        ) ;
  }                                                  ;
  Timer -> start ( 1000 )                            ;
}

void N::CpuLabel::Stop(void)
{
  if ( IsNull(Timer) ) return ;
  QTimer * E = Timer          ;
  Timer = NULL                ;
  E -> stop        ( )        ;
  E -> deleteLater ( )        ;
}

void N::CpuLabel::Update(void)
{
  short   cpu = GetUsage ( Flag )             ;
  QString U   = ""                            ;
  if (cpu<0) return                           ;
  U = QString("%")                            ;
  U = QString::number(cpu%10) + U ; cpu /= 10 ;
  U = QString::number(cpu%10) + U ; cpu /= 10 ;
  U = QString(".") + U                        ;
  U = QString::number(cpu%10) + U ; cpu /= 10 ;
  U = QString::number(cpu%10) + U ; cpu /= 10 ;
  if ( cpu > 0 )                              {
    U = QString::number(cpu%10) + U           ;
  }                                           ;
  setText ( U )                               ;
}
