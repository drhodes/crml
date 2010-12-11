// Copyright 2010 <Derek A. Rhodes>

#ifndef SPRITE_H_
#define SPRITE_H_

#include "../core/error.h"
#include "../core/crmlint.h"
#include "./rect.h"
#include "./tga_loader.h"

namespace crml {
ERR_(SPRITE_OK);

class Sprite: public Error, public Rect {
 public:
  explicit Sprite(): Error(SPRITE_OK) {
    ClassName("Sprite");
    scale_ = 1;
    angle_ = 0; // 0 on unit circle. CCW is pos.
    alpha_ = 255;
  };
  
  ~Sprite();    
  void LoadImage(TgaLoader& tga);
  
  std::vector<Color> PixelVector(); // opportunity for optimization.
  
  bool Ok();
 private:
  // Prevent copy.
  Sprite(const Sprite&);     
  Sprite& operator = (const Sprite&);

  int32 scale_;
  int32 angle_;
  uint8 alpha_;
    
  TgaLoader* image;
};

}       // namespace crml
#endif  // SPRITE_H_














