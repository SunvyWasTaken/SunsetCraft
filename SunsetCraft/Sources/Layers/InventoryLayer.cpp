//
// Created by sunvy on 08/02/2026.
//

#include "InventoryLayer.h"

#include <imgui.h>

#include "Core/Application.h"
#include "Core/ApplicationSetting.h"
#include "Slate/HorizontalBox.h"
#include "Slate/SlateImage.h"
#include "Slate/Square.h"
#include "Utility/BlockRegistry.h"
#include "World/CraftScene.h"

namespace
{
    constexpr size_t ToolbarSize = 9;
    std::unique_ptr<SunsetEngine::HorizontalBox> ToolbarBox = nullptr;

    bool DrawInventory = false;
}

InventoryLayer::InventoryLayer(CraftScene* scene)
    : _scene(scene)
{
    ToolbarBox = std::make_unique<SunsetEngine::HorizontalBox>();
    ToolbarBox->SetPosition({1280/2, 720});
    ToolbarBox->SetPadding({5, 0});
    ToolbarBox->Reserve(ToolbarSize);
    ToolbarBox->SetAnchor({0, -1});
    for (std::uint8_t i = 0; i < ToolbarSize; ++i)
    {
        BlockType block = BlockRegistry::Get(_scene->m_ToolBar[i]);
        std::shared_ptr<SunsetEngine::Slate> Square = std::make_shared<SunsetEngine::Square>(glm::ivec2{0,0}, glm::ivec2{74, 74}, glm::vec4{1.0, 0.3, 0.3, 1.0}, 15.f);
        ToolbarBox->AddChild(Square);

        if (block.id != BlockRegistry::AIR)
        {
            std::shared_ptr<SunsetEngine::Slate> img = std::make_shared<SunsetEngine::SlateImage>();
            std::static_pointer_cast<SunsetEngine::SlateImage>(img)->LoadImage("Textures/" + block.textures[4]);
            std::static_pointer_cast<SunsetEngine::Square>(Square)->AddChild(img);
        }
    }

    SunsetEngine::InputRegister::RegisterAction("OpenInventory", std::bind(&InventoryLayer::OpenInventory, this, std::placeholders::_1));
}

InventoryLayer::~InventoryLayer()
{
    ToolbarBox.reset();
}

void InventoryLayer::OnUpdate(float dt)
{
    if (!_scene)
        return;

    for (auto& box : *ToolbarBox)
    {
        box->SetSize({74, 74});
        //std::static_pointer_cast<SunsetEngine::Square>(box)->SetRadius(15.f);
    }

    (*ToolbarBox)[_scene->currentSelectTool]->SetSize({84, 84});
    //std::static_pointer_cast<SunsetEngine::Square>((*ToolbarBox)[_scene->currentSelectTool])->SetRadius(30.f);
}

void InventoryLayer::OnDraw()
{
    ToolbarBox->Draw();

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

    if (!DrawInventory)
        return;

    SunsetEngine::Square Inventory{{WinSize.x / 2, WinSize.y / 2}, {500, 500}, color, radius};
    Inventory.Draw();
}

bool InventoryLayer::OpenInventory(const SunsetEngine::Event::Action& type)
{
    if (type == SunsetEngine::Event::Action::Press)
    {
        DrawInventory = !DrawInventory;
        return true;
    }
    return false;
}
