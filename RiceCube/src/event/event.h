#pragma once

#include "ricepch.h"
#include "base.h"

namespace RiceCube
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

#define EVENT_CLASS_TYPE(type)	\
	static EventType getStaticType() { return EventType::##type; } \
	virtual	EventType getEventType() const override { return getStaticType(); } \
	virtual	const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
	virtual int getCategoryFlags() const override { return category; }

	class Event
	{
	public:
		virtual EventType getEventType() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual const char* getName() const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isInCategory(EventCategory category) { return getCategoryFlags() & category; }

		bool _handled = false;
	};

	class EventDispatcher
	{
	public:
		template<typename T>
		using EventFn = std::function<bool(T&)>;
		
		EventDispatcher(Event& evt)
			: m_evt(evt)
		{}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_evt.getEventType() == T::getStaticType())
			{
				m_evt._handled = func(*(T*)& m_evt);
                return true;
			}
            return false;
		}

	private:
		Event& m_evt;
	};

	inline std::ostream& operator << (std::ostream& os, const Event& evt)
	{
		return os << evt.toString();
	}
}