#include <exception>
#include <string>
#include <list>
using namespace std;

#include "Monster.h"
#include "Behaviour.h"

Monster::~Monster() {
	aI.clear();
	main_field = 0;
}

Monster::Monster(Level* L, int ms, int mhp, std::string nm, std::string mt, //movement speed, hit points, name, monster type
			Point pos, Point size, int ca1, int ca2, int ca3, int gd, int fa, //position, size, custom attributes, gravity degree, facing angle
			char* animT, char* modelP, Point trans, bool anim, //animation table, model path, translation, animated?
			int lt, bool a, bool aa) { //life time, active, always active
	movement_speed = ms;
	hp = mhp;
	std::list<Behaviour> temp_B;
	aI = temp_B;
	name = nm; //where will this be derived from?
	monster_type = mt; //where will this be derived from?
	
	custom_attribute1 = ca1;
	custom_attribute2 = ca2;
	custom_attribute3 = ca3;
	gravity_degree = gd;
	facing_angle = fa;
	main_field = new Field(this, pos, size, 2, modelP, L, lt, trans, anim, a, aa);
	if (anim)
		animator = new Animator(L->animation_tables.find(animT)->second, main_field->graphic_model_animated);
	else animator = 0;
}

unsigned int Monster::get_type() {
	return 2;
}

void Monster::act() {
	for (std::list<Behaviour>::iterator ii=aI.begin();ii!=aI.end();++ii)
		if (ii->check_conditions()) {
			ii->Event->invokeEvent(this->main_field, NULL);
			break;
		}
}

void Monster::remove() {
	main_field->location->remove_monster(main_field, this);
}