#ifndef __BgMovableObject_h__
#define __BgMovableObject_h__

#include "Point.h"
#include <exception>
#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class BgMovableObject;

class BgMovableObject
{
	public:
		BgMovableObject(IrrlichtDevice* Device, vector3df scale, Point position, char* TexturePath, int t);
		void move();
	private:
		int type;
		scene::ISceneNode* graphic_model;
};

#endif