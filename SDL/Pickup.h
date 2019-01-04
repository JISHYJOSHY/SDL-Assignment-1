#ifndef __pickup
#define __pickup

#include "Ship.h"

// pickup class, used to power up the player when picked up, fancy that
class Pickup : public Ship
{
public:
	Pickup(int w, int h, Vec2 pos, int t, int screenBottom);
	~Pickup();

	void Update(std::vector<Bullet*>& bullets) override;

private:
	int screenBot;
};

#endif