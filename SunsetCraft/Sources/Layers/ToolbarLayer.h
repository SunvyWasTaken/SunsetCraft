//
// Created by sunvy on 10/01/2026.
//

#ifndef SUNSETCRAFT_TOOLBARLAYER_H
#define SUNSETCRAFT_TOOLBARLAYER_H

#include "Core/Layer.h"


class ToolbarLayer : public SunsetEngine::Layer
{
    virtual void OnAttach() = 0;

    virtual void OnUpdate(float dt) = 0;
    virtual void OnDraw() = 0;
};


#endif //SUNSETCRAFT_TOOLBARLAYER_H