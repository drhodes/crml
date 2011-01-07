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

void Sprite::CopyGlMatrix(GLfloat* mat16){
  matrix_.CopyGlMatrix(mat16);
}

void Sprite::LoadTexelArray(){  
  // this only works with RGBA pixels, must chane to work with RGB.
  std::vector<Color> pixels = PixelVector();
  
  texels_ = (uint8*)(malloc (pixels.size()*4));
  uint8* cur = texels_;

  image_->GetImageType();
  
  printf("num pixels: %d\n", pixels.size()*4);  
  
  for (uint32 i=0; i < pixels.size(); i++){
    *texels_++ = pixels[i].Red();
    *texels_++ = pixels[i].Green();
    *texels_++ = pixels[i].Blue();
    *texels_++ = pixels[i].Alpha();      
  }

  texels_ = cur;
}

// consider deep sixing this method.
void Sprite::Angle(float64 a){
  if (angle_ < 0.0f)
    SetReportErr(SPRITE_ANGLE_NEGATIVE_NORMALIZE);
  if (angle_ >= 360.0f)
    SetReportErr(SPRITE_ANGLE_OVERFLOW_NORMALIZE);  
  angle_ = a;
  MarkDirty();
}

float64 Sprite::Angle(){
  return angle_;
}

void Sprite::Rotate(float64 a){
  // how to hangle negative numbers?
  matrix_.RotateUpdate(a);
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

  // this needs to be tested.
    
  MarkDirty();
}

float64 Sprite::Scale(){ return scale_; }
void Sprite::Scale(float64 s){
  matrix_.ScaleUpdate(s);
  scale_ += s;
  MarkDirty();
}

float64 Sprite::ScaleX(){ return scale_x_; }
void Sprite::ScaleX(float64 s){
  matrix_.ScaleXUpdate(s);
  scale_x_ += s;
  MarkDirty();
}


float64 Sprite::ScaleY(){ return scale_y_; }
void Sprite::ScaleY(float64 s){
  matrix_.ScaleYUpdate(s);
  scale_y_ += s;
  MarkDirty();
}


float64 Sprite::ShearX(){ return shear_x_; }
void Sprite::ShearX(float64 s){
  matrix_.ShearXUpdate(s);
  shear_x_ += s;
  MarkDirty();
}

float64 Sprite::ShearY(){ return shear_y_; }
void Sprite::ShearY(float64 s){
  matrix_.ShearYUpdate(s);
  shear_y_ += s;
  MarkDirty();
}


void Sprite::MarkDirty(){
  dirty_ = true;
}

bool Sprite::IsDirty(){
  return dirty_;
}

void Sprite::MarkClean(){
  dirty_ = false;
}

void Sprite::SetShader(Shader shdr){
  shader_ = shdr;
}

void Sprite::CreateTexture(){
  //printf("gles2_demo_cc.cc -> GLuint CreateCheckerboardTexture() {\n");
  CheckGLError("Sprite::CreateTexture", __LINE__);
  
  glGenTextures(1, &texture_);
  glBindTexture(GL_TEXTURE_2D, texture_);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


  if (image_ == 0) {
    SetReportDie("Null Image in Sprite");
  }

  int32 h = 0, w = 0;
  
  if (image_->Ok()) {
    h = image_->Height();
    w = image_->Width();
  } else {
    image_->Check();
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
               w, h,
               0, GL_RGBA, GL_UNSIGNED_BYTE, texels_);
  CheckGLError("Sprite::CreateTexture", __LINE__);
}

/*
GLuint Sprite::VertexShader() { return shader_.VertexShader(); }
GLuint Sprite::FragmentShader() { return shader_.FragmentShader(); }
GLuint Sprite::Program() { return shader_.Program(); }
GLuint Sprite::Texture() { return shader_.Texture(); }
int Sprite::TextureLoc() { return shader_.TextureLoc(); }
GLuint Sprite::WorldMatrixLoc() { return shader_.WorldMatrixLoc(); }
GLuint Sprite::Vbo() { return shader_.Vbo(); }
GLsizei Sprite::TexCoordOffset() { return shader_.TexCoordOffset(); }
*/

}       // namespace crml
#endif  // SPRITE_CC
