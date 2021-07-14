#include <Broccoli.h>
#include "Broccoli/EntryPoint.h"
#include "SandboxLayers.h"

namespace Sandbox
{
	
	class Sandbox : public brcl::Application
	{
	public:
		
		Sandbox()
		{
			EditorLayer* app = new EditorLayer();
			PushLayer(new ExampleImGuiLayer(app));
			PushLayer(app);
		}
	};

	

}

brcl::Application* brcl::CreateApplication()
{
	return new Sandbox::Sandbox();
}