// Copyright 2010 <Derek A. Rhodes>

#ifndef LAYER_H_
#define LAYER_H_

#include "../core/error.h"
#include "./rect.h"
#include "./drawer.h"
#include "./space_hash.h"
#include "./sprite.h"

namespace crml {
  ERR_(LAYER_OK);
  
class Layer : public Rect, public SpaceHash {    
 public:
  explicit Layer():
      Rect(),
      SpaceHash(32) {
    ClassName("Layer");
  }
  
  explicit Layer(uint32 gridgap):
      Rect(),
      SpaceHash(gridgap) {
      ClassName("Layer");
  }    
    
  ~Layer();
  
  void AddSprite(Sprite& s);

  bool Ok();
  
 private:

};


}       // namespace crml
#endif  // LAYER_H_







