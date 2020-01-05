#include "EnginePCH.h"
#include "WindowsWindow.h"
#include "BhanuEngine/Events/AppEvent.h"
#include "BhanuEngine/Events/KeyEvent.h" //Following Cherno, including this is causing errors possibly due to duplicate includes so don't do this unless needed
#include "BhanuEngine/Events/MouseEvent.h" //Following Cherno, including this is causing errors possibly due to duplicate includes so don't do this unless needed

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

		ENGINE_CORE_INFO("Creating Window {0} ({1} , {2})" , props.Title , props.Width , props.Height);

		if(!s_GLFWInitialised)
		{
			//TODO glfwTerminate on system shutdown
			int success = glfwInit();
			ENGINE_CORE_ASSERT(success , "Sir Bhanu, Could not initialise GLFW! :(");
			s_GLFWInitialised = true;
		}

		m_Window = glfwCreateWindow((int)props.Width , (int)props.Height , m_Data.Title.c_str() , nullptr , nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window , &m_Data);
		SetVSync(true);

		//Set GLFW Callbacks
		glfwSetWindowSizeCallback(m_Window , [](GLFWwindow* window , int width , int height)
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width , height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window , [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
			WindowCloseEvent event; 
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window , [](GLFWwindow* window , int key , int scancode , int action , int mods)
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

			switch(action)
			{
				case GLFW_PRESS:
					KeyPressedEvent event(key , 0);
					data.EventCallback(event);
				break;

				case GLFW_RELEASE:
					KeyReleasedEvent event(key);
					data.EventCallback(event);
				break;

				case GLFW_REPEAT:
					KeyPressedEvent event(key , 1);
					data.EventCallback(event);
				break;
			}
		});
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
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}
