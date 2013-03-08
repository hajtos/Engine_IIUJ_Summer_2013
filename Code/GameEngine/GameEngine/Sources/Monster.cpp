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

Monster::Monster(std::string init, Level* L, Point position) {
	movement_speed = 10;
	hp = 100;
	std::list<Behaviour> temp_B;
	aI = temp_B;
	name = "Monster"; //where will this be derived from?
	monster_type = init; //where will this be derived from?
	
	custom_attribute1 = 0;
	custom_attribute2 = 0;
	custom_attribute3 = 0;
	gravity_degree = 100;
	facing_angle = 90;
	main_field = new Field(this, position, 2, "", L);
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