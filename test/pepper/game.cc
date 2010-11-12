//#include "main.cc"
#include <crml-core.h>
#include <crml-win.h>
#include <crml-sys.h>

using namespace crml;

Core core = *Core::self_;
Display dsp;
Clock timer1, timer2;
int frame = 0;
int fps = 2;
uint32_t* pixels_;


bool firstrun = true;

void FirstRun() {
    dsp.Init();
    pixels_ = dsp.Pixels();
    firstrun = false; 
}

void Core::MainLoop() {
  if (firstrun)
    FirstRun();

  timer1.Reset();
  
  printf("fps: %f\n", frame / timer2.ElapsedSec() );
  printf("in ur loops eating ur cycles\n");
  
  //usleep( (1e6 * 1/fps) - timer1.ElapsedMicro() );

  int numpix = dsp.Width() * dsp.Height();
  
  if (dsp.Ok()) {
    for (int i = 0; i < numpix; i++) {
      pixels_[i] = frame*i*i;
    }
  }
  
  frame += 1;
  printf("frame: %d\n", frame);
  dsp.Redraw();
}
  
  //Image img1("gopher.png"); 
  //Coord c1(0, 0);
  //Sprite spr1(img1, c1);
  
  //while(Core::Running()){
  //dsp.ShowAt(c1, spr1);    
  //c1.MoveX(1);
  //}

