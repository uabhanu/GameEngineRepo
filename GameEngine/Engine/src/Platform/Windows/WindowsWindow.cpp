#include "EnginePCH.h"
#include "WindowsWindow.h"

namespace BhanuEngine
{
	static bool s_GLFWInitialised = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		ENGINE_CORE_INFO("Creating window {0} ({1} , {2})" , props.Title , props.Width , props.Height);

		if(!s_GLFWInitialised)
		{
			//TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			ENGINE_CORE_ASSERT(success , "Sir Bhanu, could not initialise GLFW! :(");
			s_GLFWInitialised = true;
		}

		m_Window = glfwCreateWindow((int)props.Width , (int)props.Height , m_Data.Title.c_str() , nullptr , nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window , &m_Data);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if(enabled)
		{
			glfwSwapInterval(1);
		}
	}
}