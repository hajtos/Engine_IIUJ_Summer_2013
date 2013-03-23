#ifndef __AnimationTable_h__
#define __AnimationTable_h__

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

class AnimationTable
{
	public:
		~AnimationTable();
		AnimationTable();
		void push(int id, int n, int vallue);

		int size[12];
		int* animation[12];
};

#endif
