// Copyright 2010 <Derek A. Rhodes>

#ifndef LAYER_H_
#define LAYER_H_

#include "../core/error.h"
#include "./mover.h"
#include "./drawer.h"

namespace crml {
  ERR_(LAYER_OK);
  
  class Layer : public Error, public Mover {    
   public:
    explicit Layer() : Error(LAYER_OK), Mover() {
      ClassName("Layer");
    }    
    ~Layer();
    
    void Draw(Drawer& dwr);

    bool Ok();
   private:
  };
  
}       // namespace crml
#endif  // LAYER_H_







