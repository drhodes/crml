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


/* Given a Rect, snap the upper left corner of it
 * to the upper left corner of the bucket it's in.
 * this doesn't mutate the rect.
 * @ param r is a rect
 * @ return Vector representing the upper left of the mentioned bucket.  
 */
Vector SpaceHash::AlignTopLeft(Rect& r){
  Vector v = r.TopLeft();
  v.X(v.X() - (v.X() % gridgap_));
  v.Y(v.Y() - (v.Y() % gridgap_));
  return v;      
}

/* Given a Rect, snap the bottom right corner of it
 * to the bottom right corner of the bucket it's in.
 * this doesn't mutate the rect.
 * @ param r is a rect
 * @ return Vector representing the bottom right of the mentioned bucket.  
 */
Vector SpaceHash::AlignBottomRight(Rect& r){
  Vector v = r.BottomRight();
  v.X(v.X() + (gridgap_ - (v.X() % gridgap_)));
  v.Y(v.Y() + (gridgap_ - (v.Y() % gridgap_)));
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

//! Retrieve a set<Rect> overlapping the Rect r
//! r must already be contained in this spacehash
/*!
  \param r is the overlapping Rect  
  \return A set<Rect*> which overlaps with r
*/
std::set<Rect*> SpaceHash::GetNeighbors(Rect& r){
  bool is_temp_rect = false;
  if (BucketCount(r) == 0){
    Add(r);
    is_temp_rect = true;
  }
  
  // get a vector of all the buckets a rect is in.
  std::vector<IntPair> bm = bucketmap_[r.Id()];

  // get the intersection of all those buckets
  std::set<Rect*> inter;
  
  for (uint i = 0; i < bm.size(); i++) {    
    std::set_union( inter.begin(), inter.end(),
                    space_[bm[i]].begin(), space_[bm[i]].end(),
                    std::inserter(inter, inter.begin()) );
  }
  
  if (is_temp_rect) {    
    Delete(r);    
  }
  
  return inter;
}

bool SpaceHash::Ok(){
  return Err() == OK;
}


}       // namespace crml
#endif  // SPACEHASH_CC
