#include "Player.h"

// take in a position, width and height
Player::Player(Vec2 pos, int w, int h)
{
	// initialise variables
	this->pos = pos;
	this->w = w;
	this->h = h;
	fireTimer = 0;
	this->health = maxHealth;
	lives = 3;
	dead = false;
	this->destroy = false;
	score = 0;
}

Player::~Player()
{
}

void Player::Update(Input* input, std::vector<Bullet*>& bullets)
{
	canShoot = false;

	// move player
	if (input->up)
		pos.y -= speed;
	if (input->down)
		pos.y += speed;
	if (input->left)
		pos.x -= speed;
	if (input->right)
		pos.x += speed;

	// increment fireTimer based on firerate
	fireTimer += fireRate;

	// if fireTimer is greater than specified number, player canshoot
	if (fireTimer > 35)
		canShoot = true;

	// if the player can shoot and presses space, shoot
	if (input->space)
	{
		if (canShoot)
			Shoot(bullets);
	}

	// keep the player on screen
	if (pos.x < bordersMin.x)
		pos.x += (bordersMin.x - pos.x);
	else if (pos.x + this->w > bordersMax.x)
		pos.x -= ((pos.x + this->w) - bordersMax.x);

	if (pos.y < bordersMin.y)
		pos.y += (bordersMin.y - pos.y);
	else if (pos.y + this->h > bordersMax.y)
		pos.y -= ((pos.y + this->h) - bordersMax.y);

	// keep the players health within range (max health and 0)
	if (this->health > maxHealth)
		this->health = maxHealth;
	else if (health <= 0 && !dead || this->destroy)
	{
		health = 0;
		this->pos = Vec2(-100, -100);
		dead = true;
	}

	if (lives > 10)
	{
		lives = 10;
	}
}

// smaller collision box because lots of bullets makes it hard to not die
bool Player::Collide(Vec2 point)
{
	if (point.x > this->pos.x + 10 && point.x < this->pos.x + w - 10
		&& point.y > this->pos.y + 5 && point.y < this->pos.y + h - 5)
		return true;

	return false;
}

void Player::Shoot(std::vector<Bullet*>& bullets)
{
	// depending on the players power level (based on firerate), spawn different patterns of bullets
	switch ((int)fireRate)
	{
	case 6:
		bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), Vec2(bordersMax.x, bordersMax.y), Vec2(0, -1), true, 1));
		break;
	case 7:
		bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center() + Vec2(3, 0), Vec2(bordersMax.x, bordersMax.y), Vec2(0, -1), true, 1));
		bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center() + Vec2(-3, 0), Vec2(bordersMax.x, bordersMax.y), Vec2(0, -1), true, 1));
		break;
	case 8:
		bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), Vec2(bordersMax.x, bordersMax.y), Vec2(0.2f, -1), true, 1));
		bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), Vec2(bordersMax.x, bordersMax.y), Vec2(0, -1), true, 1));
		bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), Vec2(bordersMax.x, bordersMax.y), Vec2(-0.2f, -1), true, 1));
		break;
	case 9:
		bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), Vec2(bordersMax.x, bordersMax.y), Vec2(0.25f, -1), true, 1));
		bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), Vec2(bordersMax.x, bordersMax.y), Vec2(0.05f, -1.1f), true, 1));
		bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), Vec2(bordersMax.x, bordersMax.y), Vec2(-0.05f, -1.1f), true, 1));
		bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), Vec2(bordersMax.x, bordersMax.y), Vec2(-0.25f, -1), true, 1));
		break;
	case 10:
	default:
		bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), Vec2(bordersMax.x, bordersMax.y), Vec2(0.25f, -1), true, 1));
		bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), Vec2(bordersMax.x, bordersMax.y), Vec2(0.05f, -1.1f), true, 1));
		bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), Vec2(bordersMax.x, bordersMax.y), Vec2(-0.05f, -1.1f), true, 1));
		bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), Vec2(bordersMax.x, bordersMax.y), Vec2(-0.25f, -1), true, 1));
		bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), Vec2(bordersMax.x, bordersMax.y), Vec2(-0.5f, -0.8f), true, 1));
		bullets.push_back(new Bullet(bulletTemplate.GetWidth(), bulletTemplate.GetHeight(), Center(), Vec2(bordersMax.x, bordersMax.y), Vec2(0.5f, -0.8f), true, 1));
		break;
	}

	// then reset the players shooting state
	ResetShot();
}

// because collision is made smaller for bullets, use base values for collision with pickups
bool Player::Pickup(Vec2 point)
{
	if (point.x > this->pos.x && point.x < this->pos.x + w
		&& point.y > this->pos.y && point.y < this->pos.y + h)
		return true;

	return false;
}

// respawn the player if function is called
void Player::Respawn(Vec2 pos)
{
	this->pos = pos;
	this->health = maxHealth;
	dead = false;
	this->destroy = false;
	lives--;
}

// set the player boundaries
void Player::Bind(Vec2 boundMin, Vec2 boundMax)
{
	bordersMin = boundMin;
	bordersMax = boundMax;
}

// deplete health
void Player::Hit()
{
	health -= 8;
}