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

//			 wlasciciel,pozycja, typ           , droga do pliku  , poziom  , czas zycia
Field::Field(Entity* O, Point P, int model_type, std::string Path, Level* L, int lifetime) {
	owner = O;
	type = O->get_type();
	movement_type = 'u'; //unknown, I assume it's based on type?
	position = P;
	time_left = lifetime;

	collision_effect = 0;
	size = Point(1,1,1);
	velocity = Point();
	movement_point = Point();
	destroy_event = 0;
	destroy_at_stop = false;
	location = L;
	switch (model_type) {
	case 1: //player
		graphic_model = 0;

		graphic_model_animated = L->smgr->addAnimatedMeshSceneNode(L->smgr->getMesh("../media/player/ninja.b3d"));
		graphic_model_animated->setMaterialFlag(video::EMF_LIGHTING, false);
		graphic_model_animated->setFrameLoop(205, 249);
		graphic_model_animated->setAnimationSpeed(15);

		graphic_model_animated->setPosition(core::vector3df(position.position_x, position.position_y, position.layer));
		graphic_model_animated->setScale(core::vector3df(size.position_x, size.position_y, size.layer));
		graphic_model_animated->setRotation(core::vector3df(0,O->facing_angle,0));
		break;
	case 2: //monster 1
		graphic_model = 0;
		
		graphic_model_animated = L->smgr->addAnimatedMeshSceneNode(L->smgr->getMesh("../media/monster/ninja.b3d"));
		graphic_model_animated->setMaterialFlag(video::EMF_LIGHTING, false);
		graphic_model_animated->setFrameLoop(205, 249);
		graphic_model_animated->setAnimationSpeed(15);

		graphic_model_animated->setPosition(core::vector3df(position.position_x, position.position_y, position.layer));
		graphic_model_animated->setScale(core::vector3df(size.position_x, size.position_y, size.layer));
		graphic_model_animated->setRotation(core::vector3df(0,O->facing_angle,0));
		break;
	case 3: //item
		graphic_model = L->smgr->addSphereSceneNode();
		graphic_model->setMaterialTexture(0, L->driver->getTexture("../media/environment/wall.bmp"));
		graphic_model->setMaterialFlag(video::EMF_LIGHTING, false);
		
		graphic_model->setPosition(core::vector3df(position.position_x, position.position_y, position.layer));
		graphic_model->setScale(core::vector3df(size.position_x, size.position_y, size.layer));
		graphic_model->setRotation(core::vector3df(0,O->facing_angle,0));

		graphic_model_animated = 0;
		break;
	case 4: //border
		graphic_model = L->smgr->addCubeSceneNode();
		graphic_model->setMaterialTexture(0, L->driver->getTexture("../media/environment/wall.jpg"));
		graphic_model->setMaterialFlag(video::EMF_LIGHTING, false);
		
		graphic_model->setPosition(core::vector3df(position.position_x, position.position_y, position.layer));
		graphic_model->setScale(core::vector3df(size.position_x, size.position_y, size.layer));
		graphic_model->setRotation(core::vector3df(0,O->facing_angle,0));
		
		graphic_model_animated = 0;
		break;
	default:
		graphic_model = 0;
		
		graphic_model_animated = 0;
		break;
	}
	size = Point(10,10,0);
}

void Field::rescale(Point to_size) {
	size = to_size;
}


void Field::update() {
	//Updating unit position based on velocity, detecting collision
	location->move_field(this);
	if (location->collision_detect(this))
	{
		location->demove_field(this);
		velocity.position_x = 0;
		velocity.position_y = 0;
	}
	
	//Updating Model position/scale/rotation
	if (graphic_model != 0) {
		graphic_model->setPosition(core::vector3df(position.position_x,position.position_y,(position.layer-1)*10));
		//graphic_model->setScale(core::vector3df(size.position_x,size.position_y,size.layer));
		if (this->owner != 0)
			graphic_model->setRotation(core::vector3df(0,this->owner->facing_angle,0));
	}
	//size = size*0.1;
	if (graphic_model_animated != 0) {
		graphic_model_animated->setPosition(core::vector3df(position.position_x,position.position_y,(position.layer-1)*10));
		//graphic_model_animated->setScale(core::vector3df(size.position_x,size.position_y,size.layer));
		if (this->owner != 0)
			graphic_model_animated->setRotation(core::vector3df(0,this->owner->facing_angle,0));
	}
	//tu jest grawitacja
	//if (this->owner && !(this->owner->get_type()&4))
	//	velocity.position_y -= location->gravity*location->delta_time;
	//size = size*10;
	//Handling life time
	if (time_left == 0)
		if (destroy_at_stop)
			location->trash(this);
		else time_left--;
		//owner->remove();
	if (time_left > 0)
		time_left--;
}
void Field::set_velocity(float vx, float vy, float vz)
{
	velocity.position_x = vx;
	velocity.position_y = vy;
	velocity.layer = vz;
}
void Field::change_velocity(float dvx, float dvy, float dvz)
{
	velocity.position_x += dvx;
	velocity.position_y += dvy;
	velocity.layer += dvz;
}
float Field::get_vx()
{	return velocity.position_x; }
float Field::get_vy()
{	return velocity.position_y; }
float Field::get_vz()
{	return velocity.layer; }

void Field::move_line(Point speed, int time) {
	throw "Not yet implemented";
}

void Field::move_circle(Point speed, Point center, int time) {
	throw "Not yet implemented";
}

