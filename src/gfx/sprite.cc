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

#ifndef SPRITE_CC
#define SPRITE_CC

#include <stdlib.h>
#include "sprite.h"

namespace crml {

/*
  Currently this is TGA centric.  As different loaders are introduced
  things will be genericized, but not before that
*/

Sprite::~Sprite(){
}

void Sprite::LoadImage(TgaLoader& tga){
  // this has got to be managed in a responsible fashion.
  //     
  image_ = &tga;
  Move(0,0);  
  StretchRight(image_->Width());
  StretchBottom(image_->Height());
  LoadTexelArray();
}

std::vector<Color> Sprite::PixelVector(){
  return image_->PixelVector();
}

void Sprite::LoadTexelArray(){
  // this only works with RGBA pixels, must chane to work with RGB.
  std::vector<Color> pixels = PixelVector();
  
  texels_ = (uint8*)(malloc (pixels.size()*4));
  uint8* cur = (uint8*)(texels_);
  
  printf("num pixels: %d\n", pixels.size()*4);  
  
  for (uint32 i=0; i < pixels.size(); i++){
    *cur++ = pixels[i].Red();
    *cur++ = pixels[i].Green();
    *cur++ = pixels[i].Blue();
    *cur++ = pixels[i].Alpha();      
  }
  texels_size_ = pixels.size() * 4;
}

Matrix2 Sprite::GetTransformationMatrix(){
  Matrix2 result;
  if (angle_changed_) {
    result.RotateUpdate(angle_);
  }
  if (shear_changed_) {
    //result.ShearUpdate(shear_);
  }
  if (scale_changed_) {
    //result.ScaleUpdate(scale_);
  }
  if (reflect_changed_) {
    //result.ReflectUpdate(reflect_);
  }

  angle_changed_ = false;
  shear_changed_ = false;
  scale_changed_ = false;
  reflect_changed_ = false;

  return result;
}

void Sprite::Angle(float64 a){
  if (angle_ < 0.0f)
    SetReportErr(SPRITE_ANGLE_NEGATIVE_NORMALIZE);
  if (angle_ >= 360.0f)
    SetReportErr(SPRITE_ANGLE_OVERFLOW_NORMALIZE);  
  angle_ = a;
  angle_changed_ = true;
}

float64 Sprite::Angle(){
  return angle_;
}

void Sprite::Rotate(float64 a){
  // how to hangle negative numbers?
  angle_ += a;

  // change this to fmod -->
  // #include <math.h>
  // fmod(double x, double y);
  // once this is determined to work as expected.
  while (a >= 360.0f) {
    a -= 360;
  }
  
  while (a < 0.0f) {
    angle_ += 360;
  }
  angle_changed_ = true;
}

float64 Sprite::Scale(){ return scale_; }
void Sprite::Scale(float64 s){
  scale_ += s;
  scale_changed_ = true;
}

float64 Sprite::Shear(){ return shear_; }
void Sprite::Shear(float64 s){
  shear_ += s;
  shear_changed_ = true;
}

float64 Sprite::Reflect(){ return reflect_; }
void Sprite::Reflect(float64 s){
  reflect_ += s;
  reflect_changed_ = true;
}

}       // namespace crml
#endif  // SPRITE_CC
