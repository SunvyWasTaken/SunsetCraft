//
// Created by sunvy on 18/01/2026.
//

#ifndef SUNSETCRAFT_VERTEXARRAY_H
#define SUNSETCRAFT_VERTEXARRAY_H

#include "Buffer.h"

namespace SunsetEngine
{
    template <typename T>
    class VertexArray
    {
    public:

        using Buffers = std::tuple<std::shared_ptr<VertexBuffer<T>>, std::shared_ptr<IndiceBuffer>>;

        VertexArray();
        virtual ~VertexArray();

        void Bind() const;
        void Unbind() const;

        void AddBuffers(const std::shared_ptr<VertexBuffer<T>>& vertexBuffer, const std::shared_ptr<IndiceBuffer>& indexBuffer = nullptr);

        std::vector<Buffers>::const_iterator begin() const;
        std::vector<Buffers>::const_iterator end() const;

    private:
        uint32_t m_Id;
        std::vector<Buffers> m_Buffers;
    };
}

#endif //SUNSETCRAFT_VERTEXARRAY_H