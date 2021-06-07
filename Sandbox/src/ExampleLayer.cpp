#include "ExampleLayer.h"
#include "Broccoli/Log.h"

namespace Sandbox
{
	void ExampleLayer::OnUpdate()
	{
		BRCL_TRACE("Sandbox: update");
	}

	void ExampleLayer::OnEvent(brcl::Event& event)
	{
		BRCL_TRACE("{0}", event);
	}
}