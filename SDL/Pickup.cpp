#include "Pickup.h"

Pickup::Pickup(int w, int h, Vec2 pos, int t, int screenBottom)
{
	this->w = w;
	this->h = h;
	this->pos = pos;
	speed = 2;
	this->type = t;
	screenBot = screenBottom;

	this->destroy = false;
}

Pickup::~Pickup()
{
}

// very basic update
void Pickup::Update(std::vector<Bullet*>& bullets)
{
	// the main part of this is to collide with the player, so not much needs to happen here
	this->pos.y += 1 * speed;

	if (this->pos.y > screenBot)
		this->destroy = true;
}