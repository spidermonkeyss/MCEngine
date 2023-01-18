#include "Vector2.h"

const float Vector2::equivalenceDifference = 0.00005f;

Vector2::Vector2()
	: x(0), y(0)
{
}

Vector2::Vector2(float x, float y)
	: x(x), y(y)
{
}

Vector2::~Vector2()
{
}

void Vector2::SetVector(float _x, float _y)
{
	x = _x;
	y = _y;
}

void Vector2::SetMagnitude(float mag)
{
	Vector2 vec = Normal() * mag;

	x = vec.x;
	y = vec.y;
}

float Vector2::Magnitude()
{
	return sqrtf(x * x + y * y);
}

Vector2 Vector2::Normal()
{
	float mag = Magnitude();
	if (mag == 0)
		return Vector2(0, 0);
	return Vector2(x / mag, y / mag);
}

float Vector2::Distance(Vector2 a, Vector2 b)
{
	return (a - b).Magnitude();
}

Vector2 Vector2::operator*(float num)
{
	return Vector2(x * num, y * num);
}

Vector2 Vector2::operator/(float num)
{
	return Vector2(x / num, y / num);
}

Vector2 Vector2::operator+(Vector2 vec)
{
	return Vector2(x + vec.x, y + vec.y);
}

Vector2 Vector2::operator-(Vector2 vec)
{
	return Vector2(x - vec.x, y - vec.y);
}

bool Vector2::operator==(Vector2 vec)
{
	float xDiff = abs(x - vec.x);
	float yDiff = abs(y - vec.y);

	if (xDiff <= equivalenceDifference && yDiff <= equivalenceDifference)
		return true;
	else
		return false;
}

bool Vector2::operator!=(Vector2 vec)
{
	float xDiff = abs(x - vec.x);
	float yDiff = abs(y - vec.y);

	if (xDiff <= equivalenceDifference && yDiff <= equivalenceDifference)
		return false;
	else
		return true;
}

void Vector2::operator=(Vector2 vec)
{
	x = vec.x;
	y = vec.y;
}

std::string Vector2::ToString()
{
	std::string str = "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
	return str;
}