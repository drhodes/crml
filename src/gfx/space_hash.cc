// Copyright 2010 <Derek A. Rhodes>

#ifndef SPACEHASH_CC
#define SPACEHASH_CC

#include "./space_hash.h"

namespace crml {

SpaceHash::~SpaceHash(){
}

void SpaceHash::Add(Mover mov){
  // this Aligns the bucket to a grid
  Vector v = mov.Align(resolution_);
  std::pair<int, int> key(v.X(), v.Y());

  if (space_.count(key) == 0) {
    std::list<Mover> lst;
    space_[key] = lst;
  }  
  space_[key].push_back(mov);  
}  

void SpaceHash::Delete(Mover mov){
  /*
  Vector v = mov.Align(resolution_);
  std::pair<int, int> key(v.X(), v.Y());

  
  if (space_.count(key) == 0) {
    std::list<Mover> lst;
    space_[key] = lst;
  }  
  */  
  
}

bool SpaceHash::Ok(){
  return Err() == SPACEHASH_OK;
}


}       // namespace crml
#endif  // SPACEHASH_CC
