#pragma once

#include "Core.h"

namespace BhanuEngine
{
	class ENGINE_API BhanuEngineApp
	{
		public:
			BhanuEngineApp();
			virtual ~BhanuEngineApp();

			void Run();
	};

	BhanuEngineApp* CreateApplication();
}

