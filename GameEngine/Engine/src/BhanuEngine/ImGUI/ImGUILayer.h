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

		public:
			ImGUILayer();
			~ImGUILayer();

			virtual void OnAttach() override;
			virtual void OnDetach() override;
			//virtual void OnImGUIRender() override;
	};
}

