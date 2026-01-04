//
// Created by sunvy on 04/01/2026.
//

#include "DebugLayer.h"
#include "Imgui/imgui.h"

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
}
