//
// Created by sunvy on 15/12/2025.
//

#include "Layer.h"

namespace SunsetEngine
{
    Layer::Layer(Scene* scene)
        : m_Scene(scene)
    {
    }

    Scene* Layer::GetScene() const
    {
        return m_Scene;
    }
}
