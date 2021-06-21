#pragma once

#include "RendererAPI.h"
#include "RenderCommand.h"

namespace brcl
{
	class Renderer
	{
	public:
		
		virtual ~Renderer() = default;

		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};

}