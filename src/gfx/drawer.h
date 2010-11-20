// Copyright 2010 <Derek A. Rhodes>

#ifndef DRAWER_H_
#define DRAWER_H_

#include "./vector.h"
#include "./layer.h"
#include "./mover.h"

namespace crml {
  class Drawer {
   public:
    Drawer();
    ~Drawer();

    void virtual Draw(Layer l) = 0;
    
   private:

  }; 
}       // namespace crml
#endif  // DRAWER_H_









