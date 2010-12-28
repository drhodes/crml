#include "../rect.cc"
#include "../vector.h"
#include <stdio.h>

#include "./test-macro.cc"
using namespace crml;

int main(){
  Rect r(0,0,100,100);
  Vector v(10, 10);

  LOG(r.ShowRect());
  
  EQ(r.Id(), 0);
  EQ(r.Top(), 0);
  EQ(r.Left(), 0);  
  EQ(r.Bottom(), 100);
  EQ(r.Right(), 100);
 
  r.StretchRight(100);
  EQ(r.Right(), 200);

  r.StretchBottom(100);
  EQ(r.Bottom(), 200);

  r.MoveRel(10, 10);
  EQ(r.Right(), 210);
  EQ(r.Bottom(), 210);

  r.Move(0, 0);
  EQ(r.Right(), 200);
  EQ(r.Bottom(), 200);

  r.MoveRel(v);
  EQ(r.Right(), 210);
  EQ(r.Bottom(), 210);

  r.MoveRel(v);
  EQ(r.Right(), 220);
  EQ(r.Bottom(), 220);

  Rect r2(0,0,0,0);
  r.CopyInto(r2);
  EQ(r2.Top(), r.Top());
  EQ(r2.Left(), r.Left());  
  EQ(r2.Right(), r.Right());
  EQ(r2.Bottom(), r.Bottom());

  EQ(max4(1,2,3,4), 4);
  EQ(max4(7,2,3,4), 7);
  EQ(min4(1,2,3,4), 1);
  EQ(min4(7,2,3,-4), -4);
  
  return 0;

}
