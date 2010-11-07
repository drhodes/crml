// Copyright 2010 <Derek A. Rhodes>

#ifndef DISPLAY_CC
#define DISPLAY_CC

#include "./display.h"
#include "../core/npn_bridge.cc"

namespace crml {

void FlushCallback(NPP instance, NPDeviceContext* context,
                   NPError err, void* user_data) {
}


Display::~Display(){}

/// Is the display OK?
bool Display::Ok(){
  return Err() == DISPLAY_OK;
}

uint32_t* Display::Pixels(){  
  uint32_t* pixel_bits = static_cast<uint32_t*>(Core::context2d_.region);
  if (pixel_bits == 0) {
    SetReportErr(DISPLAY_NULL_REGION);
    return 0;
  }
  Err(DISPLAY_OK);
  return pixel_bits;
}

int Display::Height(){
  if (Core::window_ == 0) {
    SetReportErr(DISPLAY_NULL_WINDOW);
    return -1;
  }
  Err(DISPLAY_OK);
  return Core::window_->height;
}

int Display::Width(){
  if (Core::window_ == 0) {
    SetReportErr(DISPLAY_NULL_WINDOW);
    return -1;
  }
  Err(DISPLAY_OK);
  return Core::window_->width;
}

void Display::Redraw(){
  NPDeviceFlushContextCallbackPtr callback =
      reinterpret_cast<NPDeviceFlushContextCallbackPtr>(&FlushCallback);

  Core::device2d_->flushContext(Core::npp_, &Core::context2d_, callback, NULL);
}


  

}       // namespace crml
#endif  // DISPLAY_CC










