#pragma once

#include "BhanuEngine/Input.h"

namespace BhanuEngine
{
	class WindowsInput : public Input
	{
		protected:
	       //No need to put virtual at the start as override keyword gives it away but it's a good reminder
		    virtual bool IsKeyPressedImpl(int keycode) override;
			virtual float GetMouseXImpl() override;
			virtual float GetMouseYImpl() override;
			virtual std::pair<float , float> GetMousePositionImpl() override;
			virtual bool IsMouseButtonPressedImpl(int button) override;
	};
}

