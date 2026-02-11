//
// Created by sunvy on 15/12/2025.
//

#include "Drawable.h"

#include "Mesh.h"
#include "Shader.h"

namespace SunsetEngine
{
    Drawable::Drawable()
        : m_Mesh(nullptr)
        , m_Shader(nullptr)
        , m_Position(0.f)
        , m_RenderState({})
    {
    }

    Drawable::~Drawable()
    {
    }
}
