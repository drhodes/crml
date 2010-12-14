// -*- c++ -*-
// _.-{{ crml }}-._

#ifndef CAMERA_CC
#define CAMERA_CC

#include "./camera.h"

namespace crml {

void Camera::DrawSprite(Sprite* spr){
  if (spr) printf("Drawing %p\n", spr);
}

void Camera::DrawLayer(Layer& lyr){
  Rect view;
  CopyInto(view);
  view.StretchRight(lyr.CamDistance());
  view.StretchBottom(lyr.CamDistance());

  std::set<Rect*> nbrs = lyr.GetNeighbors(view);
  std::set<Rect*>::iterator it;

  printf("num nbrs %d\n", nbrs.size());
  
  for ( it=nbrs.begin(); it != nbrs.end(); it++ ) {
    DrawSprite(static_cast<Sprite*>(*it));
  }

}

bool Camera::Ok(){
  return Err() == OK;
}

}       // namespace crml
#endif  // CAMERA_CC






