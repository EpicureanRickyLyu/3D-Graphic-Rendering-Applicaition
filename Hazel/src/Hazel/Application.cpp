#include "pch.h"
#include "Application.h"


#include "GLFW/glfw3.h"

#include "Hazel/Event/ApplicationEvent.h"
#include "Log.h"
namespace Hazel
{
	#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1) 

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		//Set Windows Event Callback to Application OnEvent
		//When Windows Initializing, bind different event type to OpenGL Windows Callback
		//When windows Callback events polled (Called in Windows OnUpdated), this OnEvent Get Called
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_isRunning)
		{
			glClearColor(1,1,1,1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		//when application event happened, dispatch it to different system
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnApplicationWindowClosedEvent));

		HZ_LOG_CORE_TRACE(e);
	}

	bool Application::OnApplicationWindowClosedEvent(Event& e)
	{
		m_isRunning = false;
		return true;
	}

}
