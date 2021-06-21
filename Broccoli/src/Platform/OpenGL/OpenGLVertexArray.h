﻿#pragma once
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

		inline const std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const override { return m_VertexBuffers; }
		inline const std::shared_ptr<IndexBuffer> GetIndexBuffer() const override { return m_IndexBuffer; }
	
	private:

		unsigned int m_RendererID;
		
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		
	};
	
}


