#pragma once

#include "RenderCommand.h"

namespace BhanuEngine
{
	class Renderer
	{
		public:
		    static void BeginScene();
			static void EndScene();
			static void SubmitObject(const std::shared_ptr<VertexArray>& vertexArray);

		    inline static RendererAPI::API GetCurrentAPI() { return RendererAPI::GetAPI(); }
	};
}

