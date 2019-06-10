#pragma once

#include "ricepch.h"

namespace RiceCube
{
    enum class ShaderDataType
    {
        None = 0, 
        Float, 
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,
        Int,
        Int2,
        Int3,
        Int4,
        Bool
    };

    static uint32_t getDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float:    return 4;
        case ShaderDataType::Float2:   return 4 * 2;
        case ShaderDataType::Float3:   return 4 * 3;
        case ShaderDataType::Float4:   return 4 * 4;
        case ShaderDataType::Mat3:     return 4 * 3 * 3;
        case ShaderDataType::Mat4:     return 4 * 4 * 4;
        case ShaderDataType::Int:      return 4;
        case ShaderDataType::Int2:     return 4 * 2;
        case ShaderDataType::Int3:     return 4 * 3;
        case ShaderDataType::Int4:     return 4 * 4;
        case ShaderDataType::Bool:     return 1;
        }

        RICE_ASSERTS(false, "Unknown ShaderDataType!");
        return 0;
    }

    struct BufferElement
    {
        std::string _name;
        ShaderDataType _type = ShaderDataType::None;
        uint32_t _size = 0;
        uint32_t _offset = 0;
        bool _normalized = false;

        BufferElement() {}

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : _name(name), _type(type), _size(getDataTypeSize(type)), _offset(0), _normalized(normalized)
        {}

        uint32_t getComponentCount() const
        {
            switch (_type)
            {
            case ShaderDataType::Float:   return 1;
            case ShaderDataType::Float2:  return 2;
            case ShaderDataType::Float3:  return 3;
            case ShaderDataType::Float4:  return 4;
            case ShaderDataType::Mat3:    return 3 * 3;
            case ShaderDataType::Mat4:    return 4 * 4;
            case ShaderDataType::Int:     return 1;
            case ShaderDataType::Int2:    return 2;
            case ShaderDataType::Int3:    return 3;
            case ShaderDataType::Int4:    return 4;
            case ShaderDataType::Bool:    return 1;
            }

            RICE_ASSERTS(false, "Unknown ShaderDataType!");
            return 0;
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout() {}

        BufferLayout(const std::initializer_list<BufferElement>& elements)
            : m_elements(elements)
        {
            calculateOffsetAndStride();
        }

        inline uint32_t getStride() const { return m_stride; }
        inline const std::vector<BufferElement>& getElements() const { return m_elements; }

        std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }
        
    private:
        void calculateOffsetAndStride()
        {
            uint32_t offset = 0;
            m_stride = 0;
            for (auto& element : m_elements)
            {
                element._offset = offset;
                offset += element._size;
                m_stride += element._size;
            }
        }
    private:
        std::vector<BufferElement> m_elements;
        uint32_t m_stride = 0;
    };

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void bind() const = 0;
        virtual void unBind() const = 0;

        virtual const BufferLayout& getLayout() const = 0;
        virtual void setLayout(const BufferLayout& layout) = 0;

        static VertexBuffer* create(float* vertices, uint32_t size);
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {}

        virtual void bind() const = 0;
        virtual void unBind() const = 0;

        virtual uint32_t getCount() const = 0;

        static IndexBuffer* create(uint32_t* indices, uint32_t size);
    };
}