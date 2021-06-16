#include <qtcomponents.h>
#include "ui_DesktopSqlConfigurator.h"
#include "ui_PhoneSqlConfigurator.h"


N::SqlConfigurator:: SqlConfigurator (QWidget * parent,Plan * p)
                   : StackedWidget   (          parent,       p)
                   , Object          (0,Types::SqlConnection   )
                   , uid             (NULL                     )
                   , uip             (NULL                     )
{
  WidgetClass             ;
  #if defined(Q_OS_IOS)
  setTemplate(PhoneSQL  ) ;
  #else
  setTemplate(DesktopSQL) ;
  #endif
}

N::SqlConfigurator:: SqlConfigurator (ConfTemplates templ,QWidget * parent,Plan * p)
                   : StackedWidget   (                              parent,       p)
                   , Object          (0,Types::SqlConnection                       )
                   , uid             (NULL                                         )
                   , uip             (NULL                                         )
{
  setTemplate ( templ ) ;
}

bool N::SqlConfigurator::setTemplate(ConfTemplates templ)
{
  switch (templ)                           {
    case DesktopSQL                        :
      uid = new Ui::DesktopSqlConfigurator ;
      uid->setupUi(this)                   ;
    break                                  ;
    case PhoneSQL                          :
      uip = new Ui::PhoneSqlConfigurator   ;
      uip->setupUi(this)                   ;
    break                                  ;
  }                                        ;
  return true                              ;
}

void N::SqlConfigurator::Selector(void)
{
  if (NotNull(uid)) setCurrentWidget ( uid->Selector ) ;
  if (NotNull(uip)) setCurrentWidget ( uip->Selector ) ;
  plan->Talk       (tr("Select your SQL server type")) ;
}

void N::SqlConfigurator::MySQL(void)
{
  if (NotNull(uid)) setCurrentWidget ( uid->MySQL ) ;
  if (NotNull(uip)) setCurrentWidget ( uip->MySQL ) ;
  plan->Talk      (tr("Setup MySQL configuration")) ;
}

void N::SqlConfigurator::PostgreSQL(void)
{
  if (NotNull(uid)) setCurrentWidget ( uid->PostgreSQL ) ;
  if (NotNull(uip)) setCurrentWidget ( uip->PostgreSQL ) ;
  plan->Talk      (tr("Setup PostgreSQL configuration")) ;
}

void N::SqlConfigurator::Firebird(void)
{
  if (NotNull(uid)) setCurrentWidget ( uid->Firebird ) ;
  if (NotNull(uip)) setCurrentWidget ( uip->Firebird ) ;
  plan->Talk      (tr("Setup Firebird configuration")) ;
}

void N::SqlConfigurator::ODBC(void)
{
  if (NotNull(uid)) setCurrentWidget ( uid->ODBC ) ;
  if (NotNull(uip)) setCurrentWidget ( uip->ODBC ) ;
  plan->Talk      (tr("Setup ODBC configuration")) ;
}

void N::SqlConfigurator::SQLite(void)
{
  if (NotNull(uid)) setCurrentWidget ( uid->SQLite ) ;
  if (NotNull(uip)) setCurrentWidget ( uip->SQLite ) ;
  plan->Talk      (tr("Setup SQLite configuration")) ;
}

void N::SqlConfigurator::TestMySQL(void)
{
  Sql sql                                                          ;
  nDropOut ( !ObtainMySQL(sql) )                                   ;
  //////////////////////////////////////////////////////////////////
  QString Q                                                        ;
  Q = tr("Test MySQL %1 connection").arg(sql.Profile)              ;
  plan->Talk        (Q)                                            ;
  plan->showMessage (Q)                                            ;
  plan->processEvents()                                            ;
  SqlConnection SC(sql)                                            ;
  bool successful = false                                          ;
  if (SC.open("DatabaseConfigurator","TestMySQL"))                 {
    bool connectivity = false                                      ;
    Q = tr("MySQL %1 is connected").arg(sql.Profile)               ;
    plan->Talk        (Q)                                          ;
    plan->showMessage (Q)                                          ;
    plan->processEvents()                                          ;
    Q = tr("Test creating tables and paraments")                   ;
    plan->Talk        (Q)                                          ;
    plan->showMessage (Q)                                          ;
    plan->processEvents()                                          ;
    Q = "create table DatabaseConfiguratorTestMySQL ("
        " id integer primary key auto_increment,"
        " ltime timestamp default CURRENT_TIMESTAMP"
        " on update CURRENT_TIMESTAMP"
        ");"                                                       ;
    if (SC.Query(Q))                                               {
      connectivity = true                                          ;
    } else Notify(SC.q.lastError().text())                         ;
    if (connectivity)                                              {
      Q = "drop table DatabaseConfiguratorTestMySQL ;"             ;
      if (SC.Query(Q))                                             {
        successful = true                                          ;
      } else connectivity = false                                  ;
    }                                                              ;
    if (successful)                                                {
      Q = "create table TestMySQLIndex ("
          " id integer primary key auto_increment,"
          " uuid bigint unsigned not null,"
          " ltime timestamp default CURRENT_TIMESTAMP"
          " on update CURRENT_TIMESTAMP,"
          " index `uuidindex` (uuid)"
          ");"                                                     ;
      if (SC.Query(Q))                                             {
        connectivity = true                                        ;
      } else connectivity = false                                  ;
      if (connectivity) {
        Q = "create table TestMySQLForeignKey ("
            " id integer primary key auto_increment,"
            " uuid bigint unsigned not null,"
            " ltime timestamp default CURRENT_TIMESTAMP"
            " on update CURRENT_TIMESTAMP,"
            " foreign key (uuid) references TestMySQLIndex(uuid)"
            ");"                                                   ;
        if (SC.Query(Q))                                           {
          connectivity = true                                      ;
        } else connectivity = false                                ;
      }                                                            ;
      if (!SC.Query("drop table TestMySQLForeignKey ;"))           {
        successful = false                                         ;
      }                                                            ;
      if (!SC.Query("drop table TestMySQLIndex ;"))                {
        successful = false                                         ;
      }                                                            ;
    }                                                              ;
    if (!successful)                                               {
      Q = tr("MySQL %1 operation is not correct").arg(sql.Profile) ;
      plan->Talk        (Q)                                        ;
      plan->showMessage (Q)                                        ;
      plan->processEvents()                                        ;
    }                                                              ;
    SC.close()                                                     ;
  } else                                                           {
    Q = tr("MySQL %1 can not connect").arg(sql.Profile)            ;
    plan->Talk        (Q)                                          ;
    plan->showMessage (Q)                                          ;
    plan->processEvents()                                          ;
  }                                                                ;
  SC.remove()                                                      ;
  if (successful)                                                  {
    Q = tr("MySQL %1 is successful").arg(sql.Profile)              ;
    plan->Talk        (Q)                                          ;
    plan->showMessage (Q)                                          ;
    plan->processEvents()                                          ;
    if (NotNull(uid)) uid->myApplyButton->setEnabled(true)         ;
    if (NotNull(uip)) uip->myApplyButton->setEnabled(true)         ;
  } else                                                           {
    if (NotNull(uid)) uid->myApplyButton->setEnabled(false)        ;
    if (NotNull(uip)) uid->myApplyButton->setEnabled(false)        ;
  }                                                                ;
}

void N::SqlConfigurator::TestPostgreSQL(void)
{
  Sql sql                                                               ;
  nDropOut ( !ObtainPostgreSQL(sql) )                                   ;
  ///////////////////////////////////////////////////////////////////////
  QString Q = tr("Test PostgreSQL %1 connection").arg(sql.Profile)      ;
  plan->Talk        (Q)                                                 ;
  plan->showMessage (Q)                                                 ;
  plan->processEvents()                                                 ;
  SqlConnection SC(sql)                                                 ;
  bool successful = false                                               ;
  if (SC.open("DatabaseConfigurator","TestPostgreSQL"))                 {
    bool connectivity = false                                           ;
    Q = tr("PostgreSQL %1 is connected").arg(sql.Profile)               ;
    plan->Talk        (Q)                                               ;
    plan->showMessage (Q)                                               ;
    plan->processEvents()                                               ;
    Q = tr("Test creating tables and paraments")                        ;
    plan->Talk        (Q)                                               ;
    plan->showMessage (Q)                                               ;
    plan->processEvents()                                               ;
    Q = "create table DatabaseConfiguratorTestPostgreSQL ("
        " id serial,"
        " ltime timestamp default CURRENT_TIMESTAMP"
        ");"                                                            ;
    if (SC.Query(Q))                                                    {
      connectivity = true                                               ;
    } else Notify(SC.q.lastError().text())                              ;
    if (connectivity)                                                   {
      Q = "drop table DatabaseConfiguratorTestPostgreSQL ;"             ;
      if (SC.Query(Q))                                                  {
        successful = true                                               ;
      } else connectivity = false                                       ;
    }                                                                   ;
    if (successful)                                                     {
      Q = "create table TestPostgreSQLIndex ("
          " id serial,"
          " uuid bigint not null,"
          " ltime timestamp default CURRENT_TIMESTAMP,"
          " unique (uuid)"
          ");"                                                          ;
      if (SC.Query(Q))                                                  {
        connectivity = true                                             ;
      } else                                                            {
        Notify(SC.q.lastError().text())                                 ;
        connectivity = false                                            ;
      }                                                                 ;
      if (connectivity) {
        Q = "create table TestPostgreSQLForeignKey ("
            " id serial,"
            " uuid bigint not null,"
            " ltime timestamp default CURRENT_TIMESTAMP,"
            " foreign key (uuid) references TestPostgreSQLIndex(uuid)"
            ");"                                                        ;
        if (SC.Query(Q))                                                {
          connectivity = true                                           ;
        } else                                                          {
          Notify(SC.q.lastError().text())                               ;
          connectivity = false                                          ;
        }                                                               ;
      }                                                                 ;
      if (!SC.Query("drop table TestPostgreSQLForeignKey ;"))           {
        successful = false                                              ;
      }                                                                 ;
      if (!SC.Query("drop table TestPostgreSQLIndex ;"))                {
        successful = false                                              ;
      }                                                                 ;
    }                                                                   ;
    if (!successful)                                                    {
      Q = tr("PostgreSQL %1 operation is not correct").arg(sql.Profile) ;
      plan->Talk        (Q)                                             ;
      plan->showMessage (Q)                                             ;
      plan->processEvents()                                             ;
    }                                                                   ;
    SC.close()                                                          ;
  } else                                                                {
    Q = tr("PostgreSQL %1 can not connect").arg(sql.Profile)            ;
    plan->Talk        (Q)                                               ;
    plan->showMessage (Q)                                               ;
    plan->processEvents()                                               ;
  }                                                                     ;
  SC.remove()                                                           ;
  if (successful)                                                       {
    Q = tr("PostgreSQL %1 is successful").arg(sql.Profile)              ;
    plan->Talk        (Q)                                               ;
    plan->showMessage (Q)                                               ;
    plan->processEvents()                                               ;
    if (NotNull(uid)) uid->pqApplyButton->setEnabled(true)              ;
    if (NotNull(uip)) uip->pqApplyButton->setEnabled(true)              ;
  } else                                                                {
    if (NotNull(uid)) uid->pqApplyButton->setEnabled(false)             ;
    if (NotNull(uip)) uip->pqApplyButton->setEnabled(false)             ;
  }                                                                     ;
}

void N::SqlConfigurator::TestFirebird(void)
{
  Sql sql                                                          ;
  nDropOut ( !ObtainFirebird(sql) )                                ;
  ///////////////////////////////////////////////////////////////////////
  QString Q = tr("Test Firebird %1 connection").arg(sql.Profile)      ;
  plan->Talk        (Q)                                               ;
  plan->showMessage (Q)                                               ;
  plan->processEvents()                                               ;
  SqlConnection SC(sql)                                              ;
  bool successful = false                                             ;
  if (SC.open("DatabaseConfigurator","TestFireBird"))                 {
    bool connectivity = false                                         ;
    Q = tr("Firebird %1 is connected").arg(sql.Profile)               ;
    plan->Talk        (Q)                                             ;
    plan->showMessage (Q)                                             ;
    plan->processEvents()                                             ;
    Q = tr("Test creating tables and paraments")                      ;
    plan->Talk        (Q)                                             ;
    plan->showMessage (Q)                                             ;
    plan->processEvents()                                             ;
    Q = "create table dbConfTestFirebird ("
        " id integer primary key,"
        " ltime timestamp"
        ");"                                                          ;
    if (SC.Query(Q))                                                  {
      connectivity = true                                             ;
    } else Notify(SC.q.lastError().text())                            ;
    if (connectivity)                                                 {
      Q = "drop table dbConfTestFirebird ;"                           ;
      if (SC.Query(Q))                                                {
        successful = true                                             ;
      } else connectivity = false                                     ;
    }                                                                 ;
    if (successful)                                                   {
      Q = "create table TestFirebirdIndex ("
          " id integer primary key,"
          " uuid bigint not null,"
          " ltime timestamp default CURRENT_TIMESTAMP,"
          " unique (uuid)"
          ");"                                                        ;
      if (SC.Query(Q))                                                {
        connectivity = true                                           ;
      } else                                                          {
        Notify(SC.q.lastError().text())                               ;
        connectivity = false                                          ;
      }                                                               ;
      if (connectivity) {
        Q = "create table TestFirebirdFKey ("
            " id integer primary key,"
            " uuid bigint not null,"
            " ltime timestamp default CURRENT_TIMESTAMP,"
            " foreign key (uuid) references TestFirebirdIndex(uuid)"
            ");"                                                      ;
        if (SC.Query(Q))                                              {
          connectivity = true                                         ;
        } else                                                        {
          Notify(SC.q.lastError().text())                             ;
          connectivity = false                                        ;
        }                                                             ;
      }                                                               ;
      if (!SC.Query("drop table TestFirebirdFKey ;"))                 {
        successful = false                                            ;
      }                                                               ;
      if (!SC.Query("drop table TestFirebirdIndex ;"))                {
        successful = false                                            ;
      }                                                               ;
    }                                                                 ;
    if (!successful)                                                  {
      Q = tr("Firebird %1 operation is not correct").arg(sql.Profile) ;
      plan->Talk        (Q)                                           ;
      plan->showMessage (Q)                                           ;
      plan->processEvents()                                           ;
    }                                                                 ;
    SC.close()                                                        ;
  } else                                                              {
    Q = tr("Firebird %1 can not connect").arg(sql.Profile)            ;
    plan->Talk        (Q)                                             ;
    plan->showMessage (Q)                                             ;
    plan->processEvents()                                             ;
  }                                                                   ;
  SC.remove()                                                         ;
  if (successful)                                                     {
    Q = tr("Firebird %1 is successful").arg(sql.Profile)              ;
    plan->Talk        (Q)                                             ;
    plan->showMessage (Q)                                             ;
    plan->processEvents()                                             ;
    if (NotNull(uid)) uid->fbApplyButton->setEnabled(true)            ;
    if (NotNull(uip)) uip->fbApplyButton->setEnabled(true)            ;
  } else                                                              {
    if (NotNull(uid)) uid->fbApplyButton->setEnabled(false)           ;
    if (NotNull(uip)) uip->fbApplyButton->setEnabled(false)           ;
  }                                                                   ;
}

void N::SqlConfigurator::TestODBC(void)
{
  Sql sql                                                          ;
  nDropOut ( !ObtainODBC(sql) )                                    ;
  ///////////////////////////////////////////////////////////////////////
  QString Q = tr("Test ODBC %1 connection").arg(sql.Profile)          ;
  plan->Talk        (Q)                                               ;
  plan->showMessage (Q)                                               ;
  plan->processEvents()                                               ;
  SqlConnection SC(sql)                                              ;
  bool successful = false                                             ;
  if (SC.open("DatabaseConfigurator","TestODBC"))                     {
    bool connectivity = false                                         ;
    Q = tr("ODBC %1 is connected").arg(sql.Profile)                   ;
    plan->Talk        (Q)                                             ;
    plan->showMessage (Q)                                             ;
    plan->processEvents()                                             ;
    Q = tr("Test creating tables and paraments")                      ;
    plan->Talk        (Q)                                             ;
    plan->showMessage (Q)                                             ;
    plan->processEvents()                                             ;
    Q = "create table DatabaseConfiguratorTestODBC ("
        " id integer primary key,"
        " ltime timestamp"
        ");"                                                          ;
    if (SC.Query(Q))                                                  {
      connectivity = true                                             ;
    } else Notify(SC.q.lastError().text())                            ;
    if (connectivity)                                                 {
      Q = "drop table DatabaseConfiguratorTestODBC ;"                 ;
      if (SC.Query(Q))                                                {
        successful = true                                             ;
      } else connectivity = false                                     ;
    }                                                                 ;
    if (successful)                                                   {
      Q = "create table TestOdbcIndex ("
          " id integer primary key,"
          " uuid bigint not null,"
          " ltime timestamp default CURRENT_TIMESTAMP,"
          " unique (uuid)"
          ");"                                                        ;
      if (SC.Query(Q))                                                {
        connectivity = true                                           ;
      } else                                                          {
        Notify(SC.q.lastError().text())                               ;
        connectivity = false                                          ;
      }                                                               ;
      if (connectivity) {
        Q = "create table TestOdbcForeignKey ("
            " id integer primary key,"
            " uuid bigint not null,"
            " ltime timestamp default CURRENT_TIMESTAMP,"
            " foreign key (uuid) references TestOdbcIndex(uuid)"
            ");"                                                      ;
        if (SC.Query(Q))                                              {
          connectivity = true                                         ;
        } else                                                        {
          Notify(SC.q.lastError().text())                             ;
          connectivity = false                                        ;
        }                                                             ;
      }                                                               ;
      if (!SC.Query("drop table TestOdbcForeignKey ;"))               {
        successful = false                                            ;
      }                                                               ;
      if (!SC.Query("drop table TestOdbcIndex ;"))                    {
        successful = false                                            ;
      }                                                               ;
    }                                                                 ;
    if (!successful)                                                  {
      Q = tr("ODBC %1 operation is not correct").arg(sql.Profile)     ;
      plan->Talk        (Q)                                           ;
      plan->showMessage (Q)                                           ;
      plan->processEvents()                                           ;
    }                                                                 ;
    SC.close()                                                        ;
  } else                                                              {
    Q = tr("ODBC %1 can not connect").arg(sql.Profile)                ;
    plan->Talk        (Q)                                             ;
    plan->showMessage (Q)                                             ;
    plan->processEvents()                                             ;
  }                                                                   ;
  SC.remove()                                                         ;
  if (successful)                                                     {
    Q = tr("ODBC %1 is successful").arg(sql.Profile)                  ;
    plan->Talk        (Q)                                             ;
    plan->showMessage (Q)                                             ;
    plan->processEvents()                                             ;
    if (NotNull(uid)) uid->ocApplyButton->setEnabled(true)            ;
    if (NotNull(uip)) uip->ocApplyButton->setEnabled(true)            ;
  } else                                                              {
    if (NotNull(uid)) uid->ocApplyButton->setEnabled(false)           ;
    if (NotNull(uip)) uip->ocApplyButton->setEnabled(false)           ;
  }                                                                   ;
}

void N::SqlConfigurator::TestSQLite(void)
{
  Sql sql                                                             ;
  nDropOut ( !ObtainSQLite(sql) )                                     ;
  /////////////////////////////////////////////////////////////////////
  QString Q = tr("Test SQLite %1 connection").arg(sql.Profile)        ;
  plan->Talk        (Q)                                               ;
  plan->showMessage (Q)                                               ;
  plan->processEvents()                                               ;
  SqlConnection SC(sql)                                               ;
  bool successful = false                                             ;
  if (SC.open("DatabaseConfigurator","TestSQLite"))                   {
    bool connectivity = false                                         ;
    Q = tr("SQLite %1 is connected").arg(sql.Profile)                 ;
    plan->Talk        (Q)                                             ;
    plan->showMessage (Q)                                             ;
    plan->processEvents()                                             ;
    Q = tr("Test creating tables and paraments")                      ;
    plan->Talk        (Q)                                             ;
    plan->showMessage (Q)                                             ;
    plan->processEvents()                                             ;
    Q = "create table DatabaseConfiguratorTestSQLITE ("
        " id integer primary key,"
        " ltime timestamp"
        ");"                                                          ;
    if (SC.Query(Q))                                                  {
      connectivity = true                                             ;
    } else Notify(SC.q.lastError().text())                            ;
    if (connectivity)                                                 {
      Q = "drop table DatabaseConfiguratorTestSQLITE ;"               ;
      if (SC.Query(Q))                                                {
        successful = true                                             ;
      } else connectivity = false                                     ;
    }                                                                 ;
    if (successful)                                                   {
      Q = "create table TestSQLiteIndex ("
          " id integer primary key autoincrement,"
          " uuid bigint not null,"
          " ltime timestamp,"
          " unique (uuid)"
          ");"                                                        ;
      if (SC.Query(Q))                                                {
        connectivity = true                                           ;
      } else                                                          {
        Notify(SC.q.lastError().text())                               ;
        connectivity = false                                          ;
      }                                                               ;
      if (connectivity) {
        Q = "create table TestSQLiteForeignKey ("
            " id integer primary key autoincrement,"
            " uuid bigint not null,"
            " ltime timestamp,"
            " foreign key (uuid) references TestSQLiteIndex(uuid)"
            ");"                                                      ;
        if (SC.Query(Q))                                              {
          connectivity = true                                         ;
        } else {
          Notify(SC.q.lastError().text())                             ;
          connectivity = false                                        ;
        }                                                             ;
      }                                                               ;
      if (!SC.Query("drop table TestSQLiteForeignKey ;"))             {
        successful = false                                            ;
      }                                                               ;
      if (!SC.Query("drop table TestSQLiteIndex ;"))                  {
        successful = false                                            ;
      }                                                               ;
    }                                                                 ;
    if (!successful)                                                  {
      Q = tr("SQLite %1 operation is not correct").arg(sql.Profile)   ;
      plan->Talk        (Q)                                           ;
      plan->showMessage (Q)                                           ;
      plan->processEvents()                                           ;
    }                                                                 ;
    SC.close()                                                        ;
  } else                                                              {
    Q = tr("SQLite %1 can not connect").arg(sql.Profile)              ;
    plan->Talk        (Q)                                             ;
    plan->showMessage (Q)                                             ;
    plan->processEvents()                                             ;
  }                                                                   ;
  SC.remove()                                                         ;
  if (successful)                                                     {
    Q = tr("SQLite %1 is successful").arg(sql.Profile)                ;
    plan->Talk        (Q)                                             ;
    plan->showMessage (Q)                                             ;
    plan->processEvents()                                             ;
    if (NotNull(uid)) uid->sqApplyButton->setEnabled(true)            ;
    if (NotNull(uip)) uip->sqApplyButton->setEnabled(true)            ;
  } else                                                              {
    if (NotNull(uid)) uid->sqApplyButton->setEnabled(false)           ;
    if (NotNull(uip)) uip->sqApplyButton->setEnabled(false)           ;
  }                                                                   ;
}

void N::SqlConfigurator::ApplyMySQL(void)
{
  nDropOut   ( !ObtainMySQL(PrivateSql) ) ;
  emit apply ( this , &PrivateSql       ) ;
  emit apply ( uuid , &PrivateSql       ) ;
}

void N::SqlConfigurator::ApplyPostgreSQL(void)
{
  nDropOut   ( !ObtainPostgreSQL(PrivateSql) ) ;
  emit apply ( this , &PrivateSql            ) ;
  emit apply ( uuid , &PrivateSql            ) ;
}

void N::SqlConfigurator::ApplyFirebird(void)
{
  nDropOut   ( !ObtainFirebird(PrivateSql) ) ;
  emit apply ( this , &PrivateSql          ) ;
  emit apply ( uuid , &PrivateSql          ) ;
}

void N::SqlConfigurator::ApplyODBC(void)
{
  nDropOut   ( !ObtainODBC(PrivateSql) ) ;
  emit apply ( this , &PrivateSql      ) ;
  emit apply ( uuid , &PrivateSql      ) ;
}

void N::SqlConfigurator::ApplySQLite(void)
{
  nDropOut   ( !ObtainSQLite(PrivateSql) ) ;
  emit apply ( this , &PrivateSql        ) ;
  emit apply ( uuid , &PrivateSql        ) ;
}

void N::SqlConfigurator::StringMySQL(QString text)
{ Q_UNUSED ( text )                       ;
  bool valid = false                      ;
  Sql  sql                                ;
  valid = ObtainMySQL(sql)                ;
  if (NotNull(uid))                       {
    uid->myTestButton ->setEnabled(valid) ;
    uid->myApplyButton->setEnabled(false) ;
  }                                       ;
  if (NotNull(uip))                       {
    uip->myTestButton ->setEnabled(valid) ;
    uip->myApplyButton->setEnabled(false) ;
  }                                       ;
}

void N::SqlConfigurator::StringPostgreSQL(QString text)
{ Q_UNUSED ( text )                       ;
  bool valid = false                      ;
  Sql  sql                                ;
  valid = ObtainPostgreSQL(sql)           ;
  if (NotNull(uid))                       {
    uid->pqTestButton ->setEnabled(valid) ;
    uid->pqApplyButton->setEnabled(false) ;
  }                                       ;
  if (NotNull(uip))                       {
    uip->pqTestButton ->setEnabled(valid) ;
    uip->pqApplyButton->setEnabled(false) ;
  }                                       ;
}

void N::SqlConfigurator::StringFirebird(QString text)
{ Q_UNUSED ( text )                       ;
  bool valid = false                      ;
  Sql  sql                                ;
  valid = ObtainFirebird(sql)             ;
  if (NotNull(uid))                       {
    uid->fbTestButton ->setEnabled(valid) ;
    uid->fbApplyButton->setEnabled(false) ;
  }                                       ;
  if (NotNull(uip))                       {
    uip->fbTestButton ->setEnabled(valid) ;
    uip->fbApplyButton->setEnabled(false) ;
  }                                       ;
}

void N::SqlConfigurator::StringODBC(QString text)
{ Q_UNUSED ( text )                       ;
  bool valid = false                      ;
  Sql  sql                                ;
  valid = ObtainODBC(sql)                 ;
  if (NotNull(uid))                       {
    uid->ocTestButton ->setEnabled(valid) ;
    uid->ocApplyButton->setEnabled(false) ;
  }                                       ;
  if (NotNull(uip))                       {
    uip->ocTestButton ->setEnabled(valid) ;
    uip->ocApplyButton->setEnabled(false) ;
  }                                       ;
}

void N::SqlConfigurator::StringSQLite(QString text)
{ Q_UNUSED ( text )                       ;
  bool valid = false                      ;
  Sql  sql                                ;
  valid = ObtainSQLite(sql)               ;
  if (NotNull(uid))                       {
    uid->sqTestButton ->setEnabled(valid) ;
    uid->sqApplyButton->setEnabled(false) ;
  }                                       ;
  if (NotNull(uip))                       {
    uip->sqTestButton ->setEnabled(valid) ;
    uip->sqApplyButton->setEnabled(false) ;
  }                                       ;
}

void N::SqlConfigurator::BrowseFirebird(void)
{
  QString filename = QFileDialog::getSaveFileName      (
                       this                            ,
                       tr("Firebird database file")    ,
                       "","*.*"                      ) ;
  if (filename.length()<=0) return                     ;
  if (NotNull(uid)) uid->fbFileEdit->setText(filename) ;
  if (NotNull(uip)) uip->fbFileEdit->setText(filename) ;
}

void N::SqlConfigurator::BrowseSQLite(void)
{
  QString filename = QFileDialog::getSaveFileName      (
                       this                            ,
                       tr("SQLite database file")      ,
                       "","*.*"                      ) ;
  if (filename.length()<=0) return                     ;
  if (NotNull(uid)) uid->sqFileEdit->setText(filename) ;
  if (NotNull(uip)) uip->sqFileEdit->setText(filename) ;
}

bool N::SqlConfigurator::ObtainMySQL(Sql & sql)
{
  bool valid = false                                     ;
  sql   . SqlMode      = ""                              ;
  if (NotNull(uid))                                      {
    sql . SqlMode      = "MYSQL"                         ;
    sql . Profile      = uid->myProfileEdit->text()      ;
    sql . Hostname     = uid->myHostEdit   ->text()      ;
    sql . Username     = uid->myUserEdit   ->text()      ;
    sql . Password     = uid->myPassEdit   ->text()      ;
    sql . dbName       = uid->mySchemeEdit ->text()      ;
    sql . Options      = uid->myOptionEdit ->text()      ;
    sql . Indexing     = uid->myIndexBox   ->isChecked() ;
    sql . isForeignKey = uid->myForeignBox ->isChecked() ;
  }                                                      ;
  if (NotNull(uip))                                      {
    sql . SqlMode      = "MYSQL"                         ;
    sql . Profile      = uip->myProfileEdit->text()      ;
    sql . Hostname     = uip->myHostEdit   ->text()      ;
    sql . Username     = uip->myUserEdit   ->text()      ;
    sql . Password     = uip->myPassEdit   ->text()      ;
    sql . dbName       = uip->mySchemeEdit ->text()      ;
    sql . Options      = uip->myOptionEdit ->text()      ;
    sql . Indexing     = uip->myIndexBox   ->isChecked() ;
    sql . isForeignKey = uip->myForeignBox ->isChecked() ;
  }                                                      ;
  if (sql.Profile.length()>0) valid = true               ;
  if (valid) valid = sql.isValid()                       ;
  return valid                                           ;
}

bool N::SqlConfigurator::ObtainPostgreSQL(Sql & sql)
{
  bool valid = false                                     ;
  sql   . SqlMode      = ""                              ;
  if (NotNull(uid))                                      {
    sql . SqlMode      = "PQSQL"                         ;
    sql . Profile      = uid->pqProfileEdit->text()      ;
    sql . Hostname     = uid->pqHostEdit   ->text()      ;
    sql . Username     = uid->pqUserEdit   ->text()      ;
    sql . Password     = uid->pqPassEdit   ->text()      ;
    sql . dbName       = uid->pqSchemeEdit ->text()      ;
    sql . Options      = uid->pqOptionEdit ->text()      ;
    sql . Indexing     = uid->pqIndexBox   ->isChecked() ;
    sql . isForeignKey = uid->pqForeignBox ->isChecked() ;
  }                                                      ;
  if (NotNull(uip))                                      {
    sql . SqlMode      = "PQSQL"                         ;
    sql . Profile      = uip->pqProfileEdit->text()      ;
    sql . Hostname     = uip->pqHostEdit   ->text()      ;
    sql . Username     = uip->pqUserEdit   ->text()      ;
    sql . Password     = uip->pqPassEdit   ->text()      ;
    sql . dbName       = uip->pqSchemeEdit ->text()      ;
    sql . Options      = uip->pqOptionEdit ->text()      ;
    sql . Indexing     = uip->pqIndexBox   ->isChecked() ;
    sql . isForeignKey = uip->pqForeignBox ->isChecked() ;
  }                                                      ;
  if (sql.Profile.length()>0) valid = true               ;
  if (valid) valid = sql.isValid()                       ;
  return valid                                           ;
}

bool N::SqlConfigurator::ObtainFirebird(Sql & sql)
{
  bool valid = false                                     ;
  sql   . SqlMode      = ""                              ;
  if (NotNull(uid))                                      {
    sql . SqlMode      = "FireBird"                      ;
    sql . Profile      = uid->fbProfileEdit->text()      ;
    sql . Hostname     = ""                              ;
    sql . Username     = uid->fbUserEdit   ->text()      ;
    sql . Password     = uid->fbPassEdit   ->text()      ;
    sql . dbName       = uid->fbFileEdit   ->text()      ;
    sql . Options      = uid->fbOptionEdit ->text()      ;
    sql . Indexing     = uid->fbIndexBox   ->isChecked() ;
    sql . isForeignKey = uid->fbForeignBox ->isChecked() ;
  }                                                      ;
  if (NotNull(uip))                                      {
    sql . SqlMode      = "FireBird"                      ;
    sql . Profile      = uip->fbProfileEdit->text()      ;
    sql . Hostname     = ""                              ;
    sql . Username     = uip->fbUserEdit   ->text()      ;
    sql . Password     = uip->fbPassEdit   ->text()      ;
    sql . dbName       = uip->fbFileEdit   ->text()      ;
    sql . Options      = uip->fbOptionEdit ->text()      ;
    sql . Indexing     = uip->fbIndexBox   ->isChecked() ;
    sql . isForeignKey = uip->fbForeignBox ->isChecked() ;
  }                                                      ;
  if (sql.Profile.length()>0) valid = true               ;
  if (valid) valid = sql.isValid()                       ;
  return valid                                           ;
}

bool N::SqlConfigurator::ObtainODBC(Sql & sql)
{
  bool valid = false                                     ;
  sql   . SqlMode      = ""                              ;
  if (NotNull(uid))                                      {
    sql . SqlMode      = "ODBC"                          ;
    sql . Profile      = uid->ocProfileEdit->text()      ;
    sql . Hostname     = uid->ocHostEdit   ->text()      ;
    sql . Username     = uid->ocUserEdit   ->text()      ;
    sql . Password     = uid->ocPassEdit   ->text()      ;
    sql . dbName       = uid->ocSchemeEdit ->text()      ;
    sql . Options      = uid->ocOptionEdit ->text()      ;
    sql . Indexing     = uid->ocIndexBox   ->isChecked() ;
    sql . isForeignKey = uid->ocForeignBox ->isChecked() ;
  }                                                      ;
  if (NotNull(uip))                                      {
    sql . SqlMode      = "ODBC"                          ;
    sql . Profile      = uip->ocProfileEdit->text()      ;
    sql . Hostname     = uip->ocHostEdit   ->text()      ;
    sql . Username     = uip->ocUserEdit   ->text()      ;
    sql . Password     = uip->ocPassEdit   ->text()      ;
    sql . dbName       = uip->ocSchemeEdit ->text()      ;
    sql . Options      = uip->ocOptionEdit ->text()      ;
    sql . Indexing     = uip->ocIndexBox   ->isChecked() ;
    sql . isForeignKey = uip->ocForeignBox ->isChecked() ;
  }                                                      ;
  if (sql.Profile.length()>0) valid = true               ;
  if (valid) valid = sql.isValid()                       ;
  return valid                                           ;
}

bool N::SqlConfigurator::ObtainSQLite(Sql & sql)
{
  bool valid = false                                     ;
  sql   . SqlMode      = ""                              ;
  if (NotNull(uid))                                      {
    sql . SqlMode      = "SQLITE"                        ;
    sql . Profile      = uid->sqProfileEdit->text()      ;
    sql . Hostname     = ""                              ;
    sql . Username     = ""                              ;
    sql . Password     = ""                              ;
    sql . dbName       = uid->sqFileEdit   ->text()      ;
    sql . Options      = uid->sqOptionEdit ->text()      ;
    sql . Indexing     = uid->sqIndexBox   ->isChecked() ;
    sql . isForeignKey = uid->sqForeignBox ->isChecked() ;
  }                                                      ;
  if (NotNull(uip))                                      {
    sql . SqlMode      = "SQLITE"                        ;
    sql . Profile      = uip->sqProfileEdit->text()      ;
    sql . Hostname     = ""                              ;
    sql . Username     = ""                              ;
    sql . Password     = ""                              ;
    sql . dbName       = uip->sqFileEdit   ->text()      ;
    sql . Options      = uip->sqOptionEdit ->text()      ;
    sql . Indexing     = uip->sqIndexBox   ->isChecked() ;
    sql . isForeignKey = uip->sqForeignBox ->isChecked() ;
  }                                                      ;
  if (sql.Profile.length()>0) valid = true               ;
  if (valid) valid = sql.isValid()                       ;
  return valid                                           ;
}

void N::SqlConfigurator::set(Sql & sql)
{
  if (sql.isMySQL   ())                                   {
    if (NotNull(uid))                                     {
      uid->myProfileEdit->setText    (sql . Profile     ) ;
      uid->myHostEdit   ->setText    (sql . Hostname    ) ;
      uid->myUserEdit   ->setText    (sql . Username    ) ;
      uid->myPassEdit   ->setText    (sql . Password    ) ;
      uid->mySchemeEdit ->setText    (sql . dbName      ) ;
      uid->myOptionEdit ->setText    (sql . Options     ) ;
      uid->myIndexBox   ->setChecked (sql . Indexing    ) ;
      uid->myForeignBox ->setChecked (sql . isForeignKey) ;
    }                                                     ;
    if (NotNull(uip))                                     {
      uip->myProfileEdit->setText    (sql . Profile     ) ;
      uip->myHostEdit   ->setText    (sql . Hostname    ) ;
      uip->myUserEdit   ->setText    (sql . Username    ) ;
      uip->myPassEdit   ->setText    (sql . Password    ) ;
      uip->mySchemeEdit ->setText    (sql . dbName      ) ;
      uip->myOptionEdit ->setText    (sql . Options     ) ;
      uip->myIndexBox   ->setChecked (sql . Indexing    ) ;
      uip->myForeignBox ->setChecked (sql . isForeignKey) ;
    }                                                     ;
    MySQL      ()                                         ;
  } else
  if (sql.isPQSQL   ())                                   {
    if (NotNull(uid))                                     {
      uid->pqProfileEdit->setText    (sql . Profile     ) ;
      uid->pqHostEdit   ->setText    (sql . Hostname    ) ;
      uid->pqUserEdit   ->setText    (sql . Username    ) ;
      uid->pqPassEdit   ->setText    (sql . Password    ) ;
      uid->pqSchemeEdit ->setText    (sql . dbName      ) ;
      uid->pqOptionEdit ->setText    (sql . Options     ) ;
      uid->pqIndexBox   ->setChecked (sql . Indexing    ) ;
      uid->pqForeignBox ->setChecked (sql . isForeignKey) ;
    }                                                     ;
    if (NotNull(uip))                                     {
      uip->pqProfileEdit->setText    (sql . Profile     ) ;
      uip->pqHostEdit   ->setText    (sql . Hostname    ) ;
      uip->pqUserEdit   ->setText    (sql . Username    ) ;
      uip->pqPassEdit   ->setText    (sql . Password    ) ;
      uip->pqSchemeEdit ->setText    (sql . dbName      ) ;
      uip->pqOptionEdit ->setText    (sql . Options     ) ;
      uip->pqIndexBox   ->setChecked (sql . Indexing    ) ;
      uip->pqForeignBox ->setChecked (sql . isForeignKey) ;
    }                                                     ;
    PostgreSQL ()                                         ;
  } else
  if (sql.isFireBird())                                   {
    if (NotNull(uid))                                     {
      uid->fbProfileEdit->setText    (sql . Profile     ) ;
      uid->fbUserEdit   ->setText    (sql . Username    ) ;
      uid->fbPassEdit   ->setText    (sql . Password    ) ;
      uid->fbFileEdit   ->setText    (sql . dbName      ) ;
      uid->fbOptionEdit ->setText    (sql . Options     ) ;
      uid->fbIndexBox   ->setChecked (sql . Indexing    ) ;
      uid->fbForeignBox ->setChecked (sql . isForeignKey) ;
    }                                                     ;
    if (NotNull(uip))                                     {
      uip->fbProfileEdit->setText    (sql . Profile     ) ;
      uip->fbUserEdit   ->setText    (sql . Username    ) ;
      uip->fbPassEdit   ->setText    (sql . Password    ) ;
      uip->fbFileEdit   ->setText    (sql . dbName      ) ;
      uip->fbOptionEdit ->setText    (sql . Options     ) ;
      uip->fbIndexBox   ->setChecked (sql . Indexing    ) ;
      uip->fbForeignBox ->setChecked (sql . isForeignKey) ;
    }                                                     ;
    Firebird   ()                                         ;
  } else
  if (sql.isODBC    ())                                   {
    if (NotNull(uid))                                     {
      uid->ocProfileEdit->setText    (sql . Profile     ) ;
      uid->ocHostEdit   ->setText    (sql . Hostname    ) ;
      uid->ocUserEdit   ->setText    (sql . Username    ) ;
      uid->ocPassEdit   ->setText    (sql . Password    ) ;
      uid->ocSchemeEdit ->setText    (sql . dbName      ) ;
      uid->ocOptionEdit ->setText    (sql . Options     ) ;
      uid->ocIndexBox   ->setChecked (sql . Indexing    ) ;
      uid->ocForeignBox ->setChecked (sql . isForeignKey) ;
    }                                                     ;
    if (NotNull(uip))                                     {
      uip->ocProfileEdit->setText    (sql . Profile     ) ;
      uip->ocHostEdit   ->setText    (sql . Hostname    ) ;
      uip->ocUserEdit   ->setText    (sql . Username    ) ;
      uip->ocPassEdit   ->setText    (sql . Password    ) ;
      uip->ocSchemeEdit ->setText    (sql . dbName      ) ;
      uip->ocOptionEdit ->setText    (sql . Options     ) ;
      uip->ocIndexBox   ->setChecked (sql . Indexing    ) ;
      uip->ocForeignBox ->setChecked (sql . isForeignKey) ;
    }                                                     ;
    ODBC       ()                                         ;
  } else
  if (sql.isSQLITE  ())                                   {
    if (NotNull(uid))                                     {
      uid->sqProfileEdit->setText    (sql . Profile     ) ;
      uid->sqFileEdit   ->setText    (sql . dbName      ) ;
      uid->sqOptionEdit ->setText    (sql . Options     ) ;
      uid->sqIndexBox   ->setChecked (sql . Indexing    ) ;
      uid->sqForeignBox ->setChecked (sql . isForeignKey) ;
    }                                                     ;
    if (NotNull(uip))                                     {
      uip->sqProfileEdit->setText    (sql . Profile     ) ;
      uip->sqFileEdit   ->setText    (sql . dbName      ) ;
      uip->sqOptionEdit ->setText    (sql . Options     ) ;
      uip->sqIndexBox   ->setChecked (sql . Indexing    ) ;
      uip->sqForeignBox ->setChecked (sql . isForeignKey) ;
    }                                                     ;
    SQLite     ()                                         ;
  }                                                       ;
}
