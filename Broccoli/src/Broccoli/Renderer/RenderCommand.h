#pragma once

#include "RendererAPI.h"
#include "Broccoli/Math/Math.h"

namespace brcl
{
	class RenderCommand
	{
	public:

		static void Init()
		{
			s_RendererAPI->Init();
		}

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x,y,width,height);
		}

		static void SetClearColor(const Vector4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}
		
		static void Clear()
		{
			s_RendererAPI->Clear();
		}
		
		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = 0)
		{
			s_RendererAPI->DrawIndexed(vertexArray, indexCount);
		}
	private:
		static std::unique_ptr<RendererAPI> s_RendererAPI;
	};
}
