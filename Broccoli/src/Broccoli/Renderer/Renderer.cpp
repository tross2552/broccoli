#include "brclpch.h"
#include "Renderer.h"

namespace brcl
{
	void brcl::Renderer::BeginScene()
	{
	}

	void brcl::Renderer::EndScene()
	{
	}

	void brcl::Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}