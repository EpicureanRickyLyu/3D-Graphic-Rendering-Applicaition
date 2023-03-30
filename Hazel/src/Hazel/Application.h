#pragma once
#include "Core.h"
#include "Hazel/Window.h"

#include <memory>
namespace Hazel
{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_isRunning = true;
	};

	//Only declaration here, To be defined in Client
	Application* CreateApplication();
}

