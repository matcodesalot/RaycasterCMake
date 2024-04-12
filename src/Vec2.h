#pragma once

class Vec2
{
public:
	float x = 0.0f;
	float y = 0.0f;

	Vec2();
	Vec2(float x, float y);

	void print() const;

	Vec2& add(const Vec2& vec);
	Vec2& subtract(const Vec2& vec);
	Vec2& multiply(const float amount);
	Vec2& divide(const float amount);

	Vec2 operator + (const Vec2& vec) const;
	Vec2 operator - (const Vec2& vec) const;
	Vec2 operator * (const float amount) const;
	Vec2 operator / (const float amount) const;

	void operator += (const Vec2& vec);
	void operator -= (const Vec2& vec);
	void operator *= (const float amount);
	void operator /= (const float amount);

	bool operator == (const Vec2& vec) const;
	bool operator != (const Vec2& vec) const;

	Vec2& scale(const float amount);
	float length() const;
	float dist(const Vec2& vec) const;
	void normalize();
};