#pragma once
#include "Broccoli/Renderer/Buffer.h"

namespace brcl
{
	
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer() override;
		
		void Bind() const override;
		void Unbind() const override;

	private:
		
		unsigned int m_RendererID;
		
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		~OpenGLIndexBuffer() override;
		
		void Bind() const override;
		void Unbind() const override;

	private:
		
		unsigned int m_RendererID;
		
	};
	
}
