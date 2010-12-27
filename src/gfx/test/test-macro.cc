#include <stdio.h>

#define LOG(_A_) printf("%s: %s\n", #_A_, _A_.c_str());

#define EQ( _V1_, _V2_ )                                                \
  if(_V1_==_V2_){ printf("passes> %s == %s\n", #_V1_, #_V2_); } else { printf("FAILS!> %s == %s\n", #_V1_, #_V2_); } 
