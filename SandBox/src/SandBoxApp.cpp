#include <Hazel.h>

class SandBox :public Hazel::Application
{
public:
	//Base Application Constructor will create a window
	SandBox()
	{
		PushLayer(new Hazel::ImGuiLayer());
	}

	~SandBox()
	{

	}
};

//define entry point function implementation
Hazel::Application* Hazel::CreateApplication()
{
	return new SandBox();
}