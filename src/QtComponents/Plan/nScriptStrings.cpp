#include <qtcomponents.h>

extern unsigned char TraditionalSource[] ;
extern unsigned char SimplifiedSource [] ;

N::ScriptStrings:: ScriptStrings (QObject * parent)
                 : QObject       (          parent)
{
}

N::ScriptStrings::~ScriptStrings (void)
{
}

void N::ScriptStrings::setupTranslation(void)
{
  QByteArray T ( (const char *)TraditionalSource ) ;
  QByteArray S ( (const char *)SimplifiedSource  ) ;
  QString    t = QString::fromUtf8(T)              ;
  QString    s = QString::fromUtf8(S)              ;
  TraditionalToSimplified.clear()                  ;
  SimplifiedToTraditional.clear()                  ;
  for (int i=0;i<t.length();i++)                   {
    QString A = t.at(i)                            ;
    QString B = s.at(i)                            ;
    TraditionalToSimplified [A] = B                ;
    SimplifiedToTraditional [B] = A                ;
  }                                                ;
}

QString N::ScriptStrings::ToTraditional(QString name)
{
  QString z ;
  for (int i=0;i<name.length();i++) {
    QString n = name.at(i) ;
    if (SimplifiedToTraditional.contains(n))
         z.append(SimplifiedToTraditional[n]);
    else z.append(n) ;
  };
  return  z ;
}

QString N::ScriptStrings::ToSimplified(QString name)
{
  QString z ;
  for (int i=0;i<name.length();i++) {
    QString n = name.at(i) ;
    if (TraditionalToSimplified.contains(n))
         z.append(TraditionalToSimplified[n]);
    else z.append(n) ;
  };
  return  z ;
}

QString N::ScriptStrings::Filename(QString url)
{
  QFileInfo F        ( url ) ;
  return F .fileName (     ) ;
}

QString N::ScriptStrings::Basename(QString url)
{
  QFileInfo F        ( url ) ;
  return F .baseName (     ) ;
}

QString N::ScriptStrings::Replace(QString name,QString key,QString replacement)
{
  QString R = name ;
  return R.replace(key,replacement) ;
}

bool N::ScriptStrings::Contains(QString name,QString key)
{
  return name . contains ( key ) ;
}

QString N::ScriptStrings::Unicode(int unicode)
{
  QChar   c ( unicode ) ;
  QString s             ;
  s . append ( c )      ;
  return s              ;
}

QString N::ScriptStrings::HtmlTag(QString tag,bool ending)
{
  QString result                       ;
  if (ending)                          {
    result = QString("</%1>").arg(tag) ;
  } else                               {
    result = QString("<%1>" ).arg(tag) ;
  }                                    ;
  return result                        ;
}

QString N::ScriptStrings::line(void)
{
  return "\n" ;
}

QString N::ScriptStrings::lrln(void)
{
  return "\r\n" ;
}

QString N::ScriptStrings::toUrlEncoded(QString s)
{
  QString     t = s                                 ;
  QStringList L = t . split ( ' ' )                 ;
  QStringList R                                     ;
  foreach ( t , L ) if ( t . length ( ) > 0 )       {
    QByteArray    B = t.toUtf8()                    ;
    unsigned char c                                 ;
    t . clear ( )                                   ;
    for (int i=0;i<B.size();i++)                    {
      QString h                                     ;
      c = (unsigned char) B . at ( i )              ;
      h = QString("%1").arg((int)c,2,16,QChar('0')) ;
      h = h . toUpper ( )                           ;
      t . append ( QChar('%') )                     ;
      t . append ( h          )                     ;
    }                                               ;
    if ( t . length ( ) > 0 ) R << t                ;
  }                                                 ;
  return R . join ( "+" )                           ;
}

QString N::ScriptStrings::toUrlEncoded(QString s,QString encoding)
{
  QString      t = s                                              ;
  QStringList  L = t . split ( ' ' )                              ;
  QStringList  R                                                  ;
  QTextCodec * codec                                              ;
  codec = QTextCodec::codecForName(encoding.toUtf8().constData()) ;
  foreach ( t , L ) if ( t . length ( ) > 0 )                     {
    QByteArray    B = codec -> fromUnicode ( t )                  ;
    unsigned char c                                               ;
    t . clear ( )                                                 ;
    for (int i=0;i<B.size();i++)                                  {
      QString h                                                   ;
      c = (unsigned char) B . at ( i )                            ;
      h = QString("%1").arg((int)c,2,16,QChar('0'))               ;
      h = h . toUpper ( )                                         ;
      t . append ( QChar('%') )                                   ;
      t . append ( h          )                                   ;
    }                                                             ;
    if ( t . length ( ) > 0 ) R << t                              ;
  }                                                               ;
  return R . join ( "+" )                                         ;
}

static QScriptValue ScriptCreateString(QScriptContext * context,QScriptEngine * engine)
{
  N::ScriptStrings * ss = new N::ScriptStrings(engine) ;
  ss->setupTranslation()                               ;
  return engine->newQObject(ss)                        ;
}
