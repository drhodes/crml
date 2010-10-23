#include "test-macros.cc"
#include "clock.cc"

namespace scm {
	bool TestClock(Scene* s) {
		std::string modulename = "Clock";
		Clock c = Clock();
		pass("Clock default constructor");

		c.Reset();
		pass("Clock resets ok");
		
		ok( c.ElapsedSec() > -1, "ElapsedSec" );
		ok( c.ElapsedMilli() > -1, "ElapsedMilli" );
		ok( c.ElapsedMicro() > -1, "ElapsedMicro" );
		ok( c.ElapsedNano() > -1, "ElapsedNano" );
		
		return true;
	}
}
