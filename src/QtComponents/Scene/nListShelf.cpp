#include <qtcomponents.h>

#ifdef QT_OPENGL_LIB

N::ListShelf:: ListShelf ( QObject * parent , Plan * p )
             : ListBox   (           parent ,        p )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::ListShelf:: ListShelf ( QObject * parent , Plan * p , SceneDestructor * des )
             : ListBox   (           parent ,        p ,                   des )
{
  WidgetClass   ;
  Configure ( ) ;
}

N::ListShelf::~ListShelf (void)
{
}

void N::ListShelf::Configure(void)
{
  QObject::setProperty ( "Type" , "ListShelf" ) ;
  setVariable          ( "Type" , "ListShelf" ) ;
}

#endif
