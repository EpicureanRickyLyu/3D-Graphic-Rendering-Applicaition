#pragma once
#include "Hazel.h"
#include "Event/Event.h"

#include <functional>
namespace Hazel
{
	struct WindowProps
	{
		std::string m_Title;
		u32 m_Width;
		u32 m_Height;

		WindowProps(const std::string title = "Hazel", u32 width = 1280, u32 height = 720)
			:m_Title(title), m_Width(width), m_Height(height)
		{
		}

	};

	class HAZEL_API Window
	{
	public:
		using EventCallbackFunc = std::function<void(Event&)>;
		virtual ~Window() {};
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFunc&callback ) const = 0;
		virtual void SetVSync(bool enabled) const = 0;
		virtual void IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());

	};

}