#ifndef CLOCK_H
#define CLOCK_H

//  thin wrapper for
//  nacl_sdk/toolchain/linux_x86/nacl64/usr/include/osg/Timer


#include <osg/Timer>		

namespace scm {
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
} // namespace scm

#endif
