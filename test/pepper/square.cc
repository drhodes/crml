// Copyright 2010 <Derek A. Rhodes>
// #include <crml-core.h>

#ifndef SQUARE_CC
#define SQUARE_CC

#include "./square.h"
#include <random>
#include <time.h>
#include <stdlib.h>

namespace crml {

Square::~Square(){}

int RandInt(int s, int n){ // unbelievable.
  srand(s);
  return rand()%n;
}

void Square::Randomize(int s){
  X(100 + RandInt(s, 200));
  Y(100 + RandInt(s, 200));
  radius_ = 0 + RandInt(s,20);
  angle_ = 0 ;
  speed_ = -5 + RandInt(s,3);
  SetColor(345546 + RandInt(s,10000000));
  dxdt_ = -5 + RandInt(s+45,10);
  dydt_ = -5 + RandInt(s,10);
}

void Square::Flick(int s){
  dxdt_ += -1 + RandInt(s, 3);
  dydt_ += -1 + RandInt(s, 3);
}

void Square::Stop(){
  dxdt_ = 0;
  dydt_ = 0;
}

void Square::Speed(int s){
  speed_ = s;
}

void Square::Heading(int angle){
  angle_ = angle;
}

void Square::SetColor(int c){
  color_ = c;
}

void Square::Step(int width, int height){
  MoveRel(Vector(dxdt_, dydt_));

  if(X() > width - radius_*2 || X() < 0) {
    MoveRel(Vector(-dxdt_, 0));
    dxdt_ *= -1;
  }

  if(Y() > height - radius_*2 || Y() < 0) {
    MoveRel(Vector(-dydt_, 0));
    dydt_ *= -1;
  }
  //printf("<%d, %d> \n", X(), Y());
}

void Square::Draw(Layer& layer){
}

void Square::OldDraw(uint32_t* pixels_, int width, int height){
  uint max = width * height;
  
  for(int i=Y(); i< Y() + radius_*2; i++){
    if(i > height) continue;
    if(i < 0) continue;
    for(int j=X(); j< X() + radius_*2; j++){      
      if(j > width) continue;
      if(j < 0) continue;
      if (i*width+j > max) continue;
      
      pixels_[i*width + j] = color_;
    }
  }
}
              
}       // namespace crml
#endif  // SQUARE_CC


