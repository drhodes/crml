// Copyright 2010 <Derek A. Rhodes>
// #include <crml-core.h>

#ifndef SQUARE_H_
#define SQUARE_H_

#include <crml-core.h>
#include <crml-gfx.h>

namespace crml {
  class Square: public Drawer {    
   public:    
    explicit Square(): Drawer() {
      Randomize(4);
    }
    ~Square();
    
    void SetColor(int x);
    //void Draw(uint32_t* pixels_, int width, int height);
    
    void Speed(int s);
    void Heading(int angle); // 0 degrees on the x axis;
    void Randomize(int s);
    void Flick(int s);
    void Stop();

    void Step(int width, int height);
    void OldDraw(uint32_t* pixels_, int width, int height);
    
    virtual void Draw(Layer& l);    
   private:    
    int dxdt_, dydt_;
    int speed_;
    int angle_;
    
    int color_;
    int radius_;
  };
  
}       // namespace crml
#endif  // SQUARE_H_








