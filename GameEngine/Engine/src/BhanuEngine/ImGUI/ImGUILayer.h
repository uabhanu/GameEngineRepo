#pragma once

#include "BhanuEngine/BhanuEngineApp.h" //Cherno didn't need this include line here
#include "BhanuEngine/Events/AppEvent.h"
#include "BhanuEngine/Events/KeyEvent.h"
#include "BhanuEngine/Events/MouseEvent.h"
#include "BhanuEngine/Layer.h"

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

