#pragma once

#include "event.h"

namespace RiceCube
{
    class KeyEvent : public Event
    {
    public:
        inline int32_t getKeyCode() const { return m_keyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        KeyEvent(int32_t keycode)
            : m_keyCode(keycode)
        {}

        int32_t m_keyCode = 0;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int32_t keycode, int32_t repeatCount)
            :KeyEvent(keycode), m_repeatCount(repeatCount)
        {}

        inline int32_t getRepeatCount() const { return m_repeatCount; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        int m_repeatCount = 0;
    };

    class KeyReleasdEvent : public KeyEvent
    {
    public:
        KeyReleasdEvent(int32_t keycode)
            :KeyEvent(keycode)
        {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_keyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(int32_t keycode)
            :KeyEvent(keycode)
        {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_keyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
}