// Copyright 2010 <Derek A. Rhodes>

#ifndef EVENT_H_
#define EVENT_H_

#include <nacl/nacl_npapi.h>
#include <nacl/npapi_extensions.h>
#include <nacl/npupp.h>

#include <queue>

namespace scm {
  enum EventErr {
    EventInitFail,
    EventInitOK,
  };

  class Event {
 public:
    Event();
    ~Event();
    void Init();
    void PushEvent(NPPepperEvent* evt);
    bool Empty();
    void Drain();
    NPPepperEvent* PopEvent();

 private:
    std::queue<NPPepperEvent*>* queue_;
  };


}  // namespace scm
#endif  // EVENT_H_
