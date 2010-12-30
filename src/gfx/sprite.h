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
// _.-{{crml}}-._


#ifndef SPRITE_H_
#define SPRITE_H_

#include "../core/error.h"
#include "../core/crmltypes.h"
#include "./rect.h"
#include "./tga_loader.h"
#include "./matrix.h"

namespace crml {
ERR_(SPRITE_ANGLE_NEGATIVE_NORMALIZE);
ERR_(SPRITE_ANGLE_OVERFLOW_NORMALIZE);  

class Sprite: public Error, public Rect {

 public:
  explicit Sprite(): Error(OK) {
    ClassName("Sprite");
    scale_ = 1;
    angle_ = 0; // 0 on unit circle. CCW is pos.
    shear_ = 0; // todo 0 or 1 here? check the transformation
    reflect_ = 1; // todo 0 or 1 here? check the transformation
    alpha_ = 255;
  };
  
  ~Sprite();    
  void LoadImage(TgaLoader& tga);
  void Angle(float64 a);
  float64 Angle();
  void SnapAngleUp();
  void SnapAngleDown();  

  float64 Scale();
  float64 Shear();
  float64 Reflect();
  
  void Rotate(float64 angle);
  void Scale(float64 scale);
  void Shear(float64 scale);
  void Reflect(float64 scale);
    
  std::vector<Color> PixelVector(); // opportunity for optimization.

  void UpdateBoundingBox();
  Matrix2 GetTransformationMatrix();
  
  // need to move texel stuff to TgaLoader.
  // think about why this might not be a good idea.
  void LoadTexelArray();
  const uint8* TexelArray();
  
 private:
  // Prevent copy.
  // allowing the = operator would introduce a false sense of
  // what happening under the covers.  
  Sprite(const Sprite&);     
  Sprite& operator = (const Sprite&);
  // ------------------------------------------------------------------
  
  float64 scale_;
  bool scale_changed_;
  
  float64 angle_;
  bool angle_changed_;
  
  float64 shear_;
  bool shear_changed_;
  
  float64 reflect_;
  bool reflect_changed_;
   
  uint8 alpha_;
    
  TgaLoader* image_;
  const uint8* texels_;
  uint32 texels_size_;
};

}       // namespace crml
#endif  // SPRITE_H_



