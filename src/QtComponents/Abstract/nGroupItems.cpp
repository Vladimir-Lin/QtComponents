#include <qtcomponents.h>

#define plan      GroupPlan
#define TYPE(T)   N::Types::T
#define RELATE(R) N::Groups::R

N::GroupItems:: GroupItems  ( Plan * p )
              : GroupPlan   (        p )
              , HiddenItems ( 100      )
              , AutoMap     ( false    )
{
  GroupTable         = PlanTable( Groups       ) ;
  GroupMappers [ 0 ] = PlanTable( Groups       ) ;
  GroupMappers [ 1 ] = PlanTable( IconGroups   ) ;
  GroupMappers [ 2 ] = PlanTable( PeopleGroups ) ;
  GroupMappers [ 3 ] = PlanTable( AlbumGroups  ) ;
  GroupMappers [ 4 ] = PlanTable( PictureGroups) ;
  GroupMappers [ 5 ] = PlanTable( CodeGroups   ) ;
  GroupMappers [ 6 ] = PlanTable( NetGroups    ) ;
  GroupMappers [ 7 ] = PlanTable( OtherGroups  ) ;
}

N::GroupItems::~GroupItems(void)
{
}

QString N::GroupItems::LookTable(int t1,int t2,int relation)
{
  if ( ! AutoMap ) return GroupTable                                                   ;
  QString T = GroupMappers [ 7 ]                                                       ;
  if (   Groups::Icon   == relation                           ) T = GroupMappers [ 1 ] ; else
  if ( ( Types::People  == t1 ) || ( Types::People    == t2 ) ) T = GroupMappers [ 2 ] ; else
  if ( ( Types::Album   == t1 ) || ( Types::Album     == t2 ) ) T = GroupMappers [ 3 ] ; else
  if ( ( Types::Picture == t1 ) || ( Types::Picture   == t2 ) ) T = GroupMappers [ 4 ] ; else
  if ( ( Types::File    == t1 ) && ( Types::Component == t2 ) ) T = GroupMappers [ 5 ] ; else
  if ( ( Types::URL     == t1 ) || ( Types::URL       == t2 ) ) T = GroupMappers [ 6 ] ;
  return T                                                                             ;
}

QString N::GroupItems::ExactItem (
          SUID    first        ,
          SUID    second       ,
          int     t1           ,
          int     t2           ,
          int     relation     ,
          QString options      ,
          QString limitString  )
{
  QString Q                           ;
  Q = QString ( "where `t1` = %1"
                 " and `t2` = %2"
                 " and `relation` = %3"
                 " and `first` = %4"
                 " and `second` = %5" )
      . arg ( t1                      )
      . arg ( t2                      )
      . arg ( relation                )
      . arg ( first                   )
      . arg ( second                ) ;
  if (options.length()>0)             {
    Q += " "                          ;
    Q += options                      ;
  }                                   ;
  if (limitString.length()>0)         {
    Q += " "                          ;
    Q += limitString                  ;
  }                                   ;
  return Q                            ;
}

QString N::GroupItems::FirstItem (
          SUID    Group        ,
          int     t1           ,
          int     t2           ,
          int     relation     ,
          QString options      ,
          QString limitString  )
{
  QString Q                           ;
  Q = QString ( "where `t1` = %1"
                 " and `t2` = %2"
                 " and `relation` = %3"
                 " and `first` = %4"  )
      .arg ( t1                       )
      .arg ( t2                       )
      .arg ( relation                 )
      .arg ( Group                  ) ;
  if (options.length()>0)             {
    Q += " "                          ;
    Q += options                      ;
  }                                   ;
  if (limitString.length()>0)         {
    Q += " "                          ;
    Q += limitString                  ;
  }                                   ;
  return Q                            ;
}

QString N::GroupItems::SecondItem (
          SUID    Second          ,
          int     t1              ,
          int     t2              ,
          int     relation        ,
          QString options         ,
          QString limitString     )
{
  QString Q                            ;
  Q = QString ( "where `t1` = %1"
                 " and `t2` = %2"
                 " and `relation` = %3"
                 " and `second` = %4"  )
      .arg ( t1                        )
      .arg ( t2                        )
      .arg ( relation                  )
      .arg ( Second                  ) ;
  if (options.length()>0)              {
    Q += " "                           ;
    Q += options                       ;
  }                                    ;
  if (limitString.length()>0)          {
    Q += " "                           ;
    Q += limitString                   ;
  }                                    ;
  return Q                             ;
}

UUIDs N::GroupItems::Groups           (
        SqlConnection       & SC      ,
        N::Types::ObjectTypes Type    ,
        QString               options )
{
  return SC . Uuids                      (
           PlanTable(Divisions)          ,
           "uuid"                        ,
           QString("where `type` = %1 %2")
           .arg(Type).arg(options)     ) ;
}

UUIDs N::GroupItems::Divisions           (
        SqlConnection       & connection ,
        N::Types::ObjectTypes Type       ,
        QString               options    )
{
  UUIDs GUIDs = Groups(connection,Type,options)     ;
  UUIDs Fuids                                       ;
  UUIDs Uuids                                       ;
  SUID  guid                                        ;
  SUID  suid                                        ;
  foreach (guid,GUIDs)                              {
    UUIDs Suids                                     ;
    Suids = connection.Uuids                        (
             GroupTable                             ,
             "first"                                ,
             SecondItem                             (
               guid                                 ,
               TYPE(Division)                       ,
               Type                                 ,
               N::Groups::Subordination         ) ) ;
    foreach (suid,Suids)                            {
      if (!Uuids.contains(suid)) Uuids << suid      ;
    }                                               ;
  }                                                 ;
  GUIDs.clear()                                     ;
  GUIDs = Groups(connection,TYPE(Division),options) ;
  foreach (guid,GUIDs)                              {
    if (Uuids.contains(guid)) Fuids << guid ; else  {
      QString Q                                     ;
      Q = connection.sql.SelectFrom                 (
            "count(*)"                              ,
            GroupTable                              ,
            QString("where `t1` = %2 "
                    "and `relation` = %3 "
                    "and `first` = %1"              )
            .arg(guid                               )
            .arg(TYPE(Division)                     )
            .arg(N::Groups::Subordination           )
          )                                         ;
      if (connection.Fetch(Q))                      {
        int Empty = connection . Int ( 0 )          ;
        if (Empty==0) Fuids << guid                 ;
      }                                             ;
    }                                               ;
  }                                                 ;
  return Fuids                                      ;
}

int N::GroupItems  :: Count      (
      SqlConnection & connection ,
      SUID            group      ,
      int             t1         ,
      int             t2         ,
      int             relation   )
{
  int     total = 0             ;
  QString Q                     ;
  Q = connection.sql.SelectFrom (
        "count(*)"              ,
        GroupTable              ,
        FirstItem               (
          group                 ,
          t1                    ,
          t2                    ,
          relation          ) ) ;
  if (connection.Fetch(Q))      {
    total = connection.Int(0)   ;
  }                             ;
  return total                  ;
}

int N::GroupItems::LastPosition (
      SqlConnection & SC        ,
      SUID            group     ,
      int             t1        ,
      int             t2        ,
      int             relation  )
{
  int final = 0                         ;
  QString Q                             ;
  Q = SC.sql.SelectFrom                 (
        SC.sql.EncapTable("position")   ,
        GroupTable                      ,
        FirstItem(group,t1,t2,relation) ,
        SC . OrderByDesc ( "position" ) ,
        SC . sql . Limit ( 0 , 1 )    ) ;
  if ( SC . Fetch ( Q ) )               {
    final = SC . Int ( 0 )              ;
  }                                     ;
  return final                          ;
}

void N::GroupItems::Join          (
       SqlConnection & connection ,
       SUID            group      ,
       int             t1         ,
       int             t2         ,
       int             relation   ,
       SUID            before     ,
       SUID            uuid       ,
       bool            gui        )
{
  UUIDs U                                                                    ;
  U << uuid                                                                  ;
  return Join ( connection , group , t1 , t2 , relation , before , U , gui ) ;
}

void N::GroupItems::Join          (
       SqlConnection & connection ,
       SUID            group      ,
       int             t1         ,
       int             t2         ,
       int             relation   ,
       SUID            before     ,
       UUIDs         & Uuids      ,
       bool            gui        )
{
  nDropOut ( group <= 0 )                                                    ;
  QString Q                                                                  ;
  QString M                                                                  ;
  int     PID   = -1                                                         ;
  qint64  index = 0                                                          ;
  bool    go    = true                                                       ;
  if ( before <= 0 )                                                         {
    //////////////////////////////////////////////////////////////////////////
    int final                                                                ;
    final = LastPosition(connection,group,t1,t2,relation) + 1                ;
    //////////////////////////////////////////////////////////////////////////
    if ( gui && Uuids . count ( ) > HiddenItems )                            {
      M   = QObject::tr("Join group %1").arg(group)                          ;
      PID = plan -> Progress ( M   , "%v/%m (%p%)"                         ) ;
      plan       ->Start    ( PID , &index , &go                           ) ;
      plan       ->setRange ( PID , 0 , Uuids.count()                      ) ;
    }                                                                        ;
    //////////////////////////////////////////////////////////////////////////
    SUID uuid                                                                ;
    //////////////////////////////////////////////////////////////////////////
    foreach (uuid,Uuids)                                                     {
      index++                                                                ;
      if (InsertItem                                                         (
            connection                                                       ,
            group                                                            ,
            uuid                                                             ,
            t1                                                               ,
            t2                                                               ,
            relation                                                         ,
            final                                                        ) ) {
        final++                                                              ;
      }                                                                      ;
    }                                                                        ;
    //////////////////////////////////////////////////////////////////////////
    if ( gui && ( PID >= 0 ) ) plan -> Finish ( PID )                        ;
  } else                                                                     {
    UUIDs Ouids                                                              ;
    UUIDs Auids                                                              ;
    SUID  uuid                                                               ;
    //////////////////////////////////////////////////////////////////////////
    Q = connection.sql.SelectFrom                                            (
          "second"                                                           ,
          GroupTable                                                         ,
          FirstItem                                                          (
            group                                                            ,
            t1                                                               ,
            t2                                                               ,
            relation                                                         ,
            connection.OrderByAsc("position")                            ) ) ;
    SqlLoopNow ( connection , Q )                                            ;
      Ouids << connection.Uuid(0)                                            ;
    SqlLoopErr ( connection , Q )                                            ;
    SqlLoopEnd ( connection , Q )                                            ;
    //////////////////////////////////////////////////////////////////////////
    foreach (uuid,Uuids)                                                     {
      if (!Ouids.contains(uuid)) Auids << uuid                               ;
    }                                                                        ;
    //////////////////////////////////////////////////////////////////////////
    if ( gui && Auids . count ( ) > HiddenItems )                            {
      M   = QObject::tr("Join group %1").arg(group)                          ;
      PID = plan -> Progress ( M   , "%v/%m (%p%)"                         ) ;
      plan       -> Start    ( PID , &index , &go                          ) ;
      plan       -> setRange ( PID , 0      , Auids.count()                ) ;
    }                                                                        ;
    //////////////////////////////////////////////////////////////////////////
    foreach ( uuid , Auids )                                                 {
      index++                                                                ;
      Insert ( connection                                                    ,
               group                                                         ,
               uuid                                                          ,
               t1                                                            ,
               t2                                                            ,
               relation                                                    ) ;
    }                                                                        ;
    //////////////////////////////////////////////////////////////////////////
    Auids . clear ( )                                                        ;
    foreach (uuid,Ouids)                                                     {
      if (!Uuids.contains(uuid)) Auids << uuid                               ;
    }                                                                        ;
    index = Auids.indexOf(before)                                            ;
    if (index>=0)                                                            {
      foreach (uuid,Uuids)                                                   {
        Auids.insert(index,uuid)                                             ;
        index++                                                              ;
      }                                                                      ;
    } else                                                                   {
      foreach (uuid,Uuids) Auids << uuid                                     ;
    }                                                                        ;
    //////////////////////////////////////////////////////////////////////////
    if ( gui ) plan ->setRange ( PID , 0 , Auids . count ( ) )               ;
    index = 0                                                                ;
    foreach (uuid,Auids)                                                     {
      index++                                                                ;
      Q = connection . sql . Update ( GroupTable )                           +
            QString("`position` = %1 ").arg(index)                           +
            ExactItem ( group , uuid , t1 , t2 , relation                  ) ;
      connection . Query ( Q )                                               ;
    }                                                                        ;
    //////////////////////////////////////////////////////////////////////////
    if ( gui && ( PID >= 0 ) ) plan -> Finish ( PID )                        ;
  }                                                                          ;
}

void N::GroupItems  :: JoinOwner  (
       SqlConnection & connection ,
       SUID            objectUuid ,
       int             t1         ,
       int             t2         ,
       int             relation   ,
       UUIDs         & Uuids      ,
       bool            gui        )
{
  UUIDs U                         ;
  SUID  u                         ;
  U << objectUuid                 ;
  foreach (u,Uuids)               {
    Join                          (
      connection                  ,
      u                           ,
      t1                          ,
      t2                          ,
      relation                    ,
      0                           ,
      U                           ,
      gui                       ) ;
  }                               ;
}

bool N::GroupItems  :: InsertItem (
       SqlConnection & connection ,
       SUID            first      ,
       SUID            second     ,
       int             t1         ,
       int             t2         ,
       int             relation   )
{
  QString Q                             ;
  Q = connection . sql . SelectFrom     (
        "id"                            ,
        GroupTable                      ,
        ExactItem ( first               ,
                    second              ,
                    t1                  ,
                    t2                  ,
                    relation        ) ) ;
  if (connection.Fetch(Q)) return false ;
  return Insert ( connection            ,
                  first                 ,
                  second                ,
                  t1                    ,
                  t2                    ,
                  relation            ) ;
}

bool N::GroupItems  :: InsertItem (
       SqlConnection & connection ,
       SUID            first      ,
       SUID            second     ,
       int             t1         ,
       int             t2         ,
       int             relation   ,
       int             position   )
{
  QString Q                             ;
  Q = connection . sql . SelectFrom     (
        "id"                            ,
        GroupTable                      ,
        ExactItem ( first               ,
                    second              ,
                    t1                  ,
                    t2                  ,
                    relation)         ) ;
  if (connection.Fetch(Q)) return false ;
  return Insert ( connection            ,
                  first                 ,
                  second                ,
                  t1                    ,
                  t2                    ,
                  relation              ,
                  position            ) ;
}

bool N::GroupItems::Insert      (
       SqlConnection & SC       ,
       SUID            first    ,
       SUID            second   ,
       int             t1       ,
       int             t2       ,
       int             relation )
{
  QString Q                                     ;
  Q = SC.sql.InsertInto                         (
        "`first`,`second`,`t1`,`t2`,`relation`" ,
        GroupTable                              ,
        QString("%1,%2,%3,%4,%5"                )
        . arg ( first                           )
        . arg ( second                          )
        . arg ( t1                              )
        . arg ( t2                              )
        . arg ( relation                    ) ) ;
  return SC . Query ( Q )                       ;
}

bool N::GroupItems::Insert      (
       SqlConnection & SC       ,
       SUID            first    ,
       SUID            second   ,
       int             t1       ,
       int             t2       ,
       int             relation ,
       int             position )
{
  QString Q                                                ;
  Q = SC.sql.InsertInto                                    (
        "`first`,`second`,`t1`,`t2`,`relation`,`position`" ,
        GroupTable                                         ,
        QString("%1,%2,%3,%4,%5,%6"                        )
        . arg ( first                                      )
        . arg ( second                                     )
        . arg ( t1                                         )
        . arg ( t2                                         )
        . arg ( relation                                   )
        . arg ( position                               ) ) ;
  return SC . Query ( Q )                                  ;
}

bool N::GroupItems::DeleteFrom      (
       SqlConnection & SC           ,
       QString         whereOptions )
{
  QString Q               ;
  Q = SC.sql.DeleteFrom   (
        GroupTable        ,
        whereOptions    ) ;
  return SC . Query ( Q ) ;
}

void N::GroupItems::Detach      (
       SqlConnection & SC       ,
       SUID            group    ,
       int             t1       ,
       int             t2       ,
       int             relation ,
       UUIDs         & Uuids    )
{
  QString Q                   ;
  SUID    u                   ;
  foreach ( u , Uuids )       {
    Q = SC . sql . DeleteFrom (
          GroupTable          ,
          ExactItem           (
            group             ,
            u                 ,
            t1                ,
            t2                ,
            relation      ) ) ;
    SC . Query ( Q )          ;
  }                           ;
}

bool N::GroupItems::FullDetach  (
       SqlConnection & SC       ,
       SUID            group    ,
       int             t1       ,
       int             t2       ,
       int             relation )
{
  QString Q                               ;
  Q = SC.sql.DeleteFrom                   (
        GroupTable                        ,
        FirstItem(group,t1,t2,relation) ) ;
  return SC.Query(Q)                      ;
}

bool N::GroupItems::ExactDetach   (
       SqlConnection & connection ,
       SUID            first      ,
       SUID            second     ,
       int             t1         ,
       int             t2         ,
       int             relation   )
{
  QString Q                     ;
  Q = connection.sql.DeleteFrom (
        GroupTable              ,
        ExactItem               (
          first                 ,
          second                ,
          t1                    ,
          t2                    ,
          relation          ) ) ;
  return connection.Query(Q)    ;
}

bool N::GroupItems::ExactDetach   (
       SqlConnection & connection ,
       Group         & group      )
{
  QString Q                     ;
  Q = connection.sql.DeleteFrom (
        GroupTable              ,
        ExactItem               (
          group . first         ,
          group . second        ,
          group . t1            ,
          group . t2            ,
          group . relation  ) ) ;
  return connection.Query(Q)    ;
}

bool N::GroupItems::Delegate      (
       SqlConnection & connection ,
       SUID            first      ,
       SUID            second     ,
       int             t1         ,
       int             t2         ,
       int             relation   )
{
  FullDetach        (
    connection      ,
    first           ,
    t1              ,
    t2              ,
    relation      ) ;
  return InsertItem (
    connection      ,
    first           ,
    second          ,
    t1              ,
    t2              ,
    relation      ) ;
}

void N::GroupItems::Relocate      (
       SqlConnection & connection ,
       SUID            group      ,
       int             t1         ,
       int             t2         ,
       int             relation   )
{
  QString Q                                     ;
  UUIDs   Uuids                                 ;
  Q = connection.sql.SelectFrom                 (
        "second"                                ,
        GroupTable                              ,
        FirstItem                               (
          group                                 ,
          t1                                    ,
          t2                                    ,
          relation                              ,
          connection.OrderByAsc("position") ) ) ;
  SqlLoopNow ( connection , Q )                 ;
    Uuids << connection . Uuid ( 0 )            ;
  SqlLoopErr ( connection , Q )                 ;
  SqlLoopEnd ( connection , Q )                 ;
  if (Uuids.count()>0)                          {
    connection.transaction()                    ;
    for (int i=0;i<Uuids.count();i++)           {
      SUID uuid = Uuids[i]                      ;
      Q = connection.sql.Update(GroupTable)     +
          QString("`position` = %1"
                  " where `t1` = %2"
                  " and `t2` = %3"
                  " and `relation` = %4"
                  " and `first` = %5"
                  " and `second` = %6 ;"        )
              .arg(i+1                          )
              .arg(t1                           )
              .arg(t2                           )
              .arg(relation                     )
              .arg(group                        )
              .arg(uuid                       ) ;
      connection.Query(Q)                       ;
      if ((i%1000)==999)                        {
        connection . commit      ( )            ;
        connection . transaction ( )            ;
      }                                         ;
    }                                           ;
    connection.commit()                         ;
  }                                             ;
}

QString N::GroupItems::ItemName(SqlConnection & SC,SUID Uuid)
{
  return SC . getName         (
           PlanTable(Names)   ,
           "uuid"             ,
           plan -> LanguageId ,
           Uuid             ) ;
}

QStringList N::GroupItems::Names(SqlConnection & connection,SUID Uuid)
{
  QStringList names                               ;
  UUIDs       Uuids                               ;
  SUID        uuid                                ;
  Uuids = connection.Uuids                        (
            PlanTable(NameMaps)                   ,
            "name"                                ,
            QString ( "%1 %2"                     )
            .arg( connection.WhereUuid(Uuid)      )
            .arg( connection.OrderByAsc("prefer") )
          )                                       ;
  foreach (uuid,Uuids)                            {
    QString Q = connection.sql.SelectFrom         (
                  "name"                          ,
                  PlanTable(Names)                ,
                  connection.WhereUuid(uuid)    ) ;
    if (connection.Fetch(Q))                      {
      names << connection.String(0)               ;
    }                                             ;
  }                                               ;
  return names                                    ;
}

SUID N::GroupItems  :: FindFirst  (
       SqlConnection & connection ,
       SUID            Second     ,
       int             t1         ,
       int             t2         ,
       int             relation   ,
       QString         options    ,
       QString         limitString )
{
  QString Q                     ;
  SUID    uuid = 0              ;
  Q = connection.sql.SelectFrom (
        "first"                 ,
        GroupTable              ,
        SecondItem              (
          Second                ,
          t1                    ,
          t2                    ,
          relation              ,
          options               ,
          limitString       ) ) ;
  if (connection.Fetch(Q))      {
    uuid = connection.Uuid(0)   ;
  }                             ;
  return uuid                   ;
}

SUID N::GroupItems  :: FindSecond  (
       SqlConnection & connection  ,
       SUID            group       ,
       int             t1          ,
       int             t2          ,
       int             relation    ,
       QString         options     ,
       QString         limitString )
{
  QString Q                     ;
  SUID    uuid = 0              ;
  Q = connection.sql.SelectFrom (
        "second"                ,
        GroupTable              ,
        FirstItem               (
          group                 ,
          t1                    ,
          t2                    ,
          relation              ,
          options               ,
          limitString       ) ) ;
  if (connection.Fetch(Q))      {
    uuid = connection.Uuid(0)   ;
  }                             ;
  return uuid                   ;
}

UUIDs N::GroupItems::Subordination  (
        SqlConnection & connection  ,
        SUID            group       ,
        int             t1          ,
        int             t2          ,
        int             relation    ,
        QString         options     ,
        QString         limitString )
{
  return connection.Uuids    (
           GroupTable        ,
           "second"          ,
           FirstItem         (
             group           ,
             t1              ,
             t2              ,
             relation        ,
             options         ,
             limitString ) ) ;
}

UUIDs N::GroupItems  :: GetOwners   (
        SqlConnection & connection  ,
        SUID            Second      ,
        int             t1          ,
        int             t2          ,
        int             relation    ,
        QString         options     ,
        QString         limitString )
{
  return connection.Uuids    (
           GroupTable        ,
           "first"           ,
           SecondItem        (
             Second          ,
             t1              ,
             t2              ,
             relation        ,
             options         ,
             limitString ) ) ;
}

bool N::GroupItems::InsertNameMap(SqlConnection & connection,SUID uuid,SUID nuid)
{
  QString Q                                           ;
  int     Prefer = -1                                 ;
  Q = connection . sql . SelectFrom                   (
        "prefer"                                      ,
        PlanTable(NameMaps)                           ,
        QString("%1 %2 %3"                            )
        .arg(QString("where uuid = %1").arg(uuid)     )
        .arg(connection.OrderByDesc("prefer")         )
        .arg(connection.sql.Limit(0,1))             ) ;
  if (connection.Fetch(Q)) Prefer = connection.Int(0) ;
  Prefer ++                                           ;
  Q = connection.sql.InsertInto                       (
        PlanTable(NameMaps)                           ,
        3,"uuid","name","prefer"                    ) ;
  connection . Prepare ( Q                 )          ;
  connection . Bind    ( "uuid"   , uuid   )          ;
  connection . Bind    ( "name"   , nuid   )          ;
  connection . Bind    ( "prefer" , Prefer )          ;
  return connection . Exec (               )          ;
}

SUID N::GroupItems::NewDivision         (
       SqlConnection       & connection ,
       QString               name       ,
       N::Types::ObjectTypes Type       )
{
  QString Q                                                                  ;
  int     position = 0                                                       ;
  SUID    uuid     = connection.Unique(PlanTable(MajorUuid),"uuid")          ;
  Q = connection . sql . SelectFrom                                          (
        "position"                                                           ,
        PlanTable(Divisions)                                                 ,
        QString("%1 %2 %3"                                                   )
        .arg( QString("where type = %1 ").arg(Type)                          )
        .arg( connection.OrderByDesc("position")                             )
        .arg( connection.sql.Limit(0,1)                                  ) ) ;
  if (connection.Fetch(Q)) position = connection.Int(0)                      ;
  position ++                                                                ;
  connection . assureUuid ( PlanTable(MajorUuid) , uuid , TYPE(Division)   ) ;
  connection . assureUuid ( PlanTable(Divisions) , uuid , (int)Type        ) ;
  connection . assureName ( PlanTable(Names    )                             ,
                            uuid                                             ,
                            plan -> LanguageId                               ,
                            name                                           ) ;
  Q = connection.sql.Update                                                  (
        PlanTable(Divisions)                                                 ,
        connection.sql.Where(1,"uuid")                                       ,
        1,"position"                                                       ) ;
  connection . Prepare ( Q                     )                             ;
  connection . Bind    ( "uuid"     , uuid     )                             ;
  connection . Bind    ( "position" , position )                             ;
  connection . Exec    (                       )                             ;
  return uuid                                                                ;
}

bool N::GroupItems  :: CopyTo     (
       SqlConnection & connection ,
       SUID            Source     ,
       SUID            Target     ,
       int             t1         ,
       int             t2         ,
       int             relation   ,
       bool            gui        ,
       QString         Text       )
{
  UUIDs Uuids                                                  ;
  Uuids = Subordination                                        (
            connection                                         ,
            Source                                             ,
            t1                                                 ,
            t2                                                 ,
            relation                                           ,
            connection.OrderByAsc("position")                ) ;
  nKickOut ( Uuids.count() <= 0 , false )                      ;
  int    PID   = -1                                            ;
  qint64 index = 0                                             ;
  bool   go    = true                                          ;
  int    final                                                 ;
  if ( gui )                                                   {
    ////////////////////////////////////////////////////////////
    final = LastPosition(connection,Target,t1,t2,relation) + 1 ;
    ////////////////////////////////////////////////////////////
    if ( Uuids . count ( ) > HiddenItems )                     {
      PID = plan -> Progress ( Text , "%v/%m (%p%)"          ) ;
      plan       -> Start    ( PID  , &index , &go           ) ;
      plan       -> setRange ( PID  , 0 , Uuids.count()      ) ;
    }                                                          ;
    ////////////////////////////////////////////////////////////
    SUID uuid                                                  ;
    int  index = 0                                             ;
    ////////////////////////////////////////////////////////////
    foreach (uuid,Uuids)                                       {
      index++                                                  ;
      if (InsertItem                                           (
            connection                                         ,
            Target                                             ,
            uuid                                               ,
            t1                                                 ,
            t2                                                 ,
            relation                                           ,
            final                                          ) ) {
        final++                                                ;
      }                                                        ;
    }                                                          ;
    if ( gui && ( PID >= 0 ) ) plan -> Finish ( PID )          ;
  } else                                                       {
    ////////////////////////////////////////////////////////////
    SUID uuid                                                  ;
    final = LastPosition(connection,Target,t1,t2,relation) + 1 ;
    ////////////////////////////////////////////////////////////
    foreach (uuid,Uuids)                                       {
      if (InsertItem                                           (
            connection                                         ,
            Target                                             ,
            uuid                                               ,
            t1                                                 ,
            t2                                                 ,
            relation                                           ,
            final                                          ) ) {
        final++                                                ;
      }                                                        ;
    }                                                          ;
  }                                                            ;
  return true                                                  ;
}

bool N::GroupItems  :: Substract  (
       SqlConnection & connection ,
       SUID            Source     ,
       SUID            Target     ,
       int             t1         ,
       int             t2         ,
       int             relation   ,
       bool            gui        ,
       QString         Text       )
{
  UUIDs Uuids                                      ;
  Uuids = Subordination                            (
            connection                             ,
            Source                                 ,
            t1                                     ,
            t2                                     ,
            relation                               ,
            connection.OrderByAsc("position")    ) ;
  nKickOut ( Uuids.count() <= 0 , false )                       ;
  int    PID   = -1                                             ;
  qint64 index = 0                                              ;
  bool   go    = true                                           ;
  if ( gui )                                                    {
    QString Q                                                   ;
    SUID    uuid                                                ;
    if ( Uuids . count ( ) > HiddenItems )                      {
      PID = plan -> Progress ( Text , "%v/%m (%p%)"         )   ;
      plan       -> Start    ( PID  , &index , &go          )   ;
      plan       -> setRange ( PID  , 0 , Uuids . count ( ) )   ;
    }                                                           ;
    foreach (uuid,Uuids)                                        {
      index++                                                   ;
      Q = connection.sql.DeleteFrom                             (
            GroupTable                                          ,
            ExactItem(Target,uuid,t1,t2,relation)             ) ;
      connection.Query(Q)                                       ;
    }                                                           ;
    if ( gui && ( PID >= 0 ) ) plan -> Finish ( PID )           ;
  } else                                                        {
    Detach ( connection , Target , t1 , t2 , relation , Uuids ) ;
  }                                                             ;
  return true                                                   ;
}

UUIDs N::GroupItems  :: RelateUuids (
        SqlConnection & connection  ,
        UUIDs         & Uuids       ,
        int             t1          ,
        int             t2          ,
        int             relation    ,
        bool            gui         ,
        QString         Text        )
{
  UUIDs  Ruids                                                ;
  nKickOut ( Uuids . count ( ) <= 0 , Ruids )                 ;
  SUID   uuid                                                 ;
  SUID   puid                                                 ;
  int    PID   = -1                                           ;
  qint64 index = 0                                            ;
  bool   go    = true                                         ;
  if ( gui )                                                  {
    if ( Uuids . count ( ) > HiddenItems )                    {
      PID = plan -> Progress ( Text , "%v/%m (%p%)"         ) ;
      plan       -> Start    ( PID  , &index , &go          ) ;
      plan       -> setRange ( PID  , 0 , Uuids . count ( ) ) ;
    }                                                         ;
    foreach ( uuid , Uuids )                                  {
      index ++                                                ;
      puid = FindFirst                                        (
               connection                                     ,
               uuid                                           ,
               t1                                             ,
               t2                                             ,
               relation                                       ,
               ""                                           ) ;
      if ( ( puid > 0 ) && ( ! Ruids . contains ( puid ) ) )  {
        Ruids << puid                                         ;
      }                                                       ;
    }                                                         ;
    if ( gui && ( PID >= 0 ) ) plan -> Finish ( PID )         ;
  } else                                                      {
    foreach ( uuid , Uuids )                                  {
      puid = FindFirst                                        (
               connection                                     ,
               uuid                                           ,
               t1                                             ,
               t2                                             ,
               relation                                       ,
               ""                                           ) ;
      if ( ( puid > 0 ) && ( ! Ruids . contains ( puid ) ) )  {
        Ruids << puid                                         ;
      }                                                       ;
    }                                                         ;
  }                                                           ;
  return Ruids                                                ;
}

NAMEs N::GroupItems::UuidNames(SqlConnection & SC,UUIDs & Uuids,int language)
{
  return SC . getNames ( PlanTable(Names) , "uuid" , language , Uuids ) ;
}

bool N::GroupItems  :: AllowType  (
       SqlConnection & connection ,
       int             Type       ,
       UUIDs         & Source     ,
       UUIDs         & Target     )
{
  QString Q                            ;
  SUID    uuid                         ;
  foreach (uuid,Source)                {
    Q = connection.sql.SelectFrom      (
          "type"                       ,
          PlanTable(MajorUuid)         ,
          connection.WhereUuid(uuid) ) ;
    if (connection.Fetch(Q))           {
      int t = connection.Int(0)        ;
      if (t==Type)                     {
        Target << uuid                 ;
      }                                ;
    }                                  ;
  }                                    ;
  return true                          ;
}

bool N::GroupItems::AllowObjectsTypes (
       SqlConnection & SC             ,
       UUIDs         & Source         ,
       CUIDs         & Types          ,
       UUIDs         & Target         )
{
  QString Q                     ;
  SUID    uuid                  ;
  foreach (uuid,Source)         {
    Q = SC.sql.SelectFrom       (
          SC.Columns(1,"type")  ,
          PlanTable(MajorUuid)  ,
          SC.WhereUuid(uuid) )  ;
    if (SC.Fetch(Q))            {
      int t = SC.Int(0)         ;
      if ( Types.contains(t)  ) {
        Target << uuid          ;
      }                         ;
    }                           ;
  }                             ;
  return ( Target.count() > 0 ) ;
}

bool N::GroupItems  :: AllowDivisionType (
       SqlConnection & connection        ,
       int             Type              ,
       UUIDs         & Source            ,
       UUIDs         & Target            )
{
  QString Q                            ;
  SUID    uuid                         ;
  foreach (uuid,Source)                {
    Q = connection.sql.SelectFrom      (
          "type"                       ,
          PlanTable(Divisions)         ,
          connection.WhereUuid(uuid) ) ;
    if (connection.Fetch(Q))           {
      int t = connection.Int(0)        ;
      if (t==Type)                     {
        Target << uuid                 ;
      }                                ;
    }                                  ;
  }                                    ;
  return true                          ;
}

bool N::GroupItems::Variable (
       SqlConnection & SC      ,
       SUID            u       ,
       QString         name    ,
       QString       & result  )
{
  QString Q                                   ;
  Q = SC . sql . SelectFrom                   (
        "value"                               ,
        PlanTable(Variables)                  ,
        SC . sql . Where ( 3                  ,
                           "uuid"             ,
                           "type"             ,
                           "name"         ) ) ;
  SC . Prepare ( Q                          ) ;
  SC . Bind    ( "uuid" , u                 ) ;
  SC . Bind    ( "type" , Types::People     ) ;
  SC . Bind    ( "name" , name . toUtf8 ( ) ) ;
  IfSqlExec ( SC )                            {
    result = SC . String ( 0 )                ;
    return true                               ;
  }                                           ;
  return false                                ;
}

bool N::GroupItems::assureVariable  (
       N::SqlConnection & SC    ,
       SUID               uuid  ,
       int                type  ,
       QString            name  ,
       QString            value )
{
  QString Q                                        ;
  deleteVariable    ( SC , uuid , name           ) ;
  Q = SC . sql . InsertInto                        (
        PlanTable(Variables)                       ,
        4                                          ,
        "uuid"                                     ,
        "type"                                     ,
        "name"                                     ,
        "value"                                  ) ;
  SC . Prepare      ( Q                          ) ;
  SC . Bind         ( "uuid"  , uuid             ) ;
  SC . Bind         ( "type"  , type             ) ;
  SC . Bind         ( "name"  , name  . toUtf8() ) ;
  SC . Bind         ( "value" , value . toUtf8() ) ;
  return  SC . Exec (                            ) ;
}

bool N::GroupItems::deleteVariable (
       SqlConnection & SC            ,
       SUID            uuid          ,
       QString         name          )
{
  QString Q                               ;
  Q = SC . sql . DeleteFrom               (
        PlanTable(Variables)              ,
        SC.sql.Where(2,"uuid","name")   ) ;
  SC . Prepare ( Q                      ) ;
  SC . Bind    ( "uuid" , uuid          ) ;
  SC . Bind    ( "name" , name.toUtf8() ) ;
  return SC . Exec ( )                    ;
}

bool N::GroupItems::assignLanguage(SqlConnection & SC,SUID first,int t1,int language)
{
  if ( ! plan -> languages . Uuids . contains ( language ) ) return false ;
  SUID u = plan -> languages . Uuids [ language ]                         ;
  /////////////////////////////////////////////////////////////////////////
  FullDetach                                                              (
           SC                                                             ,
           first                                                          ,
           t1                                                             ,
           Types  :: Language                                             ,
           Groups :: Using                                              ) ;
  /////////////////////////////////////////////////////////////////////////
  return InsertItem                                                       (
           SC                                                             ,
           first                                                          ,
           u                                                              ,
           t1                                                             ,
           Types  :: Language                                             ,
           Groups :: Using                                                ,
           0                                                            ) ;
}

int N::GroupItems::usingLanguage(SqlConnection & SC,SUID first,int t1)
{
  return usingLanguage ( SC , first , t1 , plan -> LanguageId ) ;
}

int N::GroupItems::usingLanguage(SqlConnection & SC,SUID first,int t1,int defaultLanguage)
{
  int  language = defaultLanguage                     ;
  SUID u                                              ;
  u = FindSecond                                      (
        SC                                            ,
        first                                         ,
        t1                                            ,
        Types  :: Language                            ,
        Groups :: Using                               ,
        SC . OrderByAsc  ( "position" )               ,
        SC . sql . Limit ( 0,1        )             ) ;
  if ( plan -> languages . UuidIDs . contains ( u ) ) {
    language = plan -> languages . UuidIDs [ u ]      ;
  }                                                   ;
  return language                                     ;
}

bool N::GroupItems::ObtainNames(SqlConnection & SC,int language,UUIDs & Uuids,NAMEs & N)
{
  SUID u                   ;
  foreach ( u , Uuids )    {
    QString n              ;
    n = SC . getName       (
          PlanTable(Names) ,
          "uuid"           ,
          language         ,
          u              ) ;
    N [ u ] = n            ;
  }                        ;
  return true              ;
}

bool N::GroupItems::NamesOwners (
       SqlConnection & SC       ,
       UUIDs         & Names    ,
       UUIDs         & Owners   )
{
  return NamesOwners ( SC , PlanTable(NameMaps) , Names , Owners ) ;
}

bool N::GroupItems::NamesOwners (
       SqlConnection & SC       ,
       QString         Table    ,
       UUIDs         & Names    ,
       UUIDs         & Owners   )
{
  QString Q                                   ;
  SUID    u                                   ;
  SUID    owner                               ;
  foreach ( u , Names )                       {
    Q = SC . sql . SelectFrom                 (
          "uuid"                              ,
          Table                               ,
          QString("where `name` = %1").arg(u) ,
          SC . OrderByAsc ( "id" )          ) ;
    SqlLoopNow ( SC , Q )                     ;
      owner = SC.Uuid(0)                      ;
      if ( ! Owners . contains ( owner ) )    {
        Owners << owner                       ;
      }                                       ;
    SqlLoopErr ( SC , Q )                     ;
    SqlLoopEnd ( SC , Q )                     ;
  }                                           ;
  return ( Owners . count() > 0 )             ;
}

bool N::GroupItems::FromNames (
       SqlConnection & SC     ,
       QString         Name   ,
       UUIDs         & Uuids  )
{
  QStringList NS                       ;
  NS << Name                           ;
  return FromNames ( SC , NS , Uuids ) ;
}

bool N::GroupItems::FromNames (
       SqlConnection & SC     ,
       QStringList   & Names  ,
       UUIDs         & Uuids  )
{
  return FromNames ( SC , PlanTable(Names) , Names , Uuids ) ;
}

bool N::GroupItems::FromNames (
       SqlConnection & SC     ,
       QString         Table  ,
       QString         Name   ,
       UUIDs         & Uuids  )
{
  QStringList NS                               ;
  NS << Name                                   ;
  return FromNames ( SC , Table , NS , Uuids ) ;
}

bool N::GroupItems::FromNames (
       SqlConnection & SC     ,
       QString         Table  ,
       QStringList   & Names  ,
       UUIDs         & Uuids  )
{
  QString Q                                ;
  QString W                                ;
  QString n                                ;
  foreach ( n , Names )                    {
    W = SC . sql . SmartPattern ("name",n) ;
    ////////////////////////////////////////
    Q = SC.sql.SelectFrom("uuid",Table,W ) ; // this part add into SqlConnection as UniqueUuids
    SC . Prepare ( Q                     ) ;
    SC . Bind    ( "name" , n.toUtf8()   ) ;
    IfSqlLoop ( SC )                       {
      SUID u = SC.Uuid(0)                  ;
      if ( ! Uuids . contains ( u ) )      {
        Uuids << u                         ;
      }                                    ;
    }                                      ;
    ////////////////////////////////////////
  }                                        ;
  return ( Uuids.count() > 0 )             ;
}

bool N::GroupItems::EradicateNames (
       SqlConnection & SC          ,
       SUID            nuid        )
{
  QString Q                                      ;
  Q = SC . sql . DeleteFrom                      (
        PlanTable(NameMaps)                      ,
        QString("where `name` = %1").arg(nuid) ) ;
  SC . Query ( Q )                               ;
  Q = SC . sql . DeleteFrom                      (
        PlanTable(Names)                         ,
        SC . WhereUuid ( nuid )                ) ;
  SC . Query ( Q )                               ;
  Q = SC . sql . DeleteFrom                      (
        PlanTable(MajorUuid)                     ,
        SC . WhereUuid ( nuid )                ) ;
  SC . Query ( Q )                               ;
  return true                                    ;
}

bool N::GroupItems::FindByNames   (
       SqlConnection & SC         ,
       int             TargetType ,
       QStringList   & NS         ,
       UUIDs         & Uuids      )
{
  UUIDs Names                                              ;
  UUIDs Owners                                             ;
  CUIDs Types                                              ;
  FromNames ( SC , NS , Names )                            ;
  Types << Types::Name                                     ;
  if ( AllowObjectsTypes ( SC , Names , Types , Owners ) ) {
    Names  = Owners                                        ;
    Types  . clear ( )                                     ;
    Owners . clear ( )                                     ;
    NamesOwners ( SC , Names , Owners )                    ;
    if ( Owners . count ( ) > 0 )                          {
      Types << TargetType                                  ;
      AllowObjectsTypes  ( SC , Owners , Types , Uuids )   ;
    }                                                      ;
  }                                                        ;
  return ( Uuids . count ( ) > 0 )                         ;
}
