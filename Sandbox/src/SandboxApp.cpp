#include <Broccoli.h>
#include "ExampleLayer.h"

namespace Sandbox
{
	class Sandbox : public brcl::Application
	{
	public:
		Sandbox()
		{
			PushLayer(new ExampleLayer());
		}
	};

	
}

brcl::Application* brcl::CreateApplication()
{
	return new Sandbox::Sandbox();
}