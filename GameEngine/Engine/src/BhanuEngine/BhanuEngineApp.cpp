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

		m_VertexArray.reset(VertexArray::Create());

		//No Triangle because of an exception thrown by OpenGL on Desktop but that wasn't thrown on the laptop
		//To reproduce the no triangle/exception, just put the IndexBuffer code before VertexArray
		float vertices[3 * 7] =
		{
			-0.5f , -0.5f , 0.0f, 1.0, 0.0, 0.0, 1.0,
			 0.5f , -0.5f , 0.0f, 0.0, 1.0, 0.0, 1.0,
			 0.0f ,  0.5f , 0.0f, 0.0, 0.0, 1.0, 1.0
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices , sizeof(vertices)));
		BufferLayout bufferLayout =
		{
			{ShaderDataType::FLOAT3 , "a_Position"},
			{ShaderDataType::FLOAT4 , "a_Color"}
		};

		//When I swap these lines like Cherno did, I am not getting any Assert exception but instead, only triangle not rendering
		vertexBuffer->SetLayout(bufferLayout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		//These should come after VertexArray Binding so don't change the order	
		uint32_t indices[3] = {0 , 1 , 2};
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices , sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray.reset(VertexArray::Create());

		float squareVertices[3 * 4] =
		{
			-0.75f , -0.75f , 0.0f, 
			 0.75f , -0.75f , 0.0f, 
			 0.75f ,  0.75f , 0.0f,
			-0.75f ,  0.75f , 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(VertexBuffer::Create(squareVertices , sizeof(squareVertices)));

		BufferLayout squareBufferLayout =
		{
			{ShaderDataType::FLOAT3 , "a_Position"}
		};

		//When I swap these lines like Cherno did, I am not getting any Assert exception but instead, only triangle not rendering
		squareVertexBuffer->SetLayout(squareBufferLayout);
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = {0 , 1 , 2 , 2 , 3 , 0};
		std::shared_ptr<IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(IndexBuffer::Create(squareIndices , sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		//This way you don't have to write "\n" for every line and wonder what 'R' means :)
		//'a' in a_Position represents Attribute
		//'v' in v_Position represents Varying
		std::string vertexSrc = 
		R"(
			#version 440 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position , 1.0);	
			}
		)";

		//This way you don't have to write "\n" for every line and wonder what 'R' means :)
		//'a' in a_Position represents Attribute
		std::string fragmentSrc = 
		R"(
			#version 440 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5 , 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc , fragmentSrc));

		std::string squareVertexSrc =
		R"(
			#version 440 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position , 1.0);	
			}
		)";

		//This way you don't have to write "\n" for every line and wonder what 'R' means :)
		//'a' in a_Position represents Attribute
		std::string squareFragmentSrc = 
		R"(
			#version 440 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(1.0 , 1.0 , 1.0 , 1.0);
			}
		)";

		m_SquareShader.reset(new Shader(squareVertexSrc , squareVertexSrc));
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
			glClearColor(0.0f , 0.2f , 0.2f , 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_SquareShader->Bind();
			m_SquareVertexArray->Bind();
			glDrawElements(GL_TRIANGLES , m_SquareVertexArray->GetIndexBuffer()->GetCount() , GL_UNSIGNED_INT , nullptr);

			//In OpenGL this doesn't matter as long as you bind before the draw call but in the other APIs, this must be the first step like it's here now
			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES , m_SquareVertexArray->GetIndexBuffer()->GetCount() , GL_UNSIGNED_INT , nullptr);

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