#pragma once

#include "window.h"
#include "render/graphics_context.h"

struct GLFWwindow;

namespace RiceCube
{
    class WinWindow : public Window
    {
    public:
        WinWindow(const WindowProps& props);
        virtual ~WinWindow();

        void onUpdate() override;

        inline uint32_t getWidth() const override { return m_data._width; }
        inline uint32_t getHeight() const override { return m_data._height; }

        inline void setEventCallback(const EventCallbackFn& callback) override { m_data._eventCallback = callback; }
        void setVSync(bool enabled) override;
        bool isVSync() const override;

        inline virtual void* getNativeWindow() const { return m_window; }

    private:
        virtual void init(const WindowProps& props);
        virtual void shutdown();

    private:
        struct WindowData : public WindowProps
        {
            bool vsync = false;

            EventCallbackFn _eventCallback;
        };

        WindowData m_data;
        GLFWwindow* m_window;
        std::unique_ptr<GraphicsContext> m_context;
    };
}