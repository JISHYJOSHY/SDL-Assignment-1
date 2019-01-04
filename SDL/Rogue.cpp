#include "Rogue.h"

Rogue::Rogue(Vec2 position, Vec2 dimensions, int shipType, Vec2 borders, int health, Vec2 bulletDimensions)
{
	w = dimensions.x;
	h = dimensions.y;
	pos = position;
	localPos = pos;
	type = shipType;
	bind = borders;

	this->health = health;
	SetBullet(Bullet(bulletDimensions.x, bulletDimensions.y));
	this->destroy = false;
	fireTimer = 0;
	timer = 0;
	speed = 3;

	direction = (rand() % 100 < 50);
}

Rogue::~Rogue()
{
}

void Rogue::Update(std::vector<Bullet*>& bullets)
{
	timer += (100 / 60 - (SDL_GetTicks() - SDL_GetTicks()));
	shotTimer += (100 / 60 - (SDL_GetTicks() - SDL_GetTicks()));

	localPos.y += 1 * speed;

	// move in a spiral pattern
	this->pos = Vec2(localPos.x + (sin(timer / 20) * 40 * (direction ? 1 : -1)), localPos.y + (cos(timer / 20) * 40 * (direction ? 1 : -1)));
	
	if (this->pos.y > bind.y)
		this->destroy = true;

	if (shotTimer > 100)
		canShoot = true;
	
	if (canShoot)
		if (rand() % 100 > 70)
		{
			Shoot(bullets);
		}

	this->CheckHealth();
}

void Rogue::Shoot(std::vector<Bullet*>& bullets)
{
	bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center() + Vec2(2, 0), bind, Vec2(0, 1), false, 1));
	bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center() - Vec2(2, 0), bind, Vec2(0, 1), false, 1));

	shotTimer = 0;
	canShoot = false;
}