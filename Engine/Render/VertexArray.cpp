//
// Created by sunvy on 07/02/2026.
//

#include "VertexArray.h"

#include "Buffers.h"

#include <glad/glad.h>

namespace SunsetEngine
{
    VertexArray::VertexArray()
       : m_Id(0)
       , count(0)
    {
        glGenVertexArrays(1, &m_Id);
        LOG("Engine", trace, "VertexArray {} create", m_Id)
    }

    VertexArray::~VertexArray()
    {
        LOG("Engine", trace, "VertexArray {} destroy", m_Id)
        glDeleteVertexArrays(1, &m_Id);
    }

    void VertexArray::Bind() const
    {
        LOG("Engine", trace, "VertexArray {} bind", m_Id)
        glBindVertexArray(m_Id);
    }

    void VertexArray::Unbind() const
    {
        LOG("Engine", trace, "VertexArray {} unbind", m_Id)
        glBindVertexArray(0);
    }

    void VertexArray::AddVertexBuffer(const VertexBuffer& vertexBuffer)
    {
        Bind();
        vertexBuffer.Bind();

        const auto& layout = vertexBuffer.GetLayout();
        uint32_t index = 0;

        for (auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            if (element.IsInt())
                glVertexAttribIPointer(index, element.Count(), element.Type(), layout.GetStride(), (const void*)element.offset);
            else
                glVertexAttribPointer(index, element.Count(), element.Type(), element.normalized, layout.GetStride(), (const void*)element.offset);
            index++;
        }

        count = vertexBuffer.GetSize();
        Unbind();
    }

    void VertexArray::AddIndexBuffer(const IndiceBuffer& indexBuffer)
    {
        Bind();
        indexBuffer.Bind();
        count = indexBuffer.GetCount();
        Unbind();
    }

    uint32_t VertexArray::GetVAO() const
    {
        return m_Id;
    }

    uint32_t VertexArray::GetCount() const
    {
        return count;
    }   
}
