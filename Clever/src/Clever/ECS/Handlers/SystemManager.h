#pragma once

#include "cvpch.h"
#include "System.h"
#include "Types.h"
#include <cassert>
#include <memory>
#include <unordered_map>

namespace Clever
{
	class SystemManager
	{
	public:
		template<typename T>
		std::shared_ptr<T> RegisterSystem()
		{
			const char* typeName = typeid(T).name();

			CV_CORE_ASSERT(m_Systems.find(typeName) == m_Systems.end() && "Registering system more than once.");

			auto system = std::make_shared<T>();
			m_Systems.insert({ typeName, system });
			return system;
		}

		template<typename T>
		void SetSignature(Signature signature)
		{
			const char* typeName = typeid(T).name();

			CV_CORE_ASSERT(m_Systems.find(typeName) != m_Systems.end() && "System used before registered.");

			m_Signatures.insert({ typeName, signature });
		}

		void EntityDestroyed(EntityID entity)
		{
			for (auto const& pair : m_Systems)
			{
				auto const& system = pair.second;


				system->m_Entities.erase(entity);
			}
		}

		void EntitySignatureChanged(EntityID entity, Signature entitySignature)
		{
			for (auto const& pair : m_Systems)
			{
				auto const& type = pair.first;
				auto const& system = pair.second;
				auto const& systemSignature = m_Signatures[type];

				if ((entitySignature & systemSignature) == systemSignature)
				{
					system->m_Entities.insert(entity);
				}
				else
				{
					system->m_Entities.erase(entity);
				}
			}
		}

	private:
		std::unordered_map<const char*, Signature> m_Signatures{};
		std::unordered_map<const char*, std::shared_ptr<System>> m_Systems{};
	};
}