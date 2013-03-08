#ifndef __Player_h__
#define __Player_h__

#include "Animator.h"
#include "Entity.h"
#include "Level.h"
#include "Point.h"
#include <exception>

using namespace std;

class Level;
//class Entity;
class Player;

class Player : public Entity
{
	public:
		Animator* animator;
		int hp;
		int lifes;
		
		~Player();
		Player();
		Player(Level* L);
		unsigned int get_type();
		void remove();
};

#endif
