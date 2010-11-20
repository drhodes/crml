// Copyright 2010 <Derek A. Rhodes>

#ifndef MOVER_CC
#define MOVER_CC

#include "./mover.h"

namespace crml {

Mover::Mover() : Vector() {
  X(0);
  Y(0);
}

Mover::~Mover(){
  
}

void Mover::Move(Vector v){
  X(v.X());
  Y(v.Y());
}

void Mover::MoveRel(Vector v){
  X(X() + v.X());
  Y(Y() + v.Y());
}
  
}       // namespace crml
#endif  // MOVER_CC
