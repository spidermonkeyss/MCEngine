#include "PlayerController.h"
#include "Renderer.h"
#include "TimeHandler.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include <iostream>

void ShowChunkInImGui(Chunk* chunk)
{
    std::string chunkPosStr = "Chunk:" + std::to_string(chunk->id) + chunk->chunkPos.ToString();
    if (ImGui::CollapsingHeader(chunkPosStr.c_str()))
    {
        ImGui::BeginGroup();
        ImGui::Indent();

        ImGui::Text(("isLoaded:" + (std::string)(chunk->isLoaded ? "true" : "false")).c_str());
        ImGui::Text(("isMarkedForUnload:" + (std::string)(chunk->isMarkedForUnload ? "true" : "false")).c_str());
        ImGui::Text(("isMarkedForUpdate:" + (std::string)(chunk->isMarkedForUpdate ? "true" : "false")).c_str());
        if (ImGui::CollapsingHeader(("Neighbor Chunks for:" + chunkPosStr).c_str()))
        {
            ImGui::BeginGroup();
            ImGui::Indent();
            for (int i = 0; i < 4; i++)
            {
                if (chunk->neighborChunks[i] != nullptr)
                    ImGui::Text(chunk->neighborChunks[i]->chunkPos.ToString().c_str());
                else
                    ImGui::Text("null");
            }
            ImGui::EndGroup();
        }
        if (ImGui::CollapsingHeader(("Blocks for:" + chunkPosStr).c_str()))
        {
            ImGui::BeginGroup();
            ImGui::Indent();
            for (int k = 0; k < Chunk::chunkSize; k++)
                ImGui::Text((std::to_string(chunk->blocks[k].blockId) + chunk->blocks[k].position.ToString()).c_str());
            ImGui::EndGroup();
        }
        ImGui::EndGroup();
    }
}

void RunImGuiFrame(ChunkHandler* chunkHandler)
{
    ImGui_ImplGlfwGL3_NewFrame();
    
    static bool demo = false;
    ImGui::ShowDemoWindow(&demo);
        
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
   
    ImGui::Text(("Loaded Chunks:" + std::to_string(chunkHandler->loadedChunks)).c_str());
    ImGui::Spacing();
    ImGui::Text("Chunks");
    for (int i = 0; i < chunkHandler->chunkBufferSize; i++)
        ShowChunkInImGui(&chunkHandler->chunks[i]);

    ImGui::Render();
    ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1600, 900, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
    GLCall(glEnable(GL_CULL_FACE));
    GLCall(glFrontFace(GL_CCW));
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    if (glewInit() != GLEW_OK)
        std::cout << "ERROR" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    std::cout << "Version: "  << glfwGetVersionString() << std::endl;

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, false);
    ImGui::StyleColorsDark();

    Input::window = window;

    Camera camera;
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = (float)width / (float)height;
        glViewport(0, 0, width, height);
        camera.aspectRatio = ratio;
        camera.transform.SetRotation(0, 180, 0);
        camera.transform.SetPosition(0, 70, 0);
    }
    camera.Init();

    Renderer renderer;

    BlockRegister::Init();
    std::cout << "Texture Count:" << Texture::debug_texture_count << std::endl;

    ChunkHandler chunkHandler;
    std::cout << "Chunk buffer:" << chunkHandler.chunkBufferSize << std::endl;

    PlayerController playerController;
    playerController.SetCamera(&camera);

    
    Block::blockShader->Bind();
    Block::blockShader->SetUniform1i("u_BlockTypeAmount", BlockRegister::blockRegister.size() - 1);
    Block::blockTextureAtlas->Bind(0);
    Block::blockShader->SetUniform1i("u_TextureAtlas", 0);

    TimeHandler::Init();


    while (!glfwWindowShouldClose(window))
    {
        TimeHandler::UpdateTime();
        Input::Update();
        playerController.Update();
        chunkHandler.Update(Vector2(camera.transform.position.x, camera.transform.position.z));

        renderer.Clear();
        renderer.Render(&camera, &chunkHandler);

        RunImGuiFrame(&chunkHandler);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}