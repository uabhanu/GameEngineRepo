#include "EnginePCH.h"
#include "Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"

namespace BhanuEngine
{
	VertexBuffer* VertexBuffer::Create(float* vertices , uint32_t size)
	{
		switch(Renderer::GetCurrentAPI())
		{
			case RendererAPI::NONE:
				return nullptr;
				ENGINE_CORE_ASSERT(false , "Sir Bhanu, Unable to get the current API :(");
			break;

			case RendererAPI::OPENGL:
				return new OpenGLVertexBuffer(vertices , size);
			break;
		}
		
		ENGINE_CORE_ASSERT(false , "Sir Bhanu, Unknown API :(");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices , uint32_t size)
	{
		return nullptr;
	}
}
