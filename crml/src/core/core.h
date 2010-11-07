// Copyright 2010 <Derek A. Rhodes>

#ifndef CORE_H_
#define CORE_H_

#include "error.h"
#include <nacl/npapi_extensions.h>
#include <nacl/nacl_npapi.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

namespace crml { 
  /// error codestrings.
  ERR_(CORE_NULL);
  ERR_(CORE_OK);

  /// \brief The Core object which wires all subsystems
  /// and maintains an open channel with javascript.
  //------------------------------------------------------------------
  class Core : public Error { 
   public:
    static NPDeviceContext2D context2d_;
    static NPDevice* device2d_;  // The PINPAPI 2D device.
    static NPP npp_;
    static NPWindow* window_;    
    
    explicit Core() : Error(CORE_OK) {
      ClassName("Core");      
    }    

    ~Core();
    
    void CreateContext();
    
    /// \return a context2D, be careful.
    NPDeviceContext2D GetContext2D();

    virtual bool Ok();  // Is the object in a OK state?
   private:    
  };


  
}       // namespace crml
#endif  // CORE_H_



















