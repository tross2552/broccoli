#pragma once
#include "Broccoli/Renderer/RenderContext.h"
#include "GLFW/glfw3.h"

namespace brcl
{

	class OpenGLContext : public RenderContext
	{
	public:

		OpenGLContext(GLFWwindow* window) :
			m_Window(window) {}

		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* m_Window;

	};


}
