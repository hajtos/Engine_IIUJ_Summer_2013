#ifndef __Level_h__
#define __Level_h__

#include "Entity.h"
#include "Point.h"
#include "Condition.h"

#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "Border.h"
#include <exception>
#include <irrlicht.h>
#include <string>
#include <list>
#include <vector>
#include <map>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Player;
class Point;
class Field;
class Item;
class Event;
class Monster;
class Border;
class Level;

class Level
{
	public:
		Level(IrrlichtDevice* Device);
		//Level(IrrlichtDevice* Device, std::string path);

		//irrlicht data
		IrrlichtDevice *device;
		IVideoDriver* driver;
		ISceneManager* smgr;
		IGUIEnvironment* guienv;

		Point size;
		Point respawn;
		Player* player;
		int custom_attribute1;
		int custom_attribute2;
		int custom_attribute3;
		std::map< std::string, Event* > event_dictionary;
		int gravity;
		int lc_interval;
		float delta_time;

		void add_event(std::string init);
		void add_border(Point start, Point size);
		void add_monster(std::string init, Point position = Point());
		void add_item(std::string init, Point position = Point());
		void advance_frame(ICameraSceneNode *cam);
		bool collision_detect(Field* source);
		void move_field(Field* field);
		void demove_field(Field* field);
		void remove_player(Field* field);
		void remove_border(Field* field, Border* entity);
		void remove_monster(Field* field, Monster* entity);
		void remove_item(Field* field, Item* entity);
		void trash(Field* field);
		void process_key(irr::EKEY_CODE keycode);
	private:
		std::list<Field*> fields;
		std::list<Field*> garbage;
		std::list<Item*> items;
		Point active_range;
		int time_left;
		std::list<Monster*> monsters;
		std::list<Border*> boundaries;
};

#endif
