#include <Hazel.h>





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