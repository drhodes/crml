#ifndef LOOP_CC
#define LOOP_CC

#include "loop.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

namespace scm {
	Mainloop::Mainloop(){
		started_ = false;
	}

	Mainloop::~Mainloop(){		
	}

	static void* execute_go(void* ctx) {
		Mainloop* cptr = (Mainloop*)ctx;
		cptr->Go();
		return NULL;
	}
	
	void Mainloop::Go(){
		int frame = 0;
		while (1){
			printf("scm<-- frame %d\n", frame);
			frame += 1;			
		}
	}

	MainloopErr Mainloop::Init(PluginObject* po){
		if (po == 0) {
			return InitFails;
		}

		if (!started_){
			started_ = true;
			plugin_ = po;
			printf("scm <-- Init Loop\n");

			// spawn thread here.
			pthread_create(&loop_, NULL, execute_go, this);



			return InitSucceeds;
		}
		return InitFails;
	}

} // namespace scm

#endif

