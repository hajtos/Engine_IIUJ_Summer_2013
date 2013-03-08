#include <exception>
using namespace std;

#ifndef __ExternalEvent_h__
#define __ExternalEvent_h__

#include "Field.h"

class Field;
class ExternalEvent;

class ExternalEvent : Event
{
	public:

		void invokeEvent(Field* source, Field* target);
};

#endif
