#include "brclpch.h"
#include "OpenGLRendererAPI.h"

#include "glad/glad.h"

static void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{

	std::string prefix = (type == GL_DEBUG_TYPE_ERROR) ? "Error" : "Message";
	
	switch(severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		BRCL_CORE_ERROR("OpenGL {0}: {1}", prefix, message);
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		BRCL_CORE_WARN("OpenGL {0}: {1}", prefix, message);
		break;
	case GL_DEBUG_SEVERITY_LOW:
		BRCL_CORE_INFO("OpenGL {0}: {1}", prefix, message);
		break;
	default:
		BRCL_CORE_TRACE("OpenGL {0}: {1}", prefix, message);
	}
}

namespace brcl
{
	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, nullptr);
		
	}
	void OpenGLRendererAPI::SetClearColor(const Vector4& color)
	{
		glClearColor(color[0], color[1], color[2], color[3]);
	}
	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount)
	{
		indexCount = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
		BRCL_CORE_INFO("Draw call ({0} indices drawn)", indexCount);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport( x , y , width , height );
	}
}