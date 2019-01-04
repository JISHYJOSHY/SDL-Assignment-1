#include "Pawn.h"

// basic enemy
Pawn::Pawn(Vec2 position, Vec2 dimensions, int shipType, Vec2 borders, int health)
{
	w = dimensions.x;
	h = dimensions.y;
	pos = position;
	localPos = pos;
	type = shipType;
	bind = borders;

	this->health = health;
	this->destroy = false;
	fireTimer = 0;
	timer = 0;
	speed = 3;

	direction = (rand() % 100 < 50);
}

Pawn::~Pawn()
{
}

void Pawn::Update(std::vector<Bullet*>& bullets)
{
	timer += (100 / 60 - (SDL_GetTicks() - SDL_GetTicks()));

	localPos.y += 1 * speed;
	
	// move in a sin wave
	this->pos = Vec2(localPos.x + (sin(timer / 20) * 40 * (direction ? 1 : -1)), localPos.y);

	if (localPos.y > bind.y)
		this->destroy = true;

	this->CheckHealth();
}