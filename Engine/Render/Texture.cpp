//
// Created by sunvy on 19/12/2025.
//

#include "Texture.h"

#include "Shader.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <iostream>

#include "stb_image.h"

namespace SunsetEngine
{
    Image::Image(const std::string_view& path)
        : m_Data(nullptr)
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
            std::cerr << "Load Image failed : " << path << std::endl;
        }
    }

    void Image::Clear()
    {
        if (m_Data == nullptr)
            return;

        stbi_image_free(m_Data);
        m_Data = nullptr;
        std::cerr << "Image Destroy" << std::endl;
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

    Texture::Texture(const std::shared_ptr<Image>& image)
        : m_image(image)
        , Id(0)
    {
        SenbToGpu();
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &Id);
        std::cerr << "Texture destroy" << std::endl;
    }

    void Texture::Use(const Shader* shader) const
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,Id);
        glUniform1i(glGetUniformLocation(shader->GetId(), "atlasTexture"), 0);
    }

    void Texture::SenbToGpu()
    {
        glGenTextures(1, &Id);
        glBindTexture(GL_TEXTURE_2D, Id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (m_image)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_image->width, m_image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_image->m_Data);
            glGenerateMipmap(GL_TEXTURE_2D);
            std::cerr << "Texture generated" << std::endl;
        }

        m_image->Clear();
    }
}
