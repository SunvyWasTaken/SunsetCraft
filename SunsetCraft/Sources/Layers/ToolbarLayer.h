//
// Created by sunvy on 10/01/2026.
//

#ifndef SUNSETCRAFT_TOOLBARLAYER_H
#define SUNSETCRAFT_TOOLBARLAYER_H

#include "Core/Layer.h"

class CraftScene;

class ToolbarLayer : public SunsetEngine::Layer
{
public:

    ~ToolbarLayer() override;

    void OnAttach(SunsetEngine::Scene* scene) override;
    void OnUpdate(float dt) override;
    void OnDraw() override;
    bool OnEvent(SunsetEngine::Event::Type& event) override;

    private:

    CraftScene* GetCraftScene();
};


#endif //SUNSETCRAFT_TOOLBARLAYER_H