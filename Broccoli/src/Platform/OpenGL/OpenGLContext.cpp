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
	}

	void OpenGLContext::SwapBuffers() { 
		glfwSwapBuffers(m_Window);
	}
}