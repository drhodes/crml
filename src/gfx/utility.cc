#include "../core/crmlint.h"
#include <stdio.h>

bool big_endian(){
  // http://stackoverflow.com/questions/1001307/detecting-endianness-programmatically-in-a-c-program
  int num = 1;
  return !(*(char *)&num == 1);
}

uint16 swap16(uint16 x){
  return x << 8 | x >> 8;
}

uint16 glue2bytes(uint8 a, uint8 b){
  // aaaa aaaa bbbb bbbb little endian
  uint16 result = (a << 8) | b;  
  if (big_endian())
    return swap16(result);
  return result;
}
