// Copyright 2010 <Derek A. Rhodes>

#ifndef LAYER_CC
#define LAYER_CC

#include "./layer.h"

namespace crml {

Layer::~Layer(){}

void Layer::Draw(Drawer& dwr){
}

bool Layer::Ok(){
  return Err() == LAYER_OK;
}

void Layer::AddSprite(Sprite& s){
  Add(s);
}

}       // namespace crml
#endif  // LAYER_CC
