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
			case RendererAPI::None:
				return nullptr;
				ENGINE_CORE_ASSERT(false , "Sir Bhanu, Unable to get Current API :(");
			break;

			case RendererAPI::OpenGL:
				return new OpenGLVertexBuffer(vertices , size);
			break;
		}

		ENGINE_CORE_ASSERT(false , "Sir Bhanu, Current API Unknown :(");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices , uint32_t size)
	{
		switch(Renderer::GetCurrentAPI())
		{
			case RendererAPI::None:
				return nullptr;
				ENGINE_CORE_ASSERT(false , "Sir Bhanu, Unable to get Current API :(");
			break;

			case RendererAPI::OpenGL:
				return new OpenGLIndexBuffer(indices , size);
			break;
		}

		ENGINE_CORE_ASSERT(false , "Sir Bhanu, Current API Unknown :(");
		return nullptr;
	}
}
