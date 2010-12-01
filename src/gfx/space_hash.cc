// Copyright 2010 <Derek A. Rhodes>

#ifndef SPACEHASH_CC
#define SPACEHASH_CC

#include <stdio.h>
#include "./space_hash.h"
namespace crml {

SpaceHash::~SpaceHash(){
}

Vector SpaceHash::AlignTopLeft(Rect& r){
  Vector v = r.TopLeft();
  v.X(v.X() - (v.X() % res_));
  v.Y(v.Y() - (v.Y() % res_));
  return v;      
}

Vector SpaceHash::AlignBottomRight(Rect& r){
  Vector v = r.BottomRight();
  v.X(v.X() + (res_ - (v.X() % res_)));
  v.Y(v.Y() + (res_ - (v.Y() % res_)));
  return v;
}

int SpaceHash::BucketCount(Rect& r){
  if (bucketmap_.count(r.Id()) == 0) {
    return 0;
  } else {
    return bucketmap_[r.Id()].size();
  }
}

void SpaceHash::Add(Rect& r){
  Vector tl = AlignTopLeft(r);
  Vector br = AlignBottomRight(r);
  
  for (int y = tl.Y(); y <= br.Y(); y += res_){
    for (int x = tl.X(); x <= br.X(); x += res_){
      std::pair<int, int> key(x, y);
      
      if (space_.count(key) == 0) {
        space_[key] = std::vector<Rect*>();
      }
      space_[key].push_back(&r);

      if (bucketmap_.count(r.Id()) == 0) {
        bucketmap_[r.Id()] = std::vector<IntPair>();
      }
      bucketmap_[r.Id()].push_back(key);            
    }
  }
}  

void SpaceHash::Delete(Rect& r){
  std::vector<IntPair> bm = bucketmap_[r.Id()];
  std::vector<IntPair>::iterator it;
  for (it = bm.begin(); it < bm.end(); it++) {
    bucketmap_[r.Id()].erase(it);
  }
}
  
bool SpaceHash::Ok(){
  return Err() == SPACEHASH_OK;
}


}       // namespace crml
#endif  // SPACEHASH_CC
