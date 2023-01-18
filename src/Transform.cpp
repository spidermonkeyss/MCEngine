#include "Transform.h"

#include "glm/gtc/matrix_transform.hpp"

Transform::Transform()
	: position(Vector3(0, 0, 0)), rotation(Vector3(0, 0, 0)), scale(Vector3(1,1,1))
{
}

Transform::~Transform()
{
}

void Transform::SetPosition(Vector3 pos)
{
	position = pos;
}

void Transform::SetPosition(float x, float y, float z)
{
	position.SetVector(x, y, z);
}

void Transform::SetRotation(Vector3 rot)
{
	rotation = rot;
}

void Transform::SetRotation(float x, float y, float z)
{
	rotation.SetVector(x, y, z);
}

void Transform::SetScale(Vector3 setScale)
{
	scale = setScale;
}

void Transform::SetScale(float x, float y, float z)
{
	scale.SetVector(x, y, z);
}

Vector3 Transform::Forward()
{
	//https://stackoverflow.com/questions/14607640/rotating-a-vector-in-3d-space

	//YXZ Rotation
	/*
	Vector3 yRotation;
	float theta = glm::radians(rotation.y);
	yRotation.x = 0 * cos(theta) + -1 * sin(theta);
	yRotation.y = 0;
	yRotation.z = -0 * sin(theta) + -1 * cos(theta);
	yRotation = yRotation.Normal();
	
	Vector3 yxRotation;
	theta = glm::radians(rotation.x);
	yxRotation.x = yRotation.x;
	yxRotation.y = yRotation.y * cos(theta) - yRotation.z * sin(theta);
	yxRotation.z = yRotation.y * sin(theta) + yRotation.z * cos(theta);
	yxRotation = yxRotation.Normal();
	
	Vector3 yxzRotation;
	theta = glm::radians(rotation.z);
	yxzRotation.x = yxRotation.x * cos(theta) - yxRotation.y * sin(theta);
	yxzRotation.y = yxRotation.x * sin(theta) + yxRotation.y * cos(theta);
	yxzRotation.z = yxRotation.z;
	yxzRotation = yxzRotation.Normal();
	*/
	
	Vector3 yRotation;
	float theta = glm::radians(rotation.y);
	yRotation.x = -sin(theta);
	yRotation.y = 0;
	yRotation.z = -cos(theta);
	yRotation = yRotation.Normal();

	Vector3 yxRotation;
	theta = glm::radians(rotation.x);
	yxRotation.x = yRotation.x;
	yxRotation.z = yRotation.z;
	float y = sin(theta);
	float x = cos(theta);
	float magnitudeRatio = 1.0f / x;
	yxRotation.y = y * magnitudeRatio;
	yxRotation = yxRotation.Normal();
	
	return yxRotation;
}

Vector3 Transform::Right()
{
	return Vector3::Cross(Forward(), Up()).Normal();
}

Vector3 Transform::Up()
{
	return Vector3::Up();
}

glm::mat4 Transform::GetTransformMatrix()
{
	glm::mat4 positionMat4 = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));
	glm::mat4 scaleMat4 = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, scale.z));

	//YXZ Gimbol
	glm::mat4 rotationMat4 = glm::mat4(1.0f);
	rotationMat4 = glm::rotate(rotationMat4, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	rotationMat4 = glm::rotate(rotationMat4, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	rotationMat4 = glm::rotate(rotationMat4, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	
	glm::mat4 transformMatrix = positionMat4 * rotationMat4 * scaleMat4;
	return transformMatrix;
}