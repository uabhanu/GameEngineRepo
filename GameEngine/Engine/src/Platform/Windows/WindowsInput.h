#pragma once

#include "BhanuEngine/Input.h"

namespace BhanuEngine
{
	class WindowsInput : public Input
	{
		protected:
	        virtual bool IsKeyPressedImpl(int keycode) override; 
	};
}

