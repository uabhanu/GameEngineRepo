#include "BhanuEngine/BhanuEngineApp.h"
#include "EnginePCH.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>

namespace BhanuEngine
{
	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(BhanuEngineApp::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window , keycode);
		return state = GLFW_PRESS || GLFW_REPEAT;
	}
}