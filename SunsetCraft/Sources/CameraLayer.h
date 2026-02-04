//
// Created by sunvy on 16/12/2025.
//

#ifndef SUNSETCRAFT_CAMERALAYER_H
#define SUNSETCRAFT_CAMERALAYER_H

#include "Core/Layer.h"

namespace SunsetEngine
{
    struct Scene;
}

class CameraLayer : public SunsetEngine::Layer
{
public:
    void OnAttach(SunsetEngine::Scene* scene) override;
    void OnUpdate(float dt) override;
    void OnDraw() override;
    bool OnEvent(SunsetEngine::Event::Type& event) override;
};

#endif //SUNSETCRAFT_CAMERALAYER_H