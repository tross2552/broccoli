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
			PushLayer(app);
			PushOverlay(new EditorImGuiLayer(app));
		}
	};

	

}

brcl::Application* brcl::CreateApplication()
{
	return new brcl::Editor();
}