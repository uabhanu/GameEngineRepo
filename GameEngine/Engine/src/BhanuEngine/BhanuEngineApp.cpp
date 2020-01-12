#include "EnginePCH.h"
#include "BhanuEngineApp.h"
#include "Input.h"

#include <GLFW/glfw3.h> //Don't change this order

namespace BhanuEngine
{
	#define BIND_EVENT_FN(x) std::bind(&BhanuEngineApp::x , this , std::placeholders::_1) //Wo!!!!!!

	BhanuEngineApp* BhanuEngineApp::s_Instance = nullptr;

	BhanuEngineApp::BhanuEngineApp()
	{
		ENGINE_CORE_ASSERT(!s_Instance , "Sir Bhanu, Application already exists :)");
		s_Instance = this;
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

		for(auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);

			if(e.m_Handled) //May or may not be same as e.Handled Cherno used
				break;
		}
	}

	bool BhanuEngineApp::OnWindowClose(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}

	void BhanuEngineApp::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void BhanuEngineApp::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void BhanuEngineApp::Run()
	{
		while(m_IsRunning)
		{
			glClearColor(0 , 0 , 1 , 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for(Layer* layer : m_LayerStack)
				layer->OnUpdate();

			auto[x , y] = Input::GetMousePosition();
			ENGINE_CORE_TRACE("{0} , {1}" , x , y);

			m_Window->OnUpdate();
		}
	}
}