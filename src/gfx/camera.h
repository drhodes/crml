// -*- c++ -*-
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
// _.-{{ crml }}-._

#ifndef CAMERA_H_
#define CAMERA_H_


#include "../core/error.h"
#include "../win/display.h"
#include "./layer.h"
#include "./rect.h"
#include "./sprite.h"
#include "./glutil.h"

namespace crml {
ERR_(CAMERA_NULL_SPRITE);

class Camera: public Error, public Rect {
 public:
  explicit Camera(): Error(OK),
                     Rect(0,0,100,100) {           
    ClassName("Camera");    
  }
  
  explicit Camera(float64 height, float64 width):
      Error(OK),
      Rect(0,0, width, height) {           
    ClassName("Camera");    
  }
  
  explicit Camera(Rect r):
      Error(OK),
      Rect( r.Left(), r.Top(), r.Right(), r.Bottom() ) {
    ClassName("Camera");    
  }  
  //~Camera();
  
  void GLFromCPPDraw(crml::Sprite& spr);
  void Init();
  void DrawDraw(Sprite* spr);
  void DrawSprite(Sprite* spr);
  void DrawLayer(Layer& lyr);
  void GlClearColor();
  void GlFlush();
  
 private:
  float64 cam_dist_;
  
};
  
}       // namespace crml
#endif  // CAMERA_H_






