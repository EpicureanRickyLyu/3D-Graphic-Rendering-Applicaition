#pragma once
#include "core.h"
#include "Event/Event.h"

#include <functional>
namespace Hazel
{
	struct WindowProps
	{
		std::string m_Title;
		unsigned int m_Width;
		unsigned int m_Height;

		WindowProps(const std::string title = "Capybara", unsigned int width = 1920, unsigned int height = 1080)
			:m_Title(title), m_Width(width), m_Height(height)
		{
		}

	};

	class HAZEL_API Window
	{
	public:
		using EventCallbackFunc = std::function<void(Event&)>;
		virtual ~Window() = default;
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFunc&callback )  = 0;
		virtual void SetVSync(bool enabled)  = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};

}