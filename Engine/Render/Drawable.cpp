//
// Created by sunvy on 15/12/2025.
//

#include "Drawable.h"

#include <glad/glad.h>

namespace SunsetEngine
{
    Drawable::Drawable(const std::vector<std::uint32_t>& vertices)
        : vao(0)
        , vbo(0)
        , vertexCount(vertices.size())
    {
        LOG("Drawable : {}", vertices.size());
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(std::uint32_t) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(std::uint32_t), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribDivisor(0, 1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }

    Drawable::~Drawable()
    {
        Clear();
    }

    void Drawable::Clear() const
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
    }

    void Drawable::Draw() const
    {
        glBindVertexArray(vao);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 36, static_cast<GLsizei>(vertexCount));
        glBindVertexArray(0);
    }
}
