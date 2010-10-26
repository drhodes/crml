#ifndef EVENT_H
#define EVENT_H

#include <queue>

#include <nacl/nacl_npapi.h>
#include <nacl/npapi_extensions.h>
#include <nacl/npupp.h>

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
		void PushEvent(NPPepperEvent*);		
		bool Empty();
		void Drain();
		NPPepperEvent* PopEvent();

	private:
		std::queue<NPPepperEvent*>* queue_;
	};
} // namespace scm



#endif
