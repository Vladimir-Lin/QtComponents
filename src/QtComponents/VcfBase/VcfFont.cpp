#include <qtcomponents.h>

typedef struct {
  int Style    ;
  int R        ;
  int G        ;
  int B        ;
  int A        ;
} VcfFontBrush ;

typedef struct  {
  int Style     ;
  int CapStyle  ;
  int R         ;
  int G         ;
  int B         ;
  int A         ;
  int Cosmetics ;
  double Width  ;
} VcfFontPen    ;

typedef struct {
  char   Family [4096]   ;
  double Size            ;
  int    Stretch         ;
  int    Weight          ;
  int    FixedPitch      ;
  int    Bold            ;
  int    Italic          ;
  int    Kerning         ;
  int    Overline        ;
  int    StrikeOut       ;
  int    Underline       ;
  VcfFontPen   Pen       ;
  VcfFontBrush PenBrush  ;
  VcfFontBrush Brush     ;
  VcfFontBrush Selection ;
} VcfFontConfiguration   ;

N::VcfFont:: VcfFont (void )
           : uuid    (0    )
           , size    (0.40 )
           , changed (false)
{
}

N::VcfFont::~VcfFont(void)
{
}

QByteArray N::VcfFont::Configuration(void)
{
  VcfFontConfiguration VF                                  ;
  QByteArray FontConf                                      ;
  FontConf.resize(sizeof(VcfFontConfiguration))            ;
  QString family = font.family()                           ;
  memset(&VF,0,sizeof(VcfFontConfiguration))               ;
  strcpy(VF.Family,family.toUtf8().data())                 ;
  QColor C                                                 ;
  VF.Size            = size                                ;
  VF.Stretch         = font . stretch    ()                ;
  VF.Weight          = font . weight     ()                ;
  VF.FixedPitch      = font . fixedPitch () ? 1 : 0        ;
  VF.Bold            = font . bold       () ? 1 : 0        ;
  VF.Italic          = font . italic     () ? 1 : 0        ;
  VF.Kerning         = font . kerning    () ? 1 : 0        ;
  VF.Overline        = font . overline   () ? 1 : 0        ;
  VF.StrikeOut       = font . strikeOut  () ? 1 : 0        ;
  VF.Underline       = font . underline  () ? 1 : 0        ;
  VF.Pen.Style       = pen  . style      ()                ;
  C                  = pen  . color      ()                ;
  VF.Pen.R           = C    . red        ()                ;
  VF.Pen.G           = C    . green      ()                ;
  VF.Pen.B           = C    . blue       ()                ;
  VF.Pen.A           = C    . alpha      ()                ;
  VF.Pen.CapStyle    = pen  . capStyle   ()                ;
  VF.Pen.Cosmetics   = pen  . isCosmetic ()                ;
  VF.Pen.Width       = pen  . widthF     ()                ;
  VF.PenBrush.Style  = penBrush . style  ()                ;
  C                  = penBrush . color  ()                ;
  VF.PenBrush.R      = C    . red        ()                ;
  VF.PenBrush.G      = C    . green      ()                ;
  VF.PenBrush.B      = C    . blue       ()                ;
  VF.PenBrush.A      = C    . alpha      ()                ;
  VF.Brush.Style     = brush. style      ()                ;
  C                  = brush. color      ()                ;
  VF.Brush.R         = C    . red        ()                ;
  VF.Brush.G         = C    . green      ()                ;
  VF.Brush.B         = C    . blue       ()                ;
  VF.Brush.A         = C    . alpha      ()                ;
  VF.Selection.Style = selection . style ()                ;
  C                  = selection . color ()                ;
  VF.Selection.R     = C    . red        ()                ;
  VF.Selection.G     = C    . green      ()                ;
  VF.Selection.B     = C    . blue       ()                ;
  VF.Selection.A     = C    . alpha      ()                ;
  memcpy(FontConf.data(),&VF,sizeof(VcfFontConfiguration)) ;
  return FontConf                                          ;
}

void N::VcfFont::Set(QByteArray Conf)
{
  VcfFontConfiguration * VF = (VcfFontConfiguration *)Conf.data() ;
  QColor C                                                        ;
  font.setFamily(QString::fromUtf8(VF->Family))                   ;
  size = VF->Size                                                 ;
  font . setStretch    (VF->Stretch      )                        ;
  font . setWeight     (VF->Weight       )                        ;
  font . setBold       (VF->Bold      ==1)                        ;
  font . setFixedPitch (VF->FixedPitch==1)                        ;
  font . setItalic     (VF->Italic    ==1)                        ;
  font . setKerning    (VF->Kerning   ==1)                        ;
  font . setOverline   (VF->Overline  ==1)                        ;
  font . setStrikeOut  (VF->StrikeOut ==1)                        ;
  font . setUnderline  (VF->Underline ==1)                        ;
  C.setRed   (VF->Pen.R)                                          ;
  C.setGreen (VF->Pen.G)                                          ;
  C.setBlue  (VF->Pen.B)                                          ;
  C.setAlpha (VF->Pen.A)                                          ;
  pen.setColor   (C                   )                           ;
  pen.setStyle   ((Qt::PenStyle)VF->Pen.Style)                    ;
  pen.setCapStyle((Qt::PenCapStyle)VF->Pen.CapStyle)              ;
  pen.setCosmetic(VF->Pen.Cosmetics==1)                           ;
  pen.setWidthF  (VF->Pen.Width       )                           ;
  C.setRed   (VF->PenBrush.R)                                     ;
  C.setGreen (VF->PenBrush.G)                                     ;
  C.setBlue  (VF->PenBrush.B)                                     ;
  C.setAlpha (VF->PenBrush.A)                                     ;
  penBrush.setColor(C)                                            ;
  penBrush.setStyle((Qt::BrushStyle)VF->PenBrush.Style)           ;
  C.setRed   (VF->Brush.R)                                        ;
  C.setGreen (VF->Brush.G)                                        ;
  C.setBlue  (VF->Brush.B)                                        ;
  C.setAlpha (VF->Brush.A)                                        ;
  brush.setColor(C)                                               ;
  brush.setStyle((Qt::BrushStyle)VF->Brush.Style)                 ;
  C.setRed   (VF->Selection.R)                                    ;
  C.setGreen (VF->Selection.G)                                    ;
  C.setBlue  (VF->Selection.B)                                    ;
  C.setAlpha (VF->Selection.A)                                    ;
  selection.setColor(C)                                           ;
  selection.setStyle((Qt::BrushStyle)VF->Selection.Style)         ;
}

void N::VcfFont::setFont(QPainter * p,int dpi)
{
  double fntsize = size ;
  QPen   pn      = pen  ;
  QFont  F       = font ;
  fntsize       *= dpi  ;
  fntsize       *= 100  ;
  fntsize       /= 254  ;
  F.setPixelSize((int)fntsize);
  if (penBrush.style()!=Qt::NoBrush) pn.setBrush(penBrush);
  p->setPen(pn);
  p->setFont(F);
}

QRectF N::VcfFont::boundingRect(QString text,int dpi)
{
  double fntsize = size ;
  QFont  F       = font ;
  fntsize       *= dpi  ;
  fntsize       *= 100  ;
  fntsize       /= 254  ;
  F.setPixelSize((int)fntsize);
  QFontMetricsF FMF(F);
  return FMF.boundingRect(text);
}

N::VcfFont & N::VcfFont::operator = (Font & f)
{
  font = f    ;
  size = f.cm ;
  return ME   ;
}
