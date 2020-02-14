#pragma once

#include "BhanuEngine/Renderer/RendererAPI.h"

namespace BhanuEngine
{
	class OpenGLRendererAPI : public RendererAPI
	{
		public:
		    virtual void Clear() override;
			virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
			virtual void SetClearColor(const glm::vec4& color) override;
	};
}
