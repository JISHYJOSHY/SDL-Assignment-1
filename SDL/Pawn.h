#ifndef __pawn
#define __pawn

#include "Ship.h"

// basic enemy class
class Pawn : public Ship
{
public:
	// take in width and height for collision, a spawn position, the type of ship (used for drawing), the bottom of the screen (so we can delete this ship) and health
	Pawn(Vec2 position, Vec2 dimensions, int shipType, Vec2 borders, int health);
	~Pawn();

	void Update(std::vector<Bullet*>& bullets) override;

private:
	Vec2 localPos;
	float timer;

	Vec2 bind;
	bool direction;
};

#endif