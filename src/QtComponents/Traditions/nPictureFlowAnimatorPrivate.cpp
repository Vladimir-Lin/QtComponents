#include <qtcomponents.h>
#include "nPictureFlowPrivate.hpp"

PictureFlowAnimator:: PictureFlowAnimator (void)
                    : state               (0   )
                    , target              (0   )
                    , step                (0   )
                    , frame               (0   )
{
}

PictureFlowAnimator::~PictureFlowAnimator(void)
{
}

void PictureFlowAnimator::start(int slide)
{
  target = slide                                             ;
  if (!animateTimer.isActive() && state)                     {
    step = (target < state->centerSlide.slideIndex) ? -1 : 1 ;
    animateTimer.start(30)                                   ;
  }                                                          ;
}

void PictureFlowAnimator::stop(int slide)
{
  step         = 0           ;
  target       = slide       ;
  frame        = slide << 16 ;
  animateTimer . stop()      ;
}

void PictureFlowAnimator::update(void)
{
  if (!animateTimer.isActive()) return ;
  if ( step == 0              ) return ;
  if (!state                  ) return ;

  int speed = 16384/4;

#if 1
  // deaccelerate when approaching the target
  const int max = 2 * 65536;

  int fi = frame;
  fi -= (target << 16);
  if(fi < 0)
    fi = -fi;
  fi = qMin(fi, max);

  int ia = IANGLE_MAX * (fi-max/2) / (max*2);
  speed = 512 + 16384 * (PFREAL_ONE+fsin(ia))/PFREAL_ONE;
#endif

  frame += speed*step;

  int index = frame >> 16;
  int pos = frame & 0xffff;
  int neg = 65536 - pos;
  int tick = (step < 0) ? neg : pos;
  PFreal ftick = (tick * PFREAL_ONE) >> 16;

  if(step < 0)
    index++;

  if(state->centerIndex != index)
  {
    state->centerIndex = index;
    frame = index << 16;
    state->centerSlide.slideIndex = state->centerIndex;
    for(int i = 0; i < (int)state->leftSlides.count(); i++)
      state->leftSlides[i].slideIndex = state->centerIndex-1-i;
    for(int i = 0; i < (int)state->rightSlides.count(); i++)
      state->rightSlides[i].slideIndex = state->centerIndex+1+i;
  }

  state->centerSlide.angle = (step * tick * state->angle) >> 16;
  state->centerSlide.cx = -step * fmul(state->offsetX, ftick);
  state->centerSlide.cy = fmul(state->offsetY, ftick);

  if(state->centerIndex == target)
  {
    stop(target);
    state->reset();
    return;
  }

  for(int i = 0; i < (int)state->leftSlides.count(); i++)
  {
    SlideInfo& si = state->leftSlides[i];
    si.angle = state->angle;
    si.cx = -(state->offsetX + state->spacing*i*PFREAL_ONE + step*state->spacing*ftick);
    si.cy = state->offsetY;
  }

  for(int i = 0; i < (int)state->rightSlides.count(); i++)
  {
    SlideInfo& si = state->rightSlides[i];
    si.angle = -state->angle;
    si.cx = state->offsetX + state->spacing*i*PFREAL_ONE - step*state->spacing*ftick;
    si.cy = state->offsetY;
  }

  if(step > 0)
  {
    PFreal ftick = (neg * PFREAL_ONE) >> 16;
    state->rightSlides[0].angle = -(neg * state->angle) >> 16;
    state->rightSlides[0].cx = fmul(state->offsetX, ftick);
    state->rightSlides[0].cy = fmul(state->offsetY, ftick);
  }
  else
  {
    PFreal ftick = (pos * PFREAL_ONE) >> 16;
    state->leftSlides[0].angle = (pos * state->angle) >> 16;
    state->leftSlides[0].cx = -fmul(state->offsetX, ftick);
    state->leftSlides[0].cy = fmul(state->offsetY, ftick);
  }

  // must change direction ?
  if(target < index) if(step > 0)
    step = -1;
  if(target > index) if(step < 0)
    step = 1;

  // the first and last slide must fade in/fade out
  int nleft = state->leftSlides.count();
  int nright = state->rightSlides.count();
  int fade = pos / 256;

  for(int index = 0; index < nleft; index++)
  {
    int blend = 256;
    if(index == nleft-1)
      blend = (step > 0) ? 0 : 128-fade/2;
    if(index == nleft-2)
      blend = (step > 0) ? 128-fade/2 : 256-fade/2;
    if(index == nleft-3)
      blend = (step > 0) ? 256-fade/2 : 256;
    state->leftSlides[index].blend = blend;
  }
  for(int index = 0; index < nright; index++)
  {
    int blend = (index < nright-2) ? 256 : 128;
    if(index == nright-1)
      blend = (step > 0) ? fade/2 : 0;
    if(index == nright-2)
      blend = (step > 0) ? 128+fade/2 : fade/2;
    if(index == nright-3)
      blend = (step > 0) ? 256 : 128+fade/2;
    state->rightSlides[index].blend = blend;
  }

}
