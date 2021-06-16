#include <qtcomponents.h>

N::ScopedProgress:: ScopedProgress (Plan * p,QString format,int gap)
                  : plan           (       p                       )
                  , Gap            (                            gap)
                  , Index          (0                              )
{
  Progress  = plan->Progress(format) ;
  Progress -> hide ( )               ;
}

N::ScopedProgress::~ScopedProgress(void)
{
  Progress -> hide        () ;
  Progress -> deleteLater () ;
  Progress  = NULL           ;
}

void N::ScopedProgress::show(void)
{
  Progress -> show          ( ) ;
  plan     -> processEvents ( ) ;
}

void N::ScopedProgress::setRange(int minimum,int maximum)
{
  Progress -> setRange ( minimum , maximum ) ;
  Lastest = QDateTime::currentDateTime()     ;
}

void N::ScopedProgress::setValue(int value)
{
  bool pass = false                              ;
  if (Gap==0                 ) pass = true       ;
  if (!pass)                                     {
    QDateTime Now = QDateTime::currentDateTime() ;
    if ((value%Gap)        ==0) pass = true      ;
    if (Lastest.secsTo(Now)> 0) pass = true      ;
  }                                              ;
  if (!pass) return                              ;
  Progress -> setValue      ( value )            ;
  if (Progress->isVisible())                     {
    if (plan->Visible) plan -> processEvents ( ) ;
  }                                              ;
  Lastest   = QDateTime::currentDateTime()       ;
}

void N::ScopedProgress::Final(int value)
{
  Progress -> setValue      ( value )   ;
  plan     -> processEvents (       )   ;
}

void N::ScopedProgress::Start(int index)
{
  Index = index ;
  Lastest = QDateTime::currentDateTime() ;
  Launch  = QDateTime::currentDateTime() ;
}

void N::ScopedProgress::Finish(void)
{
  Final (Index) ;
}

int N::ScopedProgress::operator ++ (void)
{
  Index++         ;
  setValue(Index) ;
  return Index    ;
}

int N::ScopedProgress::Value(void) const
{
  return Index ;
}

QDateTime N::ScopedProgress::Estimated(void)
{
  return Time::ETA(Launch,Index,Progress->maximum());
}

QString N::ScopedProgress::ETA(void)
{
  return Estimated().toString("yyyy/MM/dd hh:mm:ss") ;
}
