#ifndef LOOP_CC
#define LOOP_CC

#include "loop.h"
#include "clock.h"
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <stdlib.h>

namespace scm {
	Mainloop::Mainloop(){
		started_ = false;
		//clock_ = Clock();
		SetFramesPerSecond(1);
	}

	Mainloop::~Mainloop(){		
	}

	// this hack is necessary for calling the Go method.
	// c++0x <thread> isn't working atm.
	static void* execute_go(void* ctx) {
		Mainloop* cptr = (Mainloop*)ctx;
		cptr->Go();
		return NULL;
	}

	void Mainloop::Go(){
		Clock timer;
		int frame = 0;
		
		while (started_){
			clock_.Reset();
			printf("fps: %f\n", frame / timer.ElapsedSec() );
			/*
			  Do stuff here

			*/
			usleep( (1e6 * 1/fps_) - clock_.ElapsedMicro() );
			frame += 1;
		}
	}
   
	MainloopErr Mainloop::Init2D(NPDevice* device2d){
		if (device2d == 0){
			return Bad2DDevice;
		}
		device2d_ = device2d;		
		return InitSucceeds;
	}

	MainloopErr Mainloop::SetFramesPerSecond(double fps){
		assert(fps > 0);
		fps_ = fps;
		return InitSucceeds;
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

		SetFramesPerSecond(60);
		return InitFails;
	}	
} // namespace scm

#endif

