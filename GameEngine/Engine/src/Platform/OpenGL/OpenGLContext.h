#pragma once

#include "BhanuEngine/Renderer/GraphicsContext.h"

class GLFWwindow;

namespace BhanuEngine
{
	class OpenGLContext : public GraphicsContext
	{
		private:
		    GLFWwindow* m_WindowHandle;

		public:
		    OpenGLContext(GLFWwindow* windowHandle);
		    virtual void Init() override;
			virtual void SwapBuffers() override;
	};
}
