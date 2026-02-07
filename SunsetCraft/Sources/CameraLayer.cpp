//
// Created by sunvy on 16/12/2025.
//

#include "CameraLayer.h"

#include "Chunk/Chunk.h"
#include "Core/Input.h"
#include "Render/Camera.h"
#include "Render/RenderCommande.h"
#include "Render/Shader.h"
#include "World/CraftScene.h"
#include "World/RaycastHit.h"

#include "Core/Application.h"
#include "Core/ApplicationSetting.h"
#include "Slate/Square.h"
#include "Utility/BlockRegistry.h"

namespace
{
    float yaw = -90.f;
    float pitch = 0.f;

    std::array<bool, 4> PressDirs = { false, false, false, false };

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

void CameraLayer::OnAttach(SunsetEngine::Scene* scene)
{
    SunsetEngine::Layer::OnAttach(scene);
}

void CameraLayer::OnUpdate(float dt)
{
    if (CraftScene* scene = static_cast<CraftScene*>(GetScene()))
    {
        ProcessInput(scene->m_Camera, dt);

        // RaycastHit hit;
        // scene->LineTrace(hit , scene->m_Camera.GetPosition(), scene->m_Camera.GetForward(), 10.f);
        // if (hit)
        // {
        //     if (SunsetEngine::Input::IsMouseButtonClick(1))
        //     {
        //         if (scene->currentSelectTool == 0)
        //             hit.chunk->SetBlockId(hit.blockPose + hit.hitNormal, BlockRegistry::DIRT);
        //         else if (scene->currentSelectTool == 1)
        //             hit.chunk->SetBlockId(hit.blockPose + hit.hitNormal, BlockRegistry::STONE);
        //         else if (scene->currentSelectTool == 2)
        //             hit.chunk->SetBlockId(hit.blockPose + hit.hitNormal, BlockRegistry::Get("wood").id);
        //
        //     }
        //     else if (SunsetEngine::Input::IsMouseButtonClick(0))
        //         hit.chunk->SetBlockId(hit.blockPose, BlockRegistry::AIR);
        // }
    }
}

void CameraLayer::OnDraw()
{
}

bool CameraLayer::OnEvent(SunsetEngine::Event::Type& event)
{
    std::visit(overloads{[](SunsetEngine::Event::KeyEvent& event)
    {
        bool handle = false;

        handle = SunsetEngine::InputManager::HandleKey("Forward", event, [](const SunsetEngine::Event::Action& action)
        {
            switch (action)
            {
            case SunsetEngine::Event::Action::Release:
                {
                    PressDirs[0] = false;
                }
                default:
                {
                    PressDirs[0] = true;
                }
            }
        });
        handle = handle || SunsetEngine::InputManager::HandleKey("Backward", event, [](const SunsetEngine::Event::Action& action){});
        handle = handle || SunsetEngine::InputManager::HandleKey("Left", event, [](const SunsetEngine::Event::Action& action){});
        handle = handle || SunsetEngine::InputManager::HandleKey("Right", event, [](const SunsetEngine::Event::Action& action){});

        return handle;
    },
    [](SunsetEngine::Event::MouseEvent& event)
    {
        return false;
    }}, event);

    return false;
}
