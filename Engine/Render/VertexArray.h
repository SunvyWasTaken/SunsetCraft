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
        explicit VertexArray(std::unique_ptr<VertexBuffer> vb, std::unique_ptr<IndiceBuffer> ib = nullptr);
        ~VertexArray();
    private:
        uint32_t m_Id;
        std::unique_ptr<VertexBuffer> vertexBuffer;
        std::unique_ptr<IndiceBuffer> indiceBuffer;
    };
}

#endif //SUNSETCRAFT_VERTEXARRAY_H