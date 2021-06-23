#include "hzpch.h"
#include "Hazel/Core/Input.h"

#include "Hazel/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Hazel {

	static bool s_InputEnabled = true;

	void Input::Enable(bool enabled)
	{
		s_InputEnabled = enabled;
	}

	bool Input::IsEnabled() 
	{
		return s_InputEnabled;
	}

	bool Input::IsKeyPressed(const KeyCode key)
	{
		if (s_InputEnabled)
		{
			auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
			auto state = glfwGetKey(window, static_cast<int32_t>(key));
			return state == GLFW_PRESS || state == GLFW_REPEAT;
		}
		return false;
	}

	bool Input::IsMouseButtonPressed(const MouseCode button)
	{
		if (s_InputEnabled)
		{
			auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
			auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
			return state == GLFW_PRESS;
		}
		return false;
	}

	glm::vec2 Input::GetMousePosition()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}

}
