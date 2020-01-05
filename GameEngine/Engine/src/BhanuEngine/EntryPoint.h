#pragma once
#include "EnginePCH.h"

#ifdef ENGINE_PLATFORM_WINDOWS
    
    extern BhanuEngine::BhanuEngineApp* BhanuEngine::CreateApplication();

	int main(int argc , char** argv)
	{
		BhanuEngine::Log::Init();
		ENGINE_CORE_WARN("Bhanu Engine Initialised");
		ENGINE_CLIENT_TRACE("Bhanu Engine says Hello");

		int a = 5;
		ENGINE_CLIENT_INFO("Variable a = {0} " , a); //If "Variable a = " , a used instead, it's printed as a = blank because Log is a smart pointer

		auto app = BhanuEngine::CreateApplication();
		app->Run();
		delete app;
	}
#endif

