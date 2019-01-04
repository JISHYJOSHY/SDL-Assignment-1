#ifndef __vec2
#define __vec2

// could be a structure, but a class just to keep other classes more clean
#include <math.h>

class Vec2
{
public:
	Vec2();
	~Vec2();

	// different ways to create a Vec2
	Vec2(int a, int b);
	Vec2(float a, float b);
	Vec2(float a, int b);
	Vec2(int a, float b);
	
	// Vec2 functions
	void normalize();
	float magnitude();

	// operator overloads
	Vec2 operator*=(float other);
	Vec2 operator/=(float other);
	Vec2 operator+=(Vec2 other);
	Vec2 operator-=(Vec2 other);
	Vec2 operator*(float other);
	Vec2 operator*(int other);
	Vec2 operator/(float other);
	Vec2 operator/(int other);
	Vec2 operator+(Vec2 other);
	Vec2 operator-(Vec2 other);

	float x, y;
};

#endif