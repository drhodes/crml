#include <crml-core.h>
#include <crml-win.h>
#include <crml-sys.h>
#include <crml-evt.h>

using namespace crml;

Core core = *Core::self_;
Event evt;
Display dsp;
Clock timer1, timer2;
int frame = 0;
int fps = 15;
uint32_t* pixels_;
bool firstrun = true;
NPPepperEvent e;
int x = 1;
int y = 1;


void FirstRun() {
    dsp.Init();
    pixels_ = dsp.Pixels();
    firstrun = false;    
}

void Core::MainLoop() {

  if (firstrun) {
    FirstRun();  
  }              
  // change the js calling code of this function to call as many times as possible.
  // if timer1.Elapsed is greater than the framespan run the frame.
  // else just return.
  
  // timer1.Reset();  
  while(evt.GetEvent(&e)) {
    switch(e.type) {
      case NPEventType_MouseMove:
        printf("ASDF\n");
        x = e.u.mouse.x;
        y = e.u.mouse.y;        
    }
  }
    
  //printf("fps: %f\n", frame / timer2.ElapsedSec() );
  //printf("in ur loops eating ur cycles\n");  
  //usleep( (1e6 * 1/fps) - timer1.ElapsedMicro() );

  int numpix = dsp.Width() * dsp.Height();
  
  if (dsp.Ok()) {
    for (int i = 0; i < numpix; i++) {
      if (i % x == 0) continue;
      if (i % y == 0) continue;
      pixels_[i] = frame*i*i;
    }
  }
  
  frame += 1;
  //printf("frame: %d\n", frame);
  dsp.Redraw();
}
  
  //Image img1("gopher.png"); 
  //Coord c1(0, 0);
  //Sprite spr1(img1, c1);
  
  //while(Core::Running()){
  //dsp.ShowAt(c1, spr1);    
  //c1.MoveX(1);
  //}

