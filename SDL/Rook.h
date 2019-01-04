#ifndef __rook
#define __rook

#include "Ship.h"

// another ship class, or maybe the first, depending on what order they are viewed in
class Rook : public Ship
{
public:
	// take in width and height for collision, a spawn position, the type of ship (used for drawing), the bottom of the screen (so we can delete this ship) and health
	Rook(Vec2 position, Vec2 dimensions, int shipType, Vec2 borders, int health, Vec2 bulletDimensions);
	~Rook();

	void Update(std::vector<Bullet*>& bullets) override;
	void Shoot(std::vector<Bullet*>& bullets) override;

private:
	float timer;

	Vec2 bind;
};

#endif