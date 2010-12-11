// -*- c++ -*-
// Copyright 2010 <Derek A. Rhodes>

#ifndef SPRITE_CC
#define SPRITE_CC

#include "sprite.h"

namespace crml {
   
Sprite::~Sprite(){
}


void Sprite::LoadImage(TgaLoader& tga){
  // this has got to be managed in a responsible fashion.
  //     
  image = &tga;
  Move(0,0);
  StretchRight(image->Width());
  StretchBottom(image->Height());  
}


bool Sprite::Ok(){
  return Err() == SPRITE_OK;
}
  
}       // namespace crml
#endif  // SPRITE_CC














