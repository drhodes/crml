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
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      if (mat_[row][col] != other.mat_[row][col])
        return false;
    }
  }
  return true;
}

Matrix2 Matrix2::Multiply(Matrix2& o){
  Matrix2 r;
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      r.mat_[row][col] = mat_[row][0] * o.mat_[0][col] +
                         mat_[row][1] * o.mat_[1][col] +
                         mat_[row][2] * o.mat_[2][col] +
                         mat_[row][3] * o.mat_[3][col];      
    }  
  }
  return r;
}

void Matrix2::IdentityUpdate(){
  mat_ = {{1,0,0,0},
          {0,1,0,0},
          {0,0,1,0},
          {0,0,0,1}};
}

void Matrix2::CopyInto(Matrix2& other){
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      other.mat_[row][col] = mat_[row][col];
    }
  }
}

void Matrix2::CopyGlMatrix(GLfloat* mat16){
  if (mat16 == 0) {
    printf("Null matrix pointer encountered in Matrix2::CopyGlMatrix\n");
    exit(1);
  }

  // Need to copy in the transpose for GL
   
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      //mat16[4*row+col] = mat_[row][col];
      mat16[4*row+col] = mat_[col][row];
    }
  }
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
  mat_[0][0] *= s;
  mat_[1][1] *= s;
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
  mat_[0][0] *= s;
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
  mat_[1][1] *= s;
}

// Rotating ----------------------------------------------------------------
Matrix2 Matrix2::Rotate(float64 theta){  
  Matrix2 result;
  float64 degs = theta / 57.295779513082323;
  if (theta >= 0){ // counterclockwise
    result.mat_[0][0] = +cos(degs);
    result.mat_[0][1] = -sin(degs);
    result.mat_[1][0] = +sin(degs);
    result.mat_[1][1] = +cos(degs);
  } else { // clockwise
    result.mat_[0][0] = +cos(degs);
    result.mat_[0][1] = +sin(degs);
    result.mat_[1][0] = -sin(degs);
    result.mat_[1][1] = +cos(degs);
  }
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
  result.mat_[0][1] = n;
  return result;
}

void Matrix2::ShearXUpdate(float64 n){
  Matrix2 result = ShearX(n);
  Multiply(result).CopyInto(*this);                   
}

Vector Matrix2::ShearX(float64 n, Vector& v){
  Matrix2 result;
  return result.ShearX(n).Transform(v);
}

// Shearing Y --------------------------------------------------------------
Matrix2 Matrix2::ShearY(float64 n){
  Matrix2 result;
  result.mat_[1][0] = n;
  return result;
}

void Matrix2::ShearYUpdate(float64 n){
  Matrix2 result = ShearY(n);
  Multiply(result).CopyInto(*this);                   
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

// Translation ------------------------------------------------------------------
Matrix2 Matrix2::Translate(Vector& v){
  Matrix2 result;
  result.mat_[0][3] = v.X();
  result.mat_[1][3] = v.Y();
  return Multiply(result);
}

Vector Matrix2::TranslateVector(Vector& v){
  return Transform(v);
}

void Matrix2::TranslateUpdate(Vector& v){
  Matrix2 result = Translate(v);
  result.CopyInto(*this);
} 

Vector Matrix2::Transform(Vector v){
  // crml Vectors are 2D.
  // v_Z, v_W are phony, though it's needed
  // for some transformations.
  float64 v_Z = 1;
  float64 v_W = 1;
  
  float64 x = mat_[0][0] * v.X() +
              mat_[0][1] * v.Y() +
              mat_[0][2] * v_Z +
              mat_[0][3] * v_W;
  
  float64 y = mat_[1][0] * v.X() +
              mat_[1][1] * v.Y() +
              mat_[1][2] * v_Z +
              mat_[1][3] * v_W;
  
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

// check this out.  Write tests for this.
void Matrix2::Translate(Vector& v, Rect& r) {
  Matrix2().Translate(v).Transform(r);
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
  sprintf(buffer, "\n|%3.2f, %3.2f, %3.2f, %3.2f|\n|%3.2f, %3.2f, %3.2f, %3.2f|\n|%3.2f, %3.2f, %3.2f, %3.2f|\n|%3.2f, %3.2f, %3.2f, %3.2f|\n",
          mat_[0][0], mat_[0][1], mat_[0][2], mat_[0][3],
          mat_[1][0], mat_[1][1], mat_[1][2], mat_[1][3],
          mat_[2][0], mat_[2][1], mat_[2][2], mat_[2][3],
          mat_[3][0], mat_[3][1], mat_[3][2], mat_[3][3]);
          
          return std::string(buffer);
}


}       // namespace crml
#endif  // MATRIX2_CC
