#include <qtcomponents.h>

QString N::Scripts::StringMapper(QString script,QString source)
{
  QScriptEngine    Engine                                       ;
  Engine.globalObject(                                          )
        .setProperty                                            (
           "ScriptStrings"                                      ,
           Engine.newFunction(N::ScriptCreateString             )
        )                                                       ;
  QString          result      = source                         ;
  QString          parentheses = "(" + script + ")"             ;
  QScriptValue     func        = Engine.evaluate(parentheses)   ;
  QScriptValueList args        ; args << source                 ;
  QScriptValue     Again       = func.call(QScriptValue(),args) ;
  result = Again.toString()                                     ;
  return  result                                                ;
}

bool N::Scripts::StringMatching(QString script,QString source)
{
  QScriptEngine Engine                                          ;
  Engine.globalObject(                                          )
        .setProperty                                            (
           "ScriptStrings"                                      ,
           Engine.newFunction(N::ScriptCreateString             )
        )                                                       ;
  QString          parentheses = "(" + script + ")"             ;
  QScriptValue     func        = Engine.evaluate(parentheses)   ;
  QScriptValueList args        ; args << source                 ;
  QScriptValue     Again       = func.call(QScriptValue(),args) ;
  return Again.toBool()                                         ;
}

QString N::Scripts::DocumentMapper(QString script,QString source)
{
  QScriptEngine    Engine                                       ;
  Engine.globalObject(                                          )
        .setProperty                                            (
           "ScriptStrings"                                      ,
           Engine.newFunction(N::ScriptCreateString             )
        )                                                       ;
  QString          result      = source                         ;
  QString          parentheses = "(" + script + ")"             ;
  QScriptValue     func        = Engine.evaluate(parentheses)   ;
  QScriptValueList args        ; args << source                 ;
  QScriptValue     Again       = func.call(QScriptValue(),args) ;
  result = Again.toString()                                     ;
  return  result                                                ;
}
