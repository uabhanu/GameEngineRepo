#pragma once

#include "BhanuEngine/Core.h"

namespace BhanuEngine
{
	class ENGINE_API Input
	{
		protected:
		    virtual bool IsKeyPressedImpl(int keycode) = 0; //Implementation of the IsKeyPressed() and this is a pure virtual function

		private:
		    static Input* s_Instance;

		public:
		    static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
	};
}
