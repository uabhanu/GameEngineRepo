#pragma once

#include <Glad/glad.h>
#include <GLFW/glfw3.h>

#include "BhanuEngine/Log.h"
#include "BhanuEngine/Window.h"

namespace BhanuEngine
{
	class WindowsWindow : public Window
	{
		private:
		    virtual void Init(const WindowProps& props);
			virtual void Shutdown();
		    
			GLFWwindow* m_Window;
			
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
	};
}

