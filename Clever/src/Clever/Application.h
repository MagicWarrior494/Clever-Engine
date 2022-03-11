#pragma once

#include "Core.h"
#include "Window.h"
#include "Clever/LayerStack.h"
#include "Clever/Events/Event.h"
#include "Clever/Events/ApplicationEvent.h"

#include "Clever/Core/Timestep.h"

#include "Clever/ImGui/ImGuiLayer.h"

#include "Clever/Renderer/Shader.h"
#include "Clever/Renderer/Buffer.h"
#include "Clever/Renderer/VertexArray.h"
#include "Clever/Renderer/OrthographicCamera.h"

namespace Clever {
	
	class CLEVER_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *m_Window; }

		static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private :

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		Timestep m_LastFrameTime;
	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();
}