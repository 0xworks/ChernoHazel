#pragma once

#include "SceneCamera.h"
#include "NativeScript.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <functional>
#include <memory>
#include <unordered_map>

namespace Hazel {

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true; // TODO: think about moving to Scene
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct NativeScriptComponent
	{
		std::unordered_map<entt::id_type, std::function<std::unique_ptr<NativeScript>(Entity entity)>> InstantiateScripts;
		std::unordered_map<entt::id_type, std::unique_ptr<NativeScript>> Instances;

		template<typename T, typename... Args>
		NativeScriptComponent& Bind(Args... args)
		{
			InstantiateScripts.try_emplace(entt::type_id<T>().seq(), [args...](Entity entity) -> std::unique_ptr<NativeScript> { return std::make_unique<T>(entity, args...); });
			return *this;
		}

		NativeScriptComponent& Instantiate(Entity entity)
		{
			// note: no guarantee on order that the scripts are instantiated
			for (const auto& [id, instantiateScript] : InstantiateScripts) {
				Instances.try_emplace(id, instantiateScript(entity));
			}
			return *this;
		}

		template<typename T>
		T* GetInstance()
		{
			return Instances.at[entt::type_hash<T>];
		}

		void OnUpdate(Timestep ts)
		{
			// note: no guarantee on order that the instances are updated
			for (auto& [id, instance] : Instances) {
				instance->OnUpdate(ts);
			}
		}

	};

}
