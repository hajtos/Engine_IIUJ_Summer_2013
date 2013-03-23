#include <exception>
using namespace std;

#include "Border.h"

Border::~Border() {
	main_field = 0;
}

Border::Border(Level* L, double ms, bool abs, int b, Point pos, Point size, //level, movement speed, absolute, position, size
			int ca1, int ca2, int ca3, int gd, int fa, int mt, char* animT, //custom attributes, gravity degree, facing angle, model type, animation table
			char* modelP, Point trans, bool anim, int lt, bool a, bool aa) {//model path, translation, animated?, lifetime, active, always active
	movement_speed = ms;
	absolute = abs;
	bouncing = b;

	custom_attribute1 = ca1;
	custom_attribute2 = ca2;
	custom_attribute3 = ca3;
	gravity_degree = gd;
	facing_angle = fa;
	main_field = new Field(this, pos, size, mt, modelP, L, lt, trans, anim, a, aa);
	if (anim)
		animator = new Animator(L->animation_tables.find(animT)->second, main_field->graphic_model_animated);
	else animator = 0;
}

unsigned int Border::get_type() {
	return 4;
}

void Border::remove() {
	main_field->location->remove_border(main_field, this);
}