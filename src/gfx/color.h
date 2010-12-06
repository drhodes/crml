// Copyright 2010 <Derek A. Rhodes>

#ifndef COLOR_H_
#define COLOR_H_

#include "../core/crmlint.h"
#include <string>

namespace crml {

  class Color {
   public:
    Color();
    Color(uint8, uint8, uint8, uint8);
    Color(uint8, uint8, uint8);
    
    void Red(uint8);
    uint8 Red();
    void Blue(uint8);
    uint8 Blue();
    void Green(uint8);
    uint8 Green();     
    void Alpha(uint8);
    uint8 Alpha();
    
    // rotation around the $color axis.
    // experiment.
    void RotateRed(uint8);
    void RotateBlue(uint8);
    void RotateGreen(uint8);
    
    void ScalarAdd(uint8);    

    std::string Show();
   private:
    uint8 r_, g_, b_, a_;
    
  };
  
}       // namespace crml
#endif  // COLOR_H_
