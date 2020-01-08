#pragma once

#include "BhanuEngine/Layer.h"
#include "Platform/OpenGL/ImGUIOpenGLRenderer.h"

#include <GLFW/glfw3.h>
#include <imgui.h>

namespace BhanuEngine
{
	class ImGUILayer : public Layer
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

