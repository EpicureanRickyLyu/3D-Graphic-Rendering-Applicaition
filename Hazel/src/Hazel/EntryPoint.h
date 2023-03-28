#pragma once
#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();

	HZ_CORE_WARN("Initialized Log!");

	int a = 1, b = 10;
	HZ_CLIENT_INFO("Hello! value1:{0} value2:{1}", a, b);

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#endif