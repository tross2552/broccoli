#include "brclpch.h"
#include "Renderer.h"

namespace brcl
{

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData();
	
	void Renderer::BeginScene(const Camera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const Matrix4x4& transform)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
