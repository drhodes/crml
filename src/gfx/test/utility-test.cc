#include "../../core/crmlint.h"
#include "../utility.cc"
#include <stdio.h>

//using namespace crml;

#define EQ( _V1_, _V2_, _MSG_ ) if(_V1_==_V2_){printf("passes> %s\n",_MSG_);}else{printf("fails!! %s\n",_MSG_);}

int main(){
  EQ(swap16(1), 256, "swap16 1 <-> 256");
  EQ(swap16(101), 25856, "swap16 101 <-> 25856");
  EQ(swap16(0xffff), 0xffff, "swap16 0xffff <-> 0xffff");
  EQ(swap16(0xbeef), 0xefbe, "swap16 beef <-> efbe");

  EQ(glue2bytes(0xaa, 0xbb), 0xaabb, "glue 0xaa 0xbb -> 0xaabb");
  EQ(glue2bytes(0x00, 0x00), 0x0000, "glue 0x00 0x00 -> 0x0000");
  EQ(glue2bytes(0x12, 0x34), 0x1234, "glue 0x12 0x34 -> 0x1234");
  EQ(glue2bytes(0xbe, 0xef), 0xbeef, "glue 0xbe, 0xef -> 0xbeef");
    
  return 0;
}
