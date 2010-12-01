#include "../space_hash.cc"
#include "../rect.cc"

using namespace crml;

int main(){
  SpaceHash sh(64);

  Rect r(34,34,103,100);
  Rect r2(-234,-34,103,300);
 
  printf("r.Id(): %d\n", r.Id());  
  sh.Add(r);
  sh.Add(r2);
  printf("r.Id(): %d\n", r.Id());
  printf("BucketCount(r): %d\n", sh.BucketCount(r));
  sh.Delete(r);
  printf("r.Id(): %d\n", r.Id());
  printf("BucketCount(r): %d\n", sh.BucketCount(r));
  r.MoveRel(10,10);
  sh.Add(r);
  printf("BucketCount(r): %d\n", sh.BucketCount(r));
  sh.Delete(r);
  printf("BucketCount(r): %d\n", sh.BucketCount(r));
  printf("r2.Id(): %d\n", r2.Id());  
  printf("r2.Id(): %d\n", r2.Id());
  printf("BucketCount(r2): %d\n", sh.BucketCount(r2));
  sh.Delete(r2);
  printf("r2.Id(): %d\n", r2.Id());
  printf("BucketCount(r2): %d\n", sh.BucketCount(r2));
  r2.MoveRel(10,10);
  sh.Add(r2);
  printf("BucketCount(r2): %d\n", sh.BucketCount(r2));
  sh.Delete(r2);
  printf("BucketCount(r2): %d\n", sh.BucketCount(r2));

  /*
  int count = 0;
  while(1){
    Rect r3(count, count*2, count*3, count*4);
    sh.Add(r3);
    count += 1;
    printf("r3.Id(): %d\n", r3.Id());
    printf("BucketCount(r3): %d\n", sh.BucketCount(r3));
  }
  */  
  return 0;
}
