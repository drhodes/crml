#include <stdio.h>

#define EQ( _V1_, _V2_ )                                                \
  if(_V1_==_V2_){ printf("passes> %s == %s\n", #_V1_, #_V2_); } else { printf("FAILS!> %s == %s\n", #_V1_, #_V2_); } 
