#include <exception>
using namespace std;

#include "Border.h"

Border::~Border() {
	main_field = 0;
}

Border::Border(Point position, Point size, Level* L) {
	movement_speed = 0;
	absolute = true;
	bouncing = 0;

	custom_attribute1 = 0;
	custom_attribute2 = 0;
	custom_attribute3 = 0;
	gravity_degree = 100;
	facing_angle = 90;
	main_field = new Field(this, position, 4, "", L);
	//main_field->rescale(size);
}

unsigned int Border::get_type() {
	return 4;
}

void Border::remove() {
	main_field->location->remove_border(main_field, this);
}