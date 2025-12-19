//
// Created by sunvy on 15/12/2025.
//

#include "Renderer.h"

#include "Core/Application.h"
#include "Core/ApplicationSetting.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace
{
    GLFWwindow* m_Window = nullptr;

    GLFWwindow* CreateWindow(const SunsetEngine::ApplicationSetting& setting)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        return glfwCreateWindow(setting.WindowSize.x, setting.WindowSize.y, setting.WindowTitle.data(), NULL, NULL);
    }

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
        SunsetEngine::Application::ResizeWindow({width, height});
    }
}

namespace SunsetEngine
{
    Renderer::Renderer()
    {
        const ApplicationSetting& setting = Application::GetSetting();
        m_Window = CreateWindow(setting);
        if (m_Window == NULL)
        {
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(m_Window);

        glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

        //glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            throw std::runtime_error("Failed to initialize GLAD");
        }

        glEnable(GL_DEPTH_TEST);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    Renderer::~Renderer()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    bool Renderer::Valid() const
    {
        return !glfwWindowShouldClose(m_Window);
    }

    void Renderer::BeginFrame()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::EndFrame()
    {
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    void* Renderer::Get()
    {
        return m_Window;
    }
}
