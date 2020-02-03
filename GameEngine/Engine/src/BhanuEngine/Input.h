#pragma once

#include "BhanuEngine/Core.h"

namespace BhanuEngine
{
	class ENGINE_API Input
	{
		protected:
		    virtual bool IsKeyPressedImpl(int keycode) = 0; //Implementation of the IsKeyPressed() and this is a pure virtual function
			virtual float GetMouseXImpl() = 0;
			virtual float GetMouseYImpl() = 0;
			virtual std::pair<float , float> GetMousePositionImpl() = 0;
			virtual bool IsMouseButtonPressedImpl(int button) = 0;

		private:
		    static Input* s_Instance;

		public:
		    inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
			inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
			inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
			inline static std::pair<float , float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
			inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
	};
}
