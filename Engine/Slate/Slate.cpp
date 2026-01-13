//
// Created by sunvy on 11/01/2026.
//

#include "Slate.h"

namespace SunsetEngine
{
    Slate::Slate()
        : bIsDirty(true)
        , m_Position(0, 0)
        , m_Size(0, 0)
        , m_Anchor(0.f, 0.f)
    {
    }

    Slate::~Slate()
    {
    }

    glm::ivec2 Slate::GetPosition() const
    {
        return m_Position;
    }

    void Slate::SetPosition(const glm::ivec2& position)
    {
        m_Position = position;
        bIsDirty = true;
    }

    glm::ivec2 Slate::GetSize() const
    {
        return m_Size;
    }

    void Slate::SetSize(const glm::ivec2& size)
    {
        m_Size = size;
        bIsDirty = true;
    }
}
