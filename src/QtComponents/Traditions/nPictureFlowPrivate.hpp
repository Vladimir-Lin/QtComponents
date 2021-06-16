#ifndef PICTUREFLOWPRIVATE_HPP
#define PICTUREFLOWPRIVATE_HPP

#include <QtComponents>

#define PFREAL_SHIFT 10
#define PFREAL_ONE (1 << PFREAL_SHIFT)

#define IANGLE_MAX 1024
#define IANGLE_MASK 1023

typedef long PFreal ;

PFreal fmul ( PFreal a   , PFreal b   ) ;
PFreal fdiv ( PFreal num , PFreal den ) ;
PFreal fsin ( int iangle ) ;
PFreal fcos ( int iangle ) ;

struct SlideInfo
{
  int    slideIndex ;
  int    angle      ;
  PFreal cx         ;
  PFreal cy         ;
  int    blend      ;
};

class PictureFlowState
{
  public:

    QRgb               backgroundColor  ;
    int                slideWidth       ;
    int                slideHeight      ;
    int                reflectionEffect ;
    QVector<QImage *>  slideImages      ;
    int                angle            ;
    int                spacing          ;
    PFreal             offsetX          ;
    PFreal             offsetY          ;
    SlideInfo          centerSlide      ;
    QVector<SlideInfo> leftSlides       ;
    QVector<SlideInfo> rightSlides      ;
    int                centerIndex      ;

    explicit PictureFlowState (void) ;
    virtual ~PictureFlowState (void) ;

    void     reposition       (void) ;
    void     reset            (void) ;

};

class PictureFlowAnimator
{
  public:

    PictureFlowState * state        ;
    int                target       ;
    int                step         ;
    int                frame        ;
    QTimer             animateTimer ;

    explicit PictureFlowAnimator (void) ;
    virtual ~PictureFlowAnimator (void) ;

    void     start               (int slide) ;
    void     stop                (int slide) ;
    void     update              (void) ;

};

class PictureFlowAbstractRenderer
{
  public:

    PictureFlowState  * state   ;
    bool                dirty   ;
    QWidget           * widget  ;
    enum QImage::Format iFormat ;

    explicit PictureFlowAbstractRenderer (void                )
             : state                     (0                   )
             , dirty                     (false               )
             , widget                    (0                   )
             , iFormat                   (QImage::Format_RGB32)
    {
    }

    virtual ~PictureFlowAbstractRenderer(void)
    {
    }

    virtual void init  (void) = 0 ;
    virtual void paint (void) = 0 ;

};

class PictureFlowSoftwareRenderer: public PictureFlowAbstractRenderer
{
  public:

    explicit PictureFlowSoftwareRenderer (void) ;
    virtual ~PictureFlowSoftwareRenderer (void) ;

    virtual void init  (void) ;
    virtual void paint (void) ;

  protected:

    QSize              size         ;
    QRgb               bgcolor      ;
    int                effect       ;
    QImage             buffer       ;
    QVector<PFreal>    rays         ;
    QImage *           blankSurface ;
    QCache<int,QImage> surfaceCache ;
    QHash<int,QImage*> imageHash    ;

    void     render       (void) ;
    void     renderSlides (void) ;
    QRect    renderSlide  (const SlideInfo & slide, int col1 = -1, int col2 = -1) ;
    QImage * surface      (int slideIndex) ;

};

class PictureFlowPrivate
{
  public:

    PictureFlowState            * state        ;
    PictureFlowAnimator         * animator     ;
    PictureFlowAbstractRenderer * renderer     ;
    QTimer                        triggerTimer ;

};

#endif // PICTUREFLOWPRIVATE_HPP
