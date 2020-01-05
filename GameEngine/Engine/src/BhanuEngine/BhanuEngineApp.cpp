#include "EnginePCH.h"
#include "BhanuEngineApp.h"
#include "BhanuEngine/Events/AppEvent.h"
#include "BhanuEngine/Log.h"

#include <GLFW/glfw3.h> //Don't change this order

namespace BhanuEngine
{
	BhanuEngineApp::BhanuEngineApp()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
		
	BhanuEngineApp::~BhanuEngineApp()
	{

	}

	void BhanuEngineApp::Run()
	{
		while(m_IsRunning)
		{
			glClearColor(1 , 0 , 1 , 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}