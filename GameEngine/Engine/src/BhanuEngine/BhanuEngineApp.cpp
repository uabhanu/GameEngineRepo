#include "EnginePCH.h"
#include "BhanuEngineApp.h"
#include "BhanuEngine/Renderer/Renderer.h"
#include "Input.h"

#include <glfw/glfw3.h>

namespace BhanuEngine
{
	#define BIND_EVENT_FN(x) std::bind(&BhanuEngineApp::x , this , std::placeholders::_1) //Wo!!!!!!

	BhanuEngineApp* BhanuEngineApp::s_Instance = nullptr;

	BhanuEngineApp::BhanuEngineApp() //Revise the difference between unique_ptr & make_unique
	{
		ENGINE_CORE_ASSERT(!s_Instance , "Sir Bhanu, Application already exists :)");
		s_Instance = this;
		m_ImGUILayer = new ImGUILayer();
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		PushOverlay(m_ImGUILayer);
	}
		
	BhanuEngineApp::~BhanuEngineApp()
	{

	}

	void BhanuEngineApp::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		//ENGINE_CORE_TRACE("{0}" , e); //Uncomment this for testing if needed

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
			float time = (float)glfwGetTime();
			TimeStep timeStep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for(Layer* layer : m_LayerStack)
				layer->OnUpdate(timeStep);

			m_ImGUILayer->Begin();
			for(Layer* layer : m_LayerStack)
				layer->OnImGUIRender();
			m_ImGUILayer->End();

			m_Window->OnUpdate();
		}
	}
}