#include <Clever.h>

class Sandbox : public Clever::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Clever::Application* Clever::CreateApplication()
{
	return new Sandbox();
}