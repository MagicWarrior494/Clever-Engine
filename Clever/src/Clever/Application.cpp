#include "cvpch.h"
#include "Application.h"
#include "Clever/Events/ApplicationEvent.h"

namespace Clever{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{


		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}