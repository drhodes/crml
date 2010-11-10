//#include "main.cc"
#include <crml-core.h>
#include <crml-win.h>
#include <crml-sys.h>

using namespace crml;

void Core::MainLoop() {
  Core* core = Core::self_;
  Display dsp;
  //dsp.Pixels();
  dsp.ReportErr();
  
  Clock timer1, timer2;
  int frame = 0;
  int fps = 2;
  
  while (1){
    timer1.Reset();
    printf("fps: %f\n", frame / timer2.ElapsedSec() );
 
    printf("Height: %d\n", dsp.Height());
    printf("Width: %d\n", dsp.Width());
    printf("in ur loops eating ur cycles\n");

    usleep( (1e6 * 1/fps) - timer1.ElapsedMicro() );
    frame += 1;

    core->ReportErr();
  }
  
  //Image img1("gopher.png"); 
  //Coord c1(0, 0);
  //Sprite spr1(img1, c1);
  
  //while(Core::Running()){
  //dsp.ShowAt(c1, spr1);    
  //c1.MoveX(1);
  //}
}
