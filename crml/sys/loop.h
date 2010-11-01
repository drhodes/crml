#ifndef LOOP_H
#define LOOP_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <core/plugin_object.h>
#include <sys/clock.h>
#include <core/nacl_syscalls.h>

namespace scm {
	enum MainloopErr {
		InitFails = 0,
		InitSucceeds = 1,
		Bad2DDevice = 2,
		NegativeFPS = 3,		
	};

	class Mainloop {
	public:
		Mainloop();
		~Mainloop();

		void Go();
		MainloopErr SetFramesPerSecond(double);
		MainloopErr Init(PluginObject*);
		MainloopErr Init2D(NPDevice*);

	private:
		Clock clock_;
		bool started_; // main loop started?
		double fps_; 
		
		PluginObject* plugin_;
		pthread_t loop_;	

		
		NPDevice* device2d_;	
	};
} //namespace scm

#endif
