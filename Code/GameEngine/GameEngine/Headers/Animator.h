#ifndef __Animator_h__
#define __Animator_h__

#include "AnimationTable.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
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

class Field;

class Animator
{
	public:
		Animator(AnimationTable* Table, scene::IAnimatedMeshSceneNode* Model);

		void check();
		double checkProgress();
		int getAnimation();
		void setAnimation(int As);
		void setSpeed(int As);
		void stop();
		void resume();
		void set(bool ac, bool lo, int aid, int as, int curf, int minf, int maxf);
	private:
		bool active;
		bool looping;
		int animID;
		int animSpeed;
		AnimationTable* animTable;
		scene::IAnimatedMeshSceneNode* graphic_model;
};

#endif
