#include "Camera.h"

Camera::Camera()
	:transform(Transform()), aspectRatio(0), widthView(0)
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
	//proj = glm::ortho(-camera->GetWidthView(), camera->GetWidthView(), -camera->GetWidthView() / camera->GetAspectRatio(), camera->GetWidthView() / camera->GetAspectRatio(), -1.0f, 1.0f);
	proj = glm::perspective(45.0f, aspectRatio, 0.3f, 150.0f);
}
