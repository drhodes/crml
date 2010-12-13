// _.-{{crml}}-._

#ifndef SPRITE_H_
#define SPRITE_H_

#include "../core/error.h"
#include "../core/crmlint.h"
#include "./rect.h"
#include "./tga_loader.h"

namespace crml {

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
  void Angle(int32 h);
  int32 Angle();
  void Rotate(int32 angle);
  void Scale(float scale_);
    
  std::vector<Color> PixelVector(); // opportunity for optimization.
  
  bool Ok();
 private:
  // Prevent copy.
  Sprite(const Sprite&);     
  Sprite& operator = (const Sprite&);

  float scale_;
  int32 angle_;
  uint8 alpha_;
    
  TgaLoader* image_;
};

}       // namespace crml
#endif  // SPRITE_H_














