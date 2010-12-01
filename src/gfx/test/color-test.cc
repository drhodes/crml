// Copyright 2010 <Derek A. Rhodes>

#ifndef COLOR_H_
#define COLOR_H_

namespace crml {

  class Color {
   public:
    Color();
    Color(int, int, int, int);
    Color(int, int, int);
    
    void Red(int);
    int Red();
    void Blue(int);
    int Blue();
    void Green(int);
    int Green();     
    void Alpha(int);
    int Alpha();
    
    // rotation around the $color axis.
    // experiment.
    void RotateRed(int);
    void RotateBlue(int);
    void RotateGreen(int);
    
    void ScalarAdd(int);    

   private:
    int r_, g_, b_, a_;
    
  };
  
}       // namespace crml
#endif  // COLOR_H_
