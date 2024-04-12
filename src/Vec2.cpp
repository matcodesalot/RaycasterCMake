#include <iostream>
#include <math.h>
#include "Vec2.h"


Vec2::Vec2() {}

Vec2::Vec2(float x, float y)
{
	this->x = x;
	this->y = y;
}

//same thing ^
//Vec2::Vec2(float x, float y)
//	: x(x)
//	, y(y)
//	{ 
//	}

void Vec2::print() const
{
	std::cout << "x: " << x << ", y: " << y << std::endl;
}

Vec2& Vec2::add(const Vec2& vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

Vec2& Vec2::subtract(const Vec2& vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

Vec2& Vec2::multiply(const float amount)
{
	x *= amount;
	y *= amount;
	return *this;
}

Vec2& Vec2::divide(const float amount)
{
	if (amount != 0.0f)
	{
		x /= amount;
		y /= amount;
	}
	else
	{
		std::cerr << "Error: Division by zero!" << std::endl;
	}
	return *this;
}

Vec2 Vec2::operator + (const Vec2& vec) const
{
	return Vec2(x + vec.x, y + vec.y);
}

Vec2 Vec2::operator - (const Vec2& vec) const
{
	return Vec2(x - vec.x, y - vec.y);
}

Vec2 Vec2::operator * (const float amount) const
{
	return Vec2(x * amount, y * amount);
}

Vec2 Vec2::operator / (const float amount) const
{
	if (amount != 0.0f)
	{
		return Vec2(x / amount, y / amount);
	}
	else
	{
		std::cerr << "Error: Division by zero!" << std::endl;
		return *this;
	}
}

void Vec2::operator += (const Vec2& vec)
{
	x += vec.x;
	y += vec.y;
}

void Vec2::operator -= (const Vec2& vec)
{
	x -= vec.x;
	y -= vec.y;
}

void Vec2::operator *= (const float amount)
{
	x *= amount;
	y *= amount;
}

void Vec2::operator /= (const float amount)
{
	if (amount != 0.0f)
	{
		x /= amount;
		y /= amount;
	}
	else
	{
		std::cerr << "Error: Division by zero!" << std::endl;
	}
}

bool Vec2::operator == (const Vec2& vec) const
{
	return (x == vec.x) && (y == vec.y);
}

bool Vec2::operator != (const Vec2& vec) const
{
	return (x != vec.x) || (y != vec.y);
}

Vec2& Vec2::scale(const float amount)
{
	return multiply(amount);
}

float Vec2::length() const
{
	return sqrtf((x * x) + (y * y));
}

float Vec2::dist(const Vec2& vec) const
{
	float dx = vec.x - x;
	float dy = vec.y - y;
	return sqrtf((dx * dx) + (dy * dy));
}

void Vec2::normalize()
{
	float len = length();

	if (len != 0.0f)
	{
		x /= len;
		y /= len;
	}
}