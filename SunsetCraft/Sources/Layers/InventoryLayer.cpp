//
// Created by sunvy on 08/02/2026.
//

#include "InventoryLayer.h"

#include "Slate/HorizontalBox.h"
#include "Slate/Square.h"

namespace
{
    constexpr size_t ToolbarSize = 9;
    SunsetEngine::HorizontalBox ToolbarBox;
}

InventoryLayer::InventoryLayer(CraftScene* scene)
    : _scene(scene)
{
    // ToolbarBox.SetPosition({1280/2, 720});
    // ToolbarBox.SetPadding({5, 0});
    // ToolbarBox.Reserve(ToolbarSize);
    // ToolbarBox.SetAnchor({0, -1});
    // for (std::uint8_t i = 0; i < ToolbarSize; ++i)
    // {
    //     std::shared_ptr<SunsetEngine::Slate> Square = std::make_shared<SunsetEngine::Square>(glm::ivec2{0,0}, glm::ivec2{74, 74}, glm::vec4{1.0, 0.3, 0.3, 1.0}, 15.f);
    //     ToolbarBox.AddChild(Square);
    // }
}

void InventoryLayer::OnUpdate(float dt)
{
}

void InventoryLayer::OnDraw()
{
}
