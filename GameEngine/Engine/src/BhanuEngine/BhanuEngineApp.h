#pragma once

#include "BhanuEngine/ImGUI/ImGUILayer.h"
#include "BhanuEngine/LayerStack.h"
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
			std::unique_ptr<Window> m_Window;
			unsigned int m_IndexBuffer , m_VertexArray , m_VertexBuffer;

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

