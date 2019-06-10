#pragma once

#include "render/graphics_context.h"

struct GLFWwindow;

namespace RiceCube
{
    class ContextOpenGL : public GraphicsContext
    {
    public:
        ContextOpenGL(GLFWwindow* windowHandle);

        virtual void init() override;
        virtual void swapBuffers() override;
    private:
        GLFWwindow* m_windowHandle;
    };
}