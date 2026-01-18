//
// Created by sunvy on 18/01/2026.
//

#include "VertexArray.h"

#include <glad/glad.h>

namespace SunsetEngine
{
    template<typename T>
    VertexArray<T>::VertexArray()
    {
        glGenVertexArrays(1, &m_Id);
    }

    template<typename T>
    VertexArray<T>::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_Id);
    }

    template<typename T>
    void VertexArray<T>::Bind() const
    {
        glBindVertexArray(m_Id);
    }

    template<typename T>
    void VertexArray<T>::Unbind() const
    {
        glBindVertexArray(0);
    }

    template<typename T>
    void VertexArray<T>::AddBuffers(const std::shared_ptr<VertexBuffer<T>> &vertexBuffer,
        const std::shared_ptr<IndiceBuffer> &indexBuffer)
    {
        if (!vertexBuffer)
            return;

        if (vertexBuffer->GetLayout().empty())
        {
            LOG("Layout hasn't been set!");
            return;
        }

        m_Buffers.emplace_back(vertexBuffer, indexBuffer);

        Bind();
        vertexBuffer->Bind();

        uint32_t index = 0;
        for (const auto& element : vertexBuffer->GetLayout())
        {
            glEnableVertexAttribArray(index);
            if (element() == GL_UNSIGNED_INT)
            {
                glVertexAttribIPointer(index,
                    element.Count(),
                    element(),
                    vertexBuffer->GetLayout().GetStride(),
                    static_cast<const void *>(&element.offset));
                glVertexAttribDivisor(index, 1);
            }
            else
                glVertexAttribPointer(index,
                    element.Count(),
                    element(),
                    element.normalized ? GL_TRUE : GL_FALSE,
                    vertexBuffer->GetLayout().GetStride(),
                    static_cast<const void *>(&element.offset));
            ++index;
        }

        if (indexBuffer)
            indexBuffer->Bind();

        Unbind();
    }

    template<typename T>
    std::vector<typename VertexArray<T>::Buffers>::const_iterator VertexArray<T>::begin() const
    {
        return m_Buffers.begin();
    }

    template<typename T>
    std::vector<typename VertexArray<T>::Buffers>::const_iterator VertexArray<T>::end() const
    {
        return m_Buffers.end();
    }

    template class VertexArray<float>;
    template class VertexArray<uint32_t>;
}
