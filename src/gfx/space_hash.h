// Copyright 2010 <Derek A. Rhodes>

#ifndef SPACEHASH_H_
#define SPACEHASH_H_

#include "../core/error.h"
#include "rect.h"
#include "vector.h"

#include <map>
#include <list>

namespace crml {
  ERR_(SPACEHASH_OK);

  typedef std::map<std::pair<int, int>, std::list<Rect>> SpaceMap;
  
  class SpaceHash: public Error {
   public:
    explicit SpaceHash(int resolution):
    Error(SPACEHASH_OK) {
      ClassName("SpaceHash");
      resolution_ = resolution;
    }
    
    ~SpaceHash();    
    void Add(Rect);
    void Delete(Rect);
    void GetBuckets(Rect);

    bool Ok();
   private:    
    SpaceMap space_;
    int resolution_;    
  };
  
}       // namespace crml
#endif  // SPACEHASH_H_







