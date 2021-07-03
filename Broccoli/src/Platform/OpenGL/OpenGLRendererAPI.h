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

		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}
