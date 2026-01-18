//
// Created by sunvy on 18/01/2026.
//

#include "Buffer.h"

#include <glad/glad.h>

// Yeah, I know that it's going to be slower at runtime. But I mean it's more secure to use a std::variant than an enum
namespace
{
    template <typename R, typename Getter>
    struct Visitor
    {
        Getter getter;

        template<typename T>
        requires (!std::is_same_v<T, std::monostate>)
        R operator()(T)
        {
            return getter.template operator()<T>();
        }

        R operator()(std::monostate) const
        {
            return R{};
        }
    };

    template<typename R, typename Getter>
    auto MakeVisitor(Getter getter)
    {
        return Visitor<R, Getter>{ std::move(getter) };
    }

    size_t GetSize(const SunsetEngine::ShaderType::Type& type)
    {
        return std::visit(MakeVisitor<size_t>([]<typename T>(){ return T::size; }), type);
    }

    int GetCount(const SunsetEngine::ShaderType::Type& type)
    {
        return std::visit(MakeVisitor<int>([]<typename T>() { return T::count; }), type);
    }

    template <typename ...Ts>
    struct Typelist {};

    using FloatType = Typelist< SunsetEngine::ShaderType::Float,
                                SunsetEngine::ShaderType::Float2,
                                SunsetEngine::ShaderType::Float3,
                                SunsetEngine::ShaderType::Float4,
                                SunsetEngine::ShaderType::Mat3,
                                SunsetEngine::ShaderType::Mat4>;

    using IntType = Typelist<   SunsetEngine::ShaderType::Int,
                                SunsetEngine::ShaderType::Int2,
                                SunsetEngine::ShaderType::Int3,
                                SunsetEngine::ShaderType::Int4>;

    using UIntType = Typelist<  SunsetEngine::ShaderType::UInt>;

    using BoolType = Typelist<  SunsetEngine::ShaderType::Bool>;

    template <typename T, typename ... Ts>
    struct HasType;

    template <typename T>
    struct HasType<T, Typelist<>> : std::false_type {};

    template<typename T, typename Head, typename... Tail>
    struct HasType<T, Typelist<Head, Tail...>>
    : std::conditional_t<
          std::is_same_v<T, Head>,
          std::true_type,
          HasType<T, Typelist<Tail...>>
      >
    {};

    int GetType(const SunsetEngine::ShaderType::Type& type)
    {
        return std::visit(
            []<typename T>(T)
            {
                if constexpr (HasType<T, FloatType>::value)
                    return GL_FLOAT;

                else if constexpr (HasType<T, IntType>::value)
                    return GL_INT;

                else if constexpr (HasType<T, UIntType>::value)
                    return GL_UNSIGNED_INT;

                else if constexpr (HasType<T, BoolType>::value)
                    return GL_BOOL;

                return 0;
            }
        , type);
    }

    size_t CalculateStride(std::vector<SunsetEngine::BufferElement>& types)
    {
        uint32_t offset = 0;
        size_t stride = 0;

        for (auto& element : types)
        {
            element.offset = offset;
            offset += element.size;
            stride += element.size;
        }

        return stride;
    }
}

namespace SunsetEngine
{
    BufferElement::BufferElement(const ShaderType::Type& type, const std::string_view& name)
        : name(name)
        , type(type)
        , size(GetSize(type))
        , offset(0)
    {
    }

    int BufferElement::Count() const
    {
        return GetCount(type);
    }

    int BufferElement::operator()() const
    {
        return GetType(type);
    }

    BufferLayout::BufferLayout(const std::initializer_list<BufferElement> &elements)
        : m_Elements(elements)
        , m_Stride(0)
    {
        m_Stride = CalculateStride(m_Elements);
    }
}
