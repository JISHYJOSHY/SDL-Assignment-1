#ifndef __bishop
#define __bishop

#include "Ship.h"

// another enemy type
class Bishop : public Ship
{
public:
	Bishop(Vec2 position, Vec2 dimensions, int shipType, Vec2 borders, int health, Vec2 bulletDimensions);
	~Bishop();

	void Update(std::vector<Bullet*>& bullets) override;
	void Shoot(std::vector<Bullet*>& bullets) override;

private:
	float timer;

	Vec2 bind;
};

#endif