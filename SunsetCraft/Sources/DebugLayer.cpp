//
// Created by sunvy on 04/01/2026.
//

#include "DebugLayer.h"

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
    image = std::make_unique<SunsetEngine::SlateImage>();
    image->LoadImage("Textures/grass_block_side.png");
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
