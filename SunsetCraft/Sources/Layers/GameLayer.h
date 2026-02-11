//
// Created by sunvy on 08/02/2026.
//

#ifndef SUNSETCRAFT_GAMELAYER_H
#define SUNSETCRAFT_GAMELAYER_H

#include "Core/Layer.h"

struct CraftScene;

class GameLayer : public SunsetEngine::Layer
{
public:
    GameLayer();
    CraftScene* GetScene() const;

    void OnUpdate(float dt) override;
    void OnDraw() override;

private:
    std::unique_ptr<CraftScene> m_craftScene;
};

#endif //SUNSETCRAFT_GAMELAYER_H