#pragma once

#include "EnginePCH.h"
#include "BhanuEngine/Core.h"
#include "BhanuEngine/Events/Event.h"

namespace BhanuEngine
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		//Previous Width & Height were 1280 & 720 respectively
		WindowProps(const std::string& title = "Bhanu Engine" , unsigned int width = 1280 , unsigned int height = 720)
			: Title(title) , Width(width) , Height(height)
		{
		}
	};

	//Interface representing a desktop system based window
	class ENGINE_API Window
	{
		public:
		    using EventCallbackFn = std::function<void(Event&)>;
			virtual ~Window() {}
			virtual void OnUpdate() = 0;
			virtual unsigned int GetWidth() const = 0;
			virtual unsigned int GetHeight() const = 0;

			//Window Attributes
			virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
			virtual void SetVSync(bool enabled) = 0;
			virtual bool IsVSync() const = 0;
			virtual void* GetNativeWindow() const = 0; 
			static Window* Create(const WindowProps& props = WindowProps());
	};
}
