#include <Broccoli.h>
#include "ExampleLayer.h"
#include <Broccoli/ImGui/ImGuiLayer.h>

namespace Sandbox
{
	class Sandbox : public brcl::Application
	{
	public:
		Sandbox()
		{
			PushLayer(new ExampleLayer());
			PushLayer(new brcl::ImGuiLayer());
		}
	};

	
}

brcl::Application* brcl::CreateApplication()
{
	return new Sandbox::Sandbox();
}