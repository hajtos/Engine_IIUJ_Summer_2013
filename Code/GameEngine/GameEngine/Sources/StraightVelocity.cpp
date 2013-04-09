#include "StraightVelocity.h"


void StraightVelocity::flatten(Point q) {

}

Point StraightVelocity::nextPos(Point* p) {
	return *p+velocity;
}

bool StraightVelocity::grounded() {
	return velocity.position_y==0;
}

void StraightVelocity::applyGravity(float scale) {
	if (!grounded())
		velocity.position_y-=scale;
}

void StraightVelocity::stop() {
	velocity.layer = 0;
	velocity.position_x = 0;
	velocity.position_y = 0;
}