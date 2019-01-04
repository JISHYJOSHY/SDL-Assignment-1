#pragma once
#include "Boss.h"
class BossA : public Boss
{
public:
	BossA(Vec2 position, Vec2 dimensions, int shipType, Vec2 borders, int health, Vec2 bulletDimensions);
	~BossA();

	void Update(std::vector<Bullet*>& bullets) override;
	void Shoot(std::vector<Bullet*>& bullets) override;

private:
	Vec2 borders;
	int shootIndex;
};

