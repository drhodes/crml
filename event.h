// Copyright 2010 <Derek A. Rhodes>

#ifndef EVENT_H_
#define EVENT_H_

#include <nacl/nacl_npapi.h>
#include <nacl/npapi_extensions.h>
#include <nacl/npupp.h>

#include <queue>
#include <string>

//#include "./event_handler.h"
#include "./error_macro.cc"

namespace scm {  
  ERR_(EVENT_INIT_FAILED);
  ERR_(EVENT_OK);

  class Event {
   public:
    Event();
    ~Event();

    void Err(ErrString es);
    ErrString Err();        
        
    void Init();
    void PushEvent(NPPepperEvent* evt);
    bool Empty();
    void Drain();
    NPPepperEvent* PopEvent();
    
   private:
    std::string err_;
    std::queue<NPPepperEvent*>* queue_;
  };


}  // namespace scm
#endif  // EVENT_H_
