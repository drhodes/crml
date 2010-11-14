// Copyright 2010 <Derek A. Rhodes> All Rights Reseverd.

#ifndef EVENT_CC
#define EVENT_CC

#include <assert.h>
#include <sstream>
#include <string.h>
#include "./event.h"

namespace crml {
std::queue<NPPepperEvent> Event::queue_;

Event::~Event() {  
}

bool Event::Ok() {
  return Err() == EVENT_OK;
}

void Event::Init() {

}

bool Event::Empty() {
  return queue_.empty();
}

/*
     NPKeyEvent key;
     NPCharacterEvent character;
     NPMouseEvent mouse;
     NPMouseWheelEvent wheel;
     NPMinimizeEvent minimize;
     NPFocusEvent focus;
     NPDeviceEvent device;
*/

void appendMouseInfo(std::stringstream* out, NPPepperEvent* e) {
  // >out< | a pointer to stringstream, add some mouse info from --
  // >e    | a pointer to a pepper event
  
  *out << "Modifier: " << e->u.mouse.modifier << ", ";
  *out << "Button: " << e->u.mouse.button << ", ";
  *out << "<" << e->u.mouse.x << ", " << e->u.mouse.y << ">, ";
  *out << "ClickCount: " << e->u.mouse.clickCount;
}

NPPepperEvent Event::PopEvent() {  
  NPPepperEvent val = queue_.front();
  queue_.pop();
  return val;
}

bool Event::GetEvent(NPPepperEvent* e){
  if (!Empty()){
    *e = PopEvent();
    return true;
  }
  return false;
}



void Event::PushEvent(void* event) {
  NPPepperEvent* e = reinterpret_cast<NPPepperEvent*>(event);  
  assert(e != NULL);
 
  Event::queue_.push(*e);
  /*
  std::stringstream out;
  out << "handled Event: ";
  out << e->type << " ";

  switch (e->type) {
    case NPEventType_Undefined:
      out << "Undefined";
      break;
    case NPEventType_MouseDown:
      out << "MouseDown" << e << " | ";
      appendMouseInfo(&out, e);
      break;
    case NPEventType_MouseUp:
      out << "MouseUp";
      appendMouseInfo(&out, e);
      break;
    case NPEventType_MouseMove:
      out << "MouseMove";
      appendMouseInfo(&out, e);
      break;
    case NPEventType_MouseEnter:
      out << "MouseEnter";
      appendMouseInfo(&out, e);
      break;
    case NPEventType_MouseLeave:
      out << "MouseLeave";
      appendMouseInfo(&out, e);
      break;
    case NPEventType_MouseWheel:
      out << "MouseWheel";
      appendMouseInfo(&out, e);
      break;
    case NPEventType_RawKeyDown:
      out << "RawKeyDown";
      break;
    case NPEventType_KeyDown:
      out << "KeyDown";
      break;
    case NPEventType_KeyUp:
      out << "KeyUp";
      break;
    case NPEventType_Char:
      out << "Char";
      break;
    case NPEventType_Minimize:
      out << "Minimize";
      break;
    case NPEventType_Focus:
      out << "Focus";
      break;
    case NPEventType_Device:
      out << "Device";
      break;
  }
  */
}
}  // namespace scm

#endif
