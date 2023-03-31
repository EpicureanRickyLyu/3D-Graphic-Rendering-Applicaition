#pragma once
#include "Core.h"
#include "Hazel/Window.h"
#include "LayerStack.h"

#include <memory>
namespace Hazel
{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);

		void PushOverlay(Layer* overlay);

	private:
		bool OnApplicationWindowClosedEvent(Event &e);

	private:
		LayerStack m_layerStack;

		std::unique_ptr<Window> m_Window;

		bool m_isRunning = true;

	};

	//Only declaration here, To be defined in Client
	Application* CreateApplication();
}

