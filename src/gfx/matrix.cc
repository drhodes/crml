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

#ifndef MATRIX_CC
#define MATRIX_CC

#include "./matrix.h"

namespace crml {

bool Matrix2::Equal(Matrix2& other){
  return ( r1c1_ == other.r1c1_ &&
           r1c2_ == other.r1c2_ &&
           r2c1_ == other.r2c1_ &&
           r2c2_ == other.r2c2_ );
}

Matrix2 Matrix2::Multiply(Matrix2& other){
  Matrix2 result;
  // a11*b11 + a12*b21                      
  result.r1c1_ = r1c1_ * other.r1c1_ +
                 r1c2_ * other.r2c1_;
  // a11*b12 + a12*b22
  result.r1c2_ = r1c1_ * other.r1c2_ +
                 r1c2_ * other.r2c2_;
  // a21*b11 + a22*b21
  result.r2c1_ = r2c1_ * other.r1c1_ +
                 r2c2_ * other.r2c1_;
  // a21*b12 + a22*b22
  result.r2c2_ = r2c1_ * other.r1c2_ +
                 r2c2_ * other.r2c2_;    
  return result;  
}

void Matrix2::CopyInto(Matrix2& other){
  other.r1c1_ = r1c1_;
  other.r1c2_ = r1c2_;
  other.r2c1_ = r2c1_;
  other.r2c2_ = r2c2_;
}

std::vector<float64> Matrix2::GlMatrix(){
  // optimization, consider making this a mutable array.
  // or, in C style, pass a pointer and copy into it.
  // void Matrix2::CopyGlMatrix(char* gl_array){yatta}...
  // for now this is easier to debug.
  float64 els[] = {
      r1c1_, r1c2_, 0, 0,
      r2c1_, r2c2_, 0, 0,
      0,     0,     0, 0,
      0,     0,     0, 0,    
  };
  return std::vector<float64>(els, els + sizeof(els) / sizeof(float64));
}

void Matrix2::CopyGlMatrix(GLfloat* mat16){
  mat16[0] = r1c1_;
  mat16[1] = r1c2_;
  mat16[4] = r2c1_;
  mat16[5] = r2c2_;
}

// Scaling ------------------------------------------------------------------
Matrix2 Matrix2::Scale(float64 s){
  Matrix2 result;
  result.ScaleUpdate(s);
  return Multiply(result);
}

Vector Matrix2::Scale(float64 s, Vector& v){
  Matrix2 result;
  result.ScaleUpdate(s);
  return result.Transform(v);
}

void Matrix2::ScaleUpdate(float64 s){
  r1c1_ *= s;
  r2c2_ *= s;
}

// Scaling X ------------------------------------------------------------------
Matrix2 Matrix2::ScaleX(float64 s){
  Matrix2 result;
  result.ScaleXUpdate(s);
  return Multiply(result);
}

Vector Matrix2::ScaleX(float64 s, Vector& v){
  Matrix2 result;
  result.ScaleXUpdate(s);
  return result.Transform(v);
}

void Matrix2::ScaleXUpdate(float64 s){
  r1c1_ *= s;
}

// Scaling Y ------------------------------------------------------------------
Matrix2 Matrix2::ScaleY(float64 s){
  Matrix2 result;
  result.ScaleYUpdate(s);
  return Multiply(result);
}

Vector Matrix2::ScaleY(float64 s, Vector& v){
  Matrix2 result;
  result.ScaleYUpdate(s);
  return result.Transform(v);
}

void Matrix2::ScaleYUpdate(float64 s){
  r2c2_ *= s;
}

// Rotating ----------------------------------------------------------------
Matrix2 Matrix2::Rotate(float64 theta){  
  Matrix2 result;
  float64 degs = theta / 57.295779513082323;

  result.r1c1_ = +cos(degs);
  result.r1c2_ = -sin(degs);
  result.r2c1_ = +sin(degs);
  result.r2c2_ = +cos(degs);

  return Multiply(result); // Multiply to chain calls.
}

Vector Matrix2::Rotate(float64 angle, Vector& v){
  Matrix2 result;
  return result.Rotate(angle).Transform(v);
}

void Matrix2::RotateUpdate(float64 angle){
  Matrix2 result = Rotate(angle);
  result.CopyInto(*this);                   
}

// Shearing X --------------------------------------------------------------
Matrix2 Matrix2::ShearX(float64 n){
  Matrix2 result;
  result.r1c2_ = n;
  return Multiply(result);
}

void Matrix2::ShearXUpdate(float64 n){
  Matrix2 result = ShearX(n);
  result.CopyInto(*this);                   
}
Vector Matrix2::ShearX(float64 n, Vector& v){
  Matrix2 result;
  return result.ShearX(n).Transform(v);
}

// Shearing Y --------------------------------------------------------------
Matrix2 Matrix2::ShearY(float64 n){
  Matrix2 result;
  result.r2c1_ = n;
  return result;
}

void Matrix2::ShearYUpdate(float64 n){
  Matrix2 result = ShearY(n);
  result.CopyInto(*this);                   
}

Vector Matrix2::ShearY(float64 n, Vector& v){
  Matrix2 result;
  return result.ShearY(n).Transform(v);
}

// Reflecting ------------------------------------------------------------------
// Do some reading to see if this makes sense in 2d.
// Matrix2 Reflect(float64 n);
// Vector Reflect(float64 n, Vector& v);
// void ReflectUpdate(float64 n);
// -----------------------------------------------------------------------

Vector Matrix2::Transform(Vector v){
  float64 x = r1c1_ * v.X() + r1c2_ * v.Y();
  float64 y = r2c1_ * v.X() + r2c2_ * v.Y();
  return Vector(x,y);
}

// Rects ------------------------------------------------------------------
void Matrix2::Scale(float64 s, Rect& r) {
  Matrix2().Scale(s).Transform(r);
}
void Matrix2::ScaleX(float64 s, Rect& r) {  
  Matrix2().ScaleX(s).Transform(r);
}
void Matrix2::ScaleY(float64 s, Rect& r) {
  Matrix2().ScaleY(s).Transform(r);
}
void Matrix2::Rotate(float64 theta, Rect& r) {  
  Matrix2().Rotate(theta).Transform(r);
}
void Matrix2::ShearX(float64 n, Rect& r) {
  Matrix2().ShearX(n).Transform(r);
}
void Matrix2::ShearY(float64 n, Rect& r) {
  Matrix2().ShearY(n).Transform(r);
}
// Rect Matrix2::Reflect(float64 n, Rect& r) {
// }
void Matrix2::Transform(Rect& r){
  Vector c = r.Center();
  
  r.TopLeft(Transform(r.TopLeft().Subtract(c)).Add(c));
  r.TopRight(Transform(r.TopRight().Subtract(c)).Add(c));
  r.BottomLeft(Transform(r.BottomLeft().Subtract(c)).Add(c));
  r.BottomRight(Transform(r.BottomRight().Subtract(c)).Add(c));
}
std::string Matrix2::ShowMatrix() {
  char buffer[100];  
  sprintf(buffer, "\n|%3.2f, %3.2f|\n|%3.2f, %3.2f|\n",
          r1c1_, r1c2_, r2c1_, r2c2_);  
  return std::string(buffer);
}
}       // namespace crml
#endif  // MATRIX2_CC
