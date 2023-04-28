#include "pch.h"
#include "Application.h"


#include "GLAD/glad.h"

#include "Hazel/Event/ApplicationEvent.h"
#include "Log.h"
namespace Hazel
{
	Application* Application::instance;//static memeber

	Application::Application()
	{
		HZ_CORE_ASSERT(!instance, "Application already exist!");
		instance = this;
		//Set Windows Event Callback to Application OnEvent
		//When Windows Initializing, bind different event type to OpenGL Windows Callback
		//When windows Callback events polled (Called in Windows OnUpdated), this OnEvent Get Called
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN_1(Application::OnEvent));
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

			for (Layer* layer : m_layerStack)
			{
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		//when application event happened, dispatch it to different system
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN_1(Application::OnApplicationWindowClosedEvent));

		//iterate each layer inversely, layers on the top has priority to handle event 
		for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.m_isHandled)
				break;
		}

		HZ_LOG_CORE_TRACE(e);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_layerStack.PushOverlay(overlay);
	}

	bool Application::OnApplicationWindowClosedEvent(Event& e)
	{
		m_isRunning = false;
		return true;
	}

}
