#pragma once

#include "BhanuEngine/Input.h"

namespace BhanuEngine
{
	class WindowsInput : public Input
	{
		protected:
		     //Whether you put virtual or not, this is virtual as it's derived from base class but it's good to put virtual
		     // as a reminder even though override keyword gives it away
		    virtual bool IsKeyPressedImpl(int keycode) override;
	};
}

