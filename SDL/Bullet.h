#ifndef __bullet
#define __bullet

#include <SDL.h>
#include <math.h>
#include "Vec2.h"

// bullet class, may split into sub classes for different types
class Bullet
{
public:
	Bullet();
	Bullet(int w, int h) { this->w = w, this->h = h; };
	Bullet(int w, int h, Vec2 p, Vec2 maxBound, Vec2 d, bool player, int t);
	~Bullet();

	void Update();

	// getters and setters!
	Vec2 GetPos() { return pos; };
	void SetPos(Vec2 p) { pos = p; };

	int GetSpeed() { return speed; };
	void SetSpeed(int i) { speed = i; };

	void SetPlayer(bool p) { player = p; };
	bool isPlayer() { return player; };

	void Hit() { destroy = true; };
	bool Destroy() { return destroy; };

	int GetWidth() { return w; };
	int GetHeight() { return h; };

	int GetType() { return bulletType; };

private:
	// bullet stuff
	Vec2 pos;
	Vec2 dir;

	Vec2 localPos;
	float timer;
	bool direction;

	// borders for deletion
	Vec2 bordersMax;
	Vec2 bordersMin;

	// bullet type
	int bulletType;

	// how fast the bullet moves
	int speed = 6;

	// bools
	bool player;
	bool destroy;

	int w;
	int h;
};

#endif