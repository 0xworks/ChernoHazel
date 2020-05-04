#pragma once

#include "Hazel/ECS/System.h"

#include <memory>
#include <unordered_map>

namespace Hazel {

	namespace ECS {

		class SystemManager {
		public:
			template<typename T>
			std::shared_ptr<T> RegisterSystem() {
				const char* typeName = typeid(T).name();
				HZ_CORE_ASSERT(m_Systems.find(typeName) == m_Systems.end(), "ERROR: Registering system '{}' more than once.", typeName);
				auto system = std::make_shared<T>();
				m_Systems.insert({typeName, system});
				return system;
			}

			template<typename T>
			void SetSignature(const Signature signature) {
				const char* typeName = typeid(T).name();
				HZ_CORE_ASSERT(m_Systems.find(typeName) != m_Systems.end() && "ERROR: System '{}' used before registered.", typeName);
				m_Signatures.insert({typeName, signature});
			}

			void EntityDestroyed(const Entity entity) {
				for (auto const& [name, system] : m_Systems) {
					system->m_Entities.erase(entity);
				}
			}

			void EntitySignatureChanged(const Entity entity, const Signature entitySignature) {
				for (auto const& [type, system] : m_Systems) {
					auto const& systemSignature = m_Signatures[type];
					if ((entitySignature & systemSignature) == systemSignature) {
						system->m_Entities.insert(entity);
					} else {
						system->m_Entities.erase(entity);
					}
				}
			}

		private:
			std::unordered_map<const char*, Signature> m_Signatures;
			std::unordered_map<const char*, std::shared_ptr<System>> m_Systems;
		};

	}
}
