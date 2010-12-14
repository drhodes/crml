// Copyright 2010 <Derek A. Rhodes>

#ifndef RECT_H_
#define RECT_H_

#include "../core/crmlint.h"
#include "./vector.h"

#include <string>

namespace crml {  
  class Rect {
   public:
    static int32 ID__;
    
    Rect();
    Rect(int32, int32, int32, int32);
    Rect(Vector, Vector);

    void CopyInto(Rect& other); // rethink 
    
    void StretchLeft(int32 n);
    void StretchRight(int32 n);
    void StretchTop(int32 n);
    void StretchBottom(int32 n);

    void Move(Vector v);
    void Move(int32 x, int32 y);        
    void MoveRel(int32 x, int32 y);
    void MoveRel(Vector v);

    int32 Top();
    int32 Bottom();
    int32 Left();
    int32 Right();

    void Top(int32 n);
    void Bottom(int32 n);
    void Left(int32 n);
    void Right(int32 n);

    std::string ShowRect();
    
    int32 Id();
      
    const Vector TopLeft();
    const Vector BottomRight();      
   private:
    // Prevent copy.
    Rect(const Rect&);     
    Rect& operator = (const Rect&);
    
    int32 id__; // memory management helper.
    Vector topleft_, bottomright_;           
  };

  //static initializer.
  //int32 ID = 0;
  
}       // namespace crml
#endif  // RECT_H_













