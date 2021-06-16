#pragma once
#include "Broccoli/Layer.h"
#include "Broccoli/Events/MouseEvent.h"
#include "Broccoli/Events/KeyEvent.h"


namespace brcl
{
	class BRCL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() override;

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;

	private:
		bool m_ReleaseMouse = false;
		float m_Time = 0;
	};


}
