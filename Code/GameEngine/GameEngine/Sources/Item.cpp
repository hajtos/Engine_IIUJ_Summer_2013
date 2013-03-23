#include <exception>
using namespace std;

#include "Item.h"

Item::~Item() {
	main_field = 0;
}

Item::Item(Level* L, double ms, Point pos, Point size, //movement speed, position, size
			int ca1, int ca2, int ca3, int gd, int fa, char* animT, //custom attributes, gravity degree, facing angle, animation table
			char* modelP, Point trans, bool anim, int lt, bool a, bool aa) { //model path, translation, animated?, active, always active
	movement_speed = ms;
	custom_attribute1 = ca1;
	custom_attribute2 = ca2;
	custom_attribute3 = ca3;
	gravity_degree = gd;
	facing_angle = fa;
	main_field = new Field(this, pos, size, 3, modelP, L, lt, trans, anim, a, aa);
	if (anim)
		animator = new Animator(L->animation_tables.find(animT)->second, main_field->graphic_model_animated);
	else animator = 0;
}


unsigned int Item::get_type() {
	return 3;
}

void Item::remove() {
	main_field->location->remove_item(main_field, this);
}