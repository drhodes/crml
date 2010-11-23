// Copyright 2010 <Derek A. Rhodes>

#ifndef DRAWER_H_
#define DRAWER_H_

#include "./mover.h"

namespace crml {
  class Drawer: public Mover {
   public:
    explicit Drawer() : Mover() {
    }

    void Resize(int width, int height);      
    ~Drawer();
    
   private:

  };
  
}       // namespace crml
#endif  // DRAWER_H_









