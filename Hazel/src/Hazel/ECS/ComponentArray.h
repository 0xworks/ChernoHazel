#pragma once

#include "Hazel/ECS/ECSType.h"

#include <array>
#include <unordered_map>

namespace Hazel {

	namespace ECS {

		class IComponentArray {
		public:
			virtual ~IComponentArray() = default;
			virtual void EntityDestroyed(Entity entity) = 0;
		};


		template<typename T>
		class ComponentArray : public IComponentArray {
		public:
			void Insert(const Entity entity, T component) {
				HZ_CORE_ASSERT(m_EntityToIndexMap.find(entity) == m_EntityToIndexMap.end(), "ERROR: Component added to same entity more than once.");

				// Put new entry at end
				size_t newIndex = m_Size;
				m_EntityToIndexMap[entity] = newIndex;
				m_IndexToEntityMap[newIndex] = entity;
				m_ComponentArray[newIndex] = component;
				++m_Size;
			}


			void Remove(const Entity entity) {
				HZ_CORE_ASSERT(m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end(), "ERROR: Removing non-existent component.");

				// Copy element at end into deleted element's place to maintain density
				size_t indexOfRemovedEntity = m_EntityToIndexMap[entity];
				size_t indexOfLastElement = m_Size - 1;
				m_ComponentArray[indexOfRemovedEntity] = m_ComponentArray[indexOfLastElement];

				// Update map to point to moved spot
				Entity entityOfLastElement = m_IndexToEntityMap[indexOfLastElement];
				m_EntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
				m_IndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

				m_EntityToIndexMap.erase(entity);
				m_IndexToEntityMap.erase(indexOfLastElement);

				--m_Size;
			}


			T& Get(const Entity entity) {
				HZ_CORE_ASSERT(m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end(), "ERROR: Retrieving non-existent component.");
				return m_ComponentArray[m_EntityToIndexMap[entity]];
			}


			void EntityDestroyed(const Entity entity) override {
				if (m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end()) {
					Remove(entity);
				}
			}


		private:
			std::array<T, MAX_ENTITIES> m_ComponentArray;
			std::unordered_map<Entity, size_t> m_EntityToIndexMap;
			std::unordered_map<size_t, Entity> m_IndexToEntityMap;
			size_t m_Size = 0;
		};

	}
}
