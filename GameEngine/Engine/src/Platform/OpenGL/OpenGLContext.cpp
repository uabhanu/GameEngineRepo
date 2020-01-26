#include "EnginePCH.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>

namespace BhanuEngine
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		ENGINE_CORE_ASSERT(windowHandle , "Sir Bhanu, Window Handle is Null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ENGINE_CORE_ASSERT(status , "Sir Bhanu, Failed to initialise Glad :(");
		ENGINE_CORE_WARN("Sir Bhanu, following are your Graphics Card details : ");
		ENGINE_CORE_WARN("Vendor is {0}" , glGetString(GL_VENDOR));
		ENGINE_CORE_WARN("Renderer is {0}" , glGetString(GL_RENDERER));
		ENGINE_CORE_WARN("Version is {0}" , glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}