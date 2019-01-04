#ifndef __knight
#define __knight

#include "Ship.h"

class Knight : public Ship
{
public:
	// take in width and height for collision, a spawn position, the type of ship (used for drawing), the bottom of the screen (so we can delete this ship) and health
	Knight(Vec2 position, Vec2 dimensions, int shipType, Vec2 borders, int health, Vec2 bulletDimensions);
	~Knight();

	void Update(std::vector<Bullet*>& bullets) override;
	void Shoot(std::vector<Bullet*>& bullets) override;

private:
	float timer;

	Vec2 bind;
};

#endif