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

#include <media-blob.h>
#include <stdlib.h>

using namespace crml;

Event evt;
Display dsp;
Clock timer1, timer2;
int frame = 0;
int totalframe = 0;
int fps = 15;
bool firstrun = true;
NPPepperEvent e;
int x = 1;
int y = 1;
LayerGroup lg;
Camera cam(512,512);
Sprite s1, s2;
Sprite wedges[200];

float rand01(){
  return float(rand()/float(RAND_MAX));
}

void RunOnce() {
  Error::DebugOn();  
  firstrun=false;
  dsp.Init();
  cam.Init();
  
  cam.StretchRight(1024);
  cam.StretchBottom(1024);
  cam.Move(-100, -100);
  
  lg.AddTop("clouds");
  lg.Check();

  Shader shdr(txt__gl_v_shader, txt__gl_f_shader);  
  TgaLoader img, img2, imgwedge;
  
  img.LoadFromStash(img__ring_tga, sizeof(img__ring_tga));
  img2.LoadFromStash(img__gopher_tga, sizeof(img__gopher_tga));
  imgwedge.LoadFromStash(img__circlewedge_tga, sizeof(img__circlewedge_tga));

  
  s1.LoadImage(img);
  s1.SetShader(shdr);
  s1.CreateTexture();
  s1.Scale(.5);

  s2.LoadImage(img2);
  s2.SetShader(shdr);
  s2.CreateTexture();
  s2.Scale(.5);
 
  s2.Translate(Vector(-.5,0));

  for (int i=0; i<200; i++){
    wedges[i].LoadImage(imgwedge);
    wedges[i].SetShader(shdr);
    wedges[i].CreateTexture();
    wedges[i].Scale(rand01());
    wedges[i].Translate(Vector(.5 - rand01(), .5 - rand01()));    
  }
}

void Core::Main3D(){
  if (firstrun) { RunOnce(); }

  //auto clouds = lg.GetLayer("clouds");  
  //cam.DrawLayer(*clouds);
  /*
  if ((totalframe % 51) < 25 ) {
    s1.ScaleX(1.03);
    s1.ScaleY(.970873786);
  } else {
    s1.ScaleX(.970873786);
    s1.ScaleY(1.03);
  }    
  */
  
  cam.GlClearColor();

  s2.Scale(.99);
  s2.Translate(Vector(.001, 0));
  s2.Rotate(10.0);

  s1.Translate(Vector(-.0001, .0002));
  s1.Scale(1.001);

  for (int i=0; i<200; i++) {   
    wedges[i].Rotate(float((i%50+1))/10);
    wedges[i].Scale(.999);
    cam.GLFromCPPDraw(wedges[i]);
  }

  //cam.GLFromCPPDraw(s1);
  //cam.GLFromCPPDraw(s2);
  cam.GlFlush();
  
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
  totalframe += 1;
}


void Core::MainLoop() {    
}

