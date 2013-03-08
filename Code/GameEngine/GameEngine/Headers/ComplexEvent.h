#include <exception>
#include <list>
using namespace std;

#ifndef __ComplexEvent_h__
#define __ComplexEvent_h__

#include "Event.h"
#include "Field.h"

class Event;
class Field;
class ComplexEvent;

class ComplexEvent : Event
{
	public:

		void invokeEvent(Field* source, Field* target);
	private:
		std::list<Event*> sub_events;

};

#endif
