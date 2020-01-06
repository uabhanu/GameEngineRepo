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
		    bool m_IsRunning = true;
			bool OnWindowClose(WindowCloseEvent& e);
			LayerStack m_LayerStack;
		    std::unique_ptr<Window> m_Window;

		public:
			BhanuEngineApp();
			virtual ~BhanuEngineApp();

			void OnEvent(Event& e);
			void PushLayer(Layer* layer);
			void PushOverlay(Layer* layer);
			void Run();
	};

	BhanuEngineApp* CreateApplication();
}

