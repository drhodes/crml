// Copyright 2010 <Derek A. Rhodes>

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "../core/core.h"
#include "../core/error.h"

namespace crml {
  ERR_(DISPLAY_OK);
  ERR_(DISPLAY_CREATE_CONTEXT_FAILED);
  ERR_(DISPLAY_ACQUIRE_DEVICE_FAILED);
  
  //------------------------------------------------------------------
  class Display : public Error {
   public:
    explicit Display() : Error(DISPLAY_OK) {
      ClassName("Display");
      CreateContext();
    }    
    
    ~Display();    

    
    /// Satisfies Event.
    virtual bool Ok();  // Is the object in a OK state?    
   private:
    void CreateContext();
    void DestroyContext();
    
    Core* core_;
  };

}       // namespace crml
#endif  // DISPLAY_HPP_
