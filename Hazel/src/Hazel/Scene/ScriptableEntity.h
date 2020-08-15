#pragma once

#include "Entity.h"

namespace Hazel {

	class ScriptableEntity
	{
	public:
		ScriptableEntity(Entity entity): m_Entity(entity) {}

		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
	private:
		Entity m_Entity;
		friend class Scene;
	};

}

