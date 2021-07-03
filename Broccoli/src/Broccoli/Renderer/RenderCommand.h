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

		static void SetClearColor(const Vector4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}
		
		static void Clear()
		{
			s_RendererAPI->Clear();
		}
		
		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}
