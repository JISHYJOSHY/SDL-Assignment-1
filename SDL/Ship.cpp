#include "Ship.h"

Ship::Ship()
{
}

Ship::~Ship()
{
}

// basic collision for all classes, unless overriden
bool Ship::Collide(Vec2 point)
{
	if (point.x > this->pos.x && point.x < this->pos.x + w
		&& point.y > this->pos.y && point.y < this->pos.y + h)
		return true;

	return false;
}

void Ship::Shoot(std::vector<Bullet*>& bullets)
{

}

void Ship::ResetShot()
{
	canShoot = false;
	fireTimer = 0;
}

void Ship::Hit()
{
	health--;
}

void Ship::Kill()
{
	destroy = true;
}