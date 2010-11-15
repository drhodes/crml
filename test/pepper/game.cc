#include <crml-core.h>
#include <crml-win.h>
#include <crml-sys.h>
#include <crml-evt.h>

#include "./square.h"

using namespace crml;
#define NUMSQUARES 5000

//Core core = *Core::self_;
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
Square sqs[NUMSQUARES];

// move this off to color.h in the lib under gfx.
inline uint32_t MakeRGBA(uint32_t r, uint32_t g, uint32_t b, uint32_t a) {
  return (((a) << 24) | ((r) << 16) | ((g) << 8) | (b));
}

void RunOnce() {
    dsp.Init();
    pixels_ = dsp.Pixels();

    firstrun = false;    
}

void Core::MainLoop() {
    if (firstrun) {
    RunOnce();
    for(int i=0; i<NUMSQUARES; i++){
      sqs[i] = Square();
      sqs[i].Randomize(timer1.ElapsedNano());
      usleep(1);
    }   
  }

  if (timer1.ElapsedMilli() < 32){
    return;
  }
  
  timer1.Reset();
 

  while(evt.GetEvent(&e)) {
    switch(e.type) {
      case NPEventType_MouseDown:
        x = e.u.mouse.x;
        y = e.u.mouse.y;
        for(int i=0; i<NUMSQUARES; i++){
          sqs[i].X(x);
          sqs[i].Y(y);
        }
        break;
    }
  }
      
  //dsp.Wipe(MakeRGBA(frame%100,frame%200,frame%255,255));
  dsp.Wipe();

  for(int i=0; i<NUMSQUARES; i++){
    sqs[i].Draw(pixels_, dsp.Width(), dsp.Height());
    sqs[i].Move(dsp.Width(), dsp.Height());
    if (frame%10 == 0){      
      sqs[i].Flick(timer1.ElapsedNano());
    }
  }

  if (frame%100 == 0){      
    printf("Flick!\n");
  }  
  
  frame += 1;    
  dsp.Redraw();
}
  
  //Image img1("gopher.png"); 
  //Coord c1(0, 0);
  //Sprite spr1(img1, c1);
  
  //while(Core::Running()){
  //dsp.ShowAt(c1, spr1);    
  //c1.MoveX(1);
  //}

