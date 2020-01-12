#pragma once

//#include <imgui.h> //Uncomment this if needed

#include "BhanuEngine/BhanuEngineApp.h"
#include "BhanuEngine/Events/KeyEvent.h"
#include "BhanuEngine/Events/MouseEvent.h"
#include "BhanuEngine/Layer.h"
#include "BhanuEngine/Window.h"

namespace BhanuEngine
{
	class ENGINE_API ImGUILayer : public Layer
	{
		private:
		    float m_Time = 0.0f;

		private:
		    bool OnKeyPressedEvent(KeyPressedEvent& e);
			bool OnKeyReleasedEvent(KeyReleasedEvent& e);
			bool OnKeyTypedEvent(KeyTypedEvent& e);
		    bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
			bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
			bool OnMouseMovedEvent(MouseMovedEvent& e);
			bool OnMouseScrolledEvent(MouseScrolledEvent& e);
			bool OnWindowResizeEvent(WindowResizeEvent& e);

		public:
			ImGUILayer();
			~ImGUILayer();

			void OnAttach();
			void OnDetach();
			void OnEvent(Event& event);
			void OnUpdate();
	};
}

