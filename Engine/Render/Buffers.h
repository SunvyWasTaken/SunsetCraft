//
// Created by sunvy on 07/02/2026.
//

#ifndef SUNSETCRAFT_BUFFERS_H
#define SUNSETCRAFT_BUFFERS_H

namespace SunsetEngine
{
    enum class ShaderDataType {
        Float, Float2, Float3, Float4,
        Mat3, Mat4,
        Int, Int2, Int3, Int4,
        UInt, Bool
    };

    struct BufferElement final
    {
        BufferElement(ShaderDataType type, const std::string_view& name, bool normalized = false);

        int Count() const;
        int Type() const;

        std::string name;
        ShaderDataType type;
        uint32_t size;
        uint32_t offset;
        bool normalized;
    };
}

#endif //SUNSETCRAFT_BUFFERS_H