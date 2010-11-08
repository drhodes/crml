// Copyright 2010 The Native Client Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file.

#include "./pi_generator.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <nacl/nacl_imc.h>
#include <nacl/nacl_npapi.h>
#include <nacl/npapi_extensions.h>
#include <nacl/npruntime.h>

//#include "./scripting_bridge.h"
#include <crml-core.h>

//extern NPDevice* NPN_AcquireDevice(NPP instance, NPDeviceID device);

using bridge::ScriptingBridge;

// This is called by the brower when the 2D context has been flushed to the
// browser window.
void FlushCallback(NPP instance, NPDeviceContext* context,
                   NPError err, void* user_data) {
}

namespace bridge {

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
    printf("Should be seeing painting here\n");
    DOUBLE_TO_NPVARIANT(pi_generator->pi(), *result);
    printf("Should be seeing painting here\n");    
    return pi_generator->Paint();
  }
  return false;
} 

//void PiGenerator::DerivedSetup(){
  //pthread_create(&thread_, NULL, pi, this);
  //window_ = window;
  //return Paint() ? NPERR_NO_ERROR : NPERR_GENERIC_ERROR;
//}

void PiGenerator::DestroyContext() {
  if (!IsContextValid())
    return;
  device2d_->destroyContext(npp_, &context2d_);
}

/// pi() estimates Pi using Monte Carlo method and it is executed by a separate
/// thread created in SetWindow(). pi() puts kMaxPointCount points inside the
/// square whose length of each side is 1.0, and calculates the ratio of the
/// number of points put inside the inscribed quadrant divided by the total
/// number of random points to get Pi/4.
void* PiGenerator::pi(void* param) {
  printf("void* PiGenerator::pi(void* param) {\n");
  
  const int kMaxPointCount = 1000000000;  // The total number of points to put.
  const uint32_t kOpaqueColorMask = 0xff000000;  // Opaque pixels.
  const uint32_t kRedMask = 0xff0000;
  const uint32_t kBlueMask = 0xff;
  const unsigned kRedShift = 16;
  const unsigned kBlueShift = 0;
  int count = 0;  // The number of points put inside the inscribed quadrant.
  unsigned int seed = 1;
  PiGenerator* pi_generator = static_cast<PiGenerator*>(param);
  uint32_t* pixel_bits = static_cast<uint32_t*>(pi_generator->pixels());
  srand(seed);
  for (int i = 1; i <= kMaxPointCount && !pi_generator->quit(); ++i) {
    double x = static_cast<double>(rand_r(&seed)) / RAND_MAX;
    double y = static_cast<double>(rand_r(&seed)) / RAND_MAX;
    double distance = sqrt(x * x + y * y);
    int px = x * pi_generator->width();
    int py = (1.0 - y) * pi_generator->height();
    uint32_t color = pixel_bits[pi_generator->width() * py + px];
    if (distance < 1.0) {
      // Set color to blue.
      ++count;
      pi_generator->pi_ = 4.0 * count / i;
      color += 4 << kBlueShift;
      color &= kBlueMask;
    } else {
      // Set color to red.
      color += 4 << kRedShift;
      color &= kRedMask;
    }
    pixel_bits[pi_generator->width() * py + px] = color | kOpaqueColorMask;
  }
  return 0;
}

}  // namespace bridge
