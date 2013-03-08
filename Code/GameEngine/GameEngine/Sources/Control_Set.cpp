#include <exception>
#include <list>
using namespace std;

#include "Control_Set.h"
#include "Control.h"

void Control_Set::check_signals() {
	for (std::list<Control>::iterator ii = controls.begin();ii!=controls.end();++ii)
        ii->check_signal();
}

