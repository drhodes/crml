// -*- c++ -*-
// Copyright (c) 2010 Derek A. Rhodes. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the /crml/license directory. {{crml}}

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
  view.StretchRight(lyr.CamDistance() * Width());
  view.StretchBottom(lyr.CamDistance() * Height());

  printf("%s\n",view.ShowRect().c_str());
  
  std::set<Rect*> nbrs = lyr.GetNeighbors(view);
  std::set<Rect*>::iterator it;

  printf("num nbrs %d\n", nbrs.size());
  
  for ( it=nbrs.begin(); it != nbrs.end(); it++ ) {
    DrawSprite(static_cast<Sprite*>(*it));
  }
}

}       // namespace crml
#endif  // CAMERA_CC






