//
// Created by sunvy on 19/12/2025.
//

#include "Texture.h"

#include "Shader.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

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
    Image::Image(const std::string_view& path)
        : m_ImageName(path)
        , m_Data(nullptr)
        , width(0)
        , height(0)
        , nbrChannels(0)
    {
        if (!path.empty())
        {
            LoadImage(path);
        }
    }

    Image::~Image()
    {
        Clear();
    }

    void Image::LoadImage(const std::string_view& path)
    {
        stbi_set_flip_vertically_on_load(true);
        m_Data = stbi_load(path.data(), &width, &height, &nbrChannels, 0);
        if (m_Data == nullptr)
        {
            LOG("Load Image failed : ", path)
        }
    }

    void Image::Clear()
    {
        if (m_Data == nullptr)
            return;

        stbi_image_free(m_Data);
        m_Data = nullptr;
    }

    void Image::SetData(unsigned char* data)
    {
        m_Data = data;
    }

    Image::operator bool() const
    {
        return m_Data;
    }

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
