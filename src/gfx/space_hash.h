// Copyright 2010 <Derek A. Rhodes>

#ifndef SPACEHASH_H_
#define SPACEHASH_H_

#include "../core/error.h"
#include "rect.h"
#include "vector.h"

#include <map>
#include <vector>
#include <set>

namespace crml {
  ERR_(SPACEHASH_OK);

  typedef std::pair<int, int> IntPair;
  typedef std::map<IntPair, std::set<Rect*> > SpaceMap;
  typedef std::map<int, std::vector<IntPair> > RectIdBucketMap;
       
  class SpaceHash: public Error {
   public:
    explicit SpaceHash(int resolution):
    Error(SPACEHASH_OK) {
      ClassName("SpaceHash");
      res_ = resolution;
    }
    
    ~SpaceHash();    
    void Add(Rect&);
    void Delete(Rect&);
    void GetBuckets(Rect&);
    std::set<Rect*> GetNeighbors(Rect&);
        
    int BucketCount(Rect& r);    
    Vector AlignTopLeft(Rect& r);
    Vector AlignBottomRight(Rect& r);
    
    bool Ok();
   private:
    SpaceMap space_;

    // RectID -> BucketList, for quick deletion of rects.
    RectIdBucketMap bucketmap_;
    
    int res_; // bucket resolution.    
  };
  
}       // namespace crml
#endif  // SPACEHASH_H_







