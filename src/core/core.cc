// Copyright 2010 <Derek A. Rhodes>
#ifndef CORE_CC
#define CORE_CC

#include "core.h"

namespace crml {


// NPDeviceContext2D Core::context2d_;
// NPDevice* Core::device2d_ = 0;  // The PINPAPI 2D device.
// Core::npp_ = 0;

Core* Core::self_ = 0;  // The PINPAPI 2D device.

/*
void FlushCallback(NPP instance, NPDeviceContext* context,
                   NPError err, void* user_data) {
}
*/

Core::~Core(){}


/*
void Core::Redraw(){
  NPDeviceFlushContextCallbackPtr callback =
      reinterpret_cast<NPDeviceFlushContextCallbackPtr>(&FlushCallback);

  Core::device2d_->flushContext(Core::npp_, &Core::context2d_, callback, NULL);
}
*/


/// Initialize an event system
//NPDeviceContext2D Core::GetContext2D(){
//  return 0;
//}

bool Core::Ok() {
  return Err() == CORE_OK;
}



}       // namespace crml
#endif  // CORE_CC



















