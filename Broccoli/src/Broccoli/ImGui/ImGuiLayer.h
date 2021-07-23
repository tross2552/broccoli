#pragma once
#include "Broccoli/Layer.h"


namespace brcl
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		ImGuiLayer(const std::string& name);
		~ImGuiLayer() override;

		void OnAttach() override;
		void OnDetach() override;
		
		void OnUpdate(Timestep time) final;
		virtual void OnImGuiRender();
		
		void OnEvent(Event& event) override;
	};


}
