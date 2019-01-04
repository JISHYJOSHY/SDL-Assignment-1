#include "Cannon.h"

// initialisation
Cannon::Cannon(int w, int h, Vec2 pos, Vec2 bulletDimensions, Vec2 borders, int bulletType)
{
	this->w = w;
	this->h = h;
	this->pos = pos;
	this->type = type;
	fireTimer = 0;
	timer = 0;
	speed = 2;
	this->destroy = false;
	this->shotCheck = true;
	this->health = health;

	SetBullet(Bullet(bulletDimensions.x, bulletDimensions.y));
	bind = borders;
	this->bulletType = bulletType;
}

Cannon::~Cannon()
{
}

// update
void Cannon::Update(std::vector<Bullet*>& bullets)
{
	// timer update
	timer += (100 / 60 - (SDL_GetTicks() - SDL_GetTicks()));

	this->pos.y += 1 * speed;

	if (timer > 10)
		canShoot = true;
	
	// in this case, we generate a random number and if we miss, set the timer to 0 again to create delays in shooting
	if (canShoot)
		if (rand() % 100 > 70)
		{
			Shoot(bullets);
		}
}

void Cannon::Shoot(std::vector<Bullet*>& bullets)
{
	bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), bind, Vec2(0, 1), false, bulletType));

	canShoot = false;
	timer = 0;
}