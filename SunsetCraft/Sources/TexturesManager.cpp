//
// Created by sunvy on 19/12/2025.
//

#include "TexturesManager.h"

#include "Render/Image.h"
#include "Render/Texture.h"
#include "Render/Shader.h"

#include <filesystem>

namespace
{
    std::unordered_map<std::string, std::uint32_t> _textures;

    std::shared_ptr<SunsetEngine::Textures> m_Texture = nullptr;

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
        return {"atlasTexture", images, atlasWidth, atlasHeight};
    }
}

void TexturesManager::Init(const std::string_view& path)
{
    LOG("SunsetCraft", info, "TextureManager Init");
    m_Texture = std::make_shared<SunsetEngine::Textures>(LoadTextures(path));
}

void TexturesManager::Shutdown()
{
    LOG("SunsetCraft", info, "TextureManager Shutdown");
    m_Texture.reset();
}

std::uint32_t TexturesManager::Get(const std::string_view& name)
{
    return _textures.at(name.data());
}

std::shared_ptr<SunsetEngine::Textures>& TexturesManager::GetImage()
{
    return m_Texture;
}
