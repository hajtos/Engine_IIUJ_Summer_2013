#ifndef __Field_h__
#define __Field_h__

#include "Entity.h"
#include "Event.h"
#include "Point.h"
#include "Level.h"
#include <string>
#include <exception>
#include <irrlicht.h>

using namespace std;

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Entity;
class Event;
class Point;
class Level;
class Field;

class Field
{
	public:
		Entity* owner;
		unsigned int type;
		char movement_type;
		Point position;
		int time_left;
		bool fixed;
		Level* location;
		scene::ISceneNode* graphic_model;
		scene::IAnimatedMeshSceneNode* graphic_model_animated;
		
		~Field();
		Field(Entity* O, Point P, Point S, int model_type, std::string Path, Level* L, int lifetime = -1);
		void rescale(Point to_size);
		void update();
	private:
		Event* collision_effect;
		Point size;
		Point translation;
		Point velocity;
		Point movement_point;
		Event* destroy_event;
		bool destroy_at_stop;

		void move_line(Point speed, int time);
		void move_circle(Point speed, Point center, int time);

	friend class Level;
};

#endif
