#pragma once

#include "RendererAPI.h"
#include "RenderCommand.h"

#include "Camera.h"
#include "Shader.h"

namespace brcl::renderer
{

	struct SceneData
	{
		Matrix4x4 ViewProjectionMatrix;
	};
	
	void Init();

	void BeginScene(const Camera& camera);
	void EndScene();
	
	void ResizeViewport(uint32_t width, uint32_t height);

	void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const Matrix4x4& transform);

	RendererAPI::API GetAPI();
}
