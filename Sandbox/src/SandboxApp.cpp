#include <Clever.h>
#include "imgui/imgui.h"
#include "PlayerManager.h"
#include "ECSManager.h"

#include <glm/gtc/type_ptr.hpp>

#include "GLFW/include/GLFW/glfw3.h"

#include "Clever/ECS/DataHandelers/RenderingData.h"

#include <cstdlib>
#include <time.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include <algorithm>

class MainLayer : public Clever::Layer
{
public:
	MainLayer()
		: Layer("Example")
	{
		Clever::CompiledShader standard = Clever::CompiledShader("C:/clever/Clever-ECS/assets/Shaders/Standard.vert", "C:/clever/Clever-ECS/assets/Shaders/Standard.frag");
		Clever::Ref<Clever::ObjectData> cubeData = std::make_shared<Clever::ObjectData>(Clever::ObjectData("C:/clever/Clever-ECS/assets/Object/Cube.obj", standard));

		int numberOfEntitiesX = 100;
		int numberOfEntitiesZ = 100;

		std::srand(time(0));

		for (int x = -numberOfEntitiesX/2; x < numberOfEntitiesX/2; x++)
		{
			for (int z = -numberOfEntitiesZ/2; z < numberOfEntitiesZ/2; z++)
			{
				Clever::EntityID entity = Clever::Coordinator::getInstance().CreateEntity();

				glm::mat4 transform = glm::translate(glm::mat4(1.0f), { x * 8, 0, z * 8 });
				transform = glm::rotate(transform, 0.0f, { 0,1,0 });
				transform = glm::scale(transform, { 1, 1, 1 });

				Clever::Coordinator::getInstance().AddRenderable
				(
					entity,
					cubeData,
					transform,
					{float(std::rand())/float(RAND_MAX), float(std::rand()) / float(RAND_MAX), float(std::rand()) / float(RAND_MAX) },
					Clever::RigidBodyComponent{{0,0,0}, {0, 0, 0}},
					Clever::PointsPositionComponent
						{
							{ (x * 8) + (1 + (rand() % static_cast<int>(20) - 10)), (1 + (rand() % static_cast<int>(20) - 10)), (z * 8) + (1 + (rand() % static_cast<int>(20) - 10))},
							{ (x * 8) + (1 + (rand() % static_cast<int>(20) - 10)), (1 + (rand() % static_cast<int>(20) - 10)), (z * 8) + (1 + (rand() % static_cast<int>(20) - 10))},
							true, 10.0f 
						}
				);

				Clever::Coordinator::getInstance().AddComponent(entity, Clever::CollisionBoxComponent{ {(x * 8) - 0.5, -0.5, (z * 8) - 0.5}, {(x * 8) + 0.5, 0.5, (z * 8) + 0.5}, 0.5f });
			}
		}
	}

	void OnUpdate(Clever::Timestep ts) override
	{
		float time = ts;

		////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////

		playerManager.OnUpdate(ts);

		float renderingTimer = (glfwGetTime() * 1000);

		////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////

		ecsManager.OnRender(ts, playerManager.getCamera());

		renderingTime = (glfwGetTime() * 1000) - renderingTimer;

		////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////

		float physicsTimer = (glfwGetTime() * 1000);

		ecsManager.OnPhysics(ts);

		physicsTime = (glfwGetTime() * 1000) - physicsTimer;

		////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////

		float calculatingTimer = (glfwGetTime() * 1000);

		//ecsManager.OnCalculation(ts, m_ObjectColor);

		calculatingTime = (glfwGetTime() * 1000) - calculatingTimer;

		////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////
	}

	virtual void OnImGuiRender(Clever::Timestep ts) override
	{
		Clever::PerspectiveCamera& camera = playerManager.getCamera();
		static float sliderMovementSpeedfloat = camera.GetMovementSpeed();
		static float sliderRotationSpeedfloat = camera.GetRotationSpeed();

		glm::vec3 cameraPos = camera.GetPosition();
		glm::vec3 cameraRot = camera.GetRotation();
		ImGui::Begin("Settings");
		ImGui::Text("CameraPosition: %f, %f, %f", cameraPos.x, cameraPos.y, cameraPos.z);

		ImGui::ColorEdit3("Light Color", glm::value_ptr(m_LightColor));
		ImGui::ColorEdit3("Object Color", glm::value_ptr(m_ObjectColor));

		ImGui::Text("CameraRotation: %f, %f, %f", cameraRot.x, cameraRot.y, cameraRot.z);
		ImGui::Text("FrameRate: %f", 1.0f/ts.GetSeconds());
		ImGui::Text("CalculatingTime: %f", calculatingTime);
		ImGui::Text("RenderingTime: %f", renderingTime);
		ImGui::Text("PhysicsTime: %f", physicsTime);
		ImGui::SliderFloat("Movement Speed", &sliderMovementSpeedfloat, 0.0f, 100.0f);
		ImGui::SliderFloat("LightPos: Y-pos: %f", &m_LightPos.y, -50.0f, 50.0f);

		ImGui::Text("Mouse_Pos: %f, %f, %f", Clever::Input::GetMouseX(), Clever::Input::GetMouseY());
		ImGui::End();

		camera.SetMovementSpeed(sliderMovementSpeedfloat);
	}

	void OnEvent(Clever::Event& event) override
	{
		//CV_INFO("An EVENT HAPPENED it was: {0}", event.GetEventType());
		if (event.GetEventType() == Clever::EventType::WindowFocus)
		{
			playerManager.setMouseLockedState(true);
			Clever::Input::HideMouse(true);
		}
		else if (event.GetEventType() == Clever::EventType::WindowLostFocus)
		{
			playerManager.setMouseLockedState(false);
			Clever::Input::HideMouse(false);
		}
	}

private:
	PlayerManager playerManager;
	ECSManager ecsManager;

	float calculatingTime = 0.0f;
	float renderingTime = 0.0f;
	float physicsTime = 0.0f;

	glm::vec3 m_ObjectColor = { 0.2f, 0.3f, 0.8f };
	glm::vec3 m_LightPos = { 0,10,0 };
	glm::vec3 m_LightColor = {1, 1, 1 };
};

class Sandbox : public Clever::Application
{
public:
	Sandbox()
	{
		Clever::Layer* exampleLayer = new MainLayer();
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

