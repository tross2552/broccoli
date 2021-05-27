#pragma once

#include "Core.h"
#include "Window.h"

namespace brcl
{
	class BRCL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		Window* m_Window;
	};

	//To be defined in CLIENT
	Application* CreateApplication();

}



