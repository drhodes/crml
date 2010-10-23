#include main.cc

int mainloop(){
	scm::Display* dsp = GAME.GetDisplay();

	while (GAME.running()){
		nanosleep(1);
		
	}
}

GAME.RegisterLoop(*mainloop);

