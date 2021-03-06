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
			case RendererAPI::API::NONE:
				ENGINE_CORE_ASSERT(false , "Sir Bhanu, Unable to get the current API :(");
				return nullptr;
			break;

			case RendererAPI::API::OPENGL:
				return new OpenGLVertexBuffer(vertices , size);
			break;
		}
		
		ENGINE_CORE_ASSERT(false , "Sir Bhanu, Unknown API :(");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices , uint32_t count)
	{
		switch(Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::NONE:
				return nullptr;
				ENGINE_CORE_ASSERT(false , "Sir Bhanu, Unable to get the current API :(");
			break;

			case RendererAPI::API::OPENGL:
				return new OpenGLIndexBuffer(indices , count);
			break;
		}
		
		ENGINE_CORE_ASSERT(false , "Sir Bhanu, Unknown API :(");
		return nullptr;
	}
}
