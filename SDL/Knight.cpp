#include "Knight.h"

// same as other classes, slightly different
Knight::Knight(Vec2 position, Vec2 dimensions, int shipType, Vec2 borders, int health, Vec2 bulletDimensions)
{
	w = dimensions.x;
	h = dimensions.y;
	pos = position;
	type = shipType;
	bind = borders;

	this->health = health;
	SetBullet(Bullet(bulletDimensions.x, bulletDimensions.y));
	this->destroy = false;
	fireTimer = 0;
	timer = 0;
	speed = 2;
}

Knight::~Knight()
{
}

void Knight::Update(std::vector<Bullet*>& bullets)
{
	timer += (100 / 60 - (SDL_GetTicks() - SDL_GetTicks()));

	this->pos.y += 1 * speed;

	if (this->pos.y > bind.y)
		this->destroy = true;

	if (timer > 100)
		canShoot = true;
	
	if (canShoot)
		if (rand() % 100 > 60)
		{
			Shoot(bullets);
		}

	this->CheckHealth();
}

void Knight::Shoot(std::vector<Bullet*>& bullets)
{
	bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), bind, Vec2(0, 1), false, 1));

	timer = 0;
	canShoot = false;
}