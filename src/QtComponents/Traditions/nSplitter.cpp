#include <qtcomponents.h>

N::Splitter:: Splitter   (Qt::Orientation orientation ,
                          QWidget       * parent      ,
                          Plan          * p           )
            : QSplitter  (orientation , parent        )
            , VirtualGui (this        , p             )
{
  setAttribute ( Qt::WA_InputMethodEnabled ) ;
}

N::Splitter::~Splitter (void)
{
}

QSplitterHandle * N::Splitter::createHandle (void)
{
  SplitterHandle * nsh = new SplitterHandle(orientation(),this,plan) ;
  QObject::connect(nsh ,SIGNAL(assignOrientation(Qt::Orientation))   ,
                   this,SLOT  (assignOrientation(Qt::Orientation)) ) ;
  return nsh                                                         ;
}

void N::Splitter::assignOrientation(Qt::Orientation orientation)
{
  setOrientation ( orientation ) ;
}
