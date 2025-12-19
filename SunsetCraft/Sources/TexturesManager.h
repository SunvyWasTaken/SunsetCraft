//
// Created by sunvy on 19/12/2025.
//

#ifndef SUNSETCRAFT_TEXTURESMANAGER_H
#define SUNSETCRAFT_TEXTURESMANAGER_H

#include "Render/Texture.h"

namespace SunsetEngine
{
    class Shader;
}

class TexturesManager
{
public:
    TexturesManager();
    ~TexturesManager();

    void Use(const SunsetEngine::Shader* shader) const;

private:
    SunsetEngine::Texture m_Texture;
};

#endif //SUNSETCRAFT_TEXTURESMANAGER_H