// -*- c++ -*-
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
      bottomright_ = Vector(0, 0);
    }
    
    Rect(float64, float64, float64, float64);
    Rect(Vector, Vector);

    void CopyInto(Rect& other); // rethink 
    
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

    float64 Width();
    float64 Height();        
    const Vector TopLeft();
    const Vector BottomRight();
    
    int32 Id();
      
    std::string ShowRect();
    
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
