//
// Created by sunvy on 05/01/2026.
//

#include "RenderCommande.h"

#include "Core/Application.h"
#include "Core/ApplicationSetting.h"
#include "Buffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"

namespace SunsetEngine
{
    void RenderCommande::BeginFrame()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void RenderCommande::EndFrame()
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

        ImGui::SetNextWindowPos(ImVec2(Application::GetSetting().WindowSize.x - 200, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(200, Application::GetSetting().WindowSize.y), ImGuiCond_Always);
        ImGui::Begin("Log", nullptr);
        for (std::vector<std::string>::iterator it = Logger::begin(); it != Logger::end(); ++it)
        {
            ImGui::Text("%s", it->c_str());
        }
        ImGui::SetScrollHereY(1.0f);
        ImGui::End();

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(static_cast<GLFWwindow *>(Renderer::Get()));
        glfwPollEvents();
    }

    template <typename T>
    void RenderCommande::FunctorHelper<T>::Submit(const std::shared_ptr<VertexArray<T>>& obj)
    {
        for (const auto& [vertexBuffer, IndexBuffer] : *obj)
        {
            if (IndexBuffer)
                glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(IndexBuffer->GetCount()), GL_UNSIGNED_INT, nullptr);
            else
                glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertexBuffer->GetSize()));
        }
    }

    template <typename T>
    void RenderCommande::FunctorHelper<T>::SubmitInstance(const std::shared_ptr<VertexArray<T>>& obj, size_t nbrInstance)
    {
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);

        obj->Bind();

        for (const auto& [vertexBuffer, IndexBuffer] : *obj)
        {
            HUD("Chunk size {}", vertexBuffer->GetSize())
            glDrawArraysInstanced(GL_TRIANGLES, 0, static_cast<GLsizei>(nbrInstance), static_cast<GLsizei>(vertexBuffer->GetSize()));
        }
    };

    template struct RenderCommande::FunctorHelper<float>;
    template struct RenderCommande::FunctorHelper<uint32_t>;

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
