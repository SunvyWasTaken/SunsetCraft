//
// Created by sunvy on 19/12/2025.
//

#include "Texture.h"

#include "Image.h"
#include "Shader.h"

#include <glad/glad.h>

namespace
{
    void SendTextureToGpu(std::uint32_t& id, const int width, const int height, void* data = nullptr)
    {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
}

namespace SunsetEngine
{
    /// Texture

    Textures::Textures(std::vector<Image>& images, const int width, const int height)
        : m_Width(width)
        , m_Height(height)
        , m_Id(0)
        , m_Nbr(images.size())
    {
        SendTextureToGpu(m_Id, m_Width, m_Height);

        int currentY = 0;

        for (const auto& image : images)
        {
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, currentY, image.width, image.height, GL_RGB, GL_UNSIGNED_BYTE, image.m_Data);
            currentY += image.width;
        }
    }

    Textures::~Textures()
    {
        glDeleteTextures(1, &m_Id);
    }

    void Textures::Use(const Shader* shader, const std::string_view& name) const
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,m_Id);
        const GLint loc = glGetUniformLocation(shader->GetId(), name.data());
        glUniform1i(loc, 0);
    }

    size_t Textures::Nbr() const
    {
        return m_Nbr;
    }

    std::uint32_t Textures::operator()() const
    {
        return m_Id;
    }
}
