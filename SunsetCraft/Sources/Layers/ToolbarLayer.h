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
    ToolbarLayer(class SunsetEngine::Scene* scene);
    virtual ~ToolbarLayer();

    virtual void OnAttach();

    virtual void OnUpdate(float dt);
    virtual void OnDraw();

    private:

    CraftScene* GetCraftScene();
};


#endif //SUNSETCRAFT_TOOLBARLAYER_H