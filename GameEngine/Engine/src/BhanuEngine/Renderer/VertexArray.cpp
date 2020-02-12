#include "EnginePCH.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"
#include "VertexArray.h"

namespace BhanuEngine
{
	VertexArray* VertexArray:: Create()
	{
		switch(Renderer::GetCurrentAPI())
		{
			case RendererAPI::NONE:
				ENGINE_CORE_ASSERT(false , "Sir Bhanu, Unable to get the current API :(");
				return nullptr;
			break;

			case RendererAPI::OPENGL:
				return new OpenGLVertexArray();
			break;
		}
		
		ENGINE_CORE_ASSERT(false , "Sir Bhanu, Unknown API :(");
		return nullptr;
	}
}