#include "pch.h"

#include "WindowsWindow.h"

#include "Hazel/Log.h"

namespace Hazel
{

	static bool s_isGLFWInitialized = false;

	//Window.h static function, implement platform specific
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& Props)
	{
		Init(Props);
	}

	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		m_data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_data.VSync;
	}

	void WindowsWindow::Init(const WindowProps& Props)
	{
		m_data.m_title = Props.m_Title;
		m_data.m_width = Props.m_Width;
		m_data.m_height = Props.m_Height;

		HZ_LOG_CORE_INFO("Ceateing window {0} {1} {2}", m_data.m_title, m_data.m_width, m_data.m_height);

		if (!s_isGLFWInitialized)
		{
			int success = glfwInit();

			// #TODO ASSERTION ERROR
			HZ_CORE_ASSERT(success, "Could not initialize GLFW!");

			s_isGLFWInitialized = true;
		}
		m_Window = glfwCreateWindow((int)m_data.m_width, (int)m_data.m_height, m_data.m_title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_data);
		SetVSync(true);
	}

	void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(m_Window);
	}

}
