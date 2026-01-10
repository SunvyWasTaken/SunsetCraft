//
// Created by sunvy on 04/01/2026.
//

#include "DebugLayer.h"

#include "TexturesManager.h"
#include "Imgui/imgui.h"
#include "World/CraftScene.h"

DebugLayer::DebugLayer(SunsetEngine::Scene* scene)
    : SunsetEngine::Layer(scene)
{
}

DebugLayer::~DebugLayer()
{
}

void DebugLayer::OnAttach()
{
}

void DebugLayer::OnUpdate(float dt)
{
    HUD("Deltatime : {}", dt);
    HUD("Framerate : {}", 1.f/dt);
}

void DebugLayer::OnDraw()
{
    if (CraftScene* tmp = static_cast<CraftScene*>(this->GetScene()))
    {
        ImGui::Begin("DrawImage");
        ImGui::Image((ImTextureID)(intptr_t)tmp->m_TexturesManager.GetImage()(), ImVec2(32, 128));
        ImGui::End();
    }
}
