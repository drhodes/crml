// -*- c++ -*-
// _.-{{ crml }}-._

#ifndef CAMERA_H_
#define CAMERA_H_

#include "./layer.h"
#include "./rect.h"
#include "../win/display.h"

namespace crml {

class Camera: public Error, public Rect {
 public:
  explicit Camera(): Error(OK),
                     Rect() {           
    ClassName("Camera");    
  }
  
  explicit Camera(int height, int width): Error(OK),
                                          Rect(0,0, width, height) {           
    ClassName("Camera");    
  }
  
  explicit Camera(Rect r): Error(OK),
                           Rect( r.Left(), r.Top(), r.Right(), r.Bottom() ) {
    ClassName("Camera");    
  }
  
  //~Camera();

  void DrawSprite(Sprite* spr);
  void DrawLayer(Layer& lyr);

 private:

};
  
}       // namespace crml
#endif  // CAMERA_H_






