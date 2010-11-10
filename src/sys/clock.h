#ifndef CLOCK_H_
#define CLOCK_H_

//  thin wrapper for
//  nacl_sdk/toolchain/linux_x86/nacl64/usr/include/osg/Timer

#include <osg/Timer>		

namespace crml {
  class Clock {
   public:
    Clock();
    void Reset();
    double ElapsedSec(); // return seconds.		
    double ElapsedMilli();
    double ElapsedMicro();
    double ElapsedNano();
		
   private:		
    osg::Timer timer_;
  };
  
}       // namespace crml
#endif  // CLOCK_H_
