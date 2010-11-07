// Copyright 2010 <Derek A. Rhodes>
#ifndef CORE_CC
#define CORE_CC

#include "core.h"



namespace crml {

NPDeviceContext2D Core::context2d_;
NPDevice* Core::device2d_ = 0;  // The PINPAPI 2D device.
NPP Core::npp_ = 0;
NPWindow* Core::window_ = 0;

Core::~Core(){}



/// Initialize an event system
//NPDeviceContext2D Core::GetContext2D(){
//  return 0;
//}

bool Core::Ok() {
  return Err() == CORE_OK;
}



}       // namespace crml
#endif  // CORE_CC



















