// Copyright 2010 <Derek A. Rhodes>

#ifndef COLOR_CC
#define COLOR_CC

#include <stdio.h>
#include "./color.h"


namespace crml {

inline uint8 MakeRGBA(uint8 r, uint8 g, uint8 b, uint8 a) {
  return (a << 24) | (r << 16) | (g << 8) | b ;
}

Color::Color() {
  r_ = 0; g_ = 0; b_ = 0; a_ = 0;
}

Color::Color(uint8 r, uint8 g, uint8 b, uint8 a) {
  r_=r; g_=g; b_=b; a_=a;
}

Color::Color(uint8 r, uint8 g, uint8 b) {
  Color(r,g,b,255);
}

void Color::Red(uint8 r) {
  r_ = r;
}

uint8 Color::Red() {
  return r_;
}

void Color::Blue(uint8 b) {
  b_ = b;
}

uint8 Color::Blue() {
  return b_;
}

void Color::Green(uint8 g) {
  g_ = g;
}

uint8 Color::Green() {
  return g_;
}

void Color::Alpha(uint8 a) {
  a_ = a;
}

uint8 Color::Alpha() {
  return a_;
}

std::string Color::Show(){
  char buffer[100];
  //int32 len;
  //len =
  sprintf(buffer, "<%d, %d, %d, %d>", r_, g_, b_, a_);
  return std::string(buffer);//, len);
}


// rotation around the $color axis.
// experiment.
void Color::RotateRed(uint8) {  
}

void Color::RotateBlue(uint8) {  
}

void Color::RotateGreen(uint8) {  
}

void Color::ScalarAdd(uint8) {  
}
  
}       // namespace crml
#endif  // COLOR_CC
