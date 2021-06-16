#include <qtcomponents.h>

typedef struct     {
  N::Plan * plan   ;
  QWidget * widget ;
} ExtraPacket      ;

N::GeneralDispatcher:: GeneralDispatcher ( QObject * parent )
                     : QObject           (           parent )
                     , SyntaxDispatcher  (                  )
                     , UuidSyntax        (                  )
{
}

N::GeneralDispatcher::~GeneralDispatcher (void)
{
}

int N::GeneralDispatcher::type(void) const
{
  return CiosMenuId ( 51 , 0 , 1 ) ;
}

void N::GeneralDispatcher::Help(QStringList & help)
{
  help << tr("===== General dispatcher commands =====") ;
  help << QString("set general variable name value : %1").arg(tr("set variable into name")) ;
  help << QString("show general variables : %1"         ).arg(tr("show variables")) ;
  help << QString("optimize groups position : %1"       ).arg(tr("optimize groups relation")) ;
  help << QString("inches [length] to cgs : %1"         ).arg(tr("convert inches to cm")) ;
  help << QString("cgs [length] to inches : %1"         ).arg(tr("convert cm to inches")) ;
  help << QString("cpu : %1"                            ).arg(tr("show cpu features")) ;
}

int N::GeneralDispatcher::matching(QString cmd)
{
  QStringList C = CommandTokens ( cmd )                                      ;
  ////////////////////////////////////////////////////////////////////////////
  command    = cmd                                                           ;
  arguments  . clear ( )                                                     ;
  arguments <= C                                                             ;
  ////////////////////////////////////////////////////////////////////////////
  if ( ( C . count ( ) >2 ) && ( "optimize" == C [ 0 ] . toLower ( ) ) )     {
    if ( "groups" == C [ 1 ] . toLower ( ) )                                 {
      if ( "position" == C [ 2 ] . toLower ( ) )                             {
        return CiosMenuId ( 51 , 1 ,  1 )                                    ;
      }                                                                      ;
    }                                                                        ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( ( C . count ( ) == 5 ) && ( "set" == C [ 0 ] . toLower ( ) )        ) {
    if ( "general" == C [ 1 ] . toLower ( )                                ) {
      if ( ( "variable" == C [ 2 ] . toLower ( ) )  )                        {
        return CiosMenuId ( 51 , 2 , 1 )                                     ;
      }                                                                      ;
    }                                                                        ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( ( C . count ( ) == 3 ) && ( "show" == C [ 0 ] . toLower ( ) )       ) {
    if ( "general" == C [ 1 ] . toLower ( )                                ) {
      if ( ( "variables" == C [ 2 ] . toLower ( ) )  )                       {
        return CiosMenuId ( 51 , 2 , 2 )                                     ;
      }                                                                      ;
    }                                                                        ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( ( C . count ( ) == 4 ) && ( "inches" == C [ 0 ] . toLower ( ) ) )     {
    if ( ( "to"  == C [ 2 ] . toLower ( ) )                                 &&
         ( "cgs" == C [ 3 ] . toLower ( ) )                                ) {
      return CiosMenuId ( 51 , 3 , 1 )                                       ;
    }                                                                        ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( ( C . count ( ) == 4 ) && ( "cgs" == C [ 0 ] . toLower ( ) ) )        {
    if ( ( "to"     == C [ 2 ] . toLower ( ) )                              &&
         ( "inches" == C [ 3 ] . toLower ( ) )                             ) {
      return CiosMenuId ( 51 , 3 , 2 )                                       ;
    }                                                                        ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  if ( ( C . count ( ) == 1 ) && ( "cpu" == C [ 0 ] . toLower ( ) ) )        {
    return CiosMenuId ( 51 , 3 , 3 )                                         ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  return 0                                                                   ;
}

bool N::GeneralDispatcher::execute(int id)
{
  switch ( id )                      {
    case CiosMenuId  ( 51 , 1 ,  1 ) :
      GroupsPosition (             ) ;
    return true                      ;
    case CiosMenuId  ( 51 , 2 ,  1 ) :
      setVariable    (             ) ;
    return true                      ;
    case CiosMenuId  ( 51 , 2 ,  2 ) :
      showVariables  (             ) ;
    return true                      ;
    case CiosMenuId  ( 51 , 3 ,  1 ) :
      InchesToCGS    (             ) ;
    return true                      ;
    case CiosMenuId  ( 51 , 3 ,  2 ) :
      CGSToInches    (             ) ;
    return true                      ;
    case CiosMenuId  ( 51 , 3 ,  3 ) :
      ShowCPU        (             ) ;
    return true                      ;
  }                                  ;
  return false                       ;
}

void N::GeneralDispatcher::setExtras(void * data)
{
  ExtraPacket * ep = (ExtraPacket *) data ;
  QWidget     * ww = ep -> widget         ;
  plan = ep -> plan                       ;
}

void N::GeneralDispatcher::setVariable(void)
{
  if ( arguments . count ( ) != 5 ) return       ;
  QString n = arguments [ 3 ] . toString ( )     ;
  QString v = arguments [ 4 ] . toString ( )     ;
  Variables [ n ] = arguments [ 4 ]              ;
  Report ( QString("%1 => %2\n").arg(n).arg(v) ) ;
}

void N::GeneralDispatcher::showVariables(void)
{
  QStringList K = Variables . keys ( )             ;
  QString     k                                    ;
  QString     v                                    ;
  foreach ( k , K )                                {
    v = Variables [ k ] . toString ( )             ;
    Report ( QString("%1 => %2\n").arg(k).arg(v) ) ;
  }                                                ;
}

void N::GeneralDispatcher::GroupsPosition(void)
{
  SqlConnection SC ( plan -> sql )                                 ;
  if (SC.open("VideoCLI","GroupsPosition"))                        {
    QString Q                                                      ;
    QString T                                                      ;
    Q = SC . sql . Use ( "depot" )                                 ;
    SC . Query         ( Q       )                                 ;
    for (int i=1;i<=100;i++)                                       {
      T = QString("G00%1%2%3").arg(i/100).arg((i/10)%10).arg(i%10) ;
      Q = SC.sql.SelectFrom                                        (
            "id"                                                   ,
            T                                                      ,
            QString ( "%1 %2"                                      )
            . arg ( SC.OrderByDesc("id")                           )
            . arg ( SC.sql.Limit(0,1)                          ) ) ;
      if (SC.Fetch(Q))                                             {
        int id = SC . Int ( 0 )                                    ;
        if (id>0)                                                  {
          Report ( T    )                                          ;
          Report ( "\n" )                                          ;
          plan -> processEvents ( )                                ;
          Q = QString ( "alter table `%1` auto_increment = %2 ;"   )
              . arg   ( T                                          )
              . arg   ( id                                       ) ;
          SC  . Query ( Q                                        ) ;
        }                                                          ;
      }                                                            ;
    }                                                              ;
    ////////////////////////////////////////////////////////////////
    SC.close()                                                     ;
  }                                                                ;
  SC.remove()                                                      ;
}

void N::GeneralDispatcher::InchesToCGS(void)
{
  QString     inches                                     ;
  QString     I                                          ;
  QStringList L                                          ;
  ////////////////////////////////////////////////////////
  inches = arguments [ 1 ] . toString ( )                ;

  I      = inches                                        ;
  I      = I . replace ( "'"  , " " )                    ;
  I      = I . replace ( "\"" , "." )                    ;
  L      = I . split   ( ' '        )                    ;
  ////////////////////////////////////////////////////////
  double inch = 0                                        ;
  if (L.count()==1)                                      {
    inch  = L [ 0 ] . toDouble ( )                       ;
  } else
  if ( L . count ( ) > 1 )                               {
    inch  = L [ 0 ] . toInt    ( )                       ;
    inch *= 12                                           ;
    inch += L [ 1 ] . toDouble ( )                       ;
  }                                                      ;
  ////////////////////////////////////////////////////////
  double CM = 2.54                                       ;
  int    rr                                              ;
  CM  *= inch                                            ;
  inch = (int) CM                                        ;
  rr   = CM * 100                                        ;
  rr  -= ( inch * 100 )                                  ;
  ////////////////////////////////////////////////////////
  I = tr("%1 => %2.%3 cm").arg(inches).arg(inch).arg(rr) ;
  Report ( I    )                                        ;
  Report ( "\n" )                                        ;
}

void N::GeneralDispatcher::CGSToInches(void)
{
  QString cm                                   ;
  QString I                                    ;
  QString L                                    ;
  double  CM                                   ;
  int     feet                                 ;
  int     inch                                 ;
  int     mmm                                  ;
  //////////////////////////////////////////////
  cm   = arguments [ 1 ] . toString ( )        ;
  CM   = cm . toDouble ( )                     ;
  if ( CM < 0 ) return                         ;
  CM   /= 2.54                                 ;
  inch  = (int) CM                             ;
  mmm   = CM                                   ;
  mmm  *= 100                                  ;
  mmm  -= ( inch * 100 )                       ;
  feet  = inch / 12                            ;
  inch %= 12                                   ;
  //////////////////////////////////////////////
  if ( feet > 0 ) L = QString("%1'").arg(feet) ;
  L += QString("%1.%2").arg(inch).arg(mmm)     ;
  //////////////////////////////////////////////
  I = tr("%1 cm => %2").arg(cm).arg(L)         ;
  //////////////////////////////////////////////
  Report ( I    )                              ;
  Report ( "\n" )                              ;
}

void N::GeneralDispatcher::ShowCPU(void)
{
  CPU::Usage cpu                                     ;
  CUIDs      features = cpu . FeatureLists ( )       ;
  int        fid                                     ;
  short      cost                                    ;
  cpu . GetUsage ( )                                 ;
  Report ( "===================================\n" ) ;
  Report ( tr("CPU = %1").arg(cpu.Cpu())           ) ;
  Report ( "\n"                                    ) ;
  Report ( tr("NUM = %1").arg(cpu.Processors() )   ) ;
  Report ( "\n"                                    ) ;
  Report ( "===================================\n" ) ;
  foreach ( fid , features )                         {
    Report ( cpu . Name ( (CPU::Features) fid )    ) ;
    Report ( "\n"                                  ) ;
  }                                                  ;
  Report ( "===================================\n" ) ;
  TUID T = cpu.Timestamp()                           ;
  Report ( tr("Timestamp : %1").arg(T)             ) ;
  Report ( "\n"                                    ) ;
  Time::skip(1000)                                   ;
  Report ( "===================================\n" ) ;
  cost = cpu . GetUsage ( )                          ;
  Report ( QString("COST = %1\n").arg(cost       ) ) ;
}
