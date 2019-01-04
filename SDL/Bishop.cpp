#include "Bishop.h"

// initialisation
Bishop::Bishop(Vec2 position, Vec2 dimensions, int shipType, Vec2 borders, int health, Vec2 bulletDimensions)
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
	speed = 3;
}

Bishop::~Bishop()
{
}

// update
void Bishop::Update(std::vector<Bullet*>& bullets)
{
	// increment timer
	timer += (100 / 60 - (SDL_GetTicks() - SDL_GetTicks()));

	// move down
	this->pos.y += 1 * speed;

	// if goes off the screen, delete
	if (this->pos.y > bind.y)
		this->destroy = true;

	// if timer > determined value, shoot
	if (timer > 50)
		canShoot = true;
	
	if (canShoot)
		if (rand() % 100 > 85)
		{
			Shoot(bullets);
		}

	this->CheckHealth();
}

void Bishop::Shoot(std::vector<Bullet*>& bullets)
{
	bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), bind, Vec2(0, 1), false, 1));
	bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), bind, Vec2(0.5f, 1), false, 1));
	bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), bind, Vec2(-0.5f, 1), false, 1));
	
	timer = 0;
	canShoot = false;
}