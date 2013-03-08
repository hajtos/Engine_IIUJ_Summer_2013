#include "Level.h"
#include <exception>
#include <string>
#include <list>
#include <map>

using namespace std;

Level::Level(IrrlichtDevice* Device) {
	//Creates a simple, testing Level, more specified constructors to be implemented.
	device = Device;

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();

	size = Point(1200, 900, 2); //of the whole level? From which point?
	respawn = Point();
	player = new Player(this);
	custom_attribute1 = 0;
	custom_attribute2 = 0;
	custom_attribute3 = 0;
	std::map< std::string, Event* > Temp_ed;
	event_dictionary = Temp_ed;
	gravity = 10; //double, 9.81?
	lc_interval = 0;
	delta_time = 0;
	
	std::list<Field*> Temp_f;
	fields = Temp_f;
	fields.insert(fields.end(), player->main_field);
	std::list<Item*> Temp_i;
	items = Temp_i;
	active_range = Point(1200, 900, 2);
	time_left = -1; //forever?
	std::list<Monster*> Temp_m;
	monsters = Temp_m;
	std::list<Border*> Temp_b;
	boundaries = Temp_b;
	
	add_monster("temp1", Point(-10.0, 0.0, 0.0));
	add_monster("temp2", Point(10.0, 0.0, 0.0));
	add_monster("temp3", Point(20.0, 0.0, 0.0));
	add_item("item", Point(15.0, 20.0, 0.0));
	for (int i = 0; i < 10; i++)
		add_border(Point(-20 + 10*i, -5, 0), Point(1.0, 1.0, 1.0));
	for (int i = 1; i < 5; i++)
		add_border(Point(30, -5, i), Point(1.0, 1.0, 1.0));
	for (int i = 1; i < 5; i++)
		add_border(Point(30 + 10*i, -5, 4), Point(1.0, 1.0, 1.0));
}
/*
Level::Level(std::string path) {
	//Loads a level from a file. To be implemented
	throw "Not yet implemented";
}
*/
void Level::add_event(std::string init) {
	throw "Not yet implemented";
}

void Level::add_border(Point start, Point size) {
	Border* b = new Border(start, size, this);
	fields.insert(fields.end(), b->main_field);
	boundaries.insert(boundaries.end(), b);
}

void Level::add_monster(std::string init, Point position) {
	Monster* m = new Monster(init, this, position);
	fields.insert(fields.end(), m->main_field);
	monsters.insert(monsters.end(), m);
}

void Level::add_item(std::string init, Point position) {
	Item* i = new Item(init, this, position);
	fields.insert(fields.end(), i->main_field);
	items.insert(items.end(), i);
}

void Level::advance_frame(ICameraSceneNode *cam) {
	//Updating positions/scales/rotations:
	for (std::list<Field*>::iterator i = fields.begin(); i != fields.end(); i++)
		(*i)->update();
	//clearing garbage
	for (std::list<Field*>::iterator i = garbage.begin(); i != garbage.end(); i++)
		if ((*i)->owner != 0)
			(*i)->owner->remove();
		else {
			fields.remove(*i);
			delete(*i);
		}
	garbage.clear();
	
	//centralizing camera on player (if exists)
	if (player != 0 && cam != 0) {
		//position
		cam->setPosition(core::vector3df(player->main_field->position.position_x,
			player->main_field->position.position_y+15,(player->main_field->position.layer-1)*10-40));
		//target
		cam->setTarget(core::vector3df(player->main_field->position.position_x,
			player->main_field->position.position_y,(player->main_field->position.layer-1)*10));
	}

	//handling player velocity changes and animation
	player->animator->check();
	if (player->main_field->velocity.position_x == 0)
	{
		if (player->animator->getAnimation() != 0)
			player->animator->setAnimation(0);
	}
	else
	{
		if (player->animator->getAnimation() != 1)
			player->animator->setAnimation(1);
	}
	player->main_field->set_velocity(0, 0); //player->main_field->get_vy()

	//decrementing layer change delay
	if (lc_interval > 0)
		lc_interval--;
}

bool Level::collision_detect(Field* source) {
	std::list<Field*>::iterator target = fields.begin();
	/*std::list<Field*>::iterator me = target;
	while (*me!=source)
		++me;
	target = me;
	++target;*/
	bool p = false;
	while (target!=fields.end() && (*target)->position.position_x <= source->position.position_x+source->size.position_x) {
		if ((*target)->position.position_y >= source->position.position_y && (*target)->position.position_x + (*target)->size.position_x >= source->position.position_x
				&& (*target)->position.position_y <= source->position.position_y+source->size.position_y && *target!=source && 
				(*target)->position.layer+(*target)->size.layer>=source->position.layer && (*target)->position.layer<=source->position.layer) {
			if (source->owner!=NULL && ((source->owner)->get_type())&((*target)->type)) {
						if((*target)->collision_effect!=NULL)
							(*target)->collision_effect->invokeEvent(*target,source);
			}
			if ((*target)->owner!=NULL && (((*target)->owner)->get_type())&(source->type)) {
						if (source->collision_effect!=NULL)
							source->collision_effect->invokeEvent(source,*target);
			}
			p = true;
		}
		++target;
	}
	return p;
}

void Level::move_field(Field* field) {
	Point t = field->position;
	switch (field->movement_type) {
	case -1: {
		break;
			 }
	case 'u':{
		t= t+field->velocity*field->owner->movement_speed*delta_time;	
		break;
			}
	}
	field->position = t;
	--field->time_left;
}

void Level::demove_field(Field* field) {
	Point t = field->position;
	switch (field->movement_type) {
	case -1: {
		break;
			 }
	case 'u':{
		t= t-field->velocity*field->owner->movement_speed*delta_time;	
		break;
			}
	}
	field->position = t;
	field->time_left = 0;
}

void Level::remove_player(Field* field) {
	if (field == 0)
		return;
	//Removing entity:
	if (player != 0) {
		delete(player);
		player = 0;
	}
	//Removing field:
	fields.remove(field);
	delete(field);
}

void Level::remove_border(Field* field, Border* entity) {
	if (field == 0)
		return;
	//Removing entity:
	if (player != 0) {
		boundaries.remove(entity);
		delete(entity);
	}
	//Removing field:
	fields.remove(field);
	delete(field);
}

void Level::remove_monster(Field* field, Monster* entity) {
	if (field == 0)
		return;
	//Removing entity:
	if (player != 0) {
		monsters.remove(entity);
		delete(entity);
	}
	//Removing field:
	fields.remove(field);
	delete(field);
}

void Level::remove_item(Field* field, Item* entity) {
	if (field == 0)
		return;
	//Removing entity:
	if (player != 0) {
		items.remove(entity);
		delete(entity);
	}
	//Removing field:
	fields.remove(field);
	delete(field);
}

void Level::trash(Field* field) {
	//field->destroy_event.invoke() ??
	garbage.insert(garbage.end(), field);
}

void Level::process_key(irr::EKEY_CODE keycode) {
	if (player == 0)
		return;
	if (keycode == irr::KEY_KEY_W)
		player->main_field->set_velocity(player->main_field->get_vx(), player->movement_speed/2);
	if (keycode == irr::KEY_KEY_S)
		player->main_field->set_velocity(player->main_field->get_vx(), -player->movement_speed/2);
	if (keycode == irr::KEY_KEY_D)
	{
		player->facing_angle = 90;
		player->main_field->set_velocity(player->movement_speed, player->main_field->get_vy());
	}
	if (keycode == irr::KEY_KEY_A)
	{
		player->facing_angle = 270;
		player->main_field->set_velocity(-player->movement_speed, player->main_field->get_vy());
	}
	if (keycode == irr::KEY_KEY_Q)
	{
		if (lc_interval != 0)
			return;
		lc_interval = 30;
		player->main_field->position.layer += 1;
	}
	if (keycode == irr::KEY_KEY_Z)
	{
		if (lc_interval != 0)
			return;
		lc_interval = 30;
		player->main_field->position.layer -= 1;
	}
}