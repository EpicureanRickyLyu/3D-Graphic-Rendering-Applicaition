#include <Hazel.h>
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
class SandBox :public Hazel::Application
{
public:
	SandBox()
	{

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