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
/*
PiGenerator::PiGenerator(NPP npp)    
    : ScriptingBridge(npp),     
      quit_(false),
      pi_(0.0) {
}

PiGenerator::~PiGenerator() {
  quit_ = true;
  if (thread_) {
    pthread_join(thread_, NULL);
  }
  if (scriptable_object_) {
    NPN_ReleaseObject(scriptable_object_);
  }
  DestroyContext();
}
*/

bool PiGenerator::Paint() { 
  if (IsContextValid()) {    
    uint32_t* pixel_bits = static_cast<uint32_t*>(pixels());

    printf("  if (IsContextValid()) {\n");
    int count = 0;
    int max = width() * height() -1 ;
    while (1){
      pixel_bits[count] = rand();
      if (count > max)
        break;
      count += 1;
    }

    NPDeviceFlushContextCallbackPtr callback =
        reinterpret_cast<NPDeviceFlushContextCallbackPtr>(&FlushCallback);
    device2d_->flushContext(npp_, &context2d_, callback, NULL);
    printf("device2d_->flushContext(npp_, &context2d_, callback, NULL);\n");
    
    return true;
  }
  return false;
}

bool ScriptingBridge::Paint( const NPVariant* args,
                             uint32_t arg_count,
                             NPVariant* result) {  
  printf("bool ScriptingBridge::Paint( const NPVariant* args,\n");
  PiGenerator* pi_generator = static_cast<PiGenerator*>(npp_->pdata);
  if (pi_generator) {
    pi_generator->Paint();
  }  
  return false;
} 
/*
void PiGenerator::DestroyContext() {
  if (!IsContextValid())
    return;
  device2d_->destroyContext(npp_, &context2d_);
}
*/
}  // namespace crml
