#include "EnginePCH.h"
#include "Renderer.h"

namespace BhanuEngine
{
	void Renderer::BeginScene(OrthographicCamera& orthographicCamera)
	{

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::SubmitObject(const std::shared_ptr<VertexArray>& vertexArray , const std::shared_ptr<Shader>& shader)
	{
		shader->Bind();
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}