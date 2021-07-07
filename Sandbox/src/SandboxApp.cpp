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
			Sandbox2DLayer* app = new Sandbox2DLayer();
			PushLayer(new ExampleImGuiLayer(app));
			PushLayer(app);
		}
	};

	

}

brcl::Application* brcl::CreateApplication()
{
	return new Sandbox::Sandbox();
}