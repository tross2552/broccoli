#pragma once
#include "Broccoli/Renderer/VertexArray.h"

namespace brcl
{

	class OpenGLVertexArray : public VertexArray
	{
	public:
		
		OpenGLVertexArray();
		~OpenGLVertexArray() override;
		
		void Bind() override;
		void Unbind() override;
		
		void AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(std::shared_ptr<IndexBuffer>& indexBuffer) override;

		const std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const override { return m_VertexBuffers; }
		const std::shared_ptr<IndexBuffer> GetIndexBuffer() const override { return m_IndexBuffer; }
	
	private:

		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
		
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
	
}


