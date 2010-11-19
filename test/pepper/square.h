// Copyright 2010 <Derek A. Rhodes>
// #include <crml-core.h>

#ifndef SQUARE_H_
#define SQUARE_H_

#include <crml-core.h>

namespace crml {
  class Square {
   public:
    Square();
    ~Square();
    
    int X();
    void X(int x);
    int Y();
    void Y(int y);
    
    void Color(int x);
    void Draw(uint32_t* pixels_, int width, int height);
    void Speed(int s);
    void Heading(int angle); // 0 degrees on the x axis;
    void Move(int width, int height);
    void Randomize(int s);
    void Flick(int s);
    void Stop();
    
   private:
    int x_, y_;
    int dxdt_, dydt_;
    int speed_;
    int angle_;
    
    int color_;
    int radius_;
  };
  
}       // namespace crml
#endif  // SQUARE_H_








