#include <qtcomponents.h>

N::FileDeputy:: FileDeputy (Plan * p)
              : FilePlan   (       p)
{
}

N::FileDeputy::~FileDeputy (void)
{
}

QStringList N::FileDeputy::Scan      (
               bool      & keepGoing ,
               QString     message   ,
               QStringList startDirs )
{
  QStringList    Dirs  = startDirs                            ;
  int            index = 0                                    ;
  QFileInfoList  fil                                          ;
  QProgressBar * P = FilePlan->Progress (message)             ;
  if (Dirs.count()<=0)                                        {
    fil = QDir::drives()                                      ;
    for (int i=0;i<fil.count();i++)                           {
      Dirs << fil[i].absoluteFilePath()                       ;
    }                                                         ;
  }                                                           ;
  do                                                          {
    QString f = Dirs[index]                                   ;
    QDir    d (f)                                             ;
    P -> setRange (0,Dirs.count())                            ;
    P -> setValue (index+1       )                            ;
    FilePlan->showMessage (f)                                 ;
    FilePlan->processEvents()                                 ;
    fil = d.entryInfoList(QDir::AllDirs|QDir::NoDotAndDotDot) ;
    for (int i=0;i<fil.count();i++)                           {
      QString l = fil[i].absoluteFilePath()                   ;
      if (!Dirs.contains(l)) Dirs << l                        ;
    }                                                         ;
    index++                                                   ;
  } while (keepGoing && index<Dirs.count())                   ;
  P -> setRange    (0,Dirs.count())                           ;
  P -> setValue    (index+1       )                           ;
  P -> hide        (              )                           ;
  P -> deleteLater (              )                           ;
  return Dirs                                                 ;
}

QStringList N::FileDeputy::Scan(QToolButton * keepGoing,QString message,QStringList startDirs)
{
  QStringList    Dirs  = startDirs                            ;
  int            index = 0                                    ;
  QFileInfoList  fil                                          ;
  QProgressBar * P = FilePlan->Progress (message)             ;
  if (Dirs.count()<=0)                                        {
    fil = QDir::drives()                                      ;
    for (int i=0;i<fil.count();i++)                           {
      Dirs << fil[i].absoluteFilePath()                       ;
    }                                                         ;
  }                                                           ;
  do                                                          {
    QString f = Dirs[index]                                   ;
    QDir    d (f)                                             ;
    P -> setRange (0,Dirs.count())                            ;
    P -> setValue (index+1       )                            ;
    FilePlan->showMessage (f)                                 ;
    FilePlan->processEvents()                                 ;
    fil = d.entryInfoList(QDir::AllDirs|QDir::NoDotAndDotDot) ;
    for (int i=0;i<fil.count();i++)                           {
      QString l = fil[i].absoluteFilePath()                   ;
      if (!Dirs.contains(l)) Dirs << l                        ;
    }                                                         ;
    index++                                                   ;
  } while (keepGoing->isChecked() && index<Dirs.count())      ;
  P -> setRange    (0,Dirs.count())                           ;
  P -> setValue    (index+1       )                           ;
  P -> hide        (              )                           ;
  P -> deleteLater (              )                           ;
  return Dirs                                                 ;
}

QStringList N::FileDeputy::Scan(bool & keepGoing,QString message,QStringList filters,QStringList & Dirs)
{
  QStringList    files                                        ;
  int            index = 0                                    ;
  QFileInfoList  fil                                          ;
  QProgressBar * P = FilePlan->Progress (message)             ;
  P -> setRange (0,Dirs.count())                              ;
  do                                                          {
    QString f = Dirs[index]                                   ;
    QDir    d (f)                                             ;
    P -> setValue (index+1)                                   ;
    FilePlan->showMessage (f)                                 ;
    FilePlan->processEvents()                                 ;
    fil = d.entryInfoList(filters)                            ;
    for (int i=0;i<fil.count();i++)                           {
      QString l = fil[i].absoluteFilePath()                   ;
      if (!files.contains(l)) files << l                      ;
    }                                                         ;
    index++                                                   ;
  } while (keepGoing && index<Dirs.count())                   ;
  P -> setRange    (0,Dirs.count())                           ;
  P -> setValue    (index+1       )                           ;
  P -> hide        (              )                           ;
  P -> deleteLater (              )                           ;
  return      files                                           ;
}

QStringList N::FileDeputy :: Scan      (
               QToolButton * keepGoing ,
               QString       message   ,
               QStringList   filters   ,
               QStringList & Dirs      )
{
  QStringList    files                                        ;
  int            index = 0                                    ;
  QFileInfoList  fil                                          ;
  QProgressBar * P = FilePlan->Progress (message)             ;
  P -> setRange (0,Dirs.count())                              ;
  do                                                          {
    QString f = Dirs[index]                                   ;
    QDir    d (f)                                             ;
    P -> setValue (index+1)                                   ;
    FilePlan->showMessage (f)                                 ;
    FilePlan->processEvents()                                 ;
    fil = d.entryInfoList(filters)                            ;
    for (int i=0;i<fil.count();i++)                           {
      QString l = fil[i].absoluteFilePath()                   ;
      if (!files.contains(l)) files << l                      ;
    }                                                         ;
    index++                                                   ;
  } while (keepGoing->isChecked() && index<Dirs.count())      ;
  P -> setRange    (0,Dirs.count())                           ;
  P -> setValue    (index+1       )                           ;
  P -> hide        (              )                           ;
  P -> deleteLater (              )                           ;
  return      files                                           ;
}
