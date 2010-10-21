#ifndef LOOP_CC
#define LOOP_CC

#include "loop.h"
#include <stdio.h>

namespace scm {
	Mainloop::Mainloop(){
		started_ = false;
	}

	Mainloop::~Mainloop(){		
	}
	
	int Mainloop::Init(){
		if (!started_){
			started_ = true;
			printf("Starting Loop thread\n");
		}
		return 1; 
	}
} // namespace scm

#endif
