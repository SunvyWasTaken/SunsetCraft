//
// Created by sunvy on 18/01/2026.
//

#ifndef SUNSETCRAFT_BUFFER_H
#define SUNSETCRAFT_BUFFER_H

namespace SunsetEngine
{
    namespace ShaderType
    {
        struct Float
        {
            constexpr static size_t size = sizeof(float);
            constexpr static int count = 1;
        };
        struct Float2
        {
            constexpr static size_t size = sizeof(float) * 2;
            constexpr static int count = 2;
        };
        struct Float3
        {
            constexpr static size_t size = sizeof(float) * 3;
            constexpr static int count = 3;
        };
        struct Float4
        {
            constexpr static size_t size = sizeof(float) * 4;
            constexpr static int count = 4;
        };
        struct Mat3
        {
            constexpr static size_t size = sizeof(float) * 3 * 3;
            constexpr static int count = 3 * 3;
        };
        struct Mat4
        {
            constexpr static size_t size = sizeof(float) * 4 * 4;
            constexpr static int count = 4 * 4;
        };
        struct Int
        {
            constexpr static size_t size = sizeof(int);
            constexpr static int count = 1;
        };
        struct Int2
        {
            constexpr static size_t size = sizeof(int) * 2;
            constexpr static int count = 2;
        };
        struct Int3
        {
            constexpr static size_t size = sizeof(int) * 3;
            constexpr static int count = 3;
        };
        struct Int4
        {
            constexpr static size_t size = sizeof(int) * 4;
            constexpr static int count = 4;
        };
        struct UInt
        {
            constexpr static size_t size = sizeof(uint32_t);
            constexpr static int count = 1;
        };
        struct Bool
        {
            constexpr static size_t size = sizeof(bool);
            constexpr static int count = 1;
        };

        using Type =  std::variant<std::monostate, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, UInt, Bool>;
    };

    struct BufferElement
    {
        BufferElement(const ShaderType::Type& type, const std::string_view& name);

        std::string name;
        ShaderType::Type type;
        uint32_t size;
        int offset;
        bool normalized;

        int Count() const;

        int operator()() const;
    };

    class BufferLayout
    {
    public:
        BufferLayout(const std::initializer_list<BufferElement>& elements);

        const std::vector<BufferElement>& operator()() const { return m_Elements; }

        [[nodiscard]] std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }

        [[nodiscard]] std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

        [[nodiscard]] bool empty() const { return m_Elements.empty(); }

        uint32_t GetStride() const { return m_Stride; };

    private:

        std::vector<BufferElement> m_Elements;

        uint32_t m_Stride;
    };

    template <typename T>
    class VertexBuffer
    {
    public:
        explicit VertexBuffer(const std::vector<T>& vertices);
        virtual ~VertexBuffer();

        void Bind() const;
        void Unbind() const;

        void SetLayout(const std::initializer_list<BufferElement>& elements);
        BufferLayout GetLayout() const;

        size_t GetSize() const;

    private:
        uint32_t m_Id;
        BufferLayout m_Layout;
        size_t m_Size;
    };

    class IndiceBuffer
    {
    public:
        explicit IndiceBuffer(const std::vector<uint32_t>& indices);
        virtual ~IndiceBuffer();
        void Bind() const;
        void Unbind() const;
        size_t GetCount() const;
    private:
        uint32_t m_Id;
        size_t m_Count;
    };
}

#endif //SUNSETCRAFT_BUFFER_H