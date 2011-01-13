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

#ifndef MATRIX_H_
#define MATRIX_H_

#include <GLES2/gl2.h>
#include "../core/crmltypes.h"
#include "./vector.h"
#include "./rect.h"
#include <vector>
#include <stdlib.h>

namespace crml {

class Matrix2 {
 public:
  explicit Matrix2(){
    IdentityUpdate();
  }
  
  explicit Matrix2( float64 r1c1, float64 r1c2, float64 r2c1, float64 r2c2){
    IdentityUpdate();
    mat_[0][0] = r1c1;
    mat_[0][1] = r1c2;
    mat_[1][0] = r2c1;
    mat_[1][1] = r2c2;
  }
   
  bool Equal(Matrix2& other);  
  Matrix2 Multiply(Matrix2& other);
  Vector Transform(Vector v);
  void Transform(Rect& v);

  void CopyGlMatrix(GLfloat* mat16);
  std::vector<float64> GlMatrix();

  void IdentityUpdate();
  
  Matrix2 Scale(float64 s);
  Vector Scale(float64 s, Vector& v);
  void Scale(float64 s, Rect& v);
  void ScaleUpdate(float64 s);

  Matrix2 ScaleX(float64 s);
  Vector ScaleX(float64 s, Vector& v);
  void ScaleX(float64 s, Rect& v);
  void ScaleXUpdate(float64 s);

  Matrix2 ScaleY(float64 s);
  Vector ScaleY(float64 s, Vector& v);
  void ScaleY(float64 s, Rect& v);
  void ScaleYUpdate(float64 s);
  
  Matrix2 Rotate(float64 theta);
  Vector Rotate(float64 theta, Vector& v);
  void Rotate(float64 theta, Rect& v);
  void RotateUpdate(float64 theta);
  
  Matrix2 ShearX(float64 n);
  Vector ShearX(float64 n, Vector& v);
  void ShearX(float64 n, Rect& v);
  void ShearXUpdate(float64 n);
  
  Matrix2 ShearY(float64 n);
  Vector ShearY(float64 n, Vector& v);
  void ShearY(float64 n, Rect& v);
  void ShearYUpdate(float64 n);

  Matrix2 Translate(Vector& v);
  void TranslateUpdate(Vector& v);
  void Translate(Vector& v, Rect& r);
  Vector TranslateVector(Vector& v);
  
  Matrix2 Reflect(float64 n);
  Vector Reflect(float64 n, Vector& v);
  void Reflect(float64 n, Rect& v);
  void ReflectUpdate(float64 n);
  
  void CopyInto(Matrix2& other);
  std::string ShowMatrix();
  
 private:
  float64 mat_[4][4];
};

}       // namespace crml
#endif  // MATRIX2_H_
