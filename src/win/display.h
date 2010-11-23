// Copyright 2010 <Derek A. Rhodes>

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "../core/core.h"
#include "../gfx/drawer.h"

namespace crml {
  ERR_(DISPLAY_OK);
  ERR_(DISPLAY_CREATE_CONTEXT_FAILED);
  ERR_(DISPLAY_ACQUIRE_DEVICE_FAILED);
  ERR_(DISPLAY_NULL_REGION);
  ERR_(DISPLAY_NULL_WINDOW);
  ERR_(DISPLAY_CANT_GET_HEIGHT);
  ERR_(DISPLAY_CANT_GET_WIDTH);
  
  //------------------------------------------------------------------
  class Display : public Error {
   public:
    explicit Display() : Error(DISPLAY_OK) {
      ClassName("Display");
    }    
    
    ~Display();
    
    // \return A pointer, Core::context2d_.region
    uint32_t* Pixels();
    int Height();
    int Width();

    
    void Redraw();
    void Init();
    void Wipe();
    void Wipe(uint32_t color);

    //void FontDraw(FT_Bitmap*, int, int);
    void Draw(Drawer&);

    
    /// Satisfies Event.
    virtual bool Ok();  // Is the object in a OK state?    
   private:
    NPDeviceContext2D context_;
    NPDevice* device2d_;
    uint32_t* pixels_;

    
    void CreateContext();
    void DestroyContext();
    
  };
}       // namespace crml
#endif  // DISPLAY_HPP_
