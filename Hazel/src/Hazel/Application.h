#pragma once
#include "Core.h"
#include "Hazel/Window.h"
#include "LayerStack.h"

#include <memory>
namespace Hazel
{
	class HAZEL_API Application
	{
		MAKE_NONCOPYABLE(Application);
	public:
		Application();

		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);

		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; };

		inline static Application& GetInstance() { return *instance; };

	private:
		bool OnApplicationWindowClosedEvent(Event &e);

	private:
		LayerStack m_layerStack;

		std::unique_ptr<Window> m_Window;

		bool m_isRunning = true;

		static Application* instance;
	};

	//Only declaration here, To be defined in Client
	Application* CreateApplication();
}

