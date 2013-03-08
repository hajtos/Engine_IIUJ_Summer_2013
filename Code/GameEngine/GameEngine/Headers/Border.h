#ifndef __Border_h__
#define __Border_h__

#include "Entity.h"
#include "Level.h"
#include "Point.h"
#include <exception>

using namespace std;

class Level;
class Border;

class Border : public Entity
{
	public:
		bool absolute;

		~Border();
		Border(Point position, Point size, Level* L);

		unsigned int get_type();
		void remove();
	private:
		int bouncing;

};

#endif
