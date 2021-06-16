#include <qtcomponents.h>

#ifdef QT_OPENGL_LIB

N::NamesShelf:: NamesShelf ( QObject * parent , Plan * p )
              : ListShelf  (           parent ,        p )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::NamesShelf:: NamesShelf ( QObject * parent , Plan * p , SceneDestructor * des )
              : ListShelf  (           parent ,        p ,                   des )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::NamesShelf::~NamesShelf (void)
{
}

void N::NamesShelf::Configure(void)
{
  QObject::setProperty ( "Type" , "NamesShelf" ) ;
  setVariable          ( "Type" , "NamesShelf" ) ;
}

#endif
