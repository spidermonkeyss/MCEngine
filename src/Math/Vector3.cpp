#include "Vector3.h"
#include "Constants.h"

#include <math.h>

const float Vector3::equivalenceDifference = 0.00005f;

Vector3::Vector3()
	: x(0), y(0), z(0)
{
}

Vector3::Vector3(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

Vector3::~Vector3()
{
}

void Vector3::SetVector(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

void Vector3::SetMagnitude(float mag)
{
	Vector3 vec = Normal() * mag;

	x = vec.x;
	y = vec.y;
	z = vec.z;
}

float Vector3::Magnitude()
{
	return sqrtf(x * x + y * y + z * z);
}

Vector3 Vector3::Normal()
{
	float mag = Magnitude();
	if (mag == 0)
		return Vector3(0, 0, 0);
	return Vector3(x / mag, y / mag, z / mag);
}

float Vector3::Dot(Vector3 a, Vector3 b)
{
	float dot = (a.Magnitude() * b.Magnitude()) * cos(AngleRadians(a,b));
	return dot;
}

float Vector3::AngleRadians(Vector3 a, Vector3 b)
{
	float dot = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	float theta = acosf(dot / (a.Magnitude() * b.Magnitude()));
	
	return theta;
}

float Vector3::AngleDegrees(Vector3 a, Vector3 b)
{
	float theta = AngleRadians(a, b) * (180 / MathConstants::PI);

	return theta;
}

Vector3 Vector3::Cross(Vector3 a, Vector3 b)
{
	//(bz – cy) + (cx – az) + (ay – bx)
	//A = a + b + c
	//B = x + y + z
	
	float x = (a.y * b.z - a.z * b.y);
	float y = (a.z * b.x - a.x * b.z);
	float z = (a.x * b.y - a.y * b.x);

	return Vector3(x,y,z);
}

float Vector3::Distance(Vector3 a, Vector3 b)
{
	return (a - b).Magnitude();
}

Vector3 Vector3::Lerp(Vector3 a, Vector3 b, float t)
{
	return a + (b - a) * t;
}

Vector3 Vector3::Up()
{
	return Vector3(0, 1, 0);
}

Vector3 Vector3::Right()
{
	return Vector3(1, 0, 0);
}

Vector3 Vector3::Forward()
{
	return Vector3(0, 0, -1);
}

Vector3 Vector3::operator*(float num)
{
	return Vector3(x * num, y * num, z * num);
}

Vector3 Vector3::operator/(float num)
{
	return Vector3(x / num, y / num, z / num);
}

Vector3 Vector3::operator+(Vector3 vec)
{
	return Vector3(x + vec.x, y + vec.y, z + vec.z);
}

Vector3 Vector3::operator-(Vector3 vec)
{
	return Vector3(x - vec.x, y - vec.y, z - vec.z);
}

bool Vector3::operator==(Vector3 vec)
{
	float xDiff = abs(x - vec.x);
	float yDiff = abs(y - vec.y);
	float zDiff = abs(z - vec.z);
	
	if (xDiff <= equivalenceDifference && yDiff <= equivalenceDifference && zDiff <= equivalenceDifference)
		return true;
	else
		return false;
}

bool Vector3::operator!=(Vector3 vec)
{
	float xDiff = abs(x - vec.x);
	float yDiff = abs(y - vec.y);
	float zDiff = abs(z - vec.z);

	if (xDiff <= equivalenceDifference && yDiff <= equivalenceDifference && zDiff <= equivalenceDifference)
		return false;
	else
		return true;
}

void Vector3::operator=(Vector3 vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

std::string Vector3::ToString()
{
	std::string str = "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
	return str;
}
