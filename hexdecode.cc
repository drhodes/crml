// Copyright 2010 <Derek A. Rhodes> All Rights Reseverd.

#ifndef HEXDECODE_CC
#define HEXDECODE_CC

#include <string>

// dead simple encoding.

int hexes(char c) {
  int result = -1;
  switch (c) {
    case '0': result = 0; break;
    case '1': result = 1; break;
    case '2': result = 2; break;
    case '3': result = 3; break;
    case '4': result = 4; break;
    case '5': result = 5; break;
    case '6': result = 6; break;
    case '7': result = 7; break;
    case '8': result = 8; break;
    case '9': result = 9; break;
    case 'a': result = 10; break;
    case 'b': result = 11; break;
    case 'c': result = 12; break;
    case 'd': result = 13; break;
    case 'e': result = 14; break;
    case 'f': result = 15; break;
  }
  return result;
}

int hexof(char a, char b) {
  // take a, b | a and b are strings [0..9] + [a..f]
  // a == 16^1, b == 16^0
  int vala = 16 * hexes(a);
  int valb = hexes(b);
  if (vala < 0 || valb < 0) {
    printf("hexdecode got some bad data\n");
    return -1;
  }
  return vala+valb;
}

std::string hexdecode(std::string src) {
  int src_len = src.size();
  std::string out;

  for (int i = 0; i < src_len/2; i++) {
    char a = src[i*2];
    char b = src[i*2+1];
    char cur = hexof(a, b);
    out += cur;
  }
  return out;
}

#endif
