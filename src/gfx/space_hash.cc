/* _.-{ license management }-._ 
Copyright (c) 2010, Derek A. Rhodes
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
3. Neither the name of the PostgreSQL Global Development Group nor the names
   of its contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/
// _.-{{crml}}-._

#ifndef SPACEHASH_CC
#define SPACEHASH_CC

#include <stdio.h>
#include <algorithm>
#include <utility> 
#include "./space_hash.h"

namespace crml {

SpaceHash::~SpaceHash(){
}

Vector SpaceHash::AlignTopLeft(Rect& r){
  Vector v = r.TopLeft();
  v.X(v.X() - (v.X() % gridgap_));
  v.Y(v.Y() - (v.Y() % gridgap_));
  return v;      
}

Vector SpaceHash::AlignBottomRight(Rect& r){
  Vector v = r.BottomRight();
  v.X(v.X() + (gridgap_ - (v.X() % gridgap_)));
  v.Y(v.Y() + (gridgap_ - (v.Y() % gridgap_)));
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
  
  for (int y = tl.Y(); y <= br.Y(); y += gridgap_){
    for (int x = tl.X(); x <= br.X(); x += gridgap_){
      std::pair<int, int> key(x, y);
      
      if (space_.count(key) == 0) {        
        space_[key] = std::set<Rect*>();
      }
      space_[key].insert(&r);

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

std::set<Rect*> SpaceHash::GetNeighbors(Rect& r){
  // get a vector of all the buckets a rect is in.
  std::vector<IntPair> bm = bucketmap_[r.Id()];

  // get the intersection of all those buckets
  std::set<Rect*> inter;
  
  for (uint i = 0; i < bm.size(); i++) {    
    std::set_union( inter.begin(), inter.end(),
                    space_[bm[i]].begin(), space_[bm[i]].end(),
                    std::inserter(inter, inter.begin()) );
  }    
  return inter;
}

bool SpaceHash::Ok(){
  return Err() == OK;
}


}       // namespace crml
#endif  // SPACEHASH_CC
