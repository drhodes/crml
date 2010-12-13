// -*- c++ -*-
// _.-{{ crml }}-._

#ifndef SPRITE_CC
#define SPRITE_CC

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
}

std::vector<Color> Sprite::PixelVector(){
  return image_->PixelVector();
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














