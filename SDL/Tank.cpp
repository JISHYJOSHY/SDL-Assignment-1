#include "Tank.h"

// initialisations
Tank::Tank(Vec2 position, Vec2 dimensions, int shipType, Vec2 borders, int health, Vec2 bulletDimensions)
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

Tank::~Tank()
{
}

// update
void Tank::Update(std::vector<Bullet*>& bullets)
{
	timer += (100 / 60 - (SDL_GetTicks() - SDL_GetTicks()));

	this->pos.y += 1 * speed;

	if (this->pos.y > bind.y)
		this->destroy = true;

	if (timer > 80)
		canShoot = true;
	
	if (canShoot)
		if (rand() % 100 > 95)
		{
			Shoot(bullets);
		}

	this->CheckHealth();
}

void Tank::Shoot(std::vector<Bullet*>& bullets)
{
	bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), bind, Vec2(0, 1), false, 1));
	bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), bind, Vec2(0.5f, 0.5f), false, 1));
	bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), bind, Vec2(1, 0), false, 1));
	bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), bind, Vec2(0.5f, -0.5f), false, 1));
	bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), bind, Vec2(0, -1), false, 1));
	bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), bind, Vec2(-0.5f, -0.5f), false, 1));
	bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), bind, Vec2(-1, 0), false, 1));
	bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), bind, Vec2(-0.5f, 0.5f), false, 1));

	timer = 0;
	canShoot = false;
}