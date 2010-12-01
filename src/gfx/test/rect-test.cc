// Copyright 2010 <Derek A. Rhodes>

#ifndef RECT_H_
#define RECT_H_

#include "./vector.h"

namespace crml {
  
  class Rect {
   public:
   
    Rect();
    Rect(int, int, int, int);
    Rect(Vector, Vector);
    Rect(const Rect&);
    
    void StretchLeft(int n);
    void StretchRight(int n);
    void StretchTop(int n);
    void StretchBottom(int n);

    void Move(Vector v);
    void Move(int x, int y);        
    void MoveRel(int x, int y);
    void MoveRel(Vector v);

    int Top();
    int Bottom();
    int Left();
    int Right();
    
    const Vector TopLeft();
    const Vector BottomRight();      
   private:
    static int ID;
    
    int id__; // memory management helper.
    Vector topleft_, bottomright_;           
  };

  //static initializer.
  int ID = 0;
  
}       // namespace crml
#endif  // RECT_H_













