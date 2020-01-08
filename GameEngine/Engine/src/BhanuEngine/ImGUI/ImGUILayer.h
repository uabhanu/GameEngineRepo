#pragma once

#include "BhanuEngine/Layer.h"

namespace BhanuEngine
{
	class ImGUILayer : public Layer
	{
		private:
		    ;

		public:
		    ImGUILayer();
			~ImGUILayer();

			void OnAttach();
			void OnDetach();
			void OnEvent(Event& event);
			void OnUpdate();
	};
}

