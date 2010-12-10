#include <crml-core.h>
#include <crml-win.h>
#include <crml-sys.h>
#include <crml-evt.h>
#include <crml-gfx.h>

#include <sstream>
#include <iostream>

#include <media-blob.h>
#include "./gles2_demo_cc.cc"

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
float scale = 1;

void RunOnce() {
  firstrun = false;  
  Error::DebugOn(); 
  dsp.Init();
  glViewport(0, 0, dsp.Width(), dsp.Height());

  
  lg.AddTop("clouds");
  lg.AddTop("stars");
  lg.AddBottom("background");  
  lg.Check();
 
  TgaLoader img;
  //img.LoadFromStash(img__munch_tga, sizeof(img__sun_tga));
  img.LoadFromStash(img__sun_tga, sizeof(img__sun_tga));
  //tga.LoadFromStash(img__rainbow4_tga, sizeof(img__rainbow4_tga));

  Sprite s1;
  s1.LoadImage(img);
  s1.Move(10,10);
   
  Layer* clouds = lg.GetLayer("clouds");
  clouds->AddSprite(s1);
  // s1 will be destroyed at the end of this function. :<
  
  //Sprite s2;
  //s2 = s1; doesn't work, this is good.
   
  std::vector<Color> pixels = img.PixelVector();
  
  uint8* texels;
  texels = (uint8*) (malloc (pixels.size()*4));
  uint8* first = texels;
  
  printf("num pixels: %d\n", pixels.size()*4);  
  
  img.GetImageType();

  for (uint32 i=0; i < pixels.size(); i++){
    *texels++ = pixels[i].Red();
    *texels++ = pixels[i].Green();
    *texels++ = pixels[i].Blue();
    *texels++ = pixels[i].Alpha();      
  }
  texels = first;
  
  printf("W: %d\n", img.Width());
  printf("h: %d\n", img.Height());
  
  GLFromCPPInit(texels, img.Width(), img.Height());
  delete texels;
  
}

void Core::Main3D(){
  if (firstrun) {
    firstrun=false;
    RunOnce();    
  }

  float temp = float(frame) / 15.0;  
  GLFromCPPDraw(scale);
  
  /*
  if (timer1.ElapsedMilli() < 2){
    return;
  }  
  timer1.Reset();
  */
    
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
      case NPEventType_MouseMove:        
        x = e.u.mouse.x;
        scale = x / 100.0;
        break;
        
      case NPEventType_KeyDown: 
        if (e.u.key.normalizedKeyCode == 40){          
        }          
        break;
    }
  }
  
  if(timer2.ElapsedSec() > 1){
    printf("Framerate: %d\n", frame);
    frame = 0;
    timer2.Reset();
  }
  frame += 1;


}

void Core::MainLoop() {    
}

