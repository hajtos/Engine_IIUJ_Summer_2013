#include "Field.h"
#include <exception>
#include <iostream>
using namespace std;

Field::~Field() {
	//owner already destroyed, no need to do this
	owner = 0;
	collision_effect = 0;
	destroy_event = 0;
	if (graphic_model == 0)
		graphic_model_animated->remove();
	else graphic_model->remove();
	graphic_model = 0;
	graphic_model_animated = 0;
}

//			 wlasciciel,pozycja,wielkoœæ, typ           , droga do pliku  , poziom  , czas zycia
Field::Field(Entity* O, Point P, Point S, int model_type, std::string Path, Level* L, int lifetime) {
	owner = O;
	type = O->get_type();
	movement_type = 'u'; //unknown, I assume it's based on type?
	position = P;
	size = S;
	time_left = lifetime;

	collision_effect = 0;
	velocity = Point();
	movement_point = Point();
	destroy_event = 0;
	destroy_at_stop = false;
	location = L;
	switch (model_type) {
	case 1: //player
		fixed = false;
		graphic_model = 0;

		graphic_model_animated = L->smgr->addAnimatedMeshSceneNode(L->smgr->getMesh("../media/player/ninja.b3d"));
		graphic_model_animated->setMaterialFlag(video::EMF_LIGHTING, false);
		graphic_model_animated->setFrameLoop(205, 249);
		graphic_model_animated->setAnimationSpeed(15);
		
		translation = Point(0.0, -5.0, 0.0);
		graphic_model_animated->setPosition(core::vector3df(position.position_x + translation.position_x,
			position.position_y + translation.position_y, position.layer + translation.layer));
		graphic_model_animated->setScale(core::vector3df(1.0, 1.0, 1.0));
		graphic_model_animated->setRotation(core::vector3df(0,O->facing_angle,0));
		break;
	case 2: //monster 1
		fixed = false;
		graphic_model = 0;
		
		graphic_model_animated = L->smgr->addAnimatedMeshSceneNode(L->smgr->getMesh("../media/monster/ninja.b3d"));
		graphic_model_animated->setMaterialFlag(video::EMF_LIGHTING, false);
		graphic_model_animated->setFrameLoop(205, 249);
		graphic_model_animated->setAnimationSpeed(15);
		
		translation = Point(0.0, -5.0, 0.0);
		graphic_model_animated->setPosition(core::vector3df(position.position_x + translation.position_x,
			position.position_y + translation.position_y, position.layer + translation.layer));
		graphic_model_animated->setScale(core::vector3df(1.0, 1.0, 1.0));
		graphic_model_animated->setRotation(core::vector3df(0,O->facing_angle,0));
		break;
	case 3: //item
		fixed = true;
		graphic_model = L->smgr->addSphereSceneNode();
		graphic_model->setMaterialTexture(0, L->driver->getTexture("../media/environment/wall.bmp"));
		graphic_model->setMaterialFlag(video::EMF_LIGHTING, false);
		
		translation = Point(0.0, 0.0, 0.0);
		graphic_model->setPosition(core::vector3df(position.position_x + translation.position_x,
			position.position_y + translation.position_y, position.layer + translation.layer));
		graphic_model->setScale(core::vector3df(1.0, 1.0, 1.0));
		graphic_model->setRotation(core::vector3df(0,O->facing_angle,0));

		graphic_model_animated = 0;
		break;
	case 4: //border
		fixed = true;
		graphic_model = L->smgr->addCubeSceneNode();
		graphic_model->setMaterialTexture(0, L->driver->getTexture("../media/environment/wall.jpg"));
		graphic_model->setMaterialFlag(video::EMF_LIGHTING, false);
		
		translation = Point(0.0, 0.0, 0.0);
		graphic_model->setPosition(core::vector3df(position.position_x + translation.position_x,
			position.position_y + translation.position_y, position.layer + translation.layer));
		graphic_model->setScale(core::vector3df(1.0, 1.0, 1.0));
		//graphic_model->setScale(core::vector3df(size.position_x, size.position_y, size.layer));
		graphic_model->setRotation(core::vector3df(0,O->facing_angle,0));
		
		graphic_model_animated = 0;
		break;
	default:
		graphic_model = 0;
		
		graphic_model_animated = 0;
		break;
	}
}

void Field::rescale(Point to_size) {
	size = to_size;
}


void Field::update() {
	//Updating unit position based on velocity, detecting collision
	location->move_field(this);
	/*
	if (location->collision_detect(this))
	{
		location->demove_field(this);
		velocity.position_x = 0;
		velocity.position_y = 0;
	}
	*/
	
	//Updating Model position/scale/rotation
	if (graphic_model != 0) {
		graphic_model->setPosition(core::vector3df(position.position_x + translation.position_x,
			position.position_y + translation.position_y, (position.layer - 1 + translation.layer)*10));
		if (this->owner != 0)
			graphic_model->setRotation(core::vector3df(0,this->owner->facing_angle,0));
	}
	if (graphic_model_animated != 0) {
		graphic_model_animated->setPosition(core::vector3df(position.position_x + translation.position_x,
			position.position_y + translation.position_y, (position.layer - 1 + translation.layer)*10));
		if (this->owner != 0)
			graphic_model_animated->setRotation(core::vector3df(0,this->owner->facing_angle,0));
	}

	//Handling gravity
	if (this->owner && !(this->fixed))
		velocity.position_y -= location->gravity*location->delta_time;

	//Handling life time
	if (time_left == 0)
		if (destroy_at_stop)
			location->trash(this);
		else time_left--;
		//owner->remove();
	if (time_left > 0)
		time_left--;
}

void Field::move_line(Point speed, int time) {
	throw "Not yet implemented";
}

void Field::move_circle(Point speed, Point center, int time) {
	throw "Not yet implemented";
}

