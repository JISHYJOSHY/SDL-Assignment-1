#ifndef __cannon
#define __cannon

#include "Ship.h"

// cannon class, uses ship for features, but is more used for bosses or turrets
class Cannon : public Ship
{
public:
	// width and height for collision, pos for position
	Cannon(int w, int h, Vec2 pos, Vec2 bulletDimensions, Vec2 borders, int bulletType);
	~Cannon();

	void Update(std::vector<Bullet*>& bullets) override;
	void Shoot(std::vector<Bullet*>& bullets) override;
	
private:
	float timer;

	Vec2 bind;
	int bulletType;
};

#endif