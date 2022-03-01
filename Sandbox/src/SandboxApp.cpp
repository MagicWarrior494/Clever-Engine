#include <Clever.h>

#include "imgui/imgui.h"

class ExampleLayer : public Clever::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Clever::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.8f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.8f, 1.0f,
		};

		std::shared_ptr<Clever::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Clever::VertexBuffer::Create(vertices, sizeof(vertices)));
		Clever::BufferLayout layout = {
			{ Clever::ShaderDataType::Float3, "a_Position" },
			{ Clever::ShaderDataType::Float4, "a_Color" },
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		std::shared_ptr<Clever::IndexBuffer> indexBuffer;
		indexBuffer.reset(Clever::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Clever::VertexArray::Create());

		float squareVertices[3 * 4] = {
			 -0.75f, -0.75f, 0.0f,
			  0.75f, -0.75f, 0.0f,
			  0.75f,  0.75f, 0.0f,
			 -0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Clever::VertexBuffer> squareVB;
		squareVB.reset(Clever::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Clever::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Clever::IndexBuffer> squareIB;
		squareIB.reset(Clever::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;
			
			uniform mat4 u_ViewProjection;

			void main()
			{
				v_Color = a_Color;
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
			}

		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}

		)";


		m_Shader.reset(new Clever::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;
			
			uniform mat4 u_ViewProjection;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
			}

		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}

		)";

		m_BlueShader.reset(new Clever::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate() override
	{

		if (Clever::Input::IsKeyPressed(CV_KEY_LEFT))
			m_CameraPosition.x += m_CameraSpeed;

		if (Clever::Input::IsKeyPressed(CV_KEY_RIGHT))
			m_CameraPosition.x -= m_CameraSpeed;

		if (Clever::Input::IsKeyPressed(CV_KEY_DOWN))
			m_CameraPosition.y += m_CameraSpeed;

		if (Clever::Input::IsKeyPressed(CV_KEY_UP))
			m_CameraPosition.y -= m_CameraSpeed;

		Clever::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Clever::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		//m_Camera.SetRotation({ 0.0f, 0.0f, 45.0f });

		Clever::Renderer::BeginScene(m_Camera);

		{
			Clever::Renderer::Submit(m_BlueShader, m_SquareVA);
			Clever::Renderer::Submit(m_Shader, m_VertexArray);

		}

		Clever::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		
	}

	void OnEvent(Clever::Event& event) override
	{
		//Clever::EventDispatcher dispatcher(event);
		//dispatcher.Dispatch<Clever::KeyPressedEvent>(CV_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}
private:
	std::shared_ptr<Clever::Shader> m_Shader;
	std::shared_ptr<Clever::VertexArray> m_VertexArray;

	std::shared_ptr<Clever::Shader> m_BlueShader;
	std::shared_ptr<Clever::VertexArray> m_SquareVA;

	Clever::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 0.1f;
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

