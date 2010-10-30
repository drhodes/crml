// Copyright 2010 <Derek A. Rhodes> All Rights Reseverd.

#ifndef CLOCK_CC
#define CLOCK_CC
/* thin wrapper for
   nacl_sdk/toolchain/linux_x86/nacl64/usr/include/osg/Timer
*/

#include <time.h>
#include "./clock.h"

namespace scm {

Clock::Clock() {
  Reset();
}

void Clock::Reset() {
  timer_.setStartTick();
}

double Clock::ElapsedSec() {
  return timer_.time_s();
}

double Clock::ElapsedMilli() {
  return timer_.time_m();
}

double Clock::ElapsedMicro() {
  return timer_.time_u();
}

double Clock::ElapsedNano() {
  return timer_.time_n();
}

}  // namespace scm

#endif
