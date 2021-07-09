#include "brclpch.h"
#include "WindowsInput.h"
#include "Broccoli/Application.h"

#include <GLFW/glfw3.h>

namespace brcl
{

	std::unique_ptr<Input> Input::s_Instance = std::make_unique<WindowsInput>();

	bool WindowsInput::IsKeyPressedImpl(const KeyCode keycode) const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		int state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(const MouseCode mousecode) const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		int state = glfwGetMouseButton(window, mousecode);

		return state == GLFW_PRESS;
	}

	//temp, will be implementing 2d/3d vector struct in the future

	float WindowsInput::GetMouseXImpl() const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double x, y = 0;
		glfwGetCursorPos(window, &x, &y);

		return (float)x;
	}

	float WindowsInput::GetMouseYImpl() const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double x, y = 0;
		glfwGetCursorPos(window, &x, &y);

		return (float)y;
	}
}
