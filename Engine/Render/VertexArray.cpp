//
// Created by sunvy on 07/02/2026.
//

#include "VertexArray.h"

#include "Buffers.h"

SunsetEngine::VertexArray::VertexArray(std::unique_ptr<VertexBuffer> vb, std::unique_ptr<IndiceBuffer> ib)
    : vertexBuffer(std::move(vb))
    , indiceBuffer(std::move(ib))
{
    // Todo : ici bind les buffer au vao.
}

SunsetEngine::VertexArray::~VertexArray()
{
}
