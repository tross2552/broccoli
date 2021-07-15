#include "brclpch.h"
#include "Broccoli/Input.h"
#include "Broccoli/Application.h"

#include <GLFW/glfw3.h>

namespace brcl
{

	bool Input::IsKeyPressed(const KeyCode keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		int state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(MouseCode mousecode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		int state = glfwGetMouseButton(window, mousecode);

		return state == GLFW_PRESS;
	}

	Vector2 Input::GetMousePos()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double x, y = 0;
		glfwGetCursorPos(window, &x, &y);

		return Vector2({ static_cast<float>(x),static_cast<float>(y) });
	}

	
}
