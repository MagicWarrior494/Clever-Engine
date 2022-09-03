#pragma once

#include "ComponentManager.h"
#include "Clever/ECS/Components/Components.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "Types.h"
#include "Clever/ECS/DataHandelers/RenderingData.h"
#include <memory>

namespace Clever {
	class Coordinator
	{
	public:

		static Coordinator& getInstance()
		{
			static Coordinator coord;
			return coord;
		}

		void Init()
		{
			m_ComponentManager = std::make_unique<ComponentManager>();
			m_EntityManager = std::make_unique<EntityManager>();
			m_SystemManager = std::make_unique<SystemManager>();

		}

		// Entity methods
		EntityID CreateEntity()
		{
			return m_EntityManager->CreateEntity();
		}

		void AddRenderable(EntityID id, Ref<ObjectData> od, glm::mat4 transform, glm::vec3 texture, RigidBodyComponent rbc, PointsPositionComponent ppc)
		{
			uint32_t index = RenderingData::getInstance().AddObject(od, transform, texture, rbc, ppc);

			AddComponent(id, TransformComponent{ index });
			AddComponent(id, ColorComponent{index});
			AddComponent(id, rbc);
			AddComponent(id, ppc);
			AddComponent(id, MeshComponent{ od });
		}

		void DestroyEntity(EntityID entity)
		{
			m_EntityManager->DestroyEntity(entity);

			m_ComponentManager->EntityDestroyed(entity);

			m_SystemManager->EntityDestroyed(entity);
		}

		// Component methods
		template<typename T>
		void RegisterComponent()
		{
			m_ComponentManager->RegisterComponent<T>();
		}

		template<typename T>
		void AddComponent(EntityID entity, T component)
		{
			m_ComponentManager->AddComponent<T>(entity, component);

			auto signature = m_EntityManager->GetSignature(entity);
			signature.set(m_ComponentManager->GetComponentType<T>(), true);
			m_EntityManager->SetSignature(entity, signature);

			m_SystemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		void RemoveComponent(EntityID entity)
		{
			m_ComponentManager->RemoveComponent<T>(entity);

			auto signature = m_EntityManager->GetSignature(entity);
			signature.set(m_ComponentManager->GetComponentType<T>(), false);
			m_EntityManager->SetSignature(entity, signature);

			m_SystemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		T& GetComponent(EntityID entity)
		{
			return m_ComponentManager->GetComponent<T>(entity);
		}

		template<typename T>
		ComponentType GetComponentType()
		{
			return m_ComponentManager->GetComponentType<T>();
		}

		// System methods
		template<typename T>
		std::shared_ptr<T> RegisterSystem()
		{
			return m_SystemManager->RegisterSystem<T>();
		}

		template<typename T>
		void SetSystemSignature(Signature signature)
		{
			m_SystemManager->SetSignature<T>(signature);
		}

	private:

		Coordinator()
		{

		};

		std::unique_ptr<ComponentManager> m_ComponentManager;
		std::unique_ptr<EntityManager> m_EntityManager;
		std::unique_ptr<SystemManager> m_SystemManager;
	};
}