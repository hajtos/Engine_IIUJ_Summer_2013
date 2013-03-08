#include <exception>
#include <list>
using namespace std;

#ifndef __Control_Set_h__
#define __Control_Set_h__

#include "Control.h"

class Control;
class Control_Set;

class Control_Set
{
	public:

		void check_signals();
	private:
		std::list<Control> controls;

};

#endif
