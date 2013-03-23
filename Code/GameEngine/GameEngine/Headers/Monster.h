#ifndef __Monster_h__
#define __Monster_h__

#include "Entity.h"
#include "Level.h"
#include "Point.h"
#include "Behaviour.h"
#include <exception>
#include <string>
#include <list>

using namespace std;

//class Entity;
class Level;
class Behaviour;
class Monster;

class Monster : public Entity
{
	public:
		int hp;
		std::list<Behaviour> aI;
		std::string name;

		~Monster();
		Monster(Level* L, int ms, int mhp, std::string nm, std::string mt,
			Point pos, Point size, int ca1, int ca2, int ca3, int gd, int fa,
			char* animT, char* modelP, Point trans, bool anim, int lt, bool a, bool aa);
		unsigned int get_type();
		void act();
		void remove();
	private:
		std::string monster_type;

};

#endif
