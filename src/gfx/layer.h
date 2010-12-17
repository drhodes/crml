// -*- c++ -*-
// _.-{{ crml }}-._

#ifndef LAYER_H_
#define LAYER_H_

#include "../core/error.h"
#include "./rect.h"
#include "./drawer.h"
#include "./space_hash.h"
#include "./sprite.h"

namespace crml {
  
class Layer : public Rect, public SpaceHash {    
 public:
  explicit Layer(): Rect(),
                    SpaceHash(64) {    
    ClassName("Layer");
    cam_dist_ = 1;
  }
  
  explicit Layer(float64 gridgap): Rect(),
                                   SpaceHash(gridgap) {
    ClassName("Layer");
    cam_dist_ = 1;
  }    
  
  ~Layer();  
  void AddSprite(Sprite& s);
  void DeleteSprite(Sprite& s);
  bool ContainsSprite(Sprite& s);
  
  float64 CamDistance();
  void CamDistance(float64 d);
  
 private:
  float cam_dist_;

  
};
}       // namespace crml
#endif  // LAYER_H_







