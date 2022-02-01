#include <Clever.h>

#include "imgui/imgui.h"

class ExampleLayer : public Clever::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Clever::Input::IsKeyPressed(CV_KEY_TAB))
			CV_INFO("Tab key is pressed");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Clever::Event& event) override
	{
		//CV_TRACE("{0}", event);
	}
};

class Sandbox : public Clever::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Clever::Application* Clever::CreateApplication()
{
	return new Sandbox();
}

