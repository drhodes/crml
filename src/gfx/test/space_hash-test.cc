#include "../space_hash.cc"
#include "../rect.cc"

using namespace crml;
#define EQ( _V1_, _V2_ )                        \
  if(_V1_==_V2_){\
    printf("passes> %s == %s\n", #_V1_, #_V2_);\
  } else {\
    printf("FAILS!> %s == %s\n", #_V1_, #_V2_);}


int main(){
  SpaceHash sh(64);
    
  Rect r(0,0,100,100);
  Rect r2(20,20,100,100);
  Rect cam(-1000, -1000, 1000, 1000);
    
  EQ(r.Id(), 0);
  EQ(r2.Id(), 1);
 
  sh.Add(r);
  sh.Add(r);
  sh.Add(r2);

  EQ(sh.GetNeighbors(r).size(), 2);
  EQ(r.Id(), 0);
  EQ(r2.Id(), 1);
  EQ(cam.Id(), 2);

  EQ(sh.GetNeighbors(r).size(), 2);
  EQ(sh.GetNeighbors(cam).size(), 3);

  for(int i=0; i<3; i++){
    EQ(sh.GetNeighbors(r).size(), 2);
    EQ(sh.GetNeighbors(cam).size(), 3);
  }
    
  return 0;
}
