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
		Border(Level* L, double ms, bool abs, int b, Point pos, Point size,
			int ca1, int ca2, int ca3, int gd, int fa, int mt, char* animT,
			char* modelP, Point trans, bool anim, int lt, bool a, bool aa);

		unsigned int get_type();
		void remove();
	private:
		int bouncing;
};

#endif
