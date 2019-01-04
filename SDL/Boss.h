#ifndef __boss
#define __boss

#include "Ship.h"
#include "Cannon.h"

// boss class, currently using this AS the boss, should split up later on
class Boss : public Ship
{
public:
	Boss();
	~Boss();
	
	int cannonsSize;

protected:
	Vec2 borders;
	float timer;

	bool direction;
	int screenBot;

	std::vector<Cannon*> cannons;
};

#endif