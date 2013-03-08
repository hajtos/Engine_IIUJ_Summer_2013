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
		Monster(std::string init, Level* L, Point position = Point());
		unsigned int get_type();
		void act();
		void remove();
	private:
		std::string monster_type;

};

#endif
