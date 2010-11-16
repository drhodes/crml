#include <stdio.h>
#include <string.h>

#include "./media-blob.h"

int foo(char temp[]){
  printf("sizeof: %d", sizeof(fnt__inconsolata_otf));  
}


int main (void) {
  foo(fnt__inconsolata_otf);
  return 0;
}
