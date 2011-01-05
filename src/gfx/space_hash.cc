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
#include <assert.h>

namespace crml {

SpaceHash::~SpaceHash(){
}

/* Given a Rect, snap the upper left corner to the upper left
 * corner of the bucket it's in. this doesn't mutate the rect.
 * @ param r is a rect
 * @ return Vector representing the upper left of the mentioned bucket.  
 */
Vector SpaceHash::AlignTopLeft(Rect& r){
  Vector v = r.BoundingBox().TopLeft();
  v.X(v.X() - float64(int32(v.X()) % gridgap_));
  v.Y(v.Y() - float64(int32(v.Y()) % gridgap_));
  return v;      
}

/* Given a Rect, snap the bottom right corner to the bottom right
 * corner of the bucket it's in.
 * this doesn't mutate the rect.
 * @ param r is a rect
 * @ return Vector representing the bottom right of the mentioned bucket.  
 */
Vector SpaceHash::AlignBottomRight(Rect& r){
  Vector v = r.BoundingBox().BottomRight();
  v.X(v.X() + (gridgap_ - float64(int32(v.X()) % gridgap_)));
  v.Y(v.Y() + (gridgap_ - float64(int32(v.Y()) % gridgap_)));
  return v;
}

/* Counts the number of buckets a Rect is in
 * @param r is the source Rect  
 * @return The number of buckets the r resides in
 */
int SpaceHash::BucketCount(Rect& r){
  if (bucketmap_.count(r.Id()) == 0) {
    return 0;
  } else {
    return bucketmap_[r.Id()].size();
  }
}

/* Add a reference to Rect, or any subclass of rect to the space hash.
 * As it stands space hash doesn't manage any memory here, just references.
 * manage your sprites with care, if they are destoyed without consideration
 * there will be null references here in the in hashtable.
 * I would like to avoid checking for null references in this code,
 * But there may be no way of avoiding it.
 */
void SpaceHash::Add(Rect& r){
  if (ContainsRect(r)){
    SetReportErr("Tried to add a rect which already exists in this spacehash|layer");
    return;
  }
  
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
        bucketmap_[r.Id()] = std::vector<FloatPair>();
      }
      bucketmap_[r.Id()].push_back(key);
    }    
  }
  num_rects_ += 1;
}  


/// Delete a rect from the space_hash.  This must delete from two private
/// members: bucketmap_, which provides quick lookups for fast deletes,
/// and space_ which contains organizes and stores all the rects in space
/// @param r, The rect to delete
/// @return void

void SpaceHash::Delete(Rect& r){
  if (!ContainsRect(r)){
    SetReportErr("Tried to remove a rect which does not exist in the space hash");
    return;
  }
    
  std::vector<FloatPair> bm = bucketmap_[r.Id()];
  std::vector<FloatPair>::iterator it;  

  for (it = bm.begin(); it < bm.end(); it++) {
    // need to delete r from point (*it) in space_
    space_[*it].erase(&r);
  }
  
  bucketmap_.erase(r.Id());
  num_rects_ -= 1;
}

/// Is the Rect contained within this SpaceHash or Layer?
/// @param A rect to test the existence of.
/// @return boolean value
bool SpaceHash::ContainsRect(Rect& r){
  return BucketCount(r) > 0;
}

/// Retrieve a set<Rect> overlapping the Rect r
/// @param r is the overlapping Rect  
/// @return A set<Rect*> which overlaps with r
std::set<Rect*> SpaceHash::GetNeighbors(Rect& r){
  bool is_temp_rect = false;
  
  if (!ContainsRect(r)){
    Add(r);
    assert(ContainsRect(r));
    is_temp_rect = true;
  }
  
  // clue: the builtin [] operator on std::map creates an element.

  // get a vector of all the buckets a rect is in.
  std::vector<FloatPair> bm = bucketmap_[r.Id()];

  // get the intersection of all those buckets
  std::set<Rect*> inter;

  for (uint i = 0; i < bm.size(); i++) {    
    std::set_union( inter.begin(), // the accumulating set.
                    inter.end(),
                    space_[bm[i]].begin(), 
                    space_[bm[i]].end(),
                    std::inserter(inter, inter.begin()) );
  }

  if (is_temp_rect) {    
    Delete(r);
  }

  return inter;
}

int32 SpaceHash::NumRects(){
  return num_rects_;
}



}       // namespace crml
#endif  // SPACEHASH_CC
