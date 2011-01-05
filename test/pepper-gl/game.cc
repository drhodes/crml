/* _.-{ license management }-._ 
Copyright (c) 2010, Derek A. Rhodes
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
3. Neither the name of the PostgreSQL Global Development Group nor the names
   of its contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/
// _.-{{crml}}-._
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
//Font incon(fnt__inconsolata_otf);
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
Camera cam(512,512);

void RunOnce() {
  firstrun = false;  
  Error::DebugOn(); 
  dsp.Init();
  cam.StretchRight(1024);
  cam.StretchBottom(1024);
  cam.Move(-100, -100);
  
  glViewport(0, 0, dsp.Width(), dsp.Height());
  
  lg.AddTop("clouds");
  lg.AddTop("stars");
  lg.AddBottom("background");  
  lg.Check();
  
  TgaLoader img;
  img.LoadFromStash(img__ring_tga, sizeof(img__ring_tga));

  //Sprite s1;
  //s1.LoadImage(img); 
  //s1.Rotate(10);
  //s1.shader_.LoadVertexShader(txt__gl_v_shader);
  //s1.shader_.LoadFragmentShader(txt__gl_f_shader);
  //s1.shader_.InitShaders();
  
  Layer* clouds = lg.GetLayer("clouds");
  //clouds->AddSprite(s1);
  
  cam.DrawLayer(*clouds);  


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

  auto clouds = lg.GetLayer("clouds");  
  cam.DrawLayer(*clouds);


  //printf("number of sprites: %d\n", clouds->NumSprites());
  
  GLFromCPPDraw(scale);

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

