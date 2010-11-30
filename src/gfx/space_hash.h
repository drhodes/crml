// Copyright 2010 <Derek A. Rhodes>

#ifndef SPACEHASH_H_
#define SPACEHASH_H_

#include "../core/error.h"
#include "mover.h"
#include "vector.h"

#include <map>
#include <list>

namespace crml {
  ERR_(SPACEHASH_OK);

  typedef std::map<std::pair<int, int>, std::list<Mover>> SpaceMap;
  
  class SpaceHash: public Error {
   public:
    explicit SpaceHash(int resolution):
    Error(SPACEHASH_OK) {
      ClassName("SpaceHash");
      resolution_ = resolution;
    }
    
    ~SpaceHash();    
    void Add(Mover);
    void Delete(Mover);
    void GetBuckets(Mover);

    bool Ok();
   private:    
    SpaceMap space_;
    int resolution_;    
  };
  
}       // namespace crml
#endif  // SPACEHASH_H_







