#include "brclpch.h"
#include "WindowsWindow.h"

#include "Broccoli/Events/ApplicationEvent.h"
#include "Broccoli/Events/MouseEvent.h"
#include "Broccoli/Events/KeyEvent.h"
#include "glad/glad.h"


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

	static void ErrorCallback(int error, const char* desc)
	{
		BRCL_CORE_ERROR("GLFW Error ({0}): {1}", error, desc);
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

		m_Data.Title = props.Title;
		m_Data.Height = props.Height;
		m_Data.Width = props.Width;


		//create window and set params

		const char* title = &m_Data.Title[0];
		
		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, title, NULL, NULL);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//set callbacks

		glfwSetErrorCallback(ErrorCallback);
		
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowClosedEvent event;
			data.EventCallback(event);
			BRCL_CORE_TRACE("close callback completed");

		});
		
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizedEvent event(width, height);
			data.EventCallback(event);
			
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int bitfield)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			static int repeatcount = 0;

			switch (action)
			{
			case GLFW_PRESS:
			{
				repeatcount = 0;
				KeyPressedEvent event(key, repeatcount);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				repeatcount = 0;
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				repeatcount++;
				KeyPressedEvent event(key, repeatcount);
				data.EventCallback(event);
				break;
			}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int bitfield)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double x, double y)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event(x, y);
			data.EventCallback(event);
		});
		
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)x, (float)y);
			data.EventCallback(event);
		});


		glfwMakeContextCurrent(m_Window);
		//load opengl
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

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