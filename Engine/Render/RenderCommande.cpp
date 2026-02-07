//
// Created by sunvy on 05/01/2026.
//

#include "RenderCommande.h"

#include "Core/Application.h"
#include "Core/ApplicationSetting.h"

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace SunsetEngine
{
    void RenderCommande::BeginFrame()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void RenderCommande::EndFrame()
    {
        // ImGui::SetNextWindowPos(ImVec2(Application::GetSetting().WindowSize.x - 200, 0), ImGuiCond_Always);
        // ImGui::SetNextWindowSize(ImVec2(200, Application::GetSetting().WindowSize.y), ImGuiCond_Always);
        // ImGui::Begin("Log", nullptr);
        // for (std::vector<std::string>::iterator it = Log::begin(); it != Log::end(); ++it)
        // {
        //     ImGui::Text("%s", it->c_str());
        // }
        // ImGui::SetScrollHereY(1.0f);
        // ImGui::End();

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(static_cast<GLFWwindow*>(Application::GetWindow()));
    }

    void RenderCommande::SetWireframe(bool DrawWireframe)
    {
        if (DrawWireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    void RenderCommande::DrawCube()
    {
        glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 1);
    }
}
