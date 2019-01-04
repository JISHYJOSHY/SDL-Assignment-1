#ifndef __tank
#define __tank

#include "Ship.h"

// tank class
class Tank : public Ship
{
public:
	// we need the width and height for collision detection, the rest is the same as other ships
	Tank(Vec2 position, Vec2 dimensions, int shipType, Vec2 borders, int health, Vec2 bulletDimensions);
	~Tank();

	void Update(std::vector<Bullet*>& bullets) override;
	void Shoot(std::vector<Bullet*>& bullets) override;

private:
	float timer;

	Vec2 bind;
};

#endif