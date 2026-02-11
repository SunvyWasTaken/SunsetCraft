//
// Created by sunvy on 11/02/2026.
//

#include "Material.h"

#include <glad/glad.h>

#include "Shader.h"
#include "Texture.h"

namespace SunsetEngine
{
    Material::Material()
        : m_Shader(nullptr)
    {
    }

    Material::~Material()
    {
    }

    void Material::Bind() const
    {
        m_Shader->Use();
        int index = 0;
        for (const auto& it : m_Textures)
        {
            glActiveTexture(GL_TEXTURE0 + index);
            it->Use();
            const GLint loc = glGetUniformLocation(m_Shader->GetId(), it->GetName());
            glUniform1i(loc, index);
            ++index;
        }
    }
}
