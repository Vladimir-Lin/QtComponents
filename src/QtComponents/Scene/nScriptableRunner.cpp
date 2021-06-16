#include <qtcomponents.h>

#ifdef QT_OPENGL_LIB

N::ScriptableRunner:: ScriptableRunner ( QObject * parent )
                    : QObject          (           parent )
                    , QScriptable      (                  )
                    , PathRunner       (                  )
                    , universe         ( NULL             )
                    , Script           ( NULL             )
{
}

N::ScriptableRunner::~ScriptableRunner (void)
{
}

int N::ScriptableRunner::step(int after)
{
  if ( IsNull(Script) ) return -1 ;
  return -1                       ;
}

bool N::ScriptableRunner::execute(void)
{
  if ( IsNull(Script) ) return false ;
  return false                       ;
}

bool N::ScriptableRunner::setScript(QString step,QString execute,QString script)
{
  return false ;
}

#endif
