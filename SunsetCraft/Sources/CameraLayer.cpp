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

#include "Core/Application.h"
#include "Core/ApplicationSetting.h"
#include "Slate/Square.h"

namespace
{
    float yaw = -90.f;
    float pitch = 0.f;

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
}

void CameraLayer::OnAttach()
{
}

void CameraLayer::OnUpdate(float dt)
{
    if (CraftScene* scene = static_cast<CraftScene*>(GetScene()))
    {
        ProcessInput(scene->m_Camera, dt);



        RaycastHit hit;
        scene->LineTrace(hit , scene->m_Camera.GetPosition(), scene->m_Camera.GetForward(), 10.f);
        if (hit)
        {
            if (SunsetEngine::Input::IsMouseButtonClick(1))
            {
                if (scene->currentSelectTool == 0)
                    hit.chunk->SetBlockId(hit.blockPose + hit.hitNormal, BlockId::Dirt);
                else if (scene->currentSelectTool == 1)
                    hit.chunk->SetBlockId(hit.blockPose + hit.hitNormal, BlockId::Stone);

            }
            else if (SunsetEngine::Input::IsMouseButtonClick(0))
                hit.chunk->SetBlockId(hit.blockPose, BlockId::Air);
        }
    }
}

void CameraLayer::OnDraw()
{
    int length = 15;
    int width = 5;
    int radius = 2;
    glm::vec4 color{1.0, 0.2, 0.2, 0.5};
    int spacecing = 2;

    glm::ivec2 WinSize = SunsetEngine::Application::GetSetting().WindowSize;

    SunsetEngine::Square crossTop{{WinSize.x / 2, WinSize.y / 2 - spacecing}, {width, length}, color, radius};
    crossTop.SetAnchor({0, -1});
    SunsetEngine::Square crossDown{{WinSize.x / 2, WinSize.y / 2 + spacecing}, {width, length}, color, radius};
    crossDown.SetAnchor({0, 1});
    SunsetEngine::Square crossLeft{{WinSize.x / 2 - spacecing, WinSize.y / 2}, {length, width}, color, radius};
    crossLeft.SetAnchor({-1, 0});
    SunsetEngine::Square crossRight{{WinSize.x / 2 + spacecing, WinSize.y / 2}, {length, width}, color, radius};
    crossRight.SetAnchor({1, 0});

    crossTop.Draw();
    crossDown.Draw();
    crossLeft.Draw();
    crossRight.Draw();
}
