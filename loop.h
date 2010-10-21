#ifndef LOOP_H
#define LOOP_H

#include <stdio.h>

namespace scm {

	class Mainloop {
	public:
		Mainloop();
		~Mainloop();
		
		int Init();

	private:
		bool started_;		
	};

} //namespace scm

#endif
