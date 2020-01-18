#pragma once

//#include <imgui.h> //Uncomment this if needed

#include "BhanuEngine/Events/AppEvent.h"
#include "BhanuEngine/Events/Event.h"
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

		public:
			ImGUILayer();
			~ImGUILayer();

			void Begin();
			void End();
			virtual void OnAttach() override;
			virtual void OnDetach() override;
			virtual void OnImGUIRender() override;
	};
}

