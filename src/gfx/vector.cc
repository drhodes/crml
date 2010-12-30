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

#ifndef VECTOR_CC
#define VECTOR_CC

#include "./vector.h"

namespace crml {

Vector::Vector() {
  x_ = 0;
  y_ = 0;     
}

Vector::Vector(float64 x, float64 y) {
  x_ = x;
  y_ = y;     
}

Vector::Vector(const Vector& v){
  x_ = v.x_;
  y_ = v.y_;      
}

Vector::~Vector() {
}

void Vector::XY(float64 x, float64 y) {
  x_ = x;
  y_ = y;
}

float64 Vector::X() {
  return x_;
}

void Vector::X(float64 x) {
  x_= x;
}

float64 Vector::Y() {
  return y_;
}

void Vector::Y(float64 y) {
  y_ = y;
}

float64 Vector::Distance(Vector& other) {
  // consider the quake optimization.
  return sqrt((x_ - other.x_)*(x_ - other.x_) +
              (y_ - other.y_)*(y_ - other.y_));  
}

float64 Vector::Length() {
  return sqrt(x_*x_ + y_*y_);
}

Vector Vector::Multiply(float64 n) {
  return Vector(n*x_, n*y_);
}

Vector Vector::Normalize(){
  return Multiply(1 / Length());
}

Vector Vector::Negate() {
  return Multiply(-1);
}

Vector Vector::Add(Vector v) {
  return Vector(X() + v.X(), Y() + v.Y());  
}

Vector Vector::Subtract(Vector v) {
  Vector temp = v.Negate();
  return Add(temp);
}

bool Vector::Equal(Vector v) {
  // IEEE float rears its ugly head and demands blood
  // for the pendantics of precision.
  // bug alert
  // the error can grow over time, think about how snapping
  // to a kind of planck metric could help here.
  
  return ( fabs(x_ - v.X()) < 0.00001 &&
           fabs(y_ - v.Y()) < 0.00001 );
}

// given a grid with spacing <res>
// floor x and y to the closest grid intersection.
// todo use fmod instead.
Vector Vector::Align(int32 res){
  float64 snap_x = X() - float64(int32(X()) % res );
  float64 snap_y = Y() - float64(int32(Y()) % res );

  return Vector(snap_x, snap_y);
}

std::string Vector::ShowVector() {
  char buffer[100];
  sprintf(buffer, "<%f, %f>", X(), Y());
  return std::string(buffer);
}


}       // namespace crml
#endif  // VECTOR_CC
