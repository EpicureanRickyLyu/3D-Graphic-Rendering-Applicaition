#include "pch.h"
#include "Application.h"
#include "Hazel/Event/ApplicationEvent.h"
#include "Log.h"
namespace Hazel
{

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1920, 1080);
		HZ_LOG_TRACE(e);
	}

}
