#include "ricepch.h"
#include "buffer_opengl.h"
#include <glad/glad.h>

namespace RiceCube
{
    VertexBufferOpenGL::VertexBufferOpenGL(float* vertices, uint32_t size)
    {
        glCreateBuffers(1, &m_renderID);
        glBindBuffer(GL_ARRAY_BUFFER, m_renderID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBufferOpenGL::~VertexBufferOpenGL()
    {
        glDeleteBuffers(1, &m_renderID);
    }

    void VertexBufferOpenGL::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_renderID);
    }

    void VertexBufferOpenGL::unBind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    IndexBufferOpenGL::IndexBufferOpenGL(uint32_t* indices, uint32_t count)
        : m_count(count)
    {
        glCreateBuffers(1, &m_renderID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    IndexBufferOpenGL::~IndexBufferOpenGL()
    {
        glDeleteBuffers(1, &m_renderID);
    }

    void IndexBufferOpenGL::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderID);
    }

    void IndexBufferOpenGL::unBind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}