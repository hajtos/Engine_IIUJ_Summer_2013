#ifndef __Field_h__
#define __Field_h__

#include "Entity.h"
#include "Event.h"
#include "Point.h"
#include "Level.h"
#include <string>
#include <exception>
#include <irrlicht.h>
#include "Velocity.h"
#include "Shape.h"
#include "Rectangle.h"
#include "StraightVelocity.h"

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
		Point position;
		Level* location;
		scene::ISceneNode* graphic_model;
		scene::IAnimatedMeshSceneNode* graphic_model_animated;
		
		~Field();
		Field(Entity* O, Point P, Point S, int model_type, char* Path, Level* L,
			int lifetime, Point trans, bool anim, bool a, bool aa);
		void rescale(Point to_size);
		void update();
		Velocity* velocity;
	private:
		Event* collision_effect;
		Shape* shape;
		Point translation;
		Event* destroy_event;
		bool destroy_at_stop;
		bool active;
		bool always_active;

		void move(Velocity* v);

	friend class Level;
};

#endif
