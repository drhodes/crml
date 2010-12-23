// Copyright 2010 <Derek A. Rhodes>

#ifndef VECTOR_H_
#define VECTOR_H_

#include "../core/crmltypes.h"
#include <math.h>
#include <stdio.h>
#include <string>

namespace crml {
  
  class Vector {
   public:
    Vector();
    Vector(float64, float64);
    Vector(const Vector&);
    ~Vector();

    void XY(float64 x, float64 y);    
    float64 X();
    void X(float64 x);
    float64 Y();
    void Y(float64 y);
    float64 Length();
    float64 Distance(Vector& v);

    Vector Multiply(float n);
    Vector Negate();
    Vector Add(Vector& v);
    Vector Subtract(Vector& v);
    bool Equal(Vector& v);
    
    Vector Rotate(float64 theta);
    void RotateUpdate(float64 theta);
    
    Vector Align(int32 resolution);

    std::string ShowVector();
   private:
    float64 x_, y_;
  };
  
}       // namespace crml
#endif  // VECTOR_H_












