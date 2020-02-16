#pragma once

#include "OrthographicCamera.h"
#include "RenderCommand.h"
#include "Shader.h"

namespace BhanuEngine
{
	class Renderer
	{
		private:
		    ;

		public:
		    static void BeginScene(OrthographicCamera& orthographicCamera);
			static void EndScene();
			static void SubmitObject(const std::shared_ptr<VertexArray>& vertexArray , const std::shared_ptr<Shader>& shader);

		    inline static RendererAPI::API GetCurrentAPI() { return RendererAPI::GetAPI(); }
	};
}

