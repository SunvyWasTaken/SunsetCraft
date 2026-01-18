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
        , layout({})
    {
        Create(vertices);
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

    void Drawable::Create(const std::vector<std::uint32_t>& vertices)
    {
        vertexCount = vertices.size();

        if (layout.empty())
        {
            HUD("generation failed misarably cuz layout isn't set.");
            return;
        }

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(std::uint32_t) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        uint32_t index = 0;
        for (const auto& element : layout)
        {
            glVertexAttribIPointer(index, element.Count(), element(), layout.GetStride(), (const void*)element.offset);
            glEnableVertexAttribArray(index);
            ++index;
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }

    void Drawable::Draw() const
    {
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);

        glBindVertexArray(vao);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, static_cast<GLsizei>(vertexCount));
        glBindVertexArray(0);
    }
}
