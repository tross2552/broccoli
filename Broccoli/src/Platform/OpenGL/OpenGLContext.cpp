#include "brclpch.h"
#include "OpenGLContext.h"
#include "glad/glad.h"

namespace brcl
{

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}

	void OpenGLContext::SwapBuffers() { 
		glfwSwapBuffers(m_Window);
	}
}