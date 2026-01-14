//
// Created by sunvy on 10/01/2026.
//

#include "ToolbarLayer.h"

#include <GLFW/glfw3.h>
#include <glm/ext/quaternion_common.hpp>

#include "Core/Application.h"
#include "Core/ApplicationSetting.h"
#include "Core/Input.h"
#include "Slate/HorizontalBox.h"
#include "Slate/SlateImage.h"
#include "Slate/Square.h"
#include "World/CraftScene.h"

namespace
{
    constexpr std::uint8_t ToolbarSize = 9;
    SunsetEngine::HorizontalBox ToolbarSlate;
}

ToolbarLayer::ToolbarLayer(SunsetEngine::Scene* scene)
    : SunsetEngine::Layer(scene)
{
}

ToolbarLayer::~ToolbarLayer()
{
    ToolbarSlate.Clear();
}

void ToolbarLayer::OnAttach()
{
    ToolbarSlate.SetPosition({1280/2, 720});
    ToolbarSlate.SetPadding({5, 0});
    ToolbarSlate.Reserve(ToolbarSize);
    ToolbarSlate.SetAnchor({0, -1});

    for (std::uint8_t i = 0; i < ToolbarSize; ++i)
    {
        std::shared_ptr<SunsetEngine::Slate> Square = std::make_shared<SunsetEngine::Square>(glm::ivec2{0,0}, glm::ivec2{74, 74}, glm::vec4{1.0, 0.3, 0.3, 1.0}, 15.f);
        ToolbarSlate.AddChild(Square);
        if (i == 0)
        {
            auto img = std::make_shared<SunsetEngine::SlateImage>();
            img->LoadImage("Textures/grass_block_side.png");
            std::shared_ptr<SunsetEngine::Slate> s = ToolbarSlate[i];
            if (auto* sq = dynamic_cast<SunsetEngine::Square*>(s.get()))
            {
                sq->AddChild(img);
            }
        }
        else if (i == 1)
        {
            auto img = std::make_shared<SunsetEngine::SlateImage>();
            img->LoadImage("Textures/stone.png");
            std::shared_ptr<SunsetEngine::Slate> s = ToolbarSlate[i];
            if (auto* sq = dynamic_cast<SunsetEngine::Square*>(s.get()))
            {
                sq->AddChild(img);
            }
        }
    }
}

void ToolbarLayer::OnUpdate(float dt)
{
    if (CraftScene* craft_scene = GetCraftScene())
    {
        if (SunsetEngine::Input::IsMouseButtonClick(4))
        {
            craft_scene->currentSelectTool -= 1;
            if (0 > craft_scene->currentSelectTool)
                craft_scene->currentSelectTool = ToolbarSize - 1;
        }
        if (SunsetEngine::Input::IsMouseButtonClick(3))
        {
            craft_scene->currentSelectTool += 1;
            if (ToolbarSize - 1 < craft_scene->currentSelectTool)
                craft_scene->currentSelectTool = 0;
        }

        const int8_t currTool = craft_scene->currentSelectTool;

        if (ToolbarSize <= currTool)
            return;

        for (auto& tool : ToolbarSlate)
        {
            tool->SetSize({75, 75});
        }

        ToolbarSlate[currTool]->SetSize({90, 90});
    }
}

void ToolbarLayer::OnDraw()
{
    HUD("ToolbarLayer::Draw");

    ToolbarSlate.Draw();

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

CraftScene* ToolbarLayer::GetCraftScene()
{
    return static_cast<CraftScene*>(GetScene());
}
