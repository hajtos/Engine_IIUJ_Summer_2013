#ifndef __Rectangle_h__
#define __Rectangle_h__

#include "Shape.h"
#include "Point.h"

class Rectangle : public Shape {
	Point size;
public:
	Rectangle(Point a):size(a){}
	Point edge();
	bool collidesWith(Shape* s,Point p);
};


#endif