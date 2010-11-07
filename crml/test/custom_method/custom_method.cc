// Copyright 2010 <Derek A. Rhodes> All Rights Reseverd.

#include <stdlib.h>
#include <crml-core.h>
#include <crml-win.h>

#include "./custom_method.h"

using crml::ScriptingBridge;

/// This is called by the brower when the 2D context has been flushed to the
/// browser window.
void FlushCallback(NPP instance, NPDeviceContext* context,
                   NPError err, void* user_data) {
}

namespace crml {
bool PiGenerator::Paint() {
  //if (IsContextValid()) {    
  //uint32_t* pixel_bits = static_cast<uint32_t*>(pixels());
  uint32_t* pixel_bits = static_cast<uint32_t*>(Core::context2d_.region);
  printf("  if (IsContextValid()) {\n");

  if (pixel_bits == NULL)
    printf("PIXEL_BITS is null \n");
  printf("PIXEL_BITS is not null \n");
  
  int count = 0;
  
  int max = Core::window_->width * Core::window_->height -1 ;
  printf("%d\n", max);
  printf("PIXEL_BITS is not null2 \n");
  
  while (1){
    pixel_bits[count] = rand();
    if (count > max)
      break;
    count += 1;
  }



  NPDeviceFlushContextCallbackPtr callback =
      reinterpret_cast<NPDeviceFlushContextCallbackPtr>(&FlushCallback);

  Core::device2d_->flushContext(Core::npp_, &Core::context2d_, callback, NULL);

  //printf("device2d_->flushContext(npp_, &context2d_, callback, NULL);\n");
  return true;
}


bool ScriptingBridge::Paint( const NPVariant* args, uint32_t arg_count, NPVariant* result) {  
  printf("bool ScriptingBridge::Paint( const NPVariant* args,\n");
  PiGenerator* pi_generator = static_cast<PiGenerator*>(Core::npp_->pdata);
  printf("bool ScriptingBridge::Paint( const NPVariant* args,\n");
  
  if (pi_generator) {
    pi_generator->Paint();
  }  
  return false;
} 
}  // namespace crml
