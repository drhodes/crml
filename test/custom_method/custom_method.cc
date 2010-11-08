// Copyright 2010 <Derek A. Rhodes> All Rights Reseverd.

#include <stdlib.h>
#include <crml-core.h>
#include <crml-win.h>

#include "./custom_method.h"

namespace crml {

Display dsp;

void Noise() {
  /// Grab an array of pixels.
  uint32_t* pixel_bits = dsp.Pixels();  
  dsp.Check();
  
  int num_pixels = dsp.Height() * dsp.Width();
  dsp.Check();
  
  for (int count=0; count < num_pixels; count++){
    pixel_bits[count] = rand();
  }
  
  dsp.Redraw();
}

bool CrmlInit( const NPVariant* args, uint32_t arg_count, NPVariant* result) {
  Noise();
  return true;
}

bool ScriptingBridge::Paint( const NPVariant* args, uint32_t arg_count, NPVariant* result) {
  /*
  PiGenerator* pi_generator = static_cast<PiGenerator*>(Core::npp_->pdata);
  
  if (pi_generator) {
    pi_generator->Paint();
  }  
  return false;
  */
  Noise();
  return true;
} 
}  // namespace crml
