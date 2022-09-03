#pragma once

#include "ComponentArray.h"
#include "Types.h"
#include <any>
#include <memory>
#include <unordered_map>

namespace Clever {

	class ComponentManager
	{
	public:

		template<typename T>
		void RegisterComponent()
		{
			const char* typeName = typeid(T).name();

			CV_CORE_ASSERT(m_ComponentTypes.find(typeName) == m_ComponentTypes.end(), "Registering component type more than once.");

			m_ComponentTypes.insert({ typeName, m_NextComponentType });
			m_ComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

			m_NextComponentType++;
		}

		template<typename T>
		ComponentType GetComponentType()
		{
			const char* typeName = typeid(T).name();

			CV_CORE_ASSERT(m_ComponentTypes.find(typeName) != m_ComponentTypes.end(), "Component not registered before use.");

			return m_ComponentTypes[typeName];
		}

		template<typename T>
		void AddComponent(EntityID entity, T component)
		{
			GetComponentArray<T>()->InsertData(entity, component);
		}

		template<typename T>
		void RemoveComponent(EntityID entity)
		{
			GetComponentArray<T>()->(entity);
		}

		template<typename T>
		T& GetComponent(EntityID entity)
		{
			return GetComponentArray<T>()->GetData(entity);
		}

		void EntityDestroyed(EntityID entity)
		{
			for (auto const& pair : m_ComponentArrays)
			{
				auto const& component = pair.second;

				component->EntityDestroyed(entity);
			}
		}

	private:
		std::unordered_map<const char*, ComponentType> m_ComponentTypes{};
		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_ComponentArrays{};
		ComponentType m_NextComponentType{};


		template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray()
		{
			const char* typeName = typeid(T).name();

			CV_CORE_ASSERT(m_ComponentTypes.find(typeName) != m_ComponentTypes.end(), "Component not registered before use.");

			return std::static_pointer_cast<ComponentArray<T>>(m_ComponentArrays[typeName]);
		}
	};
}