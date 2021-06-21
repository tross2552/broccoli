#pragma once
#include <memory>
#include "Buffer.h"

namespace brcl
{

	class VertexArray
	{
	public:

		virtual ~VertexArray() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer> GetIndexBuffer() const = 0;

		virtual VertexArray* Create();
		
	};
}
