﻿#pragma once

#include "RendererAPI.h"
#include "RenderCommand.h"

#include "Camera.h"
#include "Shader.h"

namespace brcl
{
	class Renderer
	{
	public:
		
		virtual ~Renderer() = default;

		static void Init();

		static void BeginScene(const Camera& camera);
		static void EndScene();
		
		static void ResizeViewport(uint32_t width, uint32_t height);

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const Matrix4x4& transform);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:

		struct SceneData
		{
			Matrix4x4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};

}
