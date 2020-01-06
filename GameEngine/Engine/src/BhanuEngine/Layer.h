#pragma once

#include "BhanuEngine/Core.h"
#include "BhanuEngine/Events/Event.h"

namespace BhanuEngine
{
	class ENGINE_API Layer
	{
		protected:
		    std::string m_DebugName;

		public:
		    Layer(const std::string& name = "Layer");
			virtual ~Layer();

			virtual void OnAttach() {}
			virtual void OnDetach() {}
			virtual void OnEvent(Event& event) {}
			virtual void OnUpdate() {}

			inline const std::string& GetName() const { return m_DebugName; }
	};
}

