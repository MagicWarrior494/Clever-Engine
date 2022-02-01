#pragma once

#include "Core.h"
#include "Window.h"
#include "Clever/LayerStack.h"
#include "Clever/Events/Event.h"
#include "Clever/Events/ApplicationEvent.h"

#include "Clever/ImGui/ImGuiLayer.h"

#include "Clever/Renderer/Shader.h"

#include "Clever/Renderer/Buffer.h"

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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();
}