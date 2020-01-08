#include "BhanuEngine.h"
#include "BhanuEngine/ImGUI/ImGUILayer.h"

class BhanuTestLayer : public BhanuEngine::Layer
{
	public:
		BhanuTestLayer()
			: Layer("Bhanu's Test Layer")
		{
		}

		void OnEvent(BhanuEngine::Event& event) override
		{
			ENGINE_CORE_TRACE("{0}" , event);
		}

		void OnUpdate() override
		{
			ENGINE_CORE_INFO("Bhanu's Test Layer Update");
		}
};

class SandboxApp : public BhanuEngine::BhanuEngineApp
{
	public:
		SandboxApp()
		{
			PushLayer(new BhanuTestLayer());
			PushOverlay(new BhanuEngine::ImGUILayer());
		}

		~SandboxApp()
		{

		}
};

BhanuEngine::BhanuEngineApp* BhanuEngine::CreateApplication()
{
	return new SandboxApp();
}
