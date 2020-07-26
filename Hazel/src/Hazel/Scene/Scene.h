#pragma once

#include "Hazel/Core/Timestep.h"
#include "entt.hpp"

namespace Hazel {

	class Scene
	{
		friend class Entity;

	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());

		void DestroyEntity(Entity entity);

		void DestroyAllEntities();

		void OnUpdate(Timestep ts);

	// HACK: At this stage (episode 79 of Game-Engine series), I am unsure
	//       how Cherno plans to expose "groups" and "views" outside of Hazel
	//       rather than try and guess, for now I am just exposing the registry directly
	//private:
		entt::registry m_Registry;
	};

}
