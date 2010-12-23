// -*- c++ -*-
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
