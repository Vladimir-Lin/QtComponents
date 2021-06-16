#include <qtcomponents.h>

#define TABLES(ID) GraphicPlan->Tables[N::Tables::ID]
#define Language   GraphicPlan->LanguageId
#define UuidWhere  "where uuid = :UUID"

N::GraphicsManager:: GraphicsManager (Plan * p)
                   : GraphicPlan     (       p)
{
}

N::GraphicsManager::~GraphicsManager (void)
{
}

bool N::GraphicsManager::assureName(SqlConnection & connection,SUID uuid,int language,QString name)
{
  return connection.assureName(TABLES(Names),uuid,language,name) ;
}

QString N::GraphicsManager::Name(SqlConnection & connection,SUID uuid,int language)
{
  return connection.getName(TABLES(Names),"uuid",language,uuid) ;
}

bool N::GraphicsManager::DeletePainter(SqlConnection & connection,SUID uuid)
{
  QString Q                                                    ;
  nSqlDeleteUuid ( connection , Q , TABLES(Names    ) , uuid ) ;
  nSqlDeleteUuid ( connection , Q , TABLES(Painters ) , uuid ) ;
  nSqlDeleteUuid ( connection , Q , TABLES(MajorUuid) , uuid ) ;
  return true                                                  ;
}

QByteArray N::GraphicsManager::PainterParaments(SqlConnection & connection,SUID uuid)
{
  QByteArray conf                    ;
  QString    Q                       ;
  Q = connection.sql.SelectFrom      (
        "paraments"                  ,
        TABLES(Painters)             ,
        connection.WhereUuid(uuid) ) ;
  if (connection.Fetch(Q))           {
    conf = connection.ByteArray(0)   ;
  }                                  ;
  return conf                        ;
}

bool N::GraphicsManager::PainterEditable(SqlConnection & connection,SUID uuid)
{
  QString Q                          ;
  int     editable = 1               ;
  Q = connection.sql.SelectFrom      (
        "editable"                   ,
        TABLES(Painters)             ,
         connection.WhereUuid(uuid)) ;
  if (connection.Fetch(Q))           {
    editable = connection.Int(0)     ;
  }                                  ;
  return ( editable == 1 )           ;
}

bool N::GraphicsManager::SaveParaments (
       SqlConnection & connection   ,
       SUID             uuid         ,
       int              Type         ,
       QByteArray     & Data         )
{
  QString Q                                       ;
  int size     = Data.size (                    ) ;
  int checksum = qChecksum ( Data.data() , size ) ;
  Q = connection.sql.SelectFrom                   (
        "name"                                    ,
        TABLES    ( Painters )                    ,
        connection.WhereUuid( uuid )            ) ;
  if (connection.Fetch(Q))                        {
    Q = connection.sql.Update                     (
          TABLES(Painters)                        ,
          UuidWhere                               ,
          4                                       ,
          "type"                                  ,
          "size"                                  ,
          "checksum"                              ,
          "paraments"                           ) ;
  } else                                          {
    Q = connection.sql.InsertInto                 (
          TABLES(Painters)                        ,
          5                                       ,
          "uuid"                                  ,
          "type"                                  ,
          "size"                                  ,
          "checksum"                              ,
          "paraments"                           ) ;
  }                                               ;
  connection . Prepare (Q                       ) ;
  connection . Bind ("uuid"      , uuid         ) ;
  connection . Bind ("type"      , Type         ) ;
  connection . Bind ("size"      , Data.size()  ) ;
  connection . Bind ("checksum"  , checksum     ) ;
  connection . Bind ("paraments" , Data         ) ;
  return connection . Exec (                    ) ;
}

N::Font N::GraphicsManager::GetFont(SqlConnection & connection,SUID uuid)
{
  Font  F                                             ;
  QByteArray conf = PainterParaments(connection,uuid) ;
  F.setConfigure(conf)                                ;
  F.uuid     = uuid                                   ;
  F.name     = Name(connection,uuid,Language)         ;
  F.editable =  PainterEditable(connection,uuid)      ;
  return F                                            ;
}

N::Pen N::GraphicsManager::GetPen(SqlConnection & connection,SUID uuid)
{
  Pen       P                                         ;
  QByteArray conf = PainterParaments(connection,uuid) ;
  P.setConfigure(conf)                                ;
  P.uuid     = uuid                                   ;
  P.name     = Name(connection,uuid,Language)         ;
  P.editable =  PainterEditable(connection,uuid)      ;
  return P                                            ;
}

N::Brush N::GraphicsManager::GetBrush(SqlConnection & connection,SUID uuid)
{
  Brush     B                                         ;
  QByteArray conf = PainterParaments(connection,uuid) ;
  B.setConfigure(conf)                                ;
  B.uuid     = uuid                                   ;
  B.name     = Name(connection,uuid,Language)         ;
  B.editable =  PainterEditable(connection,uuid)      ;
  return B                                            ;
}

N::Gradient N::GraphicsManager::GetGradient(SqlConnection & connection,SUID uuid)
{
  Gradient  G                                        ;
  QByteArray conf = PainterParaments(connection,uuid) ;
  G.setConfigure(conf)                                ;
  G.uuid     = uuid                                   ;
  G.name     = Name(connection,uuid,Language)         ;
  G.editable =  PainterEditable(connection,uuid)      ;
  return G                                            ;
}

N::Font N::GraphicsManager::GetFont(SqlConnection & connection,QString name)
{
  SUID uuid = 0                                         ;
  QString Q                                             ;
  Q = connection.sql.SelectFrom("uuid",TABLES(Painters) ,
        "where name = :NAME and type = :TYPE;"        ) ;
  connection.Prepare(Q)                                 ;
  connection.Bind("name",name.toUtf8())                 ;
  connection.Bind("type",N::Graphics::Font)             ;
  if (connection.Exec() && connection.Next())           {
    uuid = connection.Uuid(0)                           ;
  }                                                     ;
  return GetFont(connection,uuid)                       ;
}

N::Pen N::GraphicsManager::GetPen(SqlConnection & connection,QString name)
{
  SUID uuid = 0                                         ;
  QString Q                                             ;
  Q = connection.sql.SelectFrom("uuid",TABLES(Painters) ,
        "where name = :NAME and type = :TYPE;"        ) ;
  connection.Prepare(Q)                                 ;
  connection.Bind("name",name.toUtf8())                 ;
  connection.Bind("type",N::Graphics::Pen)              ;
  if (connection.Exec() && connection.Next())           {
    uuid = connection.Uuid(0)                           ;
  }                                                     ;
  return GetPen(connection,uuid)                        ;
}

N::Brush N::GraphicsManager::GetBrush(SqlConnection & connection,QString name)
{
  SUID uuid = 0                                         ;
  QString Q                                             ;
  Q = connection.sql.SelectFrom("uuid",TABLES(Painters) ,
        "where name = :NAME and type = :TYPE;"        ) ;
  connection.Prepare(Q)                                 ;
  connection.Bind("name",name.toUtf8())                 ;
  connection.Bind("type",N::Graphics::Brush)            ;
  if (connection.Exec() && connection.Next())           {
    uuid = connection.Uuid(0)                           ;
  }                                                     ;
  return GetBrush(connection,uuid)                      ;
}

N::Gradient N::GraphicsManager::GetGradient(SqlConnection & connection,QString name)
{
  SUID uuid = 0                                         ;
  QString Q                                             ;
  Q = connection.sql.SelectFrom("uuid",TABLES(Painters) ,
        "where name = :NAME and type = :TYPE;"        ) ;
  connection.Prepare(Q)                                 ;
  connection.Bind("name",name.toUtf8())                 ;
  connection.Bind("type",N::Graphics::Gradient)         ;
  if (connection.Exec() && connection.Next())           {
    uuid = connection.Uuid(0)                           ;
  }                                                     ;
  return GetGradient(connection,uuid)                   ;
}

bool N::GraphicsManager::SaveFont(SqlConnection & connection,Font & font)
{
  QByteArray conf = font.Configure()                                 ;
  SUID       uuid = font.uuid                                        ;
  if (uuid<=0)                                                       {
    uuid = connection.Unique(TABLES(MajorUuid),"uuid")               ;
    connection.assureUuid(TABLES(MajorUuid),uuid,N::Types::Painting) ;
    font.uuid = uuid                                                 ;
  }                                                                  ;
  if (font.name.length()>0)                                          {
    assureName(connection,uuid,Language,font.name)                   ;
  }                                                                  ;
  return SaveParaments(connection,uuid,N::Graphics::Font,conf)       ;
}

bool N::GraphicsManager::SavePen(SqlConnection & connection,Pen & pen)
{
  QByteArray conf = pen.Configure()                                  ;
  SUID       uuid = pen.uuid                                         ;
  if (uuid<=0)                                                       {
    uuid = connection.Unique(TABLES(MajorUuid),"uuid")               ;
    connection.assureUuid(TABLES(MajorUuid),uuid,N::Types::Painting) ;
    pen.uuid = uuid                                                  ;
  }                                                                  ;
  if (pen.name.length()>0)                                           {
    assureName(connection,uuid,Language,pen.name)                    ;
  }                                                                  ;
  return SaveParaments(connection,uuid,N::Graphics::Pen,conf)        ;
}

bool N::GraphicsManager::SaveBrush(SqlConnection & connection,Brush & brush)
{
  QByteArray conf = brush.Configure()                                ;
  SUID       uuid = brush.uuid                                       ;
  if (uuid<=0)                                                       {
    uuid = connection.Unique(TABLES(MajorUuid),"uuid")               ;
    connection.assureUuid(TABLES(MajorUuid),uuid,N::Types::Painting) ;
    brush.uuid = uuid                                                ;
  }                                                                  ;
  if (brush.name.length()>0)                                         {
    assureName(connection,uuid,Language,brush.name)                  ;
  }                                                                  ;
  return SaveParaments(connection,uuid,N::Graphics::Brush,conf)      ;
}

bool N::GraphicsManager::SaveGradient(SqlConnection & connection,Gradient & gradient)
{
  QByteArray conf = gradient.Configure()                             ;
  SUID       uuid = gradient.uuid                                    ;
  if (uuid<=0)                                                       {
    uuid = connection.Unique(TABLES(MajorUuid),"uuid")               ;
    connection.assureUuid(TABLES(MajorUuid),uuid,N::Types::Painting) ;
    gradient.uuid = uuid                                             ;
  }                                                                  ;
  if (gradient.name.length()>0)                                      {
    assureName(connection,uuid,Language,gradient.name)               ;
  }                                                                  ;
  return SaveParaments(connection,uuid,N::Graphics::Gradient,conf)   ;
}

N::Contour N::GraphicsManager::GetContour(SqlConnection & connection,SUID uuid)
{
  QString    Q                                ;
  Contour   contour                           ;
  QByteArray data                             ;
  Q = connection.sql.SelectFrom               (
        "type,flags,contour"                  ,
        TABLES(Contours)                      ,
        connection.WhereUuid(uuid)          ) ;
  if (connection.Fetch(Q))                    {
    int T = connection.Int  (0)               ;
    int F = connection.Int  (1)               ;
    data  = connection.Value(2).toByteArray() ;
    contour . setData ( data )                ;
    contour . uuid      = uuid                ;
    contour . type      = T                   ;
    contour . closed    = IsMask(F,0x1)       ;
    contour . substract = IsMask(F,0x2)       ;
  }                                           ;
  contour .name = connection.getName          (
          TABLES(Names),"uuid",Language,uuid) ;
  return contour                              ;
}

bool N::GraphicsManager::SaveContour(SqlConnection & connection,Contour & contour,QImage & Snap)
{
  QString    Q                                  ;
  QByteArray outshape  = contour.Data()         ;
  int        Flags = 0                          ;
  Flags |= contour . closed    ? 0x01 :0        ;
  Flags |= contour . substract ? 0x02 :0        ;
  if (contour.uuid<=0)                          {
    contour.uuid = connection.Unique            (
      TABLES(MajorUuid),"uuid"                ) ;
    connection.assureUuid                       (
      TABLES(MajorUuid),contour.uuid            ,
      Types::Contour                          ) ;
    Q = connection.sql.InsertInto               (
          TABLES(Contours)                      ,
          5                                     ,
          "uuid"                                ,
          "type"                                ,
          "flags"                               ,
          "contour"                             ,
          "snap"                              ) ;
  } else                                        {
    Q = connection.sql.Update                   (
          TABLES(Contours)                      ,
          UuidWhere                             ,
          4                                     ,
          "type"                                ,
          "flags"                               ,
          "contour"                             ,
          "snap"                              ) ;
  }                                             ;
  if (contour.name.length()>0)                  {
    assureName                                  (
      connection                                ,
      contour.uuid                              ,
      Language                                  ,
      contour.name                            ) ;
  }                                             ;
  QByteArray snap = CompressPNG(Snap)           ;
  QByteArray data = qCompress(outshape)         ;
  connection.Prepare ( Q                      ) ;
  connection.Bind    ( "uuid"   ,contour.uuid ) ;
  connection.Bind    ( "type"   ,contour.type ) ;
  connection.Bind    ( "flags"  ,Flags        ) ;
  connection.Bind    ( "contour",data         ) ;
  connection.Bind    ( "snap"   ,snap         ) ;
  return connection . Exec (                  ) ;
}


QImage N::GraphicsManager::ContourSnap(QSize size,QPointF center,Contour & contour)
{
  QImage   I(size,QImage::Format_ARGB32)     ;
  QPointF  C(size.width()/2,size.height()/2) ;
  QRectF   r = contour . boundingRect ( )    ;
  double   f = r . width()                   ;
  double   m = size.width()                  ;
  QPolygon P                                 ;
  if (r.height()>f) f = r.height()           ;
  m /= f                                     ;
  for (int i=0;i<contour.count();i++)        {
    double  x = contour.points[i].x          ;
    double  y = contour.points[i].y          ;
    QPointF z(x,y)                           ;
    z -= center                              ;
    z *= m                                   ;
    z += C                                   ;
    int X = z . x ( )                        ;
    int Y = z . y ( )                        ;
    if (X<0) X = 0                           ;
    if (Y<0) Y = 0                           ;
    if (X>=size.width ()) X=size.width ()-1  ;
    if (Y>=size.height()) Y=size.height()-1  ;
    P << QPoint ( X , Y )                    ;
  }                                          ;
  memset(I.bits(),0,I.byteCount())           ;
  QPainter p                                 ;
  p . begin       ( &I                   )   ;
  p . setPen      ( QColor (  0,  0,255) )   ;
  p . setBrush    ( QColor (255,255,255) )   ;
  p . drawPolygon ( P , Qt::WindingFill  )   ;
  p . end         (                      )   ;
  return I                                   ;
}

SUID N::GraphicsManager::NewShape(SqlConnection & connection,QString name,int language)
{
  SUID uuid = connection.Unique(TABLES(MajorUuid),"uuid")        ;
  connection.assureUuid(TABLES(MajorUuid),uuid,N::Types::Shapes) ;
  connection.assureUuid(TABLES(Shapes)   ,uuid,2               ) ;
  assureName ( connection , uuid , language , name )             ;
  return uuid                                                    ;
}

QByteArray N::GraphicsManager::CompressPNG(QImage & image)
{
  QByteArray B                      ;
  QByteArray C                      ;
  QBuffer    A(&B)                  ;
  if (A.open(QIODevice::WriteOnly)) {
    image.save(&A,"PNG")            ;
    C = B                           ;
    A.close()                       ;
  }                                 ;
  B.clear()                         ;
  return qCompress(C)               ;
}

bool N::GraphicsManager::LoadColors(SqlConnection & SC,SUID uuid,Colors & colors)
{
  QString    Q                            ;
  QByteArray M                            ;
  QByteArray C                            ;
  Q = SC.sql.SelectFrom                   (
        "members"                         ,
        TABLES(ColorGroups)               ,
        SC.WhereUuid(uuid)              ) ;
  if (SC.Fetch(Q))                        {
    M = SC.ByteArray(0)                   ;
  }                                       ;
  nKickOut ( M.size() <= 0 , false )      ;
  C = XzUncompress(M)                     ;
  nKickOut ( C.size() <= 0 , false )      ;
  Graphics::addColors(C,colors)           ;
  Graphics::Uniqueness(colors)            ;
  return true                             ;
}

bool N::GraphicsManager::SaveColors(SqlConnection & SC,SUID & uuid,Colors & colors)
{
  if (uuid<=0)                                                        {
    uuid = SC.Unique(TABLES(MajorUuid),"uuid",7799)                   ;
    SC.insertUuid(TABLES(MajorUuid),uuid,Types::ColorGroup          ) ;
    SC.insertUuid(TABLES(ColorGroups),uuid,"uuid")                    ;
  }                                                                   ;
  QString    Q                                                        ;
  QByteArray M                                                        ;
  QByteArray C                                                        ;
  if (colors.count()>0)                                               {
    Graphics::toByteArray(colors,M)                                   ;
    C = XzCompress(M)                                                 ;
  }                                                                   ;
  Q = SC.sql.Update                                                   (
        TABLES(ColorGroups)                                           ,
        SC.sql.Where(1,"uuid")                                        ,
        3,"colors","length","members"                               ) ;
  SC . Prepare ( Q                             )                      ;
  SC . Bind    ( "uuid"    , uuid              )                      ;
  SC . Bind    ( "colors"  , colors . length() )                      ;
  SC . Bind    ( "length"  , C      . size  () )                      ;
  SC . Bind    ( "members" , C                 )                      ;
  return SC.Exec (                             )                      ;
}
