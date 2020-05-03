#pragma once

#include "Hazel/ECS/EntityManager.h"
#include "Hazel/ECS/ComponentManager.h"
#include "Hazel/ECS/SystemManager.h"

#if defined ECS_IMPLEMENT
#define ECS_DECL
#else
#define ECS_DECL extern
#endif

namespace Hazel {

	namespace ECS {

		ECS_DECL std::unique_ptr<EntityManager> entityManager;
		ECS_DECL std::unique_ptr<ComponentManager> componentManager;
		ECS_DECL std::unique_ptr<SystemManager> systemManager;

		inline void Init() {
			entityManager = std::make_unique<EntityManager>();
			componentManager = std::make_unique<ComponentManager>();
			systemManager = std::make_unique<SystemManager>();
		}

		inline Entity CreateEntity() {
			return entityManager->CreateEntity();
		}

		inline void DestroyEntity(const Entity entity) {
			entityManager->DestroyEntity(entity);
			componentManager->EntityDestroyed(entity);
			systemManager->EntityDestroyed(entity);
		}

		template<typename T>
		void RegisterComponent() {
			componentManager->RegisterComponent<T>();
		}

		template<typename T>
		void AddComponent(const Entity entity, T component) {
			componentManager->AddComponent<T>(entity, component);
			auto signature = entityManager->GetSignature(entity);
			signature.set(componentManager->GetComponentType<T>(), true);
			entityManager->SetSignature(entity, signature);
			systemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		void RemoveComponent(const Entity entity) {
			componentManager->RemoveComponent<T>(entity);
			auto signature = entityManager->GetSignature(entity);
			signature.set(m_componentManager->GetComponentType<T>(), false);
			entityManager->SetSignature(entity, signature);
			systemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		T& GetComponent(const Entity entity) {
			return componentManager->GetComponent<T>(entity);
		}

		template<typename T>
		ComponentType GetComponentType() {
			return componentManager->GetComponentType<T>();
		}

		template<typename T>
		std::shared_ptr<T> RegisterSystem() {
			return systemManager->RegisterSystem<T>();
		}

		template<typename T>
		void SetSystemSignature(const Signature signature) {
			systemManager->SetSignature<T>(signature);
		}

	}

}
