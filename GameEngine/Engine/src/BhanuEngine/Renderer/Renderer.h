#pragma once

#include "OrthographicCamera.h"
#include "RenderCommand.h"
#include "Shader.h"

namespace BhanuEngine
{
	class Renderer
	{
		private:
			struct SceneData
			{
				glm::mat4 ViewProjectionMatrix;
			};

			static SceneData* m_SceneData;

		public:
		    static void BeginScene(OrthographicCamera& orthographicCamera);
			static void EndScene();
			static void SubmitObject(const std::shared_ptr<Shader>& shader , const std::shared_ptr<VertexArray>& vertexArray , const glm::mat4& transform = glm::mat4(1.0f));

		    inline static RendererAPI::API GetCurrentAPI() { return RendererAPI::GetAPI(); }
	};
}

