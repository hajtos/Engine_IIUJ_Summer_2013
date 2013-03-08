
#include "Point.h"

Point::Point() {
	position_x = 0;
	position_y = 0;
	layer = 0;
}

Point::Point(float x, float y, float l) {
	position_x = x;
	position_y = y;
	layer = l;
}