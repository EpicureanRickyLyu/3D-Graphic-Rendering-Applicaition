#pragma once

#include "Event.h"
#include "sstream"
namespace Hazel {

	class WindowResizeEvent : public Event
	{
		EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

	private:
		unsigned int m_Width, m_Height;
	};

	class WindowCloseEvent : public Event
	{
		EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	public:
		WindowCloseEvent() = default;

	};

	class AppTickEvent : public Event
	{
		EVENT_CLASS_TYPE(AppTick)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	public:
		AppTickEvent() = default;

	};

	class AppUpdateEvent : public Event
	{
		EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	public:
		AppUpdateEvent() = default;

	};

	class AppRenderEvent : public Event
	{
		EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	public:
		AppRenderEvent() = default;

	};
}