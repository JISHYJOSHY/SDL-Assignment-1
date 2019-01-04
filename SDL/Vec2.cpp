#include "Vec2.h"

// uhhh..... lots of setting up and using Vev2 stuff
Vec2::Vec2()
{
}


Vec2::~Vec2()
{
}

Vec2::Vec2(int a, int b)
{
	x = a;
	y = b;
}

Vec2::Vec2(float a, float b)
{
	x = a;
	y = b;
}

Vec2::Vec2(float a, int b)
{
	x = a;
	y = b;
}

Vec2::Vec2(int a, float b)
{
	x = a;
	y = b;
}

void Vec2::normalize()
{
	float n = magnitude();
	x /= n;
	y /= n;
}

float Vec2::magnitude()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

Vec2 Vec2::operator*=(float other)
{
	return Vec2(x *= other, y *= other);
}

Vec2 Vec2::operator/=(float other)
{
	return Vec2(x /= other, y /= other);
}

Vec2 Vec2::operator+=(Vec2 other)
{
	return Vec2(x += other.x, y += other.y);
}

Vec2 Vec2::operator-=(Vec2 other)
{
	return Vec2(x -= other.x, y -= other.x);
}

Vec2 Vec2::operator*(float other)
{
	return Vec2(x * other, y * other);
}

Vec2 Vec2::operator*(int other)
{
	return Vec2(x * other, y * other);
}

Vec2 Vec2::operator/(float other)
{
	return Vec2(x / other, y / other);
}

Vec2 Vec2::operator/(int other)
{
	return Vec2(x / other, y / other);
}

Vec2 Vec2::operator+(Vec2 other)
{
	return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(Vec2 other)
{
	return Vec2(x - other.x, y - other.y);
}