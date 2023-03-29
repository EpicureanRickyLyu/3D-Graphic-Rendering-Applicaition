#include "Hazel/Window.h"

#include "GLFW/glfw3.h"

namespace Hazel
{
	class WindowsWindow:public Window
	{
	public:
		WindowsWindow(const WindowProps& Props);

		void OnUpdate() override;

		unsigned int GetWidth() const override;

		unsigned int GetHeight() const override;

		void SetEventCallback(const EventCallbackFunc& callback) const override;

		void SetVSync(bool enabled) const override;

		void IsVSync() const override;

	private:
		virtual void Init(const WindowProps& Props);
		virtual void ShutDown();

	private:
		GLFWwindow* m_Window;


		struct WindowData
		{
			//using EventCallbackFunc = std::function<void(Event&)>;
			std::string m_title;
			u32 m_width, m_height;
			bool VSync;

			EventCallbackFunc EventCallback;
		};

		WindowData m_data;
	};


}