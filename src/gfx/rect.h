// -*- c++ -*-
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
// _.-{{ crml }}-._

#ifndef RECT_H_
#define RECT_H_

#include "../core/crmltypes.h"
#include "./vector.h"

#include <string>

namespace crml {  
  class Rect {
   public:
    static int32 ID__;

    explicit Rect() : id__(ID__++) {
      topleft_ = Vector(0, 0);
      topright_ = Vector(0, 0);
      bottomleft_ = Vector(0, 0);
      bottomright_ = Vector(0, 0);
    }
    
    Rect(float64, float64, float64, float64);
    Rect(Vector, Vector);
    Rect(Vector, Vector, Vector, Vector);
      
    void CopyInto(Rect& other);     
    
    void StretchLeft(float64 n);
    void StretchRight(float64 n);
    void StretchTop(float64 n);
    void StretchBottom(float64 n);

    void Move(Vector v);
    void Move(float64 x, float64 y);        
    void MoveRel(float64 x, float64 y);
    void MoveRel(Vector v);

    float64 Top();
    float64 Bottom();
    float64 Left();
    float64 Right();

    void Top(float64 n);
    void Bottom(float64 n);
    void Left(float64 n);
    void Right(float64 n);

    Vector Center();
    Vector TopLeft();
    Vector TopRight();
    Vector BottomLeft();
    Vector BottomRight();

    void TopLeft(Vector v);
    void TopRight(Vector v);
    void BottomLeft(Vector v);
    void BottomRight(Vector v);
    
    Rect BoundingBox();
    
    // void snap? thing about snapping rect vectors to closest
    // in a float metric in an opengl context this doesn't matter
    // the concern is pixel leaks between adjacent tile edges
    // just wait and see, it's going to take some fiddling.
    
    float64 Width();
    float64 Height();
       
    int32 Id();
      
    std::string ShowRect();
    
   private:
    // Prevent copy.
    Rect(const Rect&);     
    Rect& operator = (const Rect&);

    bool dirty_;
    int32 id__; // memory management helper.
    Vector topleft_, topright_, bottomleft_, bottomright_;
  };

  //static initializer.
  //int32 ID = 0;
  
}       // namespace crml
#endif  // RECT_H_
