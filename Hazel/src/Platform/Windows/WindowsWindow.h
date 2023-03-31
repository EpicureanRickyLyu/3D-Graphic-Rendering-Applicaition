#pragma once

#include "GLFW/glfw3.h"

#include "Hazel/Window.h"


namespace Hazel
{
	class WindowsWindow :public Window
	{
	public:
		WindowsWindow(const WindowProps& Props);

		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_data.m_width; };

		unsigned int GetHeight() const override { return m_data.m_height; };

		void SetEventCallback(const EventCallbackFunc& callback)  override { m_data.m_eventCallback = callback; };

		void SetVSync(bool enabled)  override;

		bool IsVSync() const override;

	private:
		virtual void Init(const WindowProps& Props);

		virtual void ShutDown();

	private:
		//GLFW Window Type Pointer
		GLFWwindow* m_Window { nullptr };

		struct WindowData
		{
			//using EventCallbackFunc = std::function<void(Event&)>;
			std::string m_title;
			unsigned int m_width, m_height;
			bool VSync;

			EventCallbackFunc m_eventCallback;
		};

		WindowData m_data;
	};


}