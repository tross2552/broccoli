#include "brclpch.h"
#include "Renderer.h"

namespace brcl::renderer
{

	static SceneData* s_SceneData = new SceneData();

	void Init()
	{
		RenderCommand::Init();
	}

	void BeginScene(const Camera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void EndScene()
	{
	}

	void ResizeViewport(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const Matrix4x4& transform)
	{
		shader->Bind();
		//TODO: handle uniforms in Shader base class then remove these casts
		shader->SetUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetUniformMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	RendererAPI::API GetAPI()
	{
		return RendererAPI::GetAPI();
	}
}
