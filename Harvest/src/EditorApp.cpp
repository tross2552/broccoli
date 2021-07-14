#include <Broccoli.h>
#include "Broccoli/EntryPoint.h"
#include "EditorLayers.h"

namespace brcl
{
	
	class Editor : public Application
	{
	public:
		
		Editor() :
		Application("Harvest Editor")
		{
			EditorLayer* app = new EditorLayer();
			PushLayer(new ExampleImGuiLayer(app));
			PushLayer(app);
		}
	};

	

}

brcl::Application* brcl::CreateApplication()
{
	return new brcl::Editor();
}