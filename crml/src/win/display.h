// Copyright 2010 <Derek A. Rhodes>

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "../core/core.h"
#include "../core/error.h"

namespace crml {
  ERR_(DISPLAY_OK);
  ERR_(DISPLAY_CREATE_CONTEXT_FAILED);
  ERR_(DISPLAY_ACQUIRE_DEVICE_FAILED);
  ERR_(DISPLAY_NULL_REGION);
  ERR_(DISPLAY_NULL_WINDOW);
  
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
    
    
    /// Satisfies Event.
    virtual bool Ok();  // Is the object in a OK state?    
   private:
    void CreateContext();
    void DestroyContext();
    
  };
}       // namespace crml
#endif  // DISPLAY_HPP_
