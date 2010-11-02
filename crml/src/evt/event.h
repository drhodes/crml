// Copyright 2010 <Derek A. Rhodes>

#ifndef EVENT_H_
#define EVENT_H_

#include <nacl/nacl_npapi.h>
#include <nacl/npapi_extensions.h>
#include <nacl/npupp.h>

#include <queue>
#include <string>

#include "./error.h"
#include "./event_handler.h"
#include "./error_macro.cc"

namespace scm {  
  ERR_(EVENT_INIT_FAILED);
  ERR_(EVENT_OK);

  class Event : public Error {
   public:
    explicit Event() : Error(EVENT_OK) {
      ClassName("Event");
      queue_ = new std::queue<NPPepperEvent*>;
    }    
    ~Event();
        
    void Init();
    void PushEvent(NPPepperEvent* evt);
    bool Empty();
    void Drain();
    NPPepperEvent* PopEvent();

    virtual bool Ok();  // Is the object in a OK state?
   private:
    std::queue<NPPepperEvent*>* queue_;
  };


}  // namespace scm
#endif  // EVENT_H_
