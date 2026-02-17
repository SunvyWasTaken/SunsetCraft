//
// Created by sunvy on 16/02/2026.
//

#include "Sky.h"

#include "Render/Drawable.h"
#include "Render/Material.h"

void Sky::SetTexture(std::shared_ptr<SunsetEngine::Textures>& textures)
{
    m_Drawable->m_Material->m_Textures = {textures};
}

Sky::operator SunsetEngine::Drawable*() const
{
    return m_Drawable.get();
}
