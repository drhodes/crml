// Copyright 2010 <Derek A. Rhodes>

#ifndef VECTOR_H_
#define VECTOR_H_

namespace crml {
  
  class Vector {
   public:
    Vector();
    Vector(int, int);
    ~Vector();

    int X();
    void X(int x);
    int Y();
    void Y(int y);
    int Length();
         
   private:
    int x_, y_;
  };
  
}       // namespace crml
#endif  // VECTOR_H_












