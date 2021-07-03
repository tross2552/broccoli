#include "brclpch.h"
#include "OpenGLRendererAPI.h"

#include "glad/glad.h"

namespace brcl
{
	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void OpenGLRendererAPI::SetClearColor(const Vector4& color)
	{
		glClearColor(color[0], color[1], color[2], color[3]);
	}
	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		BRCL_CORE_INFO("Draw call ({0} indices drawn)", vertexArray->GetIndexBuffer()->GetCount());
	}
	
}
