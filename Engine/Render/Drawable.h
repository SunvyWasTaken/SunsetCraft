//
// Created by sunvy on 15/12/2025.
//

#ifndef SUNSETCRAFT_DRAWABLE_H
#define SUNSETCRAFT_DRAWABLE_H

namespace SunsetEngine
{
    class Shader;
    class Mesh;

    enum class BlendFactor
    {
        Zero,
        One,
        SrcAlpha,
        OneMinusSrcAlpha,
        DstAlpha,
        OneMinusDstAlpha,
        SrcColor,
        OneMinusSrcColor,
        DstColor,
        OneMinusDstColor
    };

    enum class CullMode
    {
        None,
        Back,
        Front
    };

    struct RenderState
    {
        bool depthTest = true;
        bool depthWrite = true;

        bool blending = true;
        BlendFactor src = BlendFactor::One;
        BlendFactor dest = BlendFactor::Zero;

        CullMode cullMode = CullMode::Back;
        bool wireframe = false;
        bool DrawInstance = false;
    };

    class Drawable final
    {
    public:
        Drawable();
        ~Drawable();

        std::shared_ptr<Mesh> m_Mesh;
        std::shared_ptr<Shader> m_Shader;
        glm::vec3 m_Position;
        RenderState m_RenderState;
    };
}


#endif //SUNSETCRAFT_DRAWABLE_H