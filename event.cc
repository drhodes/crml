#ifndef EVENT_CC
#define EVENT_CC

#include "log_macro.cc"
#include <assert.h>
#include <sstream>

#include "event.h"

namespace scm {
	Event::Event(){
		queue_ = new std::queue<NPPepperEvent*>;
	}

	Event::~Event(){
		delete queue_;
	}
	
   	void Event::Init() {
		Log(":) Init Event");
	}
	
	bool Event::Empty() {
		return queue_->empty();
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
		/* > out  | a pointer to stringstream, add some mouse info from --
		   > e    | a pointer to a pepper event
		   < void |  
		*/
		*out << "Modifier: " << e->u.mouse.modifier << ", ";
		*out << "Button: " << e->u.mouse.button << ", ";
		*out << "<" << e->u.mouse.x << ", " << e->u.mouse.y << ">, ";
		*out << "ClickCount: " << e->u.mouse.clickCount;
	}

	NPPepperEvent* Event::PopEvent() {		
		if (queue_->empty()){
			return 0;
		}
		NPPepperEvent* val = queue_->front();
		queue_->pop();
		return val;			
	}

	void Event::Drain() {		
		Log("Draining");
		while (!Empty())
			PopEvent();
	}

	void Event::PushEvent(NPPepperEvent* e){		
		/* > e    | a pointer to a pepper event is pushed onto queue_
		   < void |
		*/
		assert( e != NULL );
		assert( queue_ != NULL );

		std::stringstream out;
		out << "handled Event: ";
		out << e->type << " ";

		queue_->push(e);
		
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
		Log(out.str());
	}
} //namespace scm

#endif
