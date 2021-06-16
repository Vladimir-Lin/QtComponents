#include "UIs.hpp"

QT_BEGIN_NAMESPACE
CIOS_BEGIN_NAMESPACE

DataRetriever:: DataRetriever (void)
{
  row      = -1   ;
  column   = -1   ;
  language = 0    ;
  widget   = NULL ;
  parent   = NULL ;
  plan     = NULL ;
}

DataRetriever:: DataRetriever (QObject * owner,Plan * p)
{
  row      = -1    ;
  column   = -1    ;
  language = 0     ;
  widget   = NULL  ;
  parent   = owner ;
  plan     = p     ;
}

DataRetriever::~DataRetriever (void)
{
}

CIOS_END_NAMESPACE
QT_END_NAMESPACE
