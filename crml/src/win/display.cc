// Copyright 2010 <Derek A. Rhodes>

#ifndef DISPLAY_CC
#define DISPLAY_CC

#include "./display.h"
#include "../core/npn_bridge.cc"

namespace crml {
//extern NPDevice* NPN_AcquireDevice(NPP instance, NPDeviceID device);

Display::~Display(){}

/// Is the display OK?
bool Display::Ok(){
  return Err() == DISPLAY_OK;
}


    /*
    void Display::DestroyContext() {
      if (!IsContextValid())
        return;
      device2d_->destroyContext(npp_, &context2d_);
    */


/*
NPError Display::SetWindow(NPWindow* window) {
  printf("++ NPError ScriptingBridge::SetWindow(NPWindow* window) {\n");
  if (!window)
    return NPERR_NO_ERROR;
  if (!IsContextValid())
    CreateContext();
  if (!IsContextValid())
    return NPERR_GENERIC_ERROR;
  // Clear the 2D drawing context.
  //pthread_create(&thread_, NULL, pi, this);
  window_ = window;
  // return Paint() ? NPERR_NO_ERROR : NPERR_GENERIC_ERROR;
  return NPERR_NO_ERROR;
}
*/

void Display::CreateContext() {
  /*
  ReportErr();
  Core::device2d_ = NPN_AcquireDevice(Core::npp_, NPPepper2DDevice);
  if (Core::device2d_ == 0) {
    SetReportErr(DISPLAY_ACQUIRE_DEVICE_FAILED);
    return;
  } else { ReportErr(); }
 
  memset(&Core::context2d_, 0, sizeof(Core::context2d_));

  NPDeviceContext2DConfig config;
  NPError init_err = Core::device2d_->initializeContext(Core::npp_, &config, &Core::context2d_);

  if (NPERR_NO_ERROR == init_err){
    SetReportErr(DISPLAY_CREATE_CONTEXT_FAILED);
    return;
  }
  */    
  Err(DISPLAY_OK);
}


}       // namespace crml
#endif  // DISPLAY_CC










