#ifndef __Shape_h__
#define __Shape_h__

#include "Point.h"

class Shape {

public:
	virtual Point edge() {return Point(0,0,0);}
	virtual bool collidesWith(Shape* s,Point p){return false;}
};


#endif