//
// Created by sunvy on 15/12/2025.
//

#include "Renderer.h"

#include "Core/Application.h"
#include "Core/ApplicationSetting.h"

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"

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
        LOG("Render Create")
        const ApplicationSetting& setting = Application::GetSetting();
        m_Window = CreateWindow(setting);
        if (m_Window == NULL)
        {
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(m_Window);

        glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

        // glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            throw std::runtime_error("Failed to initialize GLAD");
        }

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    Renderer::~Renderer()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

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

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void Renderer::EndFrame()
    {
        if (!Hud::IsEmpty())
        {
            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
            ImGui::Begin("Stats", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
            for (std::vector<std::string>::iterator it = Hud::begin(); it != Hud::end(); ++it)
            {
                ImGui::Text("%s", it->c_str());
            }
            ImGui::End();
            Hud::Clear();
        }

        ImGui::SetNextWindowPos(ImVec2(0, Application::GetSetting().WindowSize.y - 150), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(Application::GetSetting().WindowSize.x, 150), ImGuiCond_Always);
        ImGui::Begin("Log", nullptr);
        for (std::vector<std::string>::iterator it = Logger::begin(); it != Logger::end(); ++it)
        {
             ImGui::Text("%s", it->c_str());
        }
        ImGui::SetScrollHereY(1.0f);
        ImGui::End();

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    void* Renderer::Get()
    {
        return m_Window;
    }
}
