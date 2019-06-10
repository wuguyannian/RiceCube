#include "ricepch.h"
#include "buffer.h"
#include "render/renderer.h"
#include "platform/opengl/buffer_opengl.h"

namespace RiceCube
{
    VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
    {
        switch (Renderer::getAPI())
        {
            case RenderAPI::None:
                RICE_ASSERTS(false, "RenderAPI::None is currently not supported!");
                return nullptr;
            case RenderAPI::OpenGL:
                return new VertexBufferOpenGL(vertices, size);
        }
        return nullptr;
    }

    IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t size)
    {
        switch (Renderer::getAPI())
        {
        case RenderAPI::None:
            RICE_ASSERTS(false, "RenderAPI::None is currently not supported!");
            return nullptr;
        case RenderAPI::OpenGL:
            return new IndexBufferOpenGL(indices, size);
        }
        return nullptr;
    }
}