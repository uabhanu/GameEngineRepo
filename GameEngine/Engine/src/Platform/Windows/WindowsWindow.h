#pragma once

#include <Glad/glad.h>
#include <GLFW/glfw3.h>

#include "BhanuEngine/Log.h"
#include "BhanuEngine/Window.h"
#include "BhanuEngine/Renderer/GraphicsContext.h"

namespace BhanuEngine
{
	class WindowsWindow : public Window
	{
		private:
		    virtual void Init(const WindowProps& props);
			virtual void Shutdown();
		    
			GLFWwindow* m_Window; //At the moment, there is no way of accessing this which can done in one of the following ways:
			//1. Make m_Window public which is the worst way
			//2. Make WindowsInput friend of this class which is a good way
			//3. The best & most powerful way of doing this is using a public function in the API that exposes this variable.
			   //The GetNativeWindow() of Window.h does this for us
			GraphicsContext* m_GraphicsContext;
			
			struct WindowData
			{
				std::string Title;
				unsigned int Width , Height;
				bool VSync;
				EventCallbackFn EventCallback;
			};

			WindowData m_Data;

		public:
		    WindowsWindow(const WindowProps& props);
			virtual ~WindowsWindow();
			void OnUpdate() override;
			inline unsigned int GetWidth() const override { return m_Data.Width; }
			inline unsigned int GetHeight() const override { return m_Data.Height; }

			//Window Attributes
			inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
			void SetVSync(bool enabled) override;
			bool IsVSync() const override;
			inline virtual void* GetNativeWindow() const { return m_Window; }
	};
}

