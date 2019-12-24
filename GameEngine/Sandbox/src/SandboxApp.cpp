#include "BhanuEngine.h"

class SandboxApp : public BhanuEngine::BhanuEngineApp
{
	public:
		SandboxApp()
		{

		}

		~SandboxApp()
		{

		}
};

BhanuEngine::BhanuEngineApp* BhanuEngine::CreateApplication()
{
	return new SandboxApp();
}
