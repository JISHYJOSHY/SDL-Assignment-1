#ifndef __rogue
#define __rogue

#include "Ship.h"

// another type of ship
class Rogue : public Ship
{
public:
	Rogue(Vec2 position, Vec2 dimensions, int shipType, Vec2 borders, int health, Vec2 bulletDimensions);
	~Rogue();

	void Update(std::vector<Bullet*>& bullets) override;
	void Shoot(std::vector<Bullet*>& bullets) override;

private:
	Vec2 localPos;
	float timer;
	float shotTimer;

	Vec2 bind;
	bool direction;
};

#endif