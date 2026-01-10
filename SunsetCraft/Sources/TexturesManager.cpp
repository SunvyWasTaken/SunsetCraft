//
// Created by sunvy on 19/12/2025.
//

#include "TexturesManager.h"

#include <filesystem>
#include <iostream>

#include "Render/Shader.h"

namespace
{
    std::unordered_map<std::string, std::uint32_t> _textures;

    void GetTextureFiles(const std::string_view& path, std::vector<std::string>& files)
    {
        files.clear();
        for (const auto& entry : std::filesystem::directory_iterator(path))
        {
            if (entry.is_regular_file())
            {
                const std::string file = entry.path().string();
                if (file.ends_with(".png"))
                {
                    files.emplace_back(entry.path().string());
                }
            }
        }
    }

    SunsetEngine::Textures LoadTextures(const std::string_view& path)
    {
        int atlasWidth = 0;
        int atlasHeight = 0;
        std::vector<SunsetEngine::Image> images;

        std::vector<std::string> files;
        GetTextureFiles(path, files);
        images.reserve(files.size());
        _textures.reserve(files.size());

        for (const auto& file : files)
        {
            images.emplace_back(file);

            atlasHeight += images.back().height;

            std::string tmp = file;
            if (tmp.starts_with(path))
            {
                tmp.erase(0, path.length());
            }
            _textures.emplace(tmp, images.size() - 1);
        }

        atlasWidth = images.back().width;
        return {images, atlasWidth, atlasHeight};
    }
}

TexturesManager::TexturesManager()
    : m_Texture(LoadTextures("Textures/"))
{
}

TexturesManager::~TexturesManager()
{
}

void TexturesManager::Use(const SunsetEngine::Shader* shader) const
{
    m_Texture.Use(shader, "atlasTexture");
    shader->SetInt("NbrTile", m_Texture.Nbr());
}

std::uint32_t TexturesManager::Get(const std::string_view& name)
{
    return _textures.at(name.data());
}

SunsetEngine::Textures& TexturesManager::GetImage()
{
    return m_Texture;
}
