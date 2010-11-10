//#include "main.cc"
#include <crml-core.h>
#include <crml-win.h>

using namespace crml;

void Core::MainLoop() {  
  Display dsp;
  dsp.ReportErr();
  
  for (int i = 0; i < 10; i++) {
    printf("Height: %d\n", dsp.Height());
    printf("Width: %d\n", dsp.Width());
    printf("in ur loops eating ur cycles\n");
    Core::self_->ReportErr();
  }
  
  //Image img1("gopher.png"); 
  //Coord c1(0, 0);
  //Sprite spr1(img1, c1);
  
  //while(Core::Running()){
  //dsp.ShowAt(c1, spr1);    
  //c1.MoveX(1);
  //}
}
