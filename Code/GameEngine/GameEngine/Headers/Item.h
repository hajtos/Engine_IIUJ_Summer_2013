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
		Item(std::string init, Level* L, Point position = Point(), Point Size = Point(5.0, 5.0, 1.0));

		unsigned int get_type();
		void remove();
};

#endif
