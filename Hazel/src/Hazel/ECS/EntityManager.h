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
#if defined HZ_DEBUG
					m_IsEntityActive[entity] = false;
#endif
				}
			}

			Entity CreateEntity() {
				HZ_ASSERT(m_ActiveEntityCount < MAX_ENTITIES, "ERROR: Too many entities in existence.");
				Entity entity = m_Entities.front();
				m_Entities.pop();
				++m_ActiveEntityCount;
#if defined HZ_DEBUG
				m_IsEntityActive[entity] = true;
#endif
				return entity;
			}

			void DestroyEntity(const Entity entity) {
				HZ_CORE_ASSERT(entity < MAX_ENTITIES, "ERROR: Entity out of range.");
#if defined HZ_DEBUG
				// In debug mode, check that entity exists.
				// An entity exists if and only if it is not already on the m_Entities queue
				HZ_CORE_ASSERT(m_IsEntityActive[entity], "ERROR: Attempting to delete non-active entity {}", entity);
#endif
				m_Signatures[entity].reset();
				m_Entities.push(entity);
#if defined HZ_DEBUG
				m_IsEntityActive[entity] = false;
#endif
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
#if defined HZ_DEBUG
			std::array<bool, MAX_ENTITIES> m_IsEntityActive;
#endif
		};

	}
}
