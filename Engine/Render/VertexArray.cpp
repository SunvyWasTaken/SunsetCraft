//
// Created by sunvy on 07/02/2026.
//

#include "VertexArray.h"

#include "Buffers.h"

#include <glad/glad.h>

SunsetEngine::VertexArray::VertexArray()
    : m_Id(0)
    , count(0)
{
    glGenVertexArrays(1, &m_Id);
}

SunsetEngine::VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_Id);
}

void SunsetEngine::VertexArray::Bind()
{
    glBindVertexArray(m_Id);
}

void SunsetEngine::VertexArray::Unbind()
{
    glBindVertexArray(0);
}

void SunsetEngine::VertexArray::AddVertexBuffer(const VertexBuffer& vertexBuffer)
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
}

void SunsetEngine::VertexArray::AddIndexBuffer(const IndiceBuffer& indexBuffer)
{
    Bind();
    indexBuffer.Bind();
    count = indexBuffer.GetCount();
}

uint32_t SunsetEngine::VertexArray::GetCount() const
{
    return count;
}
