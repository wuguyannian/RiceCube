﻿#pragma once

#include "event.h"

namespace RiceCube
{
	class WindowResizeEvent : public Event
	{
	public:
        WindowResizeEvent(uint32_t width, uint32_t height)
        	: m_width(width), m_height(height)
        {}
        
        inline uint32_t getWidth() { return m_width; }
        inline uint32_t getHeight() { return m_height; }
        
        std::string toString() const override
        {
        	std::stringstream ss;
        	ss << "WindowResizeEvent: " << m_width << ", " << m_height;
        	return ss.str();
        }
        
        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		uint32_t m_width;
		uint32_t m_height;
	};

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class AppTickEvent : public Event
    {
    public:
        AppTickEvent() {}

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class AppUpdateEvent : public Event
    {
    public:
        AppUpdateEvent() {}

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() {}

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
}
