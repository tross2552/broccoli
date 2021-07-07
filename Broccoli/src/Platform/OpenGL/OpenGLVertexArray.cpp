#include "brclpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

#include "OpenGLBuffer.h"

namespace brcl
{
	
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_RendererID);
	}
	
	void OpenGLVertexArray::Unbind()
	{
		glBindVertexArray(0);
	}
	
	void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		BRCL_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer layout is empty!")
		
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();
		const BufferLayout& layout = vertexBuffer->GetLayout();
		
		for (auto& element : vertexBuffer->GetLayout().GetElements())
		{
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(m_VertexBufferIndex,
				ShaderDataTypeCount(element.Type),
				ShaderDataTypeToGLType(element.Type),
				GL_FALSE,
				layout.GetStride(),
				(const void*)(intptr_t)element.Offset);
			m_VertexBufferIndex++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
		m_VertexBufferIndex += layout.GetElements().size();
		
	}
	
	void OpenGLVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
	
}
