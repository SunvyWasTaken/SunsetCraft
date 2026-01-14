//
// Created by sunvy on 04/01/2026.
//

#include "DebugLayer.h"

#include "Core/Application.h"
#include "Core/ApplicationSetting.h"
#include "Imgui/imgui.h"
#include "Slate/SlateImage.h"
#include "World/CraftScene.h"

namespace
{
    std::unique_ptr<SunsetEngine::SlateImage> image = nullptr;
}

DebugLayer::DebugLayer(SunsetEngine::Scene* scene)
    : SunsetEngine::Layer(scene)
{
}

DebugLayer::~DebugLayer()
{
    image.reset();
}

void DebugLayer::OnAttach()
{
    glm::ivec2 size = SunsetEngine::Application::GetSetting().WindowSize;
    image = std::make_unique<SunsetEngine::SlateImage>();
    image->LoadImage("Textures/grass_block_side.png");
    image->SetPosition({size.x/2, size.y/2});
    image->SetSize({150, 150});
}

void DebugLayer::OnUpdate(float dt)
{
    // HUD("Deltatime : {}", dt);
    // HUD("Framerate : {}", 1.f/dt);
}

void DebugLayer::OnDraw()
{
    if (CraftScene* tmp = static_cast<CraftScene*>(this->GetScene()))
    {
        image->Draw();
    }
}
