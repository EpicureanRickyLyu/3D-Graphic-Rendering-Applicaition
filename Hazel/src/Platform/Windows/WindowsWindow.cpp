#include "pch.h"

#include "WindowsWindow.h"
#include "Hazel/Event/ApplicationEvent.h"
#include "Hazel/Event/KeyEvent.h"
#include "Hazel/Event/MouseEvent.h"
#include "Hazel/Log.h"

#include "glad/glad.h"//GLAD will include glfw now
namespace Hazel
{

	static bool s_isGLFWInitialized = false;

	//Local Function to GLFW Error Callback
	static void GLFWErrorCallback(int error, const char* description)
	{
		HZ_LOG_CORE_ERROR("GLFW error: ({0}): {1}", error, description);
	}

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
		//Process All Pending Events, All Event Callbacks
		glfwPollEvents();

		//double buffer, swap rendering buffer base on an Interval
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
		//Initialize Customize WindowData
		m_data.m_title = Props.m_Title;
		m_data.m_width = Props.m_Width;
		m_data.m_height = Props.m_Height;

		HZ_LOG_CORE_INFO("Ceateing window {0} {1} {2}", m_data.m_title, m_data.m_width, m_data.m_height);

		if (!s_isGLFWInitialized)
		{
			int success = glfwInit();

			// #TODO ASSERTION ERROR
			HZ_CORE_ASSERT(success, "Could not initialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);

			s_isGLFWInitialized = true;
		}
		//Create GLFW Window based on Customized WindowData
		m_Window = glfwCreateWindow((int)m_data.m_width, (int)m_data.m_height, m_data.m_title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		//init GLAD Like GLEW
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Fail to initialize Glad");

		glfwSetWindowUserPointer(m_Window, &m_data);
		SetVSync(true);

		//Set GLFW Callbacks
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event(keycode);
				data.m_eventCallback(event);
			});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				//return the void* pointer to the GLFW Window passed in
				 WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				 data.m_width = width;
				 data.m_height = height;

				 WindowResizeEvent event(width, height);
				 data.m_eventCallback(event);//Call The Event Callback and pass in an event as a argument
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				//return the void* pointer to the GLFW Window passed in
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent event;
				data.m_eventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				//return the void* pointer to the GLFW Window passed in
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				//Parse GLFW specific key arguments into customize keyCode Type
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.m_eventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.m_eventCallback(event);
						break;
					}
					case GLFW_REPEAT://GLFW Will Distinguish Repeat and Press
					{
						KeyPressedEvent event(key, 1);
						data.m_eventCallback(event);
						break;
					}
				}
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				//return the void* pointer to the GLFW Window passed in
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.m_eventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.m_eventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				//return the void* pointer to the GLFW Window passed in
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.m_eventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				//return the void* pointer to the GLFW Window passed in
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.m_eventCallback(event);
			});
	}

	void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(m_Window);
	}

}
