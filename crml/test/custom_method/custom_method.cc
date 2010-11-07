// Copyright 2010 <Derek A. Rhodes> All Rights Reseverd.

#include <stdlib.h>
#include <crml-core.h>
#include <crml-win.h>

#include "./custom_method.h"


namespace crml {

Core core;

bool PiGenerator::Paint() {   
  uint32_t* pixel_bits = static_cast<uint32_t*>(Core::context2d_.region);
  printf("  if (IsContextValid()) {\n");
  
  if (pixel_bits == NULL){
  }
     
  int count = 0;  
  int max = (Core::window_->width * Core::window_->height) -1 ;  
  while (1){
    pixel_bits[count] = rand();
    if (count > max)
      break;
    count += 1;
  }

  core.Redraw();
  return true;
}


bool ScriptingBridge::Paint( const NPVariant* args, uint32_t arg_count, NPVariant* result) {  
  PiGenerator* pi_generator = static_cast<PiGenerator*>(Core::npp_->pdata);
  
  if (pi_generator) {
    pi_generator->Paint();
  }  
  return false;
} 
}  // namespace crml
