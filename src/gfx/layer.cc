// -*- c++ -*-
// _.-{{ crml }}-._

#ifndef LAYER_CC
#define LAYER_CC

#include "./layer.h"

namespace crml {

Layer::~Layer(){}

void Layer::AddSprite(Sprite& s){
  Add(s);  
}

void Layer::DeleteSprite(Sprite& s){
  Delete(s);
}

bool Layer::ContainsSprite(Sprite& s){
  return BucketCount(s) > 0;
}


void Layer::CamDistance(int32 d){
  cam_dist_ = d;
}

int32 Layer::CamDistance(){
  return cam_dist_;
}

}       // namespace crml
#endif  // LAYER_CC
