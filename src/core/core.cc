// Copyright 2010 <Derek A. Rhodes>
#ifndef CORE_CC
#define CORE_CC

#include "core.h"

namespace crml {

// NPDeviceContext2D Core::context2d_;
// NPDevice* Core::device2d_ = 0;  // The PINPAPI 2D device.
// Core::npp_ = 0;

Core* Core::self_ = new Core;  // The PINPAPI 2D device.

void Core::__MainLoop__(){
  //SetReportErr(CORE_MAINLOOP_STARTED);
  self_->MainLoop();
  //SetReportErr(CORE_MAINLOOP_STOPPED);
}

// Pluggin Getters.
NPObject Core::Header() {
  return plugin_->header_;
}

NPP Core::Npp() { return plugin_->npp(); }
int Core::Dimensions() { return plugin_->dimensions_; }

NPDevice* Core::Device2d(){
  if (plugin_->device2d_ == 0){
    SetReportErr(CORE_NULL_DEVICE_2D);
    return 0;
  }
  return plugin_->device2d_;  
}

NPDevice* Core::Device3d(){
  if (plugin_->device3d_ == 0){
    SetReportErr(CORE_NULL_DEVICE_3D);
    return 0;
  }
  return plugin_->device2d_;  
}

PGLContext Core::PglContext(){ return plugin_->pgl_context_; }
NPDevice* Core::DeviceAudio(){ 
  if (plugin_->deviceaudio_ == 0){
    SetReportErr(CORE_NULL_DEVICE_AUDIO);
    return 0;
  }
  return plugin_->deviceaudio_;    
}

NPDeviceContext3D Core::Context3d() { return plugin_->context3d_; }
NPDeviceContextAudio Core::ContextAudio() { return plugin_->context_audio_; }
unsigned int Core::Device2dChecksum() { return plugin_->device2d_checksum_; }
unsigned int Core::Plugin2dChecksum() { return plugin_->plugin2d_checksum_; }
int Core::Width() { return plugin_->width_; }
int Core::Height() { return plugin_->height_; }

void Core::SetPlugin(PluginObject* plugin){
  if (plugin) {    
    plugin_ = plugin;
    Err(CORE_OK);
  } else {
    plugin_ = 0;
    SetReportErr(CORE_NULL_PLUGIN);
  }  
}

Core::~Core(){}


bool Core::Ok() {
  return Err() == CORE_OK;
}



}       // namespace crml
#endif  // CORE_CC



















