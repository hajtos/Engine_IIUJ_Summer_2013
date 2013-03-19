#include <exception>
using namespace std;

#include "Item.h"

Item::~Item() {
	main_field = 0;
}

Item::Item(std::string init, Level* L, Point position, Point size) {
	movement_speed = 0;
	custom_attribute1 = 0;
	custom_attribute2 = 0;
	custom_attribute3 = 0;
	gravity_degree = 0;
	facing_angle = 90;
	main_field = new Field(this, position, size, 3, "", L);
}


unsigned int Item::get_type() {
	return 3;
}

void Item::remove() {
	main_field->location->remove_item(main_field, this);
}