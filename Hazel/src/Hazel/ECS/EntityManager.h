#pragma once

#include "Hazel/Core/Core.h"
#include "Hazel/ECS/ECSType.h"

#include <array>
#include <queue>

namespace Hazel {

	namespace ECS {

		class EntityManager {
		public:
			EntityManager() {
				for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
					m_Entities.push(entity);
				}
			}

			Entity CreateEntity() {
				HZ_ASSERT(m_ActiveEntityCount < MAX_ENTITIES, "ERROR: Too many entities in existence.");
				Entity id = m_Entities.front();
				m_Entities.pop();
				++m_ActiveEntityCount;
				return id;
			}

			void DestroyEntity(const Entity entity) {
				HZ_CORE_ASSERT(entity < MAX_ENTITIES, "ERROR: Entity out of range.");
				m_Signatures[entity].reset();
				m_Entities.push(entity);
				--m_ActiveEntityCount;
			}

			void SetSignature(const Entity entity, const Signature signature) {
				HZ_CORE_ASSERT(entity < MAX_ENTITIES, "ERROR: Entity out of range.");
				m_Signatures[entity] = signature;
			}

			Signature GetSignature(const Entity entity) {
				HZ_CORE_ASSERT(entity < MAX_ENTITIES, "ERROR: Entity out of range.");
				return m_Signatures[entity];
			}

		private:
			std::queue<Entity> m_Entities;
			std::array<Signature, MAX_ENTITIES> m_Signatures;
			uint32_t m_ActiveEntityCount = 0;
		};

	}
}
