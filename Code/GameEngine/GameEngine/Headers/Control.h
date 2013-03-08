#include <exception>
using namespace std;

#ifndef __Control_h__
#define __Control_h__

#include "Event.h"

class Event;
class Control;

class Control
{
	public:

		void check_signal();
	private:
		int signal;
		Event* event;

};

#endif
