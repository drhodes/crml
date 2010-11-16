// Copyright 2010 <Derek A. Rhodes>
// #include <crml-core.h>

#ifndef SQUARE_CC
#define SQUARE_CC

#include "./square.h"
#include <random>
#include <time.h>
#include <stdlib.h>

namespace crml {

Square::Square(){
  Randomize(4);
}

Square::~Square(){}

int RandInt(int s, int n){ // unbelievable.
  srand(s);
  return rand()%n;
}

void Square::Randomize(int s){
  x_ = 100 + RandInt(s, 200);
  y_ = 100 + RandInt(s, 200);
  radius_ = 0 + RandInt(s,50);
  angle_ = 0 ;
  speed_ = -5 + RandInt(s,3);
  color_ = 345546 + RandInt(s,10000000);
  dxdt_ = -5 + RandInt(s+45,10);
  dydt_ = -5 + RandInt(s,10);
}

void Square::Flick(int s){
  dxdt_ += -1 + RandInt(s, 3);
  dydt_ += -1 + RandInt(s, 3);
}


int Square::X(){
  return x_;
}

void Square::X(int x){
  x_ = x;
}

int Square::Y(){
  return y_;
}

void Square::Y(int y){
  y_ = y;
}

void Square::Speed(int s){
  speed_ = s;
}

void Square::Heading(int angle){
  angle_ = angle;
}

void Square::Color(int c){
  color_ = c;
}

void Square::Move(int width, int height){
  X(X() + dxdt_);
  Y(Y() + dydt_);

  if(X() > width - radius_*2 || X() < 0) {
    X(X() - dxdt_);
    dxdt_ *= -1;
  }

  if(Y() > height - radius_*2 || Y() < 0) {
    Y(Y() - dydt_);
    dydt_ *= -1;
  }
  
}

void Square::Draw(uint32_t* pixels_, int width, int height){
  for(int i=y_; i<y_+radius_*2; i++){
    if(i > height) continue;    
    for(int j=x_; j<x_+radius_*2; j++){      
      if(j > width) continue;
      pixels_[i*width + j] |= color_;
      pixels_[i*width + j] += color_;
    }
  }
}
              
}       // namespace crml
#endif  // SQUARE_CC


