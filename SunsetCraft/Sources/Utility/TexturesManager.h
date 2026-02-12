//
// Created by sunvy on 19/12/2025.
//

#ifndef SUNSETCRAFT_TEXTURESMANAGER_H
#define SUNSETCRAFT_TEXTURESMANAGER_H

namespace SunsetEngine
{
    class Textures;
    class Shader;
}

class TexturesManager
{
public:
    static void Init(const std::string_view& path);
    static void Shutdown();

    static std::uint32_t Get(const std::string_view& name);

    static std::shared_ptr<SunsetEngine::Textures>& GetImage();
};

#endif //SUNSETCRAFT_TEXTURESMANAGER_H