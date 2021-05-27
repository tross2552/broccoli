#include "brclpch.h"
#include "WindowsWindow.h"

namespace brcl
{
	static bool s_GLFWInitialized = false;

	void WindowsWindow::OnUpdate()
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(m_Window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	void WindowsWindow::Init(const WindowProps& props)
	{

		if (!s_GLFWInitialized)
		{
			if (!glfwInit()) return;
			s_GLFWInitialized = true;
		}

		m_Title = props.Title;
		m_Height = props.Height;
		m_Width = props.Width;

		const char* title = &m_Title[0];
		
		m_Window = glfwCreateWindow(m_Width, m_Height, title, NULL, NULL);

		SetVSync(true);

		glfwMakeContextCurrent(m_Window);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		m_VSync = enabled;

		if(m_VSync)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
}