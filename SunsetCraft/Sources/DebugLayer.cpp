//
// Created by sunvy on 04/01/2026.
//

#include "DebugLayer.h"

#include "TexturesManager.h"
#include "Imgui/imgui.h"
#include "Slate/Square.h"
#include "World/CraftScene.h"

namespace
{
    float radius = 15.f;
}

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

        SunsetEngine::Square sq{{640, 360}, {250, 150}, {1, 1, 1, 1}, radius};
        sq.Draw();

        ImGui::Begin("DrawImage");
        ImGui::InputFloat("Radius", &radius);
        ImGui::End();
    }
}
