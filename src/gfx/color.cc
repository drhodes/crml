// Copyright 2010 <Derek A. Rhodes>

#ifndef COLOR_CC
#define COLOR_CC

#include "./color.h"

namespace crml {

inline int MakeRGBA(int r, int g, int b, int a) {
  return (a << 24) | (r << 16) | (g << 8) | b ;
}

Color::Color() {
  r_ = 0; g_ = 0; b_ = 0; a_ = 0;
}

Color::Color(int r, int g, int b, int a) {
  r_=r; g_=g; b_=b; a_=a;
}

Color::Color(int r, int g, int b) {
  Color(r,g,b,255);
}

void Color::Red(int r) {
  r_ = r;
}

int Color::Red() {
  return r_;
}

void Color::Blue(int b) {
  b_ = b;
}

int Color::Blue() {
  return b_;
}

void Color::Green(int g) {
  g_ = g;
}

int Color::Green() {
  return g_;
}

void Color::Alpha(int a) {
  a_ = a;
}

int Color::Alpha() {
  return a_;
}

// rotation around the $color axis.
// experiment.
void Color::RotateRed(int) {  
}

void Color::RotateBlue(int) {  
}

void Color::RotateGreen(int) {  
}

void Color::ScalarAdd(int) {  
}
  
}       // namespace crml
#endif  // COLOR_CC
