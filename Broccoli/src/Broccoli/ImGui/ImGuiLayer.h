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
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;

		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event); 
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& event);
		bool OnTextInputEvent(TextInputEvent& event);

	private:
		bool m_ReleaseMouse = false;
		float m_Time = 0;
	};


}
