#pragma once

#include <Broccoli/Math/Math.h>

#include "VertexArray.h"

namespace brcl
{

	class RendererAPI
	{
	public:

		enum class API
		{
			None = 0, OpenGL = 1
		};

	public:

		virtual void SetClearColor(const Vector4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<brcl::VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
	
}
