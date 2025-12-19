//
// Created by sunvy on 15/12/2025.
//

#ifndef SUNSETCRAFT_CRAFTLAYER_H
#define SUNSETCRAFT_CRAFTLAYER_H

#include "Core/Layer.h"

namespace SunsetEngine
{
    class Camera;
    struct Scene;
}

class CraftLayer : public SunsetEngine::Layer
{
public:
    explicit CraftLayer(SunsetEngine::Scene* scene);
    ~CraftLayer() override;

    void OnAttach() override;

    void OnUpdate(float dt) override;
    void OnDraw() override;
};

#endif //SUNSETCRAFT_CRAFTLAYER_H
