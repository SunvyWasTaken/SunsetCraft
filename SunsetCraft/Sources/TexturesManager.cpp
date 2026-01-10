//
// Created by sunvy on 19/12/2025.
//

#include "TexturesManager.h"

#include <filesystem>
#include <iostream>

#include "Render/Shader.h"

namespace
{
    constexpr int TILE_SIZE = 32;

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

    void CreateAtlas(unsigned char* atlasData, int atlasWidth, int atlasHeight, const std::vector<SunsetEngine::Image>& m_Textures)
    {
        std::memset(atlasData, 0, atlasWidth * atlasHeight * 4);

        int currentY = 0;

        for (const auto& tex : m_Textures)
        {
            for (int y = 0; y < TILE_SIZE; ++y)
                for (int x = 0; x < TILE_SIZE; ++x)
                {
                    int dst = ((currentY + y) * atlasWidth + x) * 4;
                    int src = (y * TILE_SIZE + x) * 4;

                    atlasData[dst + 0] = tex.m_Data[src + 0];
                    atlasData[dst + 1] = tex.m_Data[src + 1];
                    atlasData[dst + 2] = tex.m_Data[src + 2];
                    atlasData[dst + 3] = tex.m_Data[src + 3];
                }

            currentY += TILE_SIZE;
            LOG("Textures loaded: {}", tex.m_ImageName);
        }
    }

    SunsetEngine::Texture LoadTextures(const std::string_view& path)
    {
        int atlasWidth = 0;
        int atlasHeight = 0;
        std::vector<SunsetEngine::Image> m_Textures;

        std::vector<std::string> files;
        GetTextureFiles(path, files);
        m_Textures.reserve(files.size());
        _textures.reserve(files.size());

        for (const auto& file : files)
        {
            m_Textures.emplace_back(file);
            atlasWidth = std::max(atlasWidth, m_Textures.back().width);
            atlasHeight += m_Textures.back().height;
            std::string tmp = file;
            if (tmp.starts_with(path))
            {
                tmp.erase(0, path.length());
            }
            _textures.emplace(tmp, m_Textures.size() - 1);
            LOG("{} Textures loaded: {}", m_Textures.size() - 1, tmp);
        }

        unsigned char* atlasData = new unsigned char[atlasWidth * atlasHeight * 4];
        CreateAtlas(atlasData, atlasWidth, atlasHeight, m_Textures);

        std::shared_ptr<SunsetEngine::Image> image = std::make_shared<SunsetEngine::Image>();
        image->SetData(atlasData);
        image->height = atlasHeight;
        image->width = atlasWidth;
        image->nbrChannels = 4;

        SunsetEngine::Texture texture{image};
        return texture;
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
    m_Texture.Use(shader);
}

std::uint32_t TexturesManager::Get(const std::string_view& name)
{
    return _textures.at(name.data());
}
