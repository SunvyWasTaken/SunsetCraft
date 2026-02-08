//
// Created by sunvy on 04/01/2026.
//

#include "DebugLayer.h"

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
}

bool DebugLayer::OnEvent(SunsetEngine::Event::Type& event)
{
    return std::visit(overloads{
        [](SunsetEngine::Event::KeyEvent& event)
        {
            return true;
        },
        [](SunsetEngine::Event::MouseEvent& event)
        {
            return true;
        }
    }, event);
}
