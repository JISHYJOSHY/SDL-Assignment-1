#include "Bullet.h"

// take in width, height, position, screen borders, direction, who shot it, and a type
Bullet::Bullet()
{

}

Bullet::Bullet(int w, int h, Vec2 p, Vec2 boundMax, Vec2 d, bool player, int t)
{
	// initialise
	this->w = w;
	this->h = h;
	this->bulletType = t;
	destroy = false;
	this->SetPlayer(player);

	pos = p;
	localPos = pos;
	dir = d;
	bordersMin = Vec2(0, 0);
	bordersMax = boundMax;

	if (bulletType == 2)
		speed = 10;
}
      
Bullet::~Bullet()
{
}

void Bullet::Update()
{
	// increment timer
	timer += (100 / 60 - (SDL_GetTicks() - SDL_GetTicks()));

	// move the bullet
	localPos.y += dir.y * speed;
	localPos.x += dir.x * speed;

	// set position based on bulletType
	if (bulletType == 3)
		this->pos = Vec2((float)(localPos.x + (sin(timer / 10) * 40 * (direction ? 1 : -1))), localPos.y);
	else
		this->pos = localPos;

	// if the bullet goes out of borders, prepare for deletion
	if (pos.y + this->h < bordersMin.y || pos.y - (this->h * 2) > bordersMax.y)
		destroy = true;

	if (pos.x < bordersMin.x - 10 || pos.x > bordersMax.x + 10)
		destroy = true;
}