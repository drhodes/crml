// -*- c++ -*-
// _.-{{ crml }}-._

#ifndef SPRITE_CC
#define SPRITE_CC

#include <stdlib.h>
#include "sprite.h"

namespace crml {

/*
  Currently this is a TGA centric sprite.  As different loaders
  are introduced things will be genericized, but not before that
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

void Sprite::Angle(int32 a){
  // how to hangle negative numbers?
  angle_ = a % 360;
}

int32 Sprite::Angle(){
  return angle_;
}


void Sprite::Rotate(int32 a){
  // how to hangle negative numbers?
  angle_ = (angle_ + a) % 360;
}

void Sprite::Scale(float s){
  scale_ = s;
}

bool Sprite::Ok(){
  return Err() == OK;
}
  
}       // namespace crml
#endif  // SPRITE_CC














