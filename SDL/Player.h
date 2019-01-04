#ifndef __player
#define __player

#include "Ship.h"

// player is child of ship
class Player : public Ship
{
public:
	Player(Vec2 pos, int w, int h);
	~Player();

	// self explanatory
	void Update(Input* input, std::vector<Bullet*>& bullets);
	void Hit() override;
	void Shoot(std::vector<Bullet*>& bullets) override;

	bool Collide(Vec2 point) override;
	bool Pickup(Vec2 point);

	void Respawn(Vec2 pos);

	// get borders for the player
	void Bind(Vec2 boundMin, Vec2 boundMax);

	void SetLives(int i) { lives = i; };
	int GetLives() { return lives; };

	bool Dead() { return dead; };

	void AddScore(int i) { score += i; };
	int GetScore() { return score; };
	
private:
	Vec2 bordersMax;
	Vec2 bordersMin;

	float timer;

	int maxHealth = 100;
	int lives;

	bool dead;

	int score;
};

#endif