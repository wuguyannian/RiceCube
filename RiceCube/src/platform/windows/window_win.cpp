#include "ricepch.h"
#include "window_win.h"
#include "platform/opengl/context_opengl.h"
#include "event/event_application.h"
#include "event/event_key.h"
#include "event/event_mouse.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace RiceCube
{
    static bool s_glfwInitialized = false;

    static void glfwErrorCallback(int32_t error, const char* description)
    {
        RICE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    Window* Window::create(const WindowProps& props)
    {
        return new WinWindow(props);
    }

    WinWindow::WinWindow(const WindowProps& props)
    {
        init(props);
    }

    WinWindow::~WinWindow()
    {
        shutdown();
    }

    void WinWindow::onUpdate()
    {
        glfwPollEvents();
        m_context->swapBuffers();
    }

    void WinWindow::setVSync(bool enabled)    
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
        m_data.vsync = enabled;
    }

    bool WinWindow::isVSync() const
    {
        return m_data.vsync;
    }

    void WinWindow::init(const WindowProps& props)
    {
        (WindowProps&)m_data = props;

        RICE_INFO("Creating window {0} {1} {2}", props._title, props._width, props._height);

        if (!s_glfwInitialized)
        {
            int32_t success = glfwInit();
            RICE_ASSERTS(success, "Could not intialize GLFW!");
            glfwSetErrorCallback(glfwErrorCallback);
            s_glfwInitialized = true;
        }

        m_window = glfwCreateWindow((int32_t)props._width, (int32_t)props._height, m_data._title.c_str(), nullptr, nullptr);
        
        glfwMakeContextCurrent(m_window);
        m_context = std::unique_ptr<GraphicsContext>(new ContextOpenGL(m_window));
        m_context->init();

        glfwSetWindowUserPointer(m_window, &m_data);
        setVSync(true);

        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int32_t width, int32_t height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data._width = width;
            data._height = height;

            WindowResizeEvent event(width, height);
            data._eventCallback(event);
        });

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data._eventCallback(event);
        });

        glfwSetKeyCallback(m_window, [](GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data._eventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasdEvent event(key);
                    data._eventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data._eventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_window, [](GLFWwindow* window, uint32_t keycode) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keycode);
            data._eventCallback(event);
        });

        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int32_t button, int32_t action, int32_t mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data._eventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data._eventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data._eventCallback(event);
        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data._eventCallback(event);
        });
    }

    void WinWindow::shutdown()
    {
        glfwDestroyWindow(m_window);
    }
}