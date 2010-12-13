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
    SpaceMap space_;

    // A lookup table RectID -> BucketList
    // Needed for quick deletes of rects.
    RectIdBucketMap bucketmap_;
    
    int gridgap_; // bucket gridgap.    
  };
  
}       // namespace crml
#endif  // SPACEHASH_H_







