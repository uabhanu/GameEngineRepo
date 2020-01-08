#pragma once

#include "BhanuEngine/BhanuEngineApp.h"
#include "BhanuEngine/Layer.h"
#include "Platform/OpenGL/ImGUIOpenGLRenderer.h"

#include <GLFW/glfw3.h>

namespace BhanuEngine
{
	class ENGINE_API ImGUILayer : public Layer
	{
		private:
		    float m_Time = 0.0f;

		public:
		    ImGUILayer();
			~ImGUILayer();

			void OnAttach();
			void OnDetach();
			void OnEvent(Event& event);
			void OnUpdate();
	};
}

