#include "../space_hash.cc"
#include "../rect.cc"

using namespace crml;

#define EQ( _V1_, _V2_, _MSG_ ) if(_V1_==_V2_){printf("passes> %s\n",_MSG_);}else{printf("fails!! %s\n",_MSG_);}

int main(){
  SpaceHash sh(64);

  Rect r(0,0,100,100);
  Rect r2(20,20,100,100);

  EQ(r.Id(), 0, "id is 0");
  EQ(r2.Id(), 1, "id is 1");
 
  sh.Add(r);
  sh.Add(r2);

  EQ(sh.GetNeighbors(r).size(), 2, "right number of neighbors");
  EQ(r.Id(), 0, "id is 0");
  
  //printf("BucketCount(r): %d\n", sh.BucketCount(r));
  sh.Delete(r);
  //printf("r.Id(): %d\n", r.Id());
  //printf("BucketCount(r): %d\n", sh.BucketCount(r));
  r.MoveRel(10,10);
  sh.Add(r);
  //printf("BucketCount(r): %d\n", sh.BucketCount(r));
  sh.Delete(r);
  //printf("BucketCount(r): %d\n", sh.BucketCount(r));
  //printf("r2.Id(): %d\n", r2.Id());  
  //printf("r2.Id(): %d\n", r2.Id());
  //printf("BucketCount(r2): %d\n", sh.BucketCount(r2));
  sh.Delete(r2);
  //printf("r2.Id(): %d\n", r2.Id());
  //printf("BucketCount(r2): %d\n", sh.BucketCount(r2));
  r2.MoveRel(10,10);
  sh.Add(r2);
  //printf("BucketCount(r2): %d\n", sh.BucketCount(r2));
  sh.Delete(r2);
  //printf("BucketCount(r2): %d\n", sh.BucketCount(r2));

  EQ(sh.GetNeighbors(r).size(), 0, "right number of neighbors");

  return 0;
}
