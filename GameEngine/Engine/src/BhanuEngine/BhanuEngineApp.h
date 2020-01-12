#pragma once

#include "BhanuEngine/Events/Event.h"
#include "BhanuEngine/Events/AppEvent.h"
#include "BhanuEngine/LayerStack.h"
#include "Window.h"

namespace BhanuEngine
{
	class ENGINE_API BhanuEngineApp
	{
		private:
		    static BhanuEngineApp* s_Instance;
		    bool m_IsRunning = true;
			LayerStack m_LayerStack;
		    std::unique_ptr<Window> m_Window;

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

