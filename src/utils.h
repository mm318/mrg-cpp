#ifndef _UTIL_H_
#define _UTIL_H_

#include "RingBuffer.h"
#include "MRG.h"


void MRG_interp1(const MRG_MATRIX_REAL &x, const MRG_MATRIX_REAL &y, const MRG_MATRIX_REAL &xi, MRG_MATRIX_REAL &yi);

inline void interp1(const MRG_MATRIX_REAL & x, const MRG_MATRIX_REAL & y, const MRG_MATRIX_REAL & xi, MRG_MATRIX_REAL & yi)
{
  MRG_interp1(x, y, xi, yi);
}

#endif
