//
// Created by sunvy on 04/01/2026.
//

#include "DebugLayer.h"

#include "Chunk/BiomeGenerator.h"
#include "Core/Application.h"
#include "Core/ApplicationSetting.h"
#include "Imgui/imgui.h"
#include "Slate/SlateImage.h"
#include "World/CraftScene.h"

namespace
{
}

void DebugLayer::OnAttach(SunsetEngine::Scene* scene)
{
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
        glm::vec2 pos = tmp->m_Camera.GetPosition();
        BiomeGenerator::RequestBiome(pos);
    }
}
