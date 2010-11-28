#include <crml-core.h>
#include <crml-win.h>
#include <crml-sys.h>
#include <crml-evt.h>
#include <crml-gfx.h>

#include <osg/GL>
#include <osg/Endian>

#include <sstream>
#include <iostream>

#include "./square.h"
#include <media-blob.h>
#include <png.h>
#include <zlib.h>
#include "osg-png-ripoff.cc"

using namespace crml;
#define NUMSQUARES 1000

Event evt;
Display dsp;
Clock timer1, timer2;
Color c;
Font incon(fnt__inconsolata_otf);
int frame = 0;
int fps = 15;
uint32_t* pixels_;
bool firstrun = true;
NPPepperEvent e;
int x = 1;
int y = 1;
Square sqs[NUMSQUARES];
LayerGroup lg;

void RunOnce() {
  Error::DebugOn();
  
  dsp.Init();
  //pixels_ = dsp.Pixels();
  firstrun = false;

  /*
  std::string str1(txt__hello_txt);
  printf("txt: %s\n", str1.c_str()-1);
  printf("md5: %s\n", MD5String(str1).c_str());
  
  std::string str2(img__doodle_png, sizeof(img__doodle_png)-1);
  printf("bin: img__doodle_png\n");
  printf("md5: %s\n", MD5String(str2).c_str()); 
  //printf("md5: %s\n", MD5String(str2).c_str()); 
  
  std::stringstream ss (std::stringstream::in | std::stringstream::out);
  ss << str2;
  readPNGStream(ss);
  */    
  lg.AddTop("clouds");
  lg.AddTop("stars");
  lg.AddBottom("background");  
  lg.Check();

}

void Core::Main3D(){
  if (firstrun) {
    RunOnce();    
  }

  printf("Hello from game\n");
  if (timer1.ElapsedMilli() < 10){
    return;
  }
  glViewport(0, 0, dsp.Width(), dsp.Height());


  GLFromCPPDraw();
  
  //pglSwapBuffers();
  //pglMakeCurrent(NULL);
  

  
  timer1.Reset();
  dsp.Wipe();
    
  Layer* clouds = lg.GetLayer("clouds");
  clouds->Move(10,10);
  
  Text txt(txt__hello_txt, incon, 70);
  txt.Move(40,40);  
  clouds->Draw(txt);
  
  txt.Move(50,50);
  clouds->Draw(txt);

  Vector p;
  
  while(evt.GetEvent(&e)) {
    switch(e.type) {
      case NPEventType_MouseDown:
        x = e.u.mouse.x;
        y = e.u.mouse.y;
        p.XY(x, y);            
        
        for(int i=0; i<NUMSQUARES; i++){
          sqs[i].Move(p);
          
          //sqs[i].Y(y);
        }
        break;
      case NPEventType_KeyDown:
        //printf("%d\n", int(e.u.key.normalizedKeyCode));
        if (e.u.key.normalizedKeyCode == 40){          
          for(int i=0; i<NUMSQUARES; i++){
            sqs[i].Stop();
          }
        }          
        break;        
    }
  }
}



void Core::MainLoop() {    
}

