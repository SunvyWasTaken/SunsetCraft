//
// Created by sunvy on 07/02/2026.
//

#ifndef SUNSETCRAFT_VERTEXARRAY_H
#define SUNSETCRAFT_VERTEXARRAY_H

namespace SunsetEngine
{
    class VertexBuffer;
    class IndiceBuffer;

    // VAO
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void Bind();
        void Unbind();

        void AddVertexBuffer(const VertexBuffer& vertexBuffer);
        void AddIndexBuffer(const IndiceBuffer& indexBuffer);

        [[nodiscard]] uint32_t GetCount() const;

    private:
        uint32_t m_Id;
        uint32_t count;
    };
}

#endif //SUNSETCRAFT_VERTEXARRAY_H