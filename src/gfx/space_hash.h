// _.-{{crml}}-._

#ifndef SPACEHASH_H_
#define SPACEHASH_H_

#include <map>
#include <vector>
#include <set>

#include "../core/error.h"
#include "rect.h"
#include "vector.h"

namespace crml {
  typedef std::pair<int, int> IntPair;
  typedef std::map<IntPair, std::set<Rect*> > SpaceMap;
  typedef std::map<int, std::vector<IntPair> > RectIdBucketMap;
       
  class SpaceHash: public Error {
   public:
    explicit SpaceHash(int gridgap):
    Error(OK) {
      ClassName("SpaceHash");
      gridgap_ = gridgap;
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
    /// IntPair -> set<Rect*>
    SpaceMap space_;

    // A lookup table RectID -> BucketList
    // Needed for quick deletes of rects.
    RectIdBucketMap bucketmap_;
    
    int gridgap_; // bucket gridgap.    
  };
  
}       // namespace crml
#endif  // SPACEHASH_H_







