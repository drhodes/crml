// Copyright 2010 <Derek A. Rhodes>

#ifndef EVENT_H_
#define EVENT_H_

#include <nacl/nacl_npapi.h>
#include <nacl/npapi_extensions.h>
#include <nacl/npupp.h>

#include <queue>
#include <string>

#include "../core/error.h"
#include "../core/event_handler.h"

namespace crml {  
  ERR_(EVENT_INIT_FAILED);
  
  class Event: public Error {
   public:       
    explicit Event() : Error(OK) {
      ClassName("Event");
      Init();
    }    
    ~Event();

    static void PushEvent(void*);
    
    void Init();
    bool Empty();
    void Drain();
    NPPepperEvent PopEvent();
    bool GetEvent(NPPepperEvent* e);
    
   private:
    static std::queue<NPPepperEvent> queue_;
  };
}  // namespace scm
#endif  // EVENT_H_
