#pragma once

#include <string>

class Vector2
{
private:
	static const float equivalenceDifference;
public:
	float x, y;

	Vector2();
	Vector2(float x, float y);
	~Vector2();

	void SetVector(float x, float y);
	void SetMagnitude(float mag);

	float Magnitude();
	Vector2 Normal();

	//static float Dot(Vector3 a, Vector3 b);
	//static float AngleRadians(Vector3 a, Vector3 b);
	//static float AngleDegrees(Vector3 a, Vector3 b);
	//static Vector3 Cross(Vector3 a, Vector3 b);
	static float Distance(Vector2 a, Vector2 b);
	//static Vector3 Lerp(Vector3 a, Vector3 b, float t);

	//static Vector3 Up();
	//static Vector3 Right();
	//static Vector3 Forward();

	Vector2 operator*(float num);
	Vector2 operator/(float num);
	Vector2 operator+(Vector2 vec);
	Vector2 operator-(Vector2 vec);
	bool operator==(Vector2 vec);
	bool operator!=(Vector2 vec);
	void operator=(Vector2 vec);

	std::string ToString();
};
