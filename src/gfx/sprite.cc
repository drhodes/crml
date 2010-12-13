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














