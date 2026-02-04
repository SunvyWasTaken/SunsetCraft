//
// Created by sunvy on 15/12/2025.
//

#include "Layer.h"

namespace SunsetEngine
{
    void Layer::OnAttach(Scene* scene)
    {
        m_Scene = scene;
    }

    bool Layer::OnEvent(Event::Type& event)
    {
        return false;
    }

    Scene* Layer::GetScene() const
    {
        return m_Scene;
    }
}
