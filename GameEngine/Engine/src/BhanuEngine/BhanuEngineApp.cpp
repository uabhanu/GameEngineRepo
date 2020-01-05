#include "EnginePCH.h"
#include "BhanuEngineApp.h"

#include <GLFW/glfw3.h> //Don't change this order

namespace BhanuEngine
{
	#define BIND_EVENT_FN(x) std::bind(&BhanuEngineApp::x , this , std::placeholders::_1) //Wo!!!!!!
	BhanuEngineApp::BhanuEngineApp()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}
		
	BhanuEngineApp::~BhanuEngineApp()
	{

	}

	void BhanuEngineApp::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		ENGINE_CORE_TRACE("{0}" , e);
	}

	bool BhanuEngineApp::OnWindowClose(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
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