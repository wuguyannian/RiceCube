#include "ricepch.h"
#include "context_opengl.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace RiceCube
{
    ContextOpenGL::ContextOpenGL(GLFWwindow* windowHandle)
        : m_windowHandle(windowHandle)
    {
        RICE_ASSERTS(windowHandle, "Window handle is null");
    }

    void ContextOpenGL::init()
    {
        glfwMakeContextCurrent(m_windowHandle);
        int32_t status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        RICE_ASSERTS(status, "Failed to initialize Glad!");

        RICE_INFO("Render: OpengGL");
        RICE_INFO(" Vendor: {0}", glGetString(GL_VENDOR));
        RICE_INFO(" Renderer: {0}", glGetString(GL_RENDERER));
        RICE_INFO(" Version: {0}", glGetString(GL_VERSION));
    }

    void ContextOpenGL::swapBuffers()
    {
        glfwSwapBuffers(m_windowHandle);
    }
}