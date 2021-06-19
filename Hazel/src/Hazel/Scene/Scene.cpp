#include "hzpch.h"
#include "Scene.h"

#include "Components.h"
#include "Hazel/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

#include "Entity.h"

namespace Hazel {

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity.m_EntityHandle);
	}

	void Scene::DestroyAllEntities()
	{
		m_Registry.clear();
	}


	void Scene::OnUpdateRuntime(Timestep ts)
	{
		// Update scripts
		{
			for(auto&&[entity, nsc] : m_Registry.view<NativeScriptComponent>().each())
			{
				// TODO: Move to Scene::OnScenePlay
				if (!nsc.Instance)
				{
					nsc.Instance = nsc.InstantiateScript({entity, this});
				}

				nsc.Instance->OnUpdate(ts);
			}
		}

		// Render 2D
		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;
		{
			for (auto&& [entity, transform, camera] : m_Registry.view<TransformComponent, CameraComponent>().each())
			{
				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = transform.GetTransform();
					break;
				}
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, cameraTransform);

			// note: use of .group<> here precludes sorting entities on TransformComponent.  Might need to change back to .view<> later.
			for (auto&& [entity, transform, sprite] : m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>).each())
			{
				Renderer2D::DrawSprite(transform.GetTransform(), sprite, static_cast<int>(entity));
			}

			Renderer2D::EndScene();
		}

	}

	void Scene::OnUpdateEditor(Timestep ts, EditorCamera& camera)
	{
		Renderer2D::BeginScene(camera);

		// note: use of .group<> here precludes sorting entities on TransformComponent.  Might need to change back to .view<> later.
		for (auto&& [entity, transform, sprite] : m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>).each())
		{
			Renderer2D::DrawSprite(transform.GetTransform(), sprite, static_cast<int>(entity));
		}

		Renderer2D::EndScene();
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// Resize our non-FixedAspectRatio cameras
		for (auto&& [entity, camera] : m_Registry.view<CameraComponent>().each())
		{
			if (!camera.FixedAspectRatio)
			{
				camera.Camera.SetViewportSize(width, height);
			}
		}
	}

	Entity Scene::GetPrimaryCameraEntity()
	{
		for (auto&& [entity, camera] : m_Registry.view<CameraComponent>().each())
		{
			if (camera.Primary)
			{
				return Entity{entity, this};
			}
		}
		return {};
	}


	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		if (m_ViewportWidth > 0 && m_ViewportHeight > 0)
		{
			component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
		}
	}

}
