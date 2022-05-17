#include <Clever.h>
#include "imgui/imgui.h"

#include "GLFW/include/GLFW/glfw3.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Clever::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(65.0f, 1280.0f, 720.0f, 0.1f, 150.0f, glm::vec3(1,8,23)), m_SquarePosition(0.0f)
	{

		staticObject.push_back(Clever::GameObject(m_Cube, { -.5, -0.5, -.5 }, { 10, 1, 10 }));
		dynamicObject.push_back(Clever::GameObject(m_Cube, { 0, 15, 0 }));

		/*dynamicObject.push_back(Clever::GameObject(m_Dragon, {0, 2, 10,}, {0,0,0}, {1,1,1}, {0.8,0.2,0.2}));
		dynamicObject.push_back(Clever::GameObject(m_Dragon, { 10, 2, 0, },  { 0,90,0 },  { 1,1,1 }, { 0.2,0.8,0.2 }));
		dynamicObject.push_back(Clever::GameObject(m_Dragon, { -10, 2, 0, }, { 0,180,0 }, { 1,1,1 }, { 0.2,0.2,0.8 }));
		dynamicObject.push_back(Clever::GameObject(m_Dragon, { 0, 2, -10, }, { 0,270,0 }, { 1,1,1 }, { 0.5,0.2,0.6 }));
*/

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					lights.push_back(Clever::GameObject(m_Light, m_LightPos + glm::vec3(((j % 2) - 0.5) * 50, i * 20, (((k) % 2) - 0.5) * 50), { 0,0,0 }, { 0.5, 0.5, 0.5 }, m_LightColor));
				}
			}
		}
	}

	void OnUpdate(Clever::Timestep ts) override
	{
		{
			float time = ts;

			std::vector<glm::vec3> accelerations;
			accelerations.push_back({ 0,-4,0 });

			if (Clever::Input::IsKeyPressed(CV_KEY_A))
			{
				dynamicObject.at(0).m_Velocity.x = -4;
			}
				//m_Camera.Translate(Clever::Camera_Movement::LEFT, time);
			else if (Clever::Input::IsKeyPressed(CV_KEY_D))
				dynamicObject.at(0).m_Velocity.x = 4;
				//m_Camera.Translate(Clever::Camera_Movement::RIGHT, time);
			else
				dynamicObject.at(0).m_Velocity.x = 0;

			if (Clever::Input::IsKeyPressed(CV_KEY_W))
				dynamicObject.at(0).m_Velocity.z = -4;
				//m_Camera.Translate(Clever::Camera_Movement::FORWARD, time);
			else if (Clever::Input::IsKeyPressed(CV_KEY_S))
				dynamicObject.at(0).m_Velocity.z = 4;
				//m_Camera.Translate(Clever::Camera_Movement::BACKWARD, time);
			else
				dynamicObject.at(0).m_Velocity.z = 0;


			if (Clever::Input::IsKeyPressed(CV_KEY_SPACE))
				dynamicObject.at(0).m_Velocity.y = 4;

				//m_Camera.Translate(Clever::Camera_Movement::UP, time);

			//if (Clever::Input::IsKeyPressed(CV_KEY_LEFT_SHIFT))
				//m_Camera.Translate(Clever::Camera_Movement::DOWN, time);

			if (startSim)
			{
				Clever::PhysicsHandler::updatePositions(dynamicObject, staticObject, accelerations, ts);
			}
				
			if (Clever::Input::IsKeyPressed(CV_KEY_T))
			{
				startSim = true;
			}

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

		}

		Clever::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Clever::RenderCommand::SetDepthTesting(true);
		Clever::RenderCommand::Clear();
		m_Camera.RecaluclateViewMatrix();

		Clever::Renderer::BeginScene(m_Camera);

		for (int i = 0; i < lights.size(); i++)
		{
			lights.at(i).setColor(m_LightColor);
		}

		std::vector<glm::vec3> lightPositions;
		std::vector<glm::vec3> lightColor;
		for (int i = 0; i < lights.size(); i++)
		{
			lightPositions.push_back(lights.at(i).m_Position);
			lightColor.push_back(lights.at(i).m_Color);
		}

		for (const Clever::GameObject& obj : dynamicObject)
		{
			Clever::Ref<Clever::Shader> shader = obj.getShader();
			std::dynamic_pointer_cast<Clever::OpenGLShader>(shader)->Bind();
			std::dynamic_pointer_cast<Clever::OpenGLShader>(shader)->UploadUniformFloat3("u_ObjectColor", obj.m_Color);
			std::dynamic_pointer_cast<Clever::OpenGLShader>(shader)->UploadUniformFloat3("u_viewPos", m_Camera.GetPosition());

			std::dynamic_pointer_cast<Clever::OpenGLShader>(shader)->UploadUniformFloat3Array("u_lightPos", lightPositions);
			std::dynamic_pointer_cast<Clever::OpenGLShader>(shader)->UploadUniformFloat3Array("u_lightColor", lightColor);


			glm::mat4 transform = glm::translate(glm::mat4(1.0f), obj.m_Position);
			transform = glm::rotate(transform, obj.m_Rotation.y, { 0, 1, 0 });
			transform = glm::scale(transform, obj.m_Scale);

			Clever::Renderer::Submit(shader, obj.getVertexArray(), transform);
		}
		for (const Clever::GameObject& obj : staticObject)
		{
			Clever::Ref<Clever::Shader> shader = obj.getShader();
			std::dynamic_pointer_cast<Clever::OpenGLShader>(shader)->Bind();
			std::dynamic_pointer_cast<Clever::OpenGLShader>(shader)->UploadUniformFloat3("u_ObjectColor", obj.m_Color);
			std::dynamic_pointer_cast<Clever::OpenGLShader>(shader)->UploadUniformFloat3("u_viewPos", m_Camera.GetPosition());

			std::dynamic_pointer_cast<Clever::OpenGLShader>(shader)->UploadUniformFloat3Array("u_lightPos", lightPositions);
			std::dynamic_pointer_cast<Clever::OpenGLShader>(shader)->UploadUniformFloat3Array("u_lightColor", lightColor);


			glm::mat4 transform = glm::translate(glm::mat4(1.0f), obj.m_Position);
			transform = glm::rotate(transform, obj.m_Rotation.y, { 0, 1, 0 });
			transform = glm::scale(transform, obj.m_Scale);

			Clever::Renderer::Submit(shader, obj.getVertexArray(), transform);
		}

		for (const Clever::GameObject& obj : lights)
		{
			Clever::Ref<Clever::Shader> shader = obj.getShader();
			std::dynamic_pointer_cast<Clever::OpenGLShader>(shader)->Bind();

			std::dynamic_pointer_cast<Clever::OpenGLShader>(shader)->UploadUniformFloat3("u_lightColor", obj.m_Color);

			glm::mat4 transform = glm::scale(glm::mat4(1.0f), obj.m_Scale);
			transform = glm::translate(transform, obj.m_Position);
			Clever::Renderer::Submit(shader, obj.getVertexArray(), transform);
		}
		//m_Texture->Bind();

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

		ImGui::ColorEdit3("Light Color", glm::value_ptr(m_LightColor));

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

	Clever::CompiledShader standard = Clever::CompiledShader("C:/clever/Clever/assets/Shaders/Standard.vert", "C:/clever/Clever/assets/Shaders/Standard.frag");
	Clever::CompiledShader light = Clever::CompiledShader("C:/clever/Clever/assets/Shaders/Light.vert", "C:/clever/Clever/assets/Shaders/Light.frag");

	Clever::ObjectData m_Dragon = Clever::ObjectData("C:/clever/Clever/assets/Object/Torus.obj", standard);
	Clever::ObjectData m_Cube = Clever::ObjectData("C:/clever/Clever/assets/Object/Cube.obj", standard);
	Clever::ObjectData m_Light = Clever::ObjectData("C:/clever/Clever/assets/Object/Cube.obj", light);

	std::vector<Clever::GameObject> dynamicObject;
	std::vector<Clever::GameObject> staticObject;
	std::vector<Clever::GameObject> lights;

	bool Multiplayer = false;

	bool startSim = false;

	Clever::PerspectiveCamera m_Camera;

	Clever::Ref<Clever::Texture2D> m_Texture;

	glm::vec3 m_SquarePosition;

	glm::vec3 m_ObjectColor = { 0.2f, 0.3f, 0.8f };
	glm::vec3 m_LightPos = { 0,5,0 };
	glm::vec3 m_LightColor = {1, 1, 1 };

	Clever::Client connection = Clever::Client("127.0.0.1", 54000);

	glm::vec3 playerPosition = { 5,15,5 };

	bool m_LockMouse = true;

	float m_LastX = 1280.0f / 2;
	float m_LastY = 720.0f / 2;
	bool m_FirstMouse = true;

	std::pair<float, float> m_MiddleOfScreen = std::pair<float, float>(1280.0f / 2, 720.0f / 2);

};

class Sandbox : public Clever::Application
{
public:
	Sandbox()
	{
		Clever::Layer* exampleLayer = new ExampleLayer();
		PushLayer(exampleLayer);
	}

	~Sandbox()
	{

	}
};

Clever::Application* Clever::CreateApplication()
{
	return new Sandbox();
}

