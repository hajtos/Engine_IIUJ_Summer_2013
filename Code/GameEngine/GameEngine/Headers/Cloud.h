#ifndef __Cloud_h__
#define __Cloud_h__

#include "Point.h"
#include <exception>
#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Cloud;

class Cloud
{
	public:
		Cloud(IrrlichtDevice* Device, Point position);
		void cloud_move();
	private:
		scene::ISceneNode* graphic_model;
};

#endif