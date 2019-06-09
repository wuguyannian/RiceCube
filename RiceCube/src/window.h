#pragma once

#include "event/event.h"

namespace RiceCube
{
    struct WindowProps
    {
        std::string _title;
        uint32_t _width;
        uint32_t _height;

        WindowProps(const std::string& title = "RiceCube", uint32_t width  = 1280, uint32_t height = 720)
            : _title(title), _width(width), _height(height)
        {}
    };

    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() {}

        virtual void onUpdate() = 0;

        virtual uint32_t getWidth() const = 0;
        virtual uint32_t getHeight() const = 0;

        virtual void setEventCallback(const EventCallbackFn& callback) = 0;
        virtual void setVSync(bool enabled) = 0;
        virtual bool isVSync() const = 0;

        virtual void *getNativeWindow() const = 0;

        static Window* create(const WindowProps& props = WindowProps());
    };
}