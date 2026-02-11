//
// Created by sunvy on 05/01/2026.
//

#include "RenderCommande.h"

#include "Core/Application.h"
#include "Core/ApplicationSetting.h"
#include "Drawable.h"
#include "Mesh.h"
#include "Shader.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Material.h"

namespace
{
    struct FrameState
    {
        uint32_t drawCalls = 0;
        uint64_t triangleCount = 0;
    };

    FrameState m_FrameState;

    struct FrameData
    {
        glm::mat4 view;
        glm::mat4 projection;
    };

    struct DrawCommand
    {
        uint32_t vao;
        uint32_t indexCount;
        std::shared_ptr<SunsetEngine::Material> material;
        glm::vec3 position;
        SunsetEngine::RenderState state;
    };

    struct HeapTest
    {
        std::chrono::steady_clock::time_point start;
        const std::string name;
        explicit HeapTest(const std::string_view& _name)
            : name(_name)
        {
            start = std::chrono::steady_clock::now();
        }

        ~HeapTest()
        {
            const auto end = std::chrono::steady_clock::now();
            const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            PRINTSCREEN("{} : {}ms", name, duration.count());
        }
    };

    // to change from just a vector to a 2 vector.
    std::vector<DrawCommand> m_DrawCommands;

    FrameData m_FrameData;

    void FlushDrawCommand()
    {
        HeapTest t(std::format("FlushDrawCommand {}", m_DrawCommands.size()));

        // Sort cmd
        std::shared_ptr<SunsetEngine::Shader> currentShader = nullptr;
        std::shared_ptr<SunsetEngine::Material> currentMaterial = nullptr;
        GLuint currentVAO = 0;

        for (DrawCommand& cmd : m_DrawCommands)
        {
            // ApplyState
            if (currentShader != cmd.material->m_Shader)
            {
                currentShader = cmd.material->m_Shader;
                currentShader->Use();
                currentShader->SetMat4("view", m_FrameData.view);
                currentShader->SetMat4("projection", m_FrameData.projection);
            }

            if (currentMaterial != cmd.material)
            {
                currentMaterial = cmd.material;
                currentMaterial->Bind();
            }

            if (currentVAO != cmd.vao)
            {
                currentVAO = cmd.vao;
                glBindVertexArray(currentVAO);
            }

            cmd.material->m_Shader->SetVec3("location", cmd.position);

            // Todo : change the draw command cuz actually it's not compatible with my instance block.
            if (cmd.state.DrawInstance)
                glDrawArraysInstanced(GL_TRIANGLES, 0, 6, cmd.indexCount);
            else
                glDrawElements(GL_TRIANGLES, cmd.indexCount, GL_UNSIGNED_INT, nullptr);
        }

        m_DrawCommands.clear();
    }
}

namespace SunsetEngine
{
    void RenderCommande::BeginFrame()
    {
        m_FrameState = {};

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void RenderCommande::EndFrame()
    {
        if (!PrintScreen::Get().empty())
        {
            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
            ImGui::Begin("Stats", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
            for (const auto& it : PrintScreen::Get())
            {
                ImGui::Text("%s", it.c_str());
            }
            ImGui::End();
            PrintScreen::Clear();
        }

        FlushDrawCommand();

        PRINTSCREEN("Nbr vertice count {}", m_FrameState.triangleCount);

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(static_cast<GLFWwindow*>(Application::GetWindow()));
    }

    void RenderCommande::Submit(const SunsetEngine::Drawable& drawable)
    {
        DrawCommand cmd;
        cmd.vao = drawable.m_Mesh->GetVAO();
        cmd.indexCount = drawable.m_Mesh->GetVertexCount();
        m_FrameState.triangleCount += cmd.indexCount * 6;
        cmd.material = drawable.m_Material;
        cmd.position = drawable.m_Position;
        cmd.state = drawable.m_RenderState;
        m_DrawCommands.emplace_back(cmd);
    }

    void RenderCommande::UseCamera(const SunsetEngine::Camera& camera)
    {
        m_FrameData.view = camera.GetViewMatrix();
        m_FrameData.projection = camera.GetProjection();
    }
}
