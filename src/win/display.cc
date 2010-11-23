// Copyright 2010 <Derek A. Rhodes>

#ifndef DISPLAY_CC
#define DISPLAY_CC

#include "./display.h"

namespace crml {
void FlushCallback(NPP instance, NPDeviceContext* context,
                   NPError err, void* user_data) {
}

inline uint32_t MakeRGBA(uint32_t r, uint32_t g, uint32_t b, uint32_t a) {
  return  (a << 24) | (r << 16) | (g << 8) | b ;
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

/*
void Display::FontDraw(FT_Bitmap* bm, int left, int top){  
  int row = top * Width() + left;
    
  for(int i=0; i<bm->rows; i++){
    for(int j=0; j<bm->width; j++){  
      pixels_[row + j] = MakeRGBA(0,0,0,bm->buffer[i*bm->pitch+j]);
    }
    row = (top+i-1) * Width() + left;
  }  
}
*/

void Display::Draw(Drawer& dwr){

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

  pixels_ = static_cast<uint32_t*>(context_.region);  
}


void Display::Wipe(){
  //memset( pixel_[], 0, Width()*Height() );
  int size= Height() * Width();

  for (int i = 0; i < size; i++) {
    pixels_[i] = 0;
  }
}

void Display::Wipe(uint32_t color){
  int size= Height() * Width();
  for (int i = 0; i < size; i++) {
    pixels_[i] = color;
  }
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
