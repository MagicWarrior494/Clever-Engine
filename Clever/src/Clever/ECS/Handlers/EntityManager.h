#pragma once
#include <cstdint>
#include <queue>
#include "Types.h"


namespace Clever {

	class EntityManager {
	public:
		EntityManager()
		{
		}

		EntityID CreateEntity()
		{
			EntityID id = m_EntityIdCounter;
			m_EntityIdCounter++;
			m_LivingEntityCount++;

			return id;
		}

		void DestroyEntity(EntityID entity)
		{
			m_Signatures[entity].reset();
			m_LivingEntityCount--;
		}

		void SetSignature(EntityID entity, Signature signature)
		{
			m_Signatures[entity] = signature;
		}

		Signature GetSignature(EntityID entity)
		{
			return m_Signatures[entity];
		}

	private:
		uint32_t m_EntityIdCounter = 0;
		std::array<Signature, MAX_SIGNATURES> m_Signatures{};
		uint32_t m_LivingEntityCount{};
	};
}