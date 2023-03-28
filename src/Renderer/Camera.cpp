#include "Camera.h"
#include "Input.h"
#include "GLCall.h"

Camera::Camera()
	:aspectRatio(0), widthView(0)
{

    float ratio;
    int width, height;
    glfwGetFramebufferSize(Input::window, &width, &height);
    ratio = (float)width / (float)height;
    glViewport(0, 0, width, height);
    aspectRatio = ratio;

    //proj = glm::ortho(-camera->GetWidthView(), camera->GetWidthView(), -camera->GetWidthView() / camera->GetAspectRatio(), camera->GetWidthView() / camera->GetAspectRatio(), -1.0f, 1.0f);
    proj = glm::perspective(45.0f, aspectRatio, 0.3f, 150.0f);
}

Camera::~Camera()
{

}