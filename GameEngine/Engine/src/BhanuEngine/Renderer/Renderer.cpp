#include "EnginePCH.h"
#include "Renderer.h"

namespace BhanuEngine
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& orthographicCamera)
	{
		m_SceneData->ViewProjectionMatrix = orthographicCamera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::SubmitObject(const std::shared_ptr<Shader>& shader , const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjectionMatrix" , m_SceneData->ViewProjectionMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}