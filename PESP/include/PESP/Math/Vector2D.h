#pragma once
#include <PESP/Prerequisites.h>

struct Vector2D
{
public:
	Vector2D() :x(0), y(0)
	{
	}
	Vector2D(f32 x, f32 y) :x(x), y(y)
	{
	}
	Vector2D(const Vector2D& vector) :x(vector.x), y(vector.y)
	{
	}

	static Vector2D lerp(const Vector2D& start, const Vector2D& end, f32 delta)
	{
		Vector2D v;
		v.x = start.x * (1.0f - delta) + end.x * (delta);
		v.y = start.y * (1.0f - delta) + end.y * (delta);
		return v;
	}

	Vector2D operator *(f32 num) const
	{
		return Vector2D(x * num, y * num);
	}
	Vector2D operator +(Vector2D vec) const
	{
		return Vector2D(x + vec.x, y + vec.y);
	}
	Vector2D operator -(Vector2D vec) const
	{
		return Vector2D(x - vec.x, y - vec.y);
	}
	~Vector2D()
	{
	}
public:
	f32 x, y;
};