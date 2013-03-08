#include <exception>
using namespace std;

#ifndef __MoveEvent_h__
#define __MoveEvent_h__

#include "Point.h"
#include "Field.h"

class Point;
class Field;
class MoveEvent;

class MoveEvent : Event
{
	public:

		void invokeEvent(Field* source, Field* target);
	private:
		char mover;
		char movement_type;
		Point velocity;
		int time;

};

#endif
