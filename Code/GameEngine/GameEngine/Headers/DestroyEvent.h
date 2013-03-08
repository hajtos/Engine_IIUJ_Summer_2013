#include <exception>
using namespace std;

#ifndef __DestroyEvent_h__
#define __DestroyEvent_h__

#include "Field.h"

class Field;
class DestroyEvent;

class DestroyEvent : Event
{
	public:

		void invokeEvent(Field* source, Field* target);
	private:
		char destroyee;

};

#endif
