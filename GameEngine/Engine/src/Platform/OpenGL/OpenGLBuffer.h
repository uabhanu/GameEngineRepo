#pragma once

#include "BhanuEngine/Renderer/Buffer.h"

namespace BhanuEngine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
		private:
		    BufferLayout m_BufferLayout;
		    uint32_t m_RendererID;
		    
		public:
		    OpenGLVertexBuffer(float* vertices , uint32_t size);
			virtual ~OpenGLVertexBuffer();
		    
			virtual void Bind() const override;
		    virtual void Unbind() const override;

			virtual const BufferLayout& GetLayout() const override { return m_BufferLayout; }
			virtual void SetLayout(const BufferLayout& bufferLayout) override { m_BufferLayout = bufferLayout; }
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
		private:
		    uint32_t m_Count , m_RendererID;
		    
		public:
		    OpenGLIndexBuffer(uint32_t* indices , uint32_t count);
			virtual ~OpenGLIndexBuffer();
		    
			virtual void Bind() const override;
		    virtual void Unbind() const override;

			virtual uint32_t GetCount() const { return m_Count; }
	};
}

