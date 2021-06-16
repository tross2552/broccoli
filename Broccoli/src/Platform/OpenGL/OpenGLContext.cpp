#include "brclpch.h"
#include "OpenGLContext.h"
#include "glad/glad.h"

namespace brcl
{

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		const int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		BRCL_CORE_ASSERT(status, "Failed to initialize Glad!");

		BRCL_CORE_INFO("Renderer: {0} {1} ", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
		BRCL_CORE_INFO("Version: {0} ", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() { 
		glfwSwapBuffers(m_Window);
	}
}