#pragma once

#include "BhanuEngine/ImGUI/ImGUILayer.h"
#include "BhanuEngine/LayerStack.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Window.h"

namespace BhanuEngine
{
	class ENGINE_API BhanuEngineApp
	{
		private:
		    static BhanuEngineApp* s_Instance;
		    bool m_IsRunning = true;
			ImGUILayer* m_ImGUILayer;
			LayerStack m_LayerStack;
			std::unique_ptr<Shader> m_Shader;
			std::unique_ptr<IndexBuffer> m_IndexBuffer;
			std::unique_ptr<VertexBuffer> m_VertexBuffer;
			std::unique_ptr<Window> m_Window;
			//unsigned int m_IndexBuffer; //Delete this permanently after this chapter finishes and no errors/exceptions
			unsigned int m_VertexArray;
			//unsigned int m_VertexBuffer; //Delete this permanently after this chapter finishes and no errors/exceptions

		private:
		    bool OnWindowClose(WindowCloseEvent& e);

		public:
			BhanuEngineApp();
			virtual ~BhanuEngineApp();

			void OnEvent(Event& e);
			void PushLayer(Layer* layer);
			void PushOverlay(Layer* layer);
			void Run();
			inline static BhanuEngineApp& Get() { return *s_Instance; }
			inline Window& GetWindow() { return *m_Window; } //This is so we can access the window via ImGUILayer.cpp
	};

	BhanuEngineApp* CreateApplication();
}

