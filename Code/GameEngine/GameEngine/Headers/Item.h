#ifndef __Item_h__
#define __Item_h__

#include "Entity.h"
#include "Level.h"
#include "Point.h"
#include <exception>

using namespace std;

class Level;
class Item;

class Item : public Entity
{
	public:
		~Item();
		Item(Level* L, double ms, Point pos, Point size,
			int ca1, int ca2, int ca3, int gd, int fa, char* animT,
			char* modelP, Point trans, bool anim, int lt, bool a, bool aa);

		unsigned int get_type();
		void remove();
};

#endif
