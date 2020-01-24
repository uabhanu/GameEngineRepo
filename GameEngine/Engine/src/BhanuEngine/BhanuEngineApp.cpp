#include "EnginePCH.h"
#include "BhanuEngineApp.h"
#include "Input.h"

#include <glad/glad.h>

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
		
		glGenBuffers(1 , &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , m_IndexBuffer);
		
		unsigned int indices[3] = {0 , 1 , 2};
		glBufferData(GL_ELEMENT_ARRAY_BUFFER , sizeof(indices) , indices , GL_STATIC_DRAW);

		glGenVertexArrays(1 , &m_VertexArray);
		glBindVertexArray(m_VertexArray);
		
		glGenBuffers(1 , &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER , m_VertexBuffer);

		//No Triangle probably because your laptop has no modern graphics card
		//Test this on your desktop before changing these values
		float vertices[3 * 3] =
		{
			-0.5f , -0.5f , 0.0f,
			 0.5f , -0.5f , 0.0f,
			 0.0f ,  0.5f , 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 3 * sizeof(float) , nullptr);
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
			glClearColor(1.0f , 0.0f , 0.0f , 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES , 3 , GL_UNSIGNED_INT , nullptr);

			for(Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGUILayer->Begin();
			for(Layer* layer : m_LayerStack)
				layer->OnImGUIRender();
			m_ImGUILayer->End();

			m_Window->OnUpdate();
		}
	}
}