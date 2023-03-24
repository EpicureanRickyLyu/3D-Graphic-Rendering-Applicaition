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

int main()
{
	SandBox* sandbox = new SandBox();
	sandbox->Run();
	delete sandbox;
	return 0;
}