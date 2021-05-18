#pragma once

#include "Core.h""

namespace brcl
{
	class BRCL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in CLIENT
	Application* CreateApplication();

}



