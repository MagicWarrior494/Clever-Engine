#include <Clever.h>

#include "imgui/imgui.h"

#include "GLFW/include/GLFW/glfw3.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Clever::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(65.0f, 1280.0f, 720.0f, 0.1f, 150.0f, glm::vec3(0,0,10)), m_SquarePosition(0.0f)
	{
		m_VertexArray.reset(Clever::VertexArray::Create());

		float vertices[8 * 5] = {
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5,   0.5f, 1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f,  0.5f, -0.5f, 1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f
		};

		Clever::Ref<Clever::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Clever::VertexBuffer::Create(vertices, sizeof(vertices)));
		Clever::BufferLayout layout = {
			{ Clever::ShaderDataType::Float3, "a_Position" },
			{ Clever::ShaderDataType::Float2, "a_TexCoord" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

			

		uint32_t indices[3 * 6 * 2] = 
		{ 
			3, 2, 1,
			7, 6, 5,
			6, 2, 5,
			7, 3, 8,
			8, 1, 6,
			4, 5, 2,
			3, 4, 2,
			7, 8, 6,
			6, 1, 2,
			7, 4, 3,
			8, 3, 1,
			4, 7, 5
		};
		for (int i = 0; i < 3 * 6 * 2; i++) {
			indices[i]--;
		}
		/*uint32_t indices[3] = { 0,1,2 };*/
		Clever::Ref<Clever::IndexBuffer> indexBuffer;
		indexBuffer.reset(Clever::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
			}

		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}

		)";

		m_Shader.reset(Clever::Shader::Create(vertexSrc, fragmentSrc));

		m_Texture= Clever::Texture2D::Create("C:/clever/Clever/assets/textures/corndog.png");

		std::dynamic_pointer_cast<Clever::OpenGLShader>(m_Shader)->Bind();
		std::dynamic_pointer_cast<Clever::OpenGLShader>(m_Shader)->UploadUniformInt("u_Texture", 0);//Texture Slot
	}

	void OnUpdate(Clever::Timestep ts) override
	{

		float time = ts;
		if (Clever::Input::IsKeyPressed(CV_KEY_A))
			m_Camera.Translate(Clever::Camera_Movement::LEFT, time);

		if (Clever::Input::IsKeyPressed(CV_KEY_D))
			m_Camera.Translate(Clever::Camera_Movement::RIGHT, time);

		if (Clever::Input::IsKeyPressed(CV_KEY_W))
			m_Camera.Translate(Clever::Camera_Movement::FORWARD, time);

		if (Clever::Input::IsKeyPressed(CV_KEY_S))
			m_Camera.Translate(Clever::Camera_Movement::BACKWARD, time);

		if (Clever::Input::IsKeyPressed(CV_KEY_SPACE))
			m_Camera.Translate(Clever::Camera_Movement::UP, time);

		if (Clever::Input::IsKeyPressed(CV_KEY_LEFT_SHIFT))
			m_Camera.Translate(Clever::Camera_Movement::DOWN, time);
		
		if (Clever::Input::IsMouseButtonPressed(1) && !m_LockMouse)
		{
			m_LockMouse = true;
			Clever::Input::HideMouse(true);
		}
			
		if (Clever::Input::IsKeyPressed(CV_KEY_ESCAPE))
		{
			m_LockMouse = false;
			Clever::Input::HideMouse(false);
		}
			
		if (m_LockMouse && Clever::Input::GetMousePosition() != m_MiddleOfScreen)
		{
			std::pair<float, float> currentMousePos = Clever::Input::GetMousePosition();

			if (m_FirstMouse)
			{
				m_LastX = currentMousePos.first;
				m_LastY = currentMousePos.second;
				m_FirstMouse = false;
			}

			float xoffset = currentMousePos.first - m_LastX;
			float yoffset = m_LastY - currentMousePos.second; //Reversed since y-coordinates go from bottom to top

			if (currentMousePos.first < 0 || currentMousePos.first > m_MiddleOfScreen.first * 2 || currentMousePos.second < 0 || currentMousePos.second > m_MiddleOfScreen.second * 2)
			{
				Clever::Input::SetMousePos(m_MiddleOfScreen.first, m_MiddleOfScreen.second);
				m_LastX = m_MiddleOfScreen.first;
				m_LastY = m_MiddleOfScreen.second;
			}
			else
			{
				m_LastX = currentMousePos.first;
				m_LastY = currentMousePos.second;
			}
			m_Camera.ProcessMouseMovement(xoffset, yoffset);
		}

		Clever::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Clever::RenderCommand::SetDepthTesting(true);
		Clever::RenderCommand::Clear();
		m_Camera.RecaluclateViewMatrix();

		Clever::Renderer::BeginScene(m_Camera);

		glm::vec4 redColor(0.8, 0.2, 0.3, 1.0);
		glm::vec4 blueColor(0.2, 0.3, 0.8, 1.0);

		std::dynamic_pointer_cast<Clever::OpenGLShader>(m_Shader)->Bind();
		std::dynamic_pointer_cast<Clever::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", m_SquareColor);

		int count = 0;

		for (int z = 0; z < 5; z++) {
			for (int y = 0; y < 5; y++) {
				for (int x = 0; x < 5; x++) {

					glm::vec3 pos(x * 2, y * 2, z * 2);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);

					Clever::Renderer::Submit(m_Shader, m_VertexArray, transform);

					count++;
				}
			}
		}

		m_Texture->Bind();

		Clever::Renderer::EndScene();
	}


	virtual void OnImGuiRender(Clever::Timestep ts) override
	{
		static float sliderMovementSpeedfloat = m_Camera.GetMovementSpeed();
		static float sliderRotationSpeedfloat = m_Camera.GetRotationSpeed();

		glm::vec3 cameraPos = m_Camera.GetPosition();
		glm::vec3 cameraRot = m_Camera.GetRotation();
		ImGui::Begin("Settings");
		ImGui::Text("CameraPosition: %f, %f, %f", cameraPos.x, cameraPos.y, cameraPos.z);

		ImGui::ColorEdit3("Box Color", glm::value_ptr(m_SquareColor));

		ImGui::Text("CameraRotation: %f, %f, %f", cameraRot.x, cameraRot.y, cameraRot.z);
		ImGui::Text("FrameRate: %f", 1.0f/ts.GetSeconds());
		ImGui::SliderFloat("Movement Speed", &sliderMovementSpeedfloat, 0.0f, 10.0f);
		ImGui::SliderFloat("Rotation Speed", &sliderRotationSpeedfloat, 0.0f, 10.0f);
		ImGui::Text("Mouse_Pos: %f, %f, %f", Clever::Input::GetMouseX(), Clever::Input::GetMouseY());
		ImGui::End();

		m_Camera.SetMovementSpeed(sliderMovementSpeedfloat);
		m_Camera.SetRotationSpeed(sliderRotationSpeedfloat);
	}

	void OnEvent(Clever::Event& event) override
	{
		//CV_INFO("An EVENT HAPPENED it was: {0}", event.GetEventType());
		if (event.GetEventType() == Clever::EventType::WindowFocus)
		{
			m_LockMouse = true;
			Clever::Input::HideMouse(true);
		}
		else if (event.GetEventType() == Clever::EventType::WindowLostFocus)
		{
			m_LockMouse = false;
			Clever::Input::HideMouse(false);
		}
	}

private:
	Clever::Ref<Clever::Shader> m_Shader;
	Clever::Ref<Clever::VertexArray> m_VertexArray;

	Clever::PerspectiveCamera m_Camera;

	Clever::Ref<Clever::Texture2D> m_Texture;

	glm::vec3 m_SquarePosition;

	std::pair<float, float> m_MiddleOfScreen = std::pair<float, float>(1280.0f / 2, 720.0f / 2);

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

	bool m_LockMouse = true;

private:
	float m_LastX = 1280.0f / 2;
	float m_LastY = 720.0f / 2;
	bool m_FirstMouse = true;
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

