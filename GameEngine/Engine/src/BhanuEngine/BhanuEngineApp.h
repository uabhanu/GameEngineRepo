#pragma once

#include "Window.h"

namespace BhanuEngine
{
	class ENGINE_API BhanuEngineApp
	{
		private:
		    bool m_IsRunning = true;
		    std::unique_ptr<Window> m_Window;
		public:
			BhanuEngineApp();
			virtual ~BhanuEngineApp();

			void Run();
	};

	BhanuEngineApp* CreateApplication();
}

