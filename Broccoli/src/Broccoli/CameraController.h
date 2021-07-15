#pragma once
#include "Broccoli/Renderer/Camera.h"
#include "Broccoli/Core/Timer.h"
#include "Broccoli/Events/ApplicationEvent.h"
#include "Broccoli/Events/MouseEvent.h"

namespace brcl
{
	class CameraController
	{
	public:
		CameraController(float aspectRatio);
		
		void OnUpdate(Timestep deltaTime);
		void OnEvent(Event& e);

		void Resize(uint32_t width, uint32_t height);
		
		Transform& GetTransform() { return m_Transform; }
		Camera& GetCamera() { return m_Camera; }
	
	private:
		
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizedEvent& e);
	
	private:
		float m_ZoomLevel = 1.0f;
		
		float m_AspectRatio;
		Camera m_Camera;
		Transform m_Transform;
		
	};
}

