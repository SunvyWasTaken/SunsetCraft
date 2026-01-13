//
// Created by sunvy on 13/01/2026.
//

#include "SlateImage.h"

#include "Render/Image.h"

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
    SlateImage::SlateImage()
    {
    }

    SlateImage::~SlateImage()
    {
        glDeleteTextures(1, &m_Id);
    }

    void SlateImage::LoadImage(const std::string_view &path)
    {
        Image img{path};
        SendTextureToGpu(m_Id, img.width, img.height, img.m_Data);
    }

    void SlateImage::Draw() const
    {

    }
}
