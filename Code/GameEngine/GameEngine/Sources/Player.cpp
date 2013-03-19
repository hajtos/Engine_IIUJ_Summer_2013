#include "Player.h"
#include <exception>

using namespace std;

Player::~Player() {
	main_field = 0;
}

Player::Player() {
	movement_speed = 5;
	hp = 100;
	lifes = 3;
	grounded = false;

	//Entity:
	custom_attribute1 = 0;
	custom_attribute2 = 0;
	custom_attribute3 = 0;
	gravity_degree = 100; //%?
	facing_angle = 90;
	main_field = 0;
	animator = 0;
}

Player::Player(Level* L) {
	movement_speed = 5;
	hp = 100;
	lifes = 3;
	grounded = false;

	//Entity:
	custom_attribute1 = 0;
	custom_attribute2 = 0;
	custom_attribute3 = 0;
	gravity_degree = 100; //%?
	facing_angle = 90;
	main_field = new Field(this, Point(), Point(5.0, 10.0, 1.0), 1, "", L);
	animator = new Animator("", main_field->graphic_model_animated);
}

unsigned int Player::get_type() {
	return 1;
}

void Player::remove() {
	main_field->location->remove_player(main_field);
}