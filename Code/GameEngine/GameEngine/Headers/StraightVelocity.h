#ifndef __Straight_Velocity_h__
#define __Straight_Velocity_h__

#include "Point.h"
#include "Velocity.h"

class StraightVelocity : public Velocity {
	Point velocity;
	void stop();
	public:
		StraightVelocity(int x,int y,int z, int t):Velocity(t),velocity(Point(x,y,z)){}
		void flatten(Point q);
		Point nextPos(Point* p);
		bool grounded();
		void applyGravity(float scale);
};

#endif