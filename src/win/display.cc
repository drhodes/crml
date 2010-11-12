// Copyright 2010 <Derek A. Rhodes>

#ifndef DISPLAY_CC
#define DISPLAY_CC

#include "./display.h"

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
    NPDeviceContext2DConfig config;
    NPDeviceContext2D context;

    NPDevice* device2d = Core::self_->Device2d();    
    if (Core::self_->Ok()){    
      NPError err = device2d->initializeContext(Core::self_->Npp(), &config, &context);
      if (err != NPERR_NO_ERROR) {
        printf("Failed to initialize 2D context\n");
        exit(1);
      }
    }
    
    uint32_t* pixel_bits = static_cast<uint32_t*>(context.region);
    if (pixel_bits == 0) {
      SetReportErr(DISPLAY_NULL_REGION);
      return 0;
    }
    
    return pixel_bits;
}

int Display::Height(){
  if (!Core::self_->Ok()) {     
    Core::self_->ReportErr();
    SetReportErr(DISPLAY_CANT_GET_HEIGHT);
    return -1;        
  }
  return Core::self_->Height();
}

int Display::Width(){
  if (!Core::self_->Ok()) {     
    Core::self_->ReportErr();
    SetReportErr(DISPLAY_CANT_GET_WIDTH);
    return -1;        
  }
  return Core::self_->Width();
}

void Display::Init(){  
  NPDeviceContext2DConfig config;
  NPDevice* device2d = Core::self_->Device2d();
  
  if (Core::self_->Ok()){    
    NPError err = device2d->initializeContext(Core::self_->Npp(), &config, &context_);
    if (err != NPERR_NO_ERROR) {
      printf("Failed to initialize 2D context\n");
    }
  }
  device2d_ = device2d;
}


void Display::Redraw(){
  /*
  NPDeviceContext2DConfig config;
  NPDeviceContext2D context;
  
  NPDevice* device2d = Core::self_->Device2d();    
  if (Core::self_->Ok()){    
    NPError err = device2d->initializeContext(Core::self_->Npp(), &config, &context);
    if (err != NPERR_NO_ERROR) {
      printf("Failed to initialize 2D context\n");
      //exit(1);
    }
  }
  */
  NPDeviceFlushContextCallbackPtr callback =
      reinterpret_cast<NPDeviceFlushContextCallbackPtr>(&FlushCallback);
  device2d_->flushContext( Core::self_->Npp(), &context_, callback, NULL);
}

}       // namespace crml
#endif  // DISPLAY_CC










