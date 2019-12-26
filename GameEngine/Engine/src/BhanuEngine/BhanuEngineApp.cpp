#include "BhanuEngineApp.h"
#include "BhanuEngine/Events/AppEvent.h"
#include "BhanuEngine/Log.h"

namespace BhanuEngine
{
	BhanuEngineApp::BhanuEngineApp()
	{

	}
		
	BhanuEngineApp::~BhanuEngineApp()
	{

	}

	void BhanuEngineApp::Run()
	{
		WindowResizeEvent e(1280 , 720);
		ENGINE_CORE_TRACE(e);
		while(true);
	}
}