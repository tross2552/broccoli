#include "brclpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

#include "OpenGLBuffer.h"

namespace brcl
{
	
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
		OpenGLVertexArray::Bind();
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

		uint32_t index = 0;
		for (auto& element : vertexBuffer->GetLayout().GetElements())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, ShaderDataTypeCount(element.Type), ShaderDataTypeToGLType(element.Type), GL_FALSE, vertexBuffer->GetLayout().GetStride(), (const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
		
	}
	
	void OpenGLVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
	
}
