#pragma once

#include "render/buffer.h"

namespace RiceCube
{
    class VertexBufferOpenGL : public VertexBuffer
    {
    public:
        VertexBufferOpenGL(float* vertices, uint32_t size);
        virtual ~VertexBufferOpenGL();

        virtual void bind() const override;
        virtual void unBind() const override;

        virtual const BufferLayout& getLayout() const override { return m_layout; }
        virtual void setLayout(const BufferLayout& layout) override { m_layout = layout; }

    private:
        uint32_t m_renderID = 0;
        BufferLayout m_layout;
    };

    class IndexBufferOpenGL : public IndexBuffer
    {
    public:
        IndexBufferOpenGL(uint32_t* indices, uint32_t count);
        virtual ~IndexBufferOpenGL();

        virtual void bind() const;
        virtual void unBind() const;

        virtual uint32_t getCount() const { return m_count; }

    private:
        uint32_t m_renderID = 0;
        uint32_t m_count = 0;
    };
}