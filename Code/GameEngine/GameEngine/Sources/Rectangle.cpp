#include "Rectangle.h"

Point Rectangle::edge() {
	return size;
}

bool Rectangle::collidesWith(Shape* r,Point p) {
	if(Rectangle* rr = dynamic_cast<Rectangle*>(r)) {
		float x1 = -(rr->size.position_x+p.position_x);
		float x2 = this->size.position_x-p.position_x;
		float y1 = -(rr->size.position_y+p.position_y);
		float y2 = this->size.position_y-p.position_y;
		return (x1*x2<0 && y1*y2<0);
	}
}