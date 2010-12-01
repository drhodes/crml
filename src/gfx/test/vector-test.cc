// Copyright 2010 <Derek A. Rhodes>

#ifndef VECTOR_H_
#define VECTOR_H_

#include <math.h>

namespace crml {
  
  class Vector {
   public:
    Vector();
    Vector(int, int);
    Vector(const Vector&);
    ~Vector();

    void XY(int x, int y);    
    int X();
    void X(int x);
    int Y();
    void Y(int y);
    int Length();
    int Distance(Vector* other);                  
    Vector Align(int resolution);
    
   private:
    int x_, y_;
  };
  
}       // namespace crml
#endif  // VECTOR_H_












