#include <qtcomponents.h>
#include "nPictureFlowPrivate.hpp"

PFreal fmul(PFreal a, PFreal b)
{
  return ((long long)(a))*((long long)(b)) >> PFREAL_SHIFT;
}

PFreal fdiv(PFreal num, PFreal den)
{
  long long p = (long long)(num) << (PFREAL_SHIFT*2);
  long long q = p / (long long)den;
  long long r = q >> PFREAL_SHIFT;

  return r;
}

PFreal fsin(int iangle)
{
  // warning: regenerate the table if IANGLE_MAX and PFREAL_SHIFT are changed!
  static const PFreal tab[] = {
     3,    103,    202,    300,    394,    485,    571,    652,
   726,    793,    853,    904,    947,    980,   1004,   1019,
  1023,   1018,   1003,    978,    944,    901,    849,    789,
   721,    647,    566,    479,    388,    294,    196,     97,
    -4,   -104,   -203,   -301,   -395,   -486,   -572,   -653,
  -727,   -794,   -854,   -905,   -948,   -981,  -1005,  -1020,
 -1024,  -1019,  -1004,   -979,   -945,   -902,   -850,   -790,
  -722,   -648,   -567,   -480,   -389,   -295,   -197,    -98,
  3
  };

  while(iangle < 0)
    iangle += IANGLE_MAX;
  iangle &= IANGLE_MASK;

  int i = (iangle >> 4);
  PFreal p = tab[i];
  PFreal q = tab[(i+1)];
  PFreal g = (q - p);
  return p + g * (iangle-i*16)/16;
}

PFreal fcos(int iangle)
{
  return fsin(iangle + (IANGLE_MAX >> 2));
}
