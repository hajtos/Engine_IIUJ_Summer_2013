#ifndef __Velocity_h__
#define __Velocity_h__

#include "Point.h"

class Velocity {
	int time;
	virtual void stop(){};
	public:
		Velocity(int t):time(t){}
		void reduceTime() {if (time>=0) --time; if (!time) stop();}
		bool finished(){return time<=0;}
		virtual void flatten(Point q){}
		virtual Point nextPos(Point* p){ return *p;}
		virtual bool grounded(){return false;}
		virtual void applyGravity(float scale){}
};

#endif