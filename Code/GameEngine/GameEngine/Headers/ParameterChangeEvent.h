#include <exception>
using namespace std;

#ifndef __ParameterChangeEvent_h__
#define __ParameterChangeEvent_h__

#include "Field.h"

class Field;
class ParameterChangeEvent;

class ParameterChangeEvent : Event
{
	public:

		void invokeEvent(Field* source, Field* target);
	private:
		char parameter_identifier;
		bool relative;
		int value_change;

};

#endif
