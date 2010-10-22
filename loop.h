#ifndef LOOP_H
#define LOOP_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "plugin_object.h"

namespace scm {
	enum MainloopErr {
		InitFails = 0,
		InitSucceeds = 1,
	};

	class Mainloop {
	public:
		Mainloop();
		~Mainloop();

		void Go();
		MainloopErr Init(PluginObject*);

	private:
		bool started_;		
		PluginObject* plugin_;
		pthread_t loop_;
	};
} //namespace scm

#endif
