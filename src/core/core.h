// Copyright 2010 <Derek A. Rhodes>

#ifndef CORE_H_
#define CORE_H_

#include "error.h"
//#include <nacl/npapi_extensions.h>
//#include <nacl/nacl_npapi.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "./plugin_object.h"

namespace crml { 
  /// error codestrings.
  ERR_(CORE_NULL);
  ERR_(CORE_OK);

  /// \brief The Core object which wires all subsystems
  /// and maintains an open channel with javascript.
  //------------------------------------------------------------------
  class Core : public Error, PluginObject { 
   public:
    static Core* self_;
    
    explicit Core(NPP_t* npp) : Error(CORE_OK), PluginObject(npp) {
      ClassName("Core");
      self_ = 0;
    }    

    
    ~Core();
    void CoreInit();    
    void CreateContext();
    void Redraw();
    
    /// \return a context2D, be careful.
    NPDeviceContext2D GetContext2D();

    virtual bool Ok();  // Is the object in a OK state?
   private:    
  };  
}       // namespace crml
#endif  // CORE_H_



















