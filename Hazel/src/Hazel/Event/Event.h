#pragma once

#include <string>

namespace Hazel {

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
		EventCategoryApplication    = (1 << 0),// ? ? 
		EventCategoryInput          = (1 << 1),
		EventCategoryKeyboard       = (1 << 2),
		EventCategoryMouse          = (1 << 3),
		EventCategoryMouseButton    = (1 << 4)
	};

	//## will concatenating argument
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
	public:
		virtual ~Event() = default;

		bool m_isHandled = false;

		virtual EventType GetEventType() const = 0;//override in Macro
		virtual const char* GetName() const = 0;//override in Macro
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}
		
		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func)//func must return bool to show the event is handled
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				// when the function to dispatch is handled, change m_isHandled set to true
				m_Event.m_isHandled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}
