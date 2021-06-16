#include <qtcomponents.h>

N::FullSettings:: FullSettings (const QString & organization,const QString & application,QObject * parent)
                : Settings     (                organization,                application,          parent)
{
}

N::FullSettings:: FullSettings (QSettings::Scope scope,const QString & organization,const QString & application,QObject * parent)
                : Settings     (                 scope,                organization,                application,          parent)
{
}

N::FullSettings:: FullSettings (QSettings::Format format,QSettings::Scope scope,const QString & organization,const QString & application,QObject * parent)
                : Settings     (                  format,                 scope,                organization,                application,          parent)
{
}

N::FullSettings:: FullSettings (const QString & fileName,QSettings::Format format,QObject * parent)
                : Settings     (                fileName,                  format,          parent)
{
}

N::FullSettings:: FullSettings (Sql & sql,QObject * parent)
                : Settings     (      sql,          parent)
{
}

N::FullSettings:: FullSettings (QObject * parent)
                : Settings     (          parent)
{
}

N::FullSettings::~FullSettings(void)
{
}

QAuthenticator N::FullSettings::getUser(QString Scope)
{
  QAuthenticator user                                        ;
  Mutex.lock()                                               ;
  beginGroup(Scope)                                          ;
  if ("SQL"==Mode)                                           {
    QString      cn = SQL->connection("nSettings","getUser") ;
    {
      QSqlDatabase db = SQL->db(cn)                          ;
      if (SQL->Open(db))                                     {
        QSqlQuery q(db)                                      ;
        user . setUser     (valueString(q,"username"))       ;
        user . setPassword (valueString(q,"password"))       ;
        SQL->Close(db)                                       ;
      }                                                      ;
    }                                                        ;
    QSqlDatabase::removeDatabase(cn)                         ;
  } else                                                     {
    user . setUser     (valueString("username"))             ;
    user . setPassword (valueString("password"))             ;
  }                                                          ;
  endGroup()                                                 ;
  Mutex.unlock()                                             ;
  return user                                                ;
}

void N::FullSettings::SaveUserRecord(QString Scope,QAuthenticator & user)
{
  Mutex.lock()                                                      ;
  beginGroup(Scope)                                                 ;
  if ("SQL"==Mode)                                                  {
    QString      cn = SQL->connection("nSettings","SaveUserRecord") ;
    {
      QSqlDatabase db = SQL->db(cn)                                 ;
      if (SQL->Open(db))                                            {
        QSqlQuery q(db)                                             ;
        setValue(q,"username",user.user())                          ;
        setValue(q,"password",user.password())                      ;
        SQL->Close(db)                                              ;
      }                                                             ;
      db = QSqlDatabase()                                           ;
    }                                                               ;
    QSqlDatabase::removeDatabase(cn)                                ;
  } else                                                            {
    setValue("username",user.user())                                ;
    setValue("password",user.password())                            ;
  }                                                                 ;
  endGroup()                                                        ;
  Mutex.unlock()                                                    ;
}

void N::FullSettings::SaveFont(QString scope,QFont & font)
{
  Mutex.lock()                                                ;
  beginGroup (scope)                                          ;
  if ("SQL"==Mode)                                            {
    QString      cn = SQL->connection("nSettings","SaveFont") ;
    {
      QSqlDatabase db = SQL->db(cn)                           ;
      if (SQL->Open(db))                                      {
        QSqlQuery q(db)                                       ;
        setValue (q,"Family"   ,font.family().toUtf8())       ;
        setValue (q,"PixelSize",font.pixelSize      ())       ;
        setValue (q,"PointSize",font.pointSize      ())       ;
        setValue (q,"Bold"     ,font.bold           ())       ;
        setValue (q,"Kerning"  ,font.kerning        ())       ;
        setValue (q,"Italic"   ,font.italic         ())       ;
        setValue (q,"Overline" ,font.overline       ())       ;
        setValue (q,"StrikeOut",font.strikeOut      ())       ;
        setValue (q,"Underline",font.underline      ())       ;
        SQL->Close(db)                                        ;
      }                                                       ;
      db = QSqlDatabase()                                     ;
    }                                                         ;
    QSqlDatabase::removeDatabase(cn)                          ;
  } else                                                      {
    setValue ("Family"   ,font.family().toUtf8    ())         ;
    setValue ("PixelSize",font.pixelSize          ())         ;
    setValue ("PointSize",font.pointSize          ())         ;
    setValue ("Bold"     ,font.bold               ())         ;
    setValue ("Kerning"  ,font.kerning            ())         ;
    setValue ("Italic"   ,font.italic             ())         ;
    setValue ("Overline" ,font.overline           ())         ;
    setValue ("StrikeOut",font.strikeOut          ())         ;
    setValue ("Underline",font.underline          ())         ;
  }                                                           ;
  endGroup   (     )                                          ;
  Mutex.unlock()                                              ;
}

void N::FullSettings::LoadFont(QString scope,QFont & font)
{
  Mutex.lock()                                                     ;
  beginGroup (scope)                                               ;
  if ("SQL"==Mode) {
    QString      cn = SQL->connection("nSettings","LoadFont")      ;
    {
      QSqlDatabase db = SQL->db(cn)                                ;
      if (SQL->Open(db))                                           {
        QSqlQuery q(db)                                            ;
        font . setFamily    (valueString (q,"Family"   )         ) ;
        font . setPixelSize (value       (q,"PixelSize").toInt ()) ;
        font . setPointSize (value       (q,"PointSize").toInt ()) ;
        font . setBold      (value       (q,"Bold"     ).toBool()) ;
        font . setKerning   (value       (q,"Kerning"  ).toBool()) ;
        font . setItalic    (value       (q,"Italic"   ).toBool()) ;
        font . setOverline  (value       (q,"Overline" ).toBool()) ;
        font . setStrikeOut (value       (q,"StrikeOut").toBool()) ;
        font . setUnderline (value       (q,"Underline").toBool()) ;
        SQL->Close(db)                                             ;
      }                                                            ;
      db = QSqlDatabase()                                          ;
    }                                                              ;
    QSqlDatabase::removeDatabase(cn)                               ;
  } else                                                           {
    font . setFamily    (valueString ("Family"   )         )       ;
    font . setPixelSize (value       ("PixelSize").toInt ())       ;
    font . setPointSize (value       ("PointSize").toInt ())       ;
    font . setBold      (value       ("Bold"     ).toBool())       ;
    font . setKerning   (value       ("Kerning"  ).toBool())       ;
    font . setItalic    (value       ("Italic"   ).toBool())       ;
    font . setOverline  (value       ("Overline" ).toBool())       ;
    font . setStrikeOut (value       ("StrikeOut").toBool())       ;
    font . setUnderline (value       ("Underline").toBool())       ;
  }                                                                ;
  endGroup   (     )                                               ;
  Mutex.unlock()                                                   ;
}

void N::FullSettings::SaveFont(QString scope,Font & font)
{
  Mutex.lock()                                                ;
  beginGroup (scope)                                          ;
  if ("SQL"==Mode)                                            {
    QString      cn = SQL->connection("nSettings","SaveFont") ;
    {
      QSqlDatabase db = SQL->db(cn)                           ;
      if (SQL->Open(db))                                      {
        QSqlQuery q(db)                                       ;
        setValue (q,"Family"   ,font.family().toUtf8())       ;
        setValue (q,"cm"       ,font.cm               )       ;
        setValue (q,"PixelSize",font.pixelSize      ())       ;
        setValue (q,"PointSize",font.pointSize      ())       ;
        setValue (q,"Bold"     ,font.bold           ())       ;
        setValue (q,"Kerning"  ,font.kerning        ())       ;
        setValue (q,"Italic"   ,font.italic         ())       ;
        setValue (q,"Overline" ,font.overline       ())       ;
        setValue (q,"StrikeOut",font.strikeOut      ())       ;
        setValue (q,"Underline",font.underline      ())       ;
        SQL->Close(db)                                        ;
      }                                                       ;
      db = QSqlDatabase()                                     ;
    }                                                         ;
    QSqlDatabase::removeDatabase(cn)                          ;
  } else                                                      {
    setValue ("Family"   ,font.family().toUtf8      ())       ;
    setValue ("cm"       ,font.cm                     )       ;
    setValue ("PixelSize",font.pixelSize            ())       ;
    setValue ("PointSize",font.pointSize            ())       ;
    setValue ("Bold"     ,font.bold                 ())       ;
    setValue ("Kerning"  ,font.kerning              ())       ;
    setValue ("Italic"   ,font.italic               ())       ;
    setValue ("Overline" ,font.overline             ())       ;
    setValue ("StrikeOut",font.strikeOut            ())       ;
    setValue ("Underline",font.underline            ())       ;
  }                                                           ;
  endGroup   (     )                                          ;
  Mutex.unlock()                                              ;
}

void N::FullSettings::LoadFont(QString scope,Font & font)
{
  Mutex.lock()                                                       ;
  beginGroup (scope)                                                 ;
  if ("SQL"==Mode) {
    QString      cn = SQL->connection("nSettings","LoadFont")        ;
    {
      QSqlDatabase db = SQL->db(cn)                                  ;
      if (SQL->Open(db))                                             {
        QSqlQuery q(db)                                              ;
        if (contains(q,"cm"))                                        {
          font . cm = value(q,"cm").toDouble()                       ;
        }                                                            ;
        if (contains(q,"Family"))                                    {
          font . setFamily    (valueString (q,"Family"   )         ) ;
        }                                                            ;
        if (contains(q,"PixelSize"))                                 {
          int ps = value       (q,"PixelSize").toInt ()              ;
          if (ps>0) font . setPixelSize (ps                        ) ;
        }                                                            ;
        if (contains(q,"PointSize"))                                 {
          int ps = value       (q,"PointSize").toInt ()              ;
          if (ps>0) font . setPointSize (ps                        ) ;
        }                                                            ;
        if (contains(q,"Bold"))                                      {
          font . setBold      (value       (q,"Bold"     ).toBool()) ;
        }                                                            ;
        if (contains(q,"Kerning"))                                   {
          font . setKerning   (value       (q,"Kerning"  ).toBool()) ;
        }                                                            ;
        if (contains(q,"Italic"))                                    {
          font . setItalic    (value       (q,"Italic"   ).toBool()) ;
        }                                                            ;
        if (contains(q,"Overline"))                                  {
          font . setOverline  (value       (q,"Overline" ).toBool()) ;
        }                                                            ;
        if (contains(q,"StrikeOut"))                                 {
          font . setStrikeOut (value       (q,"StrikeOut").toBool()) ;
        }                                                            ;
        if (contains(q,"Underline"))                                 {
          font . setUnderline (value       (q,"Underline").toBool()) ;
        }                                                            ;
        SQL->Close(db)                                               ;
      }                                                              ;
      db = QSqlDatabase()                                            ;
    }                                                                ;
    QSqlDatabase::removeDatabase(cn)                                 ;
  } else                                                             {
    if (contains("cm"))                                              {
      font . cm = value   ("cm") . toDouble ( )                      ;
    }                                                                ;
    if (contains("Family"))                                          {
      font . setFamily    (valueString ("Family"   )         )       ;
    }                                                                ;
    if (contains("PixelSize"))                                       {
      int ps = value       ("PixelSize").toInt ()                    ;
      if (ps>0) font . setPixelSize (ps                      )       ;
    }                                                                ;
    if (contains("PointSize"))                                       {
      int ps = value       ("PointSize").toInt ()                    ;
      if (ps>0) font . setPointSize (ps                      )       ;
    }                                                                ;
    if (contains("Bold"))                                            {
      font . setBold      (value       ("Bold"     ).toBool())       ;
    }                                                                ;
    if (contains("Kerning"))                                         {
      font . setKerning   (value       ("Kerning"  ).toBool())       ;
    }                                                                ;
    if (contains("Italic"))                                          {
      font . setItalic    (value       ("Italic"   ).toBool())       ;
    }                                                                ;
    if (contains("Overline"))                                        {
      font . setOverline  (value       ("Overline" ).toBool())       ;
    }                                                                ;
    if (contains("StrikeOut"))                                       {
      font . setStrikeOut (value       ("StrikeOut").toBool())       ;
    }                                                                ;
    if (contains("Underline"))                                       {
      font . setUnderline (value       ("Underline").toBool())       ;
    }                                                                ;
  }                                                                  ;
  endGroup   (     )                                                 ;
  Mutex.unlock()                                                     ;
}

void N::FullSettings::LoadDock(QString scope,DockInformation & dock)
{
  Mutex . lock (       )                                  ;
  beginGroup   ( scope )                                  ;
  if ( ( "SQL" == Mode ) && ( NotNull ( SQL ) ) )         {
    SqlConnection SC ( *SQL )                             ;
    if ( SC . open ( FunctionString ) )                   {
      #define FETCHITEM(NAMEX,VARX,FUNC)                  \
        if (contains(SC.q,NAMEX))              {          \
          dock.VARX = value(SC.q,NAMEX).FUNC() ;          \
        }
      FETCHITEM ( "DockArea"   , area     , toInt       ) ;
      FETCHITEM ( "DockShow"   , show     , toBool      ) ;
      FETCHITEM ( "DockFloat"  , floating , toBool      ) ;
      FETCHITEM ( "DockWidth"  , width    , toInt       ) ;
      FETCHITEM ( "DockHeight" , height   , toInt       ) ;
      FETCHITEM ( "Dock"       , geometry , toByteArray ) ;
      #undef  FETCHITEM
      SC . close  ( )                                     ;
    }                                                     ;
    SC   . remove ( )                                     ;
  } else                                                  {
    #define FETCHITEM(NAMEX,VARX,FUNC)                    \
      if (contains(NAMEX))              {                 \
        dock.VARX = value(NAMEX).FUNC() ;                 \
      }
    FETCHITEM ( "DockArea"   , area     , toInt       )   ;
    FETCHITEM ( "DockShow"   , show     , toBool      )   ;
    FETCHITEM ( "DockFloat"  , floating , toBool      )   ;
    FETCHITEM ( "DockWidth"  , width    , toInt       )   ;
    FETCHITEM ( "DockHeight" , height   , toInt       )   ;
    FETCHITEM ( "Dock"       , geometry , toByteArray )   ;
    #undef  FETCHITEM
  }                                                       ;
  endGroup       ( )                                      ;
  Mutex . unlock ( )                                      ;
}

void N::FullSettings::SaveDock(QString scope,DockInformation & dock)
{
  Mutex.lock()                                                   ;
  beginGroup (scope)                                             ;
  if ("SQL"==Mode) {
    QString      cn = SQL->connection("nSettings","SaveDock")    ;
    {
    QSqlDatabase db = SQL->db(cn)                                ;
    if (SQL->Open(db))                                           {
      QSqlQuery q(db)                                            ;
      setValue   (q,"Dock"      ,dock.geometry                 ) ;
      setValue   (q,"DockFloat" ,dock.floating                 ) ;
      setValue   (q,"DockShow"  ,dock.show                     ) ;
      setValue   (q,"DockArea"  ,dock.area                     ) ;
      setValue   (q,"DockWidth" ,dock.width                    ) ;
      setValue   (q,"DockHeight",dock.height                   ) ;
      SQL->Close(db)                                             ;
    }                                                            ;
    }                                                            ;
    QSqlDatabase::removeDatabase(cn)                             ;
  } else                                                         {
    setValue   ("Dock"      ,dock.geometry                     ) ;
    setValue   ("DockFloat" ,dock.floating                     ) ;
    setValue   ("DockShow"  ,dock.show                         ) ;
    setValue   ("DockArea"  ,dock.area                         ) ;
    setValue   ("DockWidth" ,dock.width                        ) ;
    setValue   ("DockHeight",dock.height                       ) ;
  }                                                              ;
  endGroup   (     )                                             ;
  Mutex.unlock()                                                 ;
}
