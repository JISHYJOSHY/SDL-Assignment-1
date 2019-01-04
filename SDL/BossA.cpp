#include "BossA.h"

BossA::BossA(Vec2 position, Vec2 dimensions, int shipType, Vec2 borders, int health, Vec2 bulletDimensions)
{
	this->w = dimensions.x;
	this->h = dimensions.y;
	this->borders = borders;
	this->pos = position;
	this->type = type;

	SetBullet(Bullet(bulletDimensions.x, bulletDimensions.y));

	fireTimer = 0;
	timer = 0;
	speed = 1;

	this->destroy = false;
	this->health = health;

	// here is the 'customisable' part, load in how many turrets needed for the ship, and where they are relative to the ships center
	// values are arbirtrary as they are part of a larger image, so 'magic numbers' apply
	cannons.push_back(new Cannon(12, 20, this->Center() + Vec2(-50, 22), bulletDimensions, borders, 3));
	cannons.push_back(new Cannon(6, 10, this->Center() + Vec2(-17, 29), bulletDimensions, borders, 1));
	cannons.push_back(new Cannon(6, 10, this->Center() + Vec2(50, 22), bulletDimensions, borders, 1));
	cannons.push_back(new Cannon(12, 20, this->Center() + Vec2(50, 22), bulletDimensions, borders, 3));

	cannonsSize = cannons.size();
	this->extras = cannonsSize;

	direction = true;
	type = 9;
	canShoot = true;
	shootIndex = 0;
}

BossA::~BossA()
{
	// when deleted, delete all cannons in this object
	for (int i = 0; i < cannonsSize;)
	{
		delete cannons[i];
		cannonsSize--;
	}
}

void BossA::Update(std::vector<Bullet*>& bullets)
{
	// increment timer
	timer += (100 / 60 - (SDL_GetTicks() - SDL_GetTicks()));

	// if the boss is above the screen, move it into view
	if (this->pos.y < 50)
		this->pos.y += 1 * speed;
	else
	{
		// based on it's position, move the ship left or right
		if (!direction)
			if (this->pos.x > 0)
				this->pos.x--;
			else
				direction = !direction;
		else
			if (this->pos.x + this->w < borders.x)
				this->pos.x++;
			else
				direction = !direction;
	}

	// if for some reason the boss falls off the screen, delete it
	if (this->pos.y > borders.y)
		this->destroy = true;

	// if the set timer values are met, allow the boss to shoot
	if (timer > 20)
	{
		timer = 0;
		shootIndex += (rand() % 100 < 4 ? 2 : 1);
		if (shootIndex > 7)
			shootIndex = 0;
	}

	if (canShoot && shotCheck)
		if (rand() % 100 > 60)
		{
			Shoot(bullets);
		}

	// find a way to make this a loop
	// update all cannons related to this boss


	for (int i = 0; i < extras; i++)
	{
		switch (i)
		{
		case 0:
			cannons[i]->SetPos(this->Center() + Vec2(-50, 22));
			break;
		case 1:
			cannons[i]->SetPos(this->Center() + Vec2(-17, 29));
			break;
		case 2:
			cannons[i]->SetPos(this->Center() + Vec2(17, 29));
			break;
		case 3:
			cannons[i]->SetPos(this->Center() + Vec2(50, 22));
			break;
		}
	}

	switch (shootIndex)
	{
	case 0:
		cannons[0]->Update(bullets);
		break;
	case 1:
		cannons[0]->Update(bullets);
		cannons[1]->Update(bullets);
		break;
	case 2:
		cannons[1]->Update(bullets);
		break;
	case 3:
		cannons[1]->Update(bullets);
		cannons[2]->Update(bullets);
		break;
	case 4:
		cannons[2]->Update(bullets);
		break;
	case 5:
		cannons[2]->Update(bullets);
		cannons[3]->Update(bullets);
		break;
	case 6:
		cannons[3]->Update(bullets);
		break;
	case 7:
		cannons[0]->Update(bullets);
		cannons[3]->Update(bullets);
		break;
	}

	this->CheckHealth();

	shotCheck = true;
}

void BossA::Shoot(std::vector<Bullet*>& bullets)
{
	bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), borders, Vec2(0, 1), false, 1));
	bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), borders, Vec2(0.5f, 1), false, 1));
	bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), borders, Vec2(-0.5f, 1), false, 1));

	canShoot = false;
	timer = 0;
}