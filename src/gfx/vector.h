// Copyright 2010 <Derek A. Rhodes>

#ifndef VECTOR_H_
#define VECTOR_H_

#include "../core/crmltypes.h"
#include <math.h>

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
    float64 Distance(Vector* other);                  
    Vector Align(int32 resolution);
    
   private:
    float64 x_, y_;
  };
  
}       // namespace crml
#endif  // VECTOR_H_












