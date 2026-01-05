//
// Created by sunvy on 16/12/2025.
//

#include "CameraLayer.h"

#include "Chunk/Chunk.h"
#include "Core/Input.h"
#include "Render/Camera.h"
#include "Render/Render.h"
#include "Render/Shader.h"
#include "World/CraftScene.h"
#include "World/RaycastHit.h"

#include <GLFW/glfw3.h>

namespace
{
    float yaw = -90.f;
    float pitch = 0.f;

    SunsetEngine::Shader* m_Shader = nullptr;

    void ProcessInput(SunsetEngine::Camera& camera, const float dt)
    {
        const float cameraSpeed = 10.f * dt;
        if (SunsetEngine::Input::IsKeyPress('W'))
            camera.AddPosition(cameraSpeed * camera.GetForward());
        if (SunsetEngine::Input::IsKeyPress('S'))
            camera.AddPosition(-(cameraSpeed * camera.GetForward()));
        if (SunsetEngine::Input::IsKeyPress('A'))
            camera.AddPosition(-(glm::normalize(glm::cross(camera.GetForward(), camera.GetUp())) * cameraSpeed));
        if (SunsetEngine::Input::IsKeyPress('D'))
            camera.AddPosition(glm::normalize(glm::cross(camera.GetForward(), camera.GetUp())) * cameraSpeed);
        if (SunsetEngine::Input::IsKeyPress('Q'))
            camera.AddPosition(-cameraSpeed * camera.GetUp());
        if (SunsetEngine::Input::IsKeyPress('E'))
            camera.AddPosition(cameraSpeed * camera.GetUp());

        glm::vec2 offset = SunsetEngine::Input::GetMousePosition();

        float sensitivity = 0.1f; // change this value to your liking
        offset.x *= sensitivity;
        offset.y *= sensitivity;

        yaw += offset.x;
        pitch -= offset.y;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camera.SetForward(glm::normalize(front));
    }
}


CameraLayer::CameraLayer(SunsetEngine::Scene* scene)
    : SunsetEngine::Layer(scene)
{
}

CameraLayer::~CameraLayer()
{
    delete m_Shader;
}

void CameraLayer::OnAttach()
{
    m_Shader = new SunsetEngine::Shader("SunsetCraft/Shaders/CubeOutline.vert", "SunsetCraft/Shaders/CubeOutline.frag");
}

void CameraLayer::OnUpdate(float dt)
{
    if (CraftScene* scene = static_cast<CraftScene*>(GetScene()))
    {
        ProcessInput(scene->m_Camera, dt);

        RaycastHit hit;
        glm::vec3 dir = scene->m_Camera.GetForward() * 2.f;
        HUD("Dir : {}", dir);
        glm::vec3 blockPos = scene->m_Camera.GetPosition() + dir;
        HUD("Blockpos : {}", blockPos);
        glm::ivec3 targetPos = glm::floor(blockPos);
        HUD("Target : {}", targetPos);
        //scene->LineTrace(hit , scene->m_Camera.GetPosition(), scene->m_Camera.GetForward(), 10.f);
        Chunk* c = scene->m_Chunks.GetChunks(targetPos);

        if (c != nullptr)
        {
            if (SunsetEngine::Input::IsMouseButtonClick(GLFW_MOUSE_BUTTON_1))
                c->SetBlockId(targetPos, BlockId::Dirt);
            else if (SunsetEngine::Input::IsMouseButtonClick(GLFW_MOUSE_BUTTON_2))
                c->SetBlockId(targetPos, BlockId::Air);

            m_Shader->Use();
            m_Shader->SetVec3("BlockLocation", targetPos);
            m_Shader->SetMat4("view", scene->m_Camera.GetViewMatrix());
            m_Shader->SetMat4("projection", scene->m_Camera.GetProjection());
            SunsetEngine::Render::SetWireframe(true);
            SunsetEngine::Render::DrawCube();
            SunsetEngine::Render::SetWireframe(false);
        }
    }
}

void CameraLayer::OnDraw()
{
}
