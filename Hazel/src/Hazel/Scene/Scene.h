#pragma once

#include "Hazel/Core/Timestep.h"
#include "entt.hpp"

namespace Hazel {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());

		void DestroyEntity(Entity entity);

		void DestroyAllEntities();

		void OnUpdate(Timestep ts);
		void OnViewportResize(uint32_t width, uint32_t height);

	// HACK: At this stage (episode 82 of Game-Engine series), I am unsure
	//       how (or if) Cherno plans to expose "groups" and "views" to clients
	//       of the Hazel Engine.
	//       Right now clients do need access (because the engine isnt finished yet),
	//       I'm just going to hackaround this by exposing the registry directly
		entt::registry m_Registry;

	private:
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		friend class Entity;
	};

}
