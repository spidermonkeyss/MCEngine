#include "UI.h"
#include "Input.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

UI::UI()
{
	std::unique_ptr<Shader> shader(new Shader(shaderFilePath, false));
    std::unique_ptr<Texture> texture(new Texture(textureFilePath, 0));

	uiShader = std::move(shader);
    uiTexture = std::move(texture);

    int width, height;
    glfwGetFramebufferSize(Input::window, &width, &height);
    proj = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
    //proj = glm::ortho(0.0f, 2.0f, 2.0f, 0.0f, -1.0f, 1.0f);

    float left = (float)width / 3.0f;
    float right = left + left;
    float bot = 0.0f;
    float top = ((float)height / 10);

    float vertices[16] =
    {
        left, bot, 0.0f ,0.0f,
        left, top, 0.0f, 1.0f,
        right, top, 1.0f, 1.0f,
        right, bot, 1.0f, 0.0f
    };

    unsigned int indices[6] =
    {
        0,1,2,
        2,3,0
    };

    vertexBuffer.GenBuffer(vertices, 16 * sizeof(float));
    layout.Push<float>(2);//position coords
    layout.Push<float>(2);//texture coords
    vertexArray.AddBuffer(vertexBuffer, layout);
    indexBuffer.BufferData(indices, 6);
}
