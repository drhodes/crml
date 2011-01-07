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
//Font incon(fnt__inconsolata_otf);
int frame = 0;
int totalframe = 0;
int fps = 15;
bool firstrun = true;
NPPepperEvent e;
int x = 1;
int y = 1;
LayerGroup lg;
float scale = 1;
Shader shdr;
Camera cam(512,512);
Sprite s1;

void RunOnce() {
  firstrun = false;  
  Error::DebugOn(); 
  dsp.Init();
  
  cam.StretchRight(1024);
  cam.StretchBottom(1024);
  cam.Move(-100, -100);
  
  glViewport(0, 0, dsp.Width(), dsp.Height());
  
  lg.AddTop("clouds");
  lg.Check();

  shdr.CreateProgram();
  shdr.LoadVertexShader(txt__gl_v_shader);
  shdr.LoadFragmentShader(txt__gl_f_shader);
  shdr.Link();
  shdr.UseProgram();
  shdr.InitShaders();
  
  TgaLoader img;
  //img.LoadFromStash(img__ring_tga, sizeof(img__ring_tga));
  img.LoadFromStash(img__gopher_tga, sizeof(img__gopher_tga));

  s1.LoadImage(img);
  s1.SetShader(shdr);
  s1.CreateTexture();
  s1.Scale(.5);
  
  //GLFromCPPInit(s1.texels_, img.Width(), img.Height());
  //GLFromCPPInit2(s1)
}

void Core::Main3D(){
  if (firstrun) {
    firstrun=false;
    RunOnce();    
  }

  auto clouds = lg.GetLayer("clouds");  
  cam.DrawLayer(*clouds);

  //GLFromCPPDraw(scale);
  if ((totalframe % 50) <= 25) {
    s1.ScaleX(1.03);
    s1.ScaleY(.97);
  } else {
    s1.ScaleX(.97);
    s1.ScaleY(1.03);
  }    

  GLFromCPPDraw(s1); 
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
  totalframe += 1;

}

void Core::MainLoop() {    
}

