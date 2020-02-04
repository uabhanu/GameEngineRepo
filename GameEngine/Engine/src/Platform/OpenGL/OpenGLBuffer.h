#pragma once

#include "BhanuEngine/Renderer/Buffer.h"

namespace BhanuEngine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
		private:
		    uint32_t m_RendererID;
		    
		public:
		    OpenGLVertexBuffer(float* vertices , uint32_t size);
			virtual ~OpenGLVertexBuffer();
		    
			virtual void Bind() const;
		    virtual void Unbind() const;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{

	};
}

