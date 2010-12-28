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
  typedef std::pair<float64, float64> FloatPair;
  typedef std::map<FloatPair, std::set<Rect*> > SpaceMap;
  typedef std::map<int32, std::vector<FloatPair> > RectIdBucketMap;
       
  class SpaceHash: public Error {
   public:
    explicit SpaceHash(int32 gridgap):
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

   private:
    /// IntPair -> set<Rect*>
    SpaceMap space_;

    // A lookup table RectID -> BucketList
    // Needed for quick deletes of rects.
    RectIdBucketMap bucketmap_;

    // todo: decide if this should be a float64.    
    int32 gridgap_; // bucket gridgap.    
  };
  
}       // namespace crml
#endif  // SPACEHASH_H_







