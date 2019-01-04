#include "Rook.h"

Rook::Rook(Vec2 position, Vec2 dimensions, int shipType, Vec2 borders, int health, Vec2 bulletDimensions)
{
	w = dimensions.x;
	h = dimensions.y;
	pos = position;
	type = shipType;
	bind = borders;

	this->health = health;
	SetLaser(Bullet(bulletDimensions.x, bulletDimensions.y));
	this->destroy = false;
	fireTimer = 0;
	timer = 0;
	speed = 2;
}

Rook::~Rook()
{
}

void Rook::Update(std::vector<Bullet*>& bullets)
{
	timer += (100 / 60 - (SDL_GetTicks() - SDL_GetTicks()));

	this->pos.y += 1 * speed;

	if (this->pos.y > bind.y)
		this->destroy = true;

	if (timer > 800)
		canShoot = true;

	// reset timer to a lower value to crate a 'laser' effect
	if (canShoot)
	{
		Shoot(bullets);
	}

	this->CheckHealth();
}

void Rook::Shoot(std::vector<Bullet*>& bullets)
{
	bullets.push_back(new Bullet(laserTemplate.GetWidth(), laserTemplate.GetHeight(), Center() + Vec2(0, 1), bind, Vec2(0, 1), false, 2));

	timer = 798;
	canShoot = false;
}