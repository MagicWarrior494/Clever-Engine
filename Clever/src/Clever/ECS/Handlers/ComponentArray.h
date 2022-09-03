#pragma once

#include "cvpch.h"
#include "Types.h"
#include <array>
#include <span>
#include <cassert>
#include <unordered_map>


namespace Clever {

	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
		virtual void EntityDestroyed(EntityID entity) = 0;
	};


	template<typename T>
	class ComponentArray : public IComponentArray
	{
	public:

		void InsertData(EntityID entity, T component)
		{
			CV_CORE_ASSERT(m_EntityToIndexMap.find(entity) == m_EntityToIndexMap.end(), "Component added to same entity more than once.");

			// Put new entry at end
			size_t newIndex = m_Size;
			m_EntityToIndexMap[entity] = newIndex;
			m_IndexToEntityMap[newIndex] = entity;
			m_ComponentArray[newIndex] = component;
			m_Size++;
		}
		void RemoveData(EntityID entity)
		{
			CV_CORE_ASSERT(m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end(), "Removing non-existent component.");

			// Copy element at end into deleted element's place to maintain density
			size_t indexOfRemovedEntity = m_EntityToIndexMap[entity];
			size_t indexOfLastElement = m_Size - 1;
			m_ComponentArray[indexOfRemovedEntity] = m_ComponentArray[indexOfLastElement];

			// Update map to point to moved spot
			EntityID entityOfLastElement = m_IndexToEntityMap[indexOfLastElement];
			m_EntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
			m_IndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

			m_EntityToIndexMap.erase(entity);
			m_IndexToEntityMap.erase(indexOfLastElement);

			--m_Size;
		}
		T& GetData(EntityID entity)
		{
			CV_CORE_ASSERT(m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end(), "Retrieving non-existent component.");

			return m_ComponentArray[m_EntityToIndexMap[entity]];
		}

		void EntityDestroyed(EntityID entity) override
		{
			if (m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end())
			{
				RemoveData(entity);
			}
		}

	private:
		std::array<T, MAX_SIGNATURES> m_ComponentArray{};
		std::unordered_map<EntityID, size_t> m_EntityToIndexMap{};
		std::unordered_map<size_t, EntityID> m_IndexToEntityMap{};
		size_t m_Size{};
	};
}