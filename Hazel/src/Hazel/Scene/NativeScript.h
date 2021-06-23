#pragma once

#include "Entity.h"

namespace Hazel {

	class NativeScript
	{
	public:
		NativeScript(Entity entity) : m_Entity(entity) {}
		virtual ~NativeScript() {}

		virtual void OnUpdate(Timestep ts) {}

		Scene& GetScene()
		{
			return m_Entity.GetScene();
		}

		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

		Entity CreateEntity()
		{
			return m_Entity.CreateEntity();
		}

		void DestroyAllEntities()
		{
			return m_Entity.DestroyAllEntities();
		}

		void DestroyEntity(Entity entity)
		{
			m_Entity.DestroyEntity(entity);
		}


	private:
		Entity m_Entity;
	};

}
