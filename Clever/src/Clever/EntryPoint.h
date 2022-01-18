#pragma once
#ifdef CV_PLATFORM_WINDOWS

extern Clever::Application* Clever::CreateApplication();

int main(int argc, char** argv)
{
	Clever::Log::Init();
	CV_CORE_WARN("Initialize Log!");
	int a = 5;
	CV_INFO("Initialize Log but fron yeah! Var = {0}", a);

	auto app = Clever::CreateApplication();
	app->Run();
	delete app;
}

#endif // CL_PLATFORM_WINDOWS