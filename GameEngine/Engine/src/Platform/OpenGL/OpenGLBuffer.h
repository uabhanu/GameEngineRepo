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
		private:
		    uint32_t m_Count , m_RendererID;
		    
		public:
		    OpenGLIndexBuffer(uint32_t* indices , uint32_t count);
			virtual ~OpenGLIndexBuffer();
		    
			virtual void Bind() const;
		    virtual void Unbind() const;

			virtual uint32_t GetCount() const { return m_Count; }
	};
}

