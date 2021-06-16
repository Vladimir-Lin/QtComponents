#include <qtcomponents.h>
#include "nPictureFlowPrivate.hpp"

PictureFlowState:: PictureFlowState (void)
                 : backgroundColor  (0   )
                 , slideWidth       (150 )
                 , slideHeight      (200 )
                 , reflectionEffect (2   )
                 , centerIndex      (0   )
{
}

PictureFlowState::~PictureFlowState(void)
{
  for (int i = 0; i < (int)slideImages.count(); i++) {
    delete slideImages[i]                            ;
  }                                                  ;
}

// readjust the settings, call this when slide dimension is changed
void PictureFlowState::reposition(void)
{
  angle    = 70 * IANGLE_MAX    / 360                      ; // approx. 70 degrees tilted
  offsetX  = ( slideWidth / 2 ) * (PFREAL_ONE-fcos(angle)) ;
  offsetY  = ( slideWidth / 2 ) * fsin(angle)              ;
  offsetX +=   slideWidth       * PFREAL_ONE               ;
  offsetY +=   slideWidth       * PFREAL_ONE / 4           ;
  spacing  = 40                                            ;
}

// adjust slides so that they are in "steady state" position
void PictureFlowState::reset(void)
{
  centerSlide.angle      = 0           ;
  centerSlide.cx         = 0           ;
  centerSlide.cy         = 0           ;
  centerSlide.slideIndex = centerIndex ;
  centerSlide.blend      = 256         ;

  leftSlides.resize(6);
  for(int i = 0; i < (int)leftSlides.count(); i++)
  {
    SlideInfo& si = leftSlides[i];
    si.angle = angle;
    si.cx = -(offsetX + spacing*i*PFREAL_ONE);
    si.cy = offsetY;
    si.slideIndex = centerIndex-1-i;
    si.blend = 256;
    if(i == (int)leftSlides.count()-2)
      si.blend = 128;
    if(i == (int)leftSlides.count()-1)
      si.blend = 0;
  }

  rightSlides.resize(6);
  for(int i = 0; i < (int)rightSlides.count(); i++)
  {
    SlideInfo & si = rightSlides[i];
    si.angle = -angle;
    si.cx = offsetX + spacing*i*PFREAL_ONE;
    si.cy = offsetY;
    si.slideIndex = centerIndex+1+i;
    si.blend = 256;
    if(i == (int)rightSlides.count()-2)
      si.blend = 128;
    if(i == (int)rightSlides.count()-1)
      si.blend = 0;
  }
}
