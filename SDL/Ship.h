#ifndef __ship
#define __ship

#include <cstdlib>
#include <math.h>
#include <vector>

#include "Vec2.h"
#include "Input.h"
#include "Bullet.h"

// the master class for all ships to derive from
class Ship
{
public:
	Ship();
	~Ship();

	virtual void Update(std::vector<Bullet*>& bullets) {};

	// LOTS of getters and setters for variables
	inline Vec2 GetPos() {	return this->pos; };
	inline void SetPos(Vec2 a) { this->pos = a; };
	inline Vec2 Center() { return Vec2(this->pos.x + (this->w / 2), this->pos.y + (this->h / 2)); }

	void SetBullet(Bullet bullet) { bulletTemplate = bullet; };
	void SetLaser(Bullet bullet) { laserTemplate = bullet; };

	inline virtual void DisableShot() { shotCheck = false; };

	virtual bool Collide(Vec2 point);
	virtual void Shoot(std::vector<Bullet*>& bullets);

	inline float GetSpeed() { return speed; };
	inline void SetSpeed(float f) { speed = f; };

	inline int GetFireRate() { return (int)fireRate; };
	inline void SetFireRate(int i) { fireRate = (float)i; };
	inline int GetHealth() { return health; };
	inline void SetHealth(int i) { health = i; };

	inline int GetType() { return type; };
	int extras;

	void ResetShot();

	inline bool Destroy() { return destroy; };
	virtual void Hit();
	void Kill();

protected:
	// stuff that the derived classes should access, but not the game itself
	void CheckHealth() { if (health <= 0) destroy = true; };
	Vec2 pos;

	Bullet bulletTemplate;
	Bullet laserTemplate;

	float speed;
	int damage;

	float fireRate = 100;
	float fireTimer;

	int health = 100;

	bool destroy;
	bool canShoot;

	bool shotCheck;

	int type;

	int w;
	int h;
};

#endif