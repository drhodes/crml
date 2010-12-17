// -*- c++ -*-
// _.-{{crml}}-._

#ifndef SPRITE_H_
#define SPRITE_H_

#include "../core/error.h"
#include "../core/crmltypes.h"
#include "./rect.h"
#include "./tga_loader.h"

namespace crml {
ERR_(SPRITE_ANGLE_NEGATIVE_NORMALIZE);
ERR_(SPRITE_ANGLE_OVERFLOW_NORMALIZE);  

class Sprite: public Error, public Rect {

 public:
  explicit Sprite(): Error(OK) {
    ClassName("Sprite");
    scale_ = 1;
    angle_ = 0; // 0 on unit circle. CCW is pos.
    alpha_ = 255;
  };
  
  ~Sprite();    
  void LoadImage(TgaLoader& tga);
  void Angle(float64 a);
  float64 Angle();
  void Rotate(float64 angle);
  void Scale(float64 scale_);
    
  std::vector<Color> PixelVector(); // opportunity for optimization.

  // need to move texel stuff to TgaLoader.
  // think about why this might not be a good idea.
  void LoadTexelArray();
  const uint8* TexelArray();
  
 private:
  // Prevent copy.
  Sprite(const Sprite&);     
  Sprite& operator = (const Sprite&);
  // ------------------------------------------------------------------
  
  float64 scale_;
  float64 angle_;
  uint8 alpha_;
    
  TgaLoader* image_;
  const uint8* texels_;
  uint32 texels_size_;
};

}       // namespace crml
#endif  // SPRITE_H_



