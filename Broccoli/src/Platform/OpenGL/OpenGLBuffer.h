#pragma once
#include "Broccoli/Renderer/Buffer.h"

#include "glad/glad.h"

namespace brcl
{

	static GLenum ShaderDataTypeToGLType(ShaderDataType type)
	{
		switch(type) {
			
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4: return GL_FLOAT;
		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4: return GL_INT;
			
		case ShaderDataType::Mat3:
		case ShaderDataType::Mat4: return GL_FLOAT;
			
		case ShaderDataType::Bool: return GL_BOOL;
		}

		BRCL_CORE_ASSERT(false, "Buffer Layout Error: Unknown ShaderDataType!");
		return 0;


	}
	
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:

		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer() override;

		const BufferLayout& GetLayout() const override;
		void SetLayout(const BufferLayout& layout) override;
		
		void Bind() const override;
		void Unbind() const override;
		void SetData(const void* data, uint32_t size) override;
	
	private:
		
		unsigned int m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:

		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		~OpenGLIndexBuffer() override;
		
		void Bind() const override;
		void Unbind() const override;

		uint32_t GetCount() const override;
	
	private:
		
		unsigned int m_RendererID;
		uint32_t m_Count;
		
	};
	
}
