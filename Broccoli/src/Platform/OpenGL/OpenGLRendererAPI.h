#pragma once
#include "Broccoli/Renderer/RendererAPI.h"

namespace brcl
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:

		void Init() override;
		void SetClearColor(const Vector4& color) override;
		void Clear() override;

		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = UINT32_MAX) override;
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
	};
}
