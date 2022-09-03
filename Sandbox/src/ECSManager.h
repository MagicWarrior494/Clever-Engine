#pragma once
#include <Clever.h>
#include <ctime>


class ECSManager
{
public:

	ECSManager()
	{

		Clever::Coordinator& coordinator = Clever::Coordinator::getInstance();

		coordinator.Init();
		coordinator.RegisterComponent<Clever::RigidBodyComponent>();
		coordinator.RegisterComponent<Clever::TransformComponent>();
		coordinator.RegisterComponent<Clever::MeshComponent>();
		coordinator.RegisterComponent<Clever::ColorComponent>();
		coordinator.RegisterComponent<Clever::PointsPositionComponent>();
		coordinator.RegisterComponent<Clever::CollisionBoxComponent>();


		renderingSystem = coordinator.RegisterSystem<Clever::RenderingSystem>();
		{
			Clever::Signature signature;
			signature.set(coordinator.GetComponentType<Clever::MeshComponent>());
			signature.set(coordinator.GetComponentType<Clever::TransformComponent>());
			signature.set(coordinator.GetComponentType<Clever::ColorComponent>());
			coordinator.SetSystemSignature<Clever::RenderingSystem>(signature);
		}

		renderingSystem->init();

		colorSystem = coordinator.RegisterSystem<Clever::ColorController>();
		{
			Clever::Signature signature;
			signature.set(coordinator.GetComponentType<Clever::ColorComponent>());
			coordinator.SetSystemSignature<Clever::RenderingSystem>(signature);
		}

		renderingSystem->init();

		travelBetweenPointsSystem = coordinator.RegisterSystem<Clever::TravelBetweenPointsSystem>();
		{
			Clever::Signature signature;
			signature.set(coordinator.GetComponentType<Clever::PointsPositionComponent>());
			signature.set(coordinator.GetComponentType<Clever::TransformComponent>());
			signature.set(coordinator.GetComponentType<Clever::RigidBodyComponent>());
			coordinator.SetSystemSignature<Clever::TravelBetweenPointsSystem>(signature);
		}

		travelBetweenPointsSystem->Init();

		platformPhysicsSystem = coordinator.RegisterSystem<Clever::PlatformPhysicsSystem>();
		{
			Clever::Signature signature;
			signature.set(coordinator.GetComponentType<Clever::CollisionBoxComponent>());
			signature.set(coordinator.GetComponentType<Clever::RigidBodyComponent>());
			signature.set(coordinator.GetComponentType<Clever::TransformComponent>());
			coordinator.SetSystemSignature<Clever::PlatformPhysicsSystem>(signature);
		}

		platformPhysicsSystem->Init();
	}

	void OnRender(float dt, Clever::PerspectiveCamera pc)
	{
		renderingSystem->Update(dt, pc);
	}

	void OnPhysics(float dt)
	{
		platformPhysicsSystem->Update(dt);
		travelBetweenPointsSystem->Update(dt);
	}

	void OnCalculation(float dt, glm::vec3 color)
	{
		colorSystem->Update(color);
	}

public:

	Clever::Ref<Clever::RenderingSystem> renderingSystem{};
	Clever::Ref<Clever::ColorController> colorSystem{};
	Clever::Ref<Clever::PlatformPhysicsSystem> platformPhysicsSystem{};
	Clever::Ref<Clever::TravelBetweenPointsSystem> travelBetweenPointsSystem{};
};