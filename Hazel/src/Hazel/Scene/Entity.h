#pragma once

#include "Scene.h"
#include "Hazel/Core/Log.h"

#include <entt.hpp>

namespace Hazel {

	class Entity
	{
		friend class Scene;

	public:
		Entity() = default;
		Entity(entt::entity handle, Scene& scene);
		Entity(const Entity& other) = default;

		Scene& GetScene()
		{
			return *m_Scene;
		}

		template<typename T, typename... Args>
		Entity& AddComponent(Args&&... args)
		{
			HZ_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded<T>(*this, component);
			return *this;
		}

		template<typename T>
		T& GetComponent()
		{
			HZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			HZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		Entity CreateEntity(const std::string_view name = {})
		{
			return m_Scene->CreateEntity(name);
		}

		void DestroyAllEntities()
		{
			m_Scene->DestroyAllEntities();
		}

		void DestroyEntity(Entity entity)
		{
			m_Scene->DestroyEntity(entity);
		}

		operator bool() const { return m_Scene && m_Scene->m_Registry.valid(m_EntityHandle); }

		bool operator==(const Entity& other) const
		{
			return (m_EntityHandle == other.m_EntityHandle) && (m_Scene == other.m_Scene);
		}

		bool operator!=(const Entity& other) const {
			return !(*this == other);
		}

	private:
		entt::entity m_EntityHandle = entt::null;
		Scene* m_Scene = nullptr;
	};

}
