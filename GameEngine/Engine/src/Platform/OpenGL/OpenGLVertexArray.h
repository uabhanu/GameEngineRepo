#pragma once

#include "BhanuEngine/Renderer/VertexArray.h"

namespace BhanuEngine
{
	class OpenGLVertexArray : public VertexArray
	{
		private:
		    std::shared_ptr<IndexBuffer> m_IndexBuffer;
		    std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
			uint32_t m_RendererID;

		public:
		    OpenGLVertexArray();
		    virtual ~OpenGLVertexArray() {}
		    
			virtual void Bind() const override;
		    virtual void Unbind() const override;

			virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
			virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
	};
}

