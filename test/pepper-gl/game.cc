#include <crml-core.h>
#include <crml-win.h>
#include <crml-sys.h>
#include <crml-evt.h>
#include <crml-gfx.h>

#include <osg/GL>
#include <osg/Endian>

#include <sstream>
#include <iostream>

#include <media-blob.h>
#include <png.h>
#include <zlib.h>
#include "./gles2_demo_cc.cc"
#include "osg-png-ripoff.cc"

using namespace crml;

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
LayerGroup lg;
SpaceHash sh(32);

void RunOnce() {
  firstrun = false;
  
  Error::DebugOff(); 
  dsp.Init();

  lg.AddTop("clouds");
  lg.AddTop("stars");
  lg.AddBottom("background");  
  lg.Check();

  GLFromCPPInit();  
  TgaLoader tga;
  tga.LoadFromStash(img__munch_tga, sizeof(img__munch_tga));
  printf("Image Type %d\n", tga.GetImageType());
}

void Core::Main3D(){
  if (firstrun) {
    RunOnce();    
  }

  

  
  glViewport(0, 0, dsp.Width(), dsp.Height());
  GLFromCPPDraw();
    
  if (timer1.ElapsedMilli() < 30){
    return;
  }
          
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
        break;
      case NPEventType_KeyDown: 
        if (e.u.key.normalizedKeyCode == 40){          
        }          
        break;
    }
  }
}


void Core::MainLoop() {    
}

