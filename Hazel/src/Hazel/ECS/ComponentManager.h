#pragma  once

#include "Hazel/ECS/ComponentArray.h"

#include <memory>
#include <unordered_map>

namespace Hazel {

	namespace ECS {

		class ComponentManager {
		public:
			template<typename T>
			void RegisterComponent() {
				const char* typeName = typeid(T).name();
				HZ_CORE_ASSERT(m_ComponentTypes.find(typeName) == m_ComponentTypes.end(), "ERROR: Component '{}' cannot be registered more than once.", typeName);
				m_ComponentTypes.insert({typeName, m_NextComponentType});
				m_ComponentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
				++m_NextComponentType;
			}

			template<typename T>
			ComponentType GetComponentType() {
				const char* typeName = typeid(T).name();
				HZ_CORE_ASSERT(m_ComponentTypes.find(typeName) != m_ComponentTypes.end(), "ERROR: Component '{}' must be registered before use.", typeName);
				return m_ComponentTypes[typeName];
			}

			template<typename T>
			void AddComponent(const Entity entity, T component) {
				GetComponentArray<T>()->Insert(entity, component);
			}

			template<typename T>
			void RemoveComponent(const Entity entity) {
				GetComponentArray<T>()->Remove(entity);
			}

			template<typename T>
			T& GetComponent(const Entity entity) {
				return GetComponentArray<T>()->Get(entity);
			}

			template<typename T>
			bool HasComponent(const Entity entity) {
				return GetComponentArray<T>()->Has(entity);
			}

			void EntityDestroyed(const Entity entity) {
				for (auto const& [name, component] : m_ComponentArrays) {
					component->EntityDestroyed(entity);
				}
			}

		private:
			std::unordered_map<const char*, ComponentType> m_ComponentTypes;
			std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_ComponentArrays;
			ComponentType m_NextComponentType = 0;

			template<typename T>
			std::shared_ptr<ComponentArray<T>> GetComponentArray() {
				const char* typeName = typeid(T).name();
				HZ_CORE_ASSERT(m_ComponentTypes.find(typeName) != m_ComponentTypes.end(), "ERROR: Component '{}' must be registered before use.", typeName);
				return std::static_pointer_cast<ComponentArray<T>>(m_ComponentArrays[typeName]);
			}

		};

	}
}
