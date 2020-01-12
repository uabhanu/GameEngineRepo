#include "BhanuEngine/BhanuEngineApp.h"
#include "EnginePCH.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>

namespace BhanuEngine
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		//Getting BhanuEngineApp is not a class or a namespace error and no clue why; ignore the other errors for now as they may be resolved automatically once this is
		auto window = static_cast<GLFWwindow*>(BhanuEngineApp::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window , keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [x , y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x , y] = GetMousePositionImpl();
		return y;
	}

	std::pair<float , float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(BhanuEngineApp::Get().GetWindow().GetNativeWindow());
		double xpos , ypos;
		glfwGetCursorPos(window , &xpos , &ypos);
		return {(float)xpos , (float)ypos};
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		//Getting BhanuEngineApp is not a class or a namespace error and no clue why; ignore the other errors for now as they may be resolved automatically once this is
		auto window = static_cast<GLFWwindow*>(BhanuEngineApp::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window , button);
		return state == GLFW_PRESS;
	}
}
