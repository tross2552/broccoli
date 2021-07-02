#pragma once
#include "Broccoli/Layer.h"


namespace brcl
{
	class BRCL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		ImGuiLayer(const std::string& name);
		~ImGuiLayer() override;

		void OnAttach() final;
		void OnDetach() final;
		
		void OnUpdate(Timestep time) final;
		virtual void OnImGuiRender();
		
		void OnEvent(Event& event) override;
	};


}
