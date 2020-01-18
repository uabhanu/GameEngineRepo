#include "BhanuEngine.h"

class BhanuTestLayer : public BhanuEngine::Layer
{
	public:
		BhanuTestLayer()
			: Layer("Bhanu's Test Layer")
		{
		}

		void OnEvent(BhanuEngine::Event& event) override
		{
			if(event.GetEventType() == BhanuEngine::EventType::KeyPressed)
			{
				BhanuEngine::KeyPressedEvent& e = (BhanuEngine::KeyPressedEvent&)event;
				ENGINE_CORE_TRACE("Key Pressed : {0}" , (char)e.GetKeyCode());

				if(BhanuEngine::Input::IsKeyPressed(ENGINE_KEY_TAB))
					ENGINE_CORE_WARN("Sir Bhanu, You pressed the Tab Key");
			}
		}

		void OnUpdate() override
		{
			if(BhanuEngine::Input::IsKeyPressed(ENGINE_KEY_TAB))
				ENGINE_CORE_INFO("Sir Bhanu, you have pressed a Tab Key :)");
		}
};

class SandboxApp : public BhanuEngine::BhanuEngineApp
{
	public:
		SandboxApp()
		{
			PushLayer(new BhanuTestLayer());
		}

		~SandboxApp()
		{

		}
};

BhanuEngine::BhanuEngineApp* BhanuEngine::CreateApplication()
{
	return new SandboxApp();
}
