// Copyright 2010 <Derek A. Rhodes>

#ifndef MOVER_H_
#define MOVER_H_

#include "./vector.h"

namespace crml {  
  class Mover : public Vector {
   public:
    Mover();
    ~Mover();
    
    void Move(Vector v);
    void MoveRel(Vector v);
    void Move(int x, int y);
    void MoveRel(int x, int y);
  };
    
}       // namespace crml
#endif  // MOVER_H_






