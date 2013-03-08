#include <exception>
using namespace std;

#ifndef __NewFieldEvent_h__
#define __NewFieldEvent_h__

#include "Event.h"
#include "Point.h"
#include "Field.h"

class Event;
class Point;
class Field;
class NewFieldEvent;

class NewFieldEvent : Event
{
	public:

		void invokeEvent(Field* source, Field* target);
	private:
		Event* field_event;
		Point start;
		Point size;
		char owner;
		int time;
		char movement_type;
		Point movement_point;
		char position_relation;
		Point velocity;
		unsigned int field_target;

};

#endif
