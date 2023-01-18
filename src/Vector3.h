#pragma once

#include <string>

class Vector3
{
private:
	static const float equivalenceDifference;
public:
	float x, y, z;
	
	Vector3();
	Vector3(float x, float y, float z);
	~Vector3();
	
	void SetVector(float x, float y, float z);
	void SetMagnitude(float mag);

	float Magnitude();
	Vector3 Normal();

	static float Dot(Vector3 a, Vector3 b);
	static float AngleRadians(Vector3 a, Vector3 b);
	static float AngleDegrees(Vector3 a, Vector3 b);
	static Vector3 Cross(Vector3 a, Vector3 b);
	static float Distance(Vector3 a, Vector3 b);
	static Vector3 Lerp(Vector3 a, Vector3 b, float t);

	static Vector3 Up();
	static Vector3 Right();
	static Vector3 Forward();

	Vector3 operator*(float num);
	Vector3 operator/(float num);
	Vector3 operator+(Vector3 vec);
	Vector3 operator-(Vector3 vec);
	bool operator==(Vector3 vec);
	bool operator!=(Vector3 vec);
	void operator=(Vector3 vec);

	std::string ToString();
};
