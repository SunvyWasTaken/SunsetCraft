//
// Created by sunvy on 11/01/2026.
//

#include "HorizontalBox.h"

namespace SunsetEngine
{
    void HorizontalBox::Draw() const
    {
        const_cast<HorizontalBox*>(this)->Rebuild();

        for (auto& child : m_Children)
            child->Draw();
    }

    void HorizontalBox::Clear()
    {
        m_Children.clear();
    }

    void HorizontalBox::Reserve(size_t size)
    {
        m_Children.reserve(size);
    }

    void HorizontalBox::SetPadding(const glm::ivec2& padding)
    {
        m_Padding = padding;
        bIsDirty = true;
    }

    void HorizontalBox::AddChild(const std::shared_ptr<Slate>& child)
    {
        m_Children.emplace_back(child);
        bIsDirty = true;
    }

    void HorizontalBox::Rebuild()
    {
        if (!bIsDirty)
            return;

        m_Size = {0, 0};

        for (auto& child : m_Children)
        {
            m_Size.x += child->GetSize().x + m_Padding.x;
            if (m_Size.y < child->GetSize().y)
                m_Size.y = child->GetSize().y;
        }
        m_Size.y += m_Padding.y * 2;

        const size_t step = m_Size.x / m_Children.size();
        const size_t HalfSize = m_Size.x / 2;
        const size_t StartPosition = m_Position.x - HalfSize;

        for (size_t i = 0; i < m_Children.size(); ++i)
        {
            m_Children[i]->SetPosition({StartPosition + step * i, m_Position.y});
        }

        bIsDirty = false;
    }
}
