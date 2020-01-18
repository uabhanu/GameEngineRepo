#pragma once

#include "BhanuEngine/Core.h"
#include "Layer.h"

#include <vector>

namespace BhanuEngine
{
	class ENGINE_API LayerStack
	{
		private:
		    std::vector<Layer*> m_Layers;
			std::vector<Layer*>::iterator m_LayerInsert;

		public:
		    LayerStack();
			~LayerStack();

			void PopLayer(Layer* layer);
			void PopOverlay(Layer* overlay);
			void PushLayer(Layer* layer);
			void PushOverlay(Layer* overlay);

			std::vector<Layer*>::iterator begin() { return m_Layers.begin(); } //Phew
			std::vector<Layer*>::iterator end() { return m_Layers.end(); } //Phew
	};
}

