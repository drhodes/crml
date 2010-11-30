// Copyright 2010 <Derek A. Rhodes>

#ifndef LAYER_H_
#define LAYER_H_

#include "../core/error.h"
#include "./rect.h"
#include "./drawer.h"

namespace crml {
  ERR_(LAYER_OK);
  
  class Layer : public Error, public Rect {    
   public:
    explicit Layer() : Error(LAYER_OK), Rect() {
      ClassName("Layer");
    }    
    ~Layer();
    
    void Draw(Drawer& dwr);

    bool Ok();
   private:
  };
  
}       // namespace crml
#endif  // LAYER_H_







